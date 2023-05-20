//
//  main.cpp
//  ReadKnapsack
//
//  Created by Eduardo Pecora on 2019-06-30.
//  Copyright © 2019 UFPR. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <time.h>

using namespace std;

bool feasible(float *sol, float **A, float * b, int row, int col)
{
    bool f = true;
    
    for(int j =0; j< row; j++){
        float sum = 0;
        for(int i =0; i< col; i++)
            sum += sol[i]*A[j][i];
        
        if(sum > b[j]){
            f = false;
            break;
            
        }
    }
    return f;
}

int main(int argc, const char * argv[]) {
    
    srand (time(NULL));
    ifstream inFile;
    
    inFile.open("Knap_C500I500.dat");
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    
    int cols = 0;
    int rows =0;
    
    //read the dimensions
    inFile >> rows;
    inFile >> cols;
    cout << "(" << cols << " , " <<  rows << ")" << endl;
    
    // Read the cost Array
    
    float *c;
    c = new float[cols];
    
    for(int i =0; i< cols; i++){
        inFile >> c[i];
        cout << c[i] << endl;
    }
    
    //Read the A Matrix
   // float A[rows][cols];
    
    
    float ** A;
    A = new float *[rows];
    for(int i = 0; i <rows; i++)
        A[i] = new float[cols];
    
    for(int j =0; j< rows; j++){
       for(int i =0; i< cols; i++) {
        inFile >> A[j][i];
        cout << A[j][i] << " , ";
       }
        cout << endl;
    }
    
    //read the b (RHS) array
    float *b;
    b = new float[rows];
    
    
    for(int j =0; j< rows; j++){
        inFile >> b[j];
        cout << b[j] << " , ";
    }
    cout << endl;
    
    inFile.close();
    
    float bestScore = 0;
    int count =0;
    for(int k =0; k <=1000000; k++){
        
        if (count >=10000){
            cout << "Ainda estou vivo " << k <<endl;
            count = 0;
        }
        count ++;
        
        float *sol;
        sol = new float[cols];
        
        for(int i =0; i< cols; i++) {
            float r = float(rand())/RAND_MAX;
            if(r <= 0.5)
                sol[i] = 1;
            else
                sol[i]=0;
        }
        
       
        if(feasible(sol, A, b, rows, cols)){
            float score = 0;
            
            for(int i =0; i< cols; i++)
                score += sol[i]*c[i];
            
            if(score > bestScore){
                for(int i =0; i< cols; i++)
                    cout << sol[i] << " , ";
                cout << "  SCORE = " << score << endl;
                bestScore = score;
            }
        }
            delete[] sol;
    }
    
    delete[] b;

    delete[] c;
    delete[] A;
    
    return 0;
}
