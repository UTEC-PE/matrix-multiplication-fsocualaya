#include <iostream>
#include <stdio.h>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

#define NUM_THREADS 3

mutex mtx;

void printMatrix(vector<vector<int>> matrix);
vector<vector<int>> randomizeMatrix();
void threadMultiply(vector<vector<int>>* mult, vector<vector<int>> m1,vector<vector<int>> m2,int i);

int main(){
    srand(time(nullptr));
    cout << "===========================================================" << endl;
    cout << "\tMatrix Multiplication" << endl;
    cout << "===========================================================" << endl << endl;
    
    thread threads[NUM_THREADS];

    vector<vector<int>> ma = randomizeMatrix(), mb = randomizeMatrix(),mc(NUM_THREADS,vector<int>(NUM_THREADS));
    cout<<"Matrix A:"<<endl;
    printMatrix(ma);
    cout<<"Matrix B:"<<endl;
    printMatrix(mb);

    // multiply with threads
    for(int i=0;i<NUM_THREADS;i++){
        threads[i] = thread(threadMultiply, &mc,ma,mb,i);
    }

    // join threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads[i].join();
    }

    cout<<"Matrix C (product):"<<endl;
    printMatrix(mc);    

    return EXIT_SUCCESS;
}

void threadMultiply(vector<vector<int>>* mult, vector<vector<int>> m1,vector<vector<int>> m2,int i){
    mtx.lock();
    for(int j = 0;j<NUM_THREADS;j++)
        for(int k = 0;k<NUM_THREADS;k++)
            (*mult)[i][j] += m1[i][k] * m2[k][j];

    mtx.unlock();
}

void printMatrix(vector<vector<int>> matrix){
    for(int i=0; i<NUM_THREADS; i++){
        for(int j=0; j<NUM_THREADS; j++){
            cout<<matrix[i][j]<<"\t";
        }
        cout<<endl;
    }
}

vector<vector<int>> randomizeMatrix(){
    vector<vector<int>> randomVector(NUM_THREADS, vector<int>(NUM_THREADS));
    for(int i=0;i<NUM_THREADS;i++){
        for(int j=0;j<NUM_THREADS;j++){
            randomVector[i][j] = rand() % 10;
       }
    }
    return randomVector;
}