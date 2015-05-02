//
//  averages.cpp
//  dataPreProcess
//
//  Created by Roshan Agrawal on 4/30/15.
//  Copyright (c) 2015 Roshan Agrawal. All rights reserved.
//

#include "averages.h"

int TOTAL_USERS = 458293;
int TOTAL_MOVIES = 17770;

int** createSparseMatrix(int* trainingData) {
    long BASE_SIZE = 94362233;
    std::ifstream data;
    std::string line;
    
    int **trainingDataMatrix = new int *[TOTAL_USERS];
    
    for(int i = 0; i < TOTAL_USERS; i++) {
        trainingDataMatrix[i] = new int [TOTAL_MOVIES];
    }
    
   
    for(int i = 0; i < BASE_SIZE; i++){
        
        trainingDataMatrix[trainingData[i * 4] - 1][trainingData[i * 4 + 1] - 1] = trainingData[i * 4 + 3];
        
        if((i + 1) % 10000000 == 0) {
            printf("%d test points added to sparse matrix\n", i + 1);
        }
    }
    
    return trainingDataMatrix;
}

double calculateGlobalAverage(int* trainingData){
    double BASE_SIZE = 94362233;
    double sum = 0.0;
    for(int i = 0; i < BASE_SIZE; i++){
        sum += trainingData[i * 4 + 3];
        //printf("%d\n", trainingData[i * 4 + 3]);
    }
    
    double average = sum/BASE_SIZE;
    
    printf("%f\n", average);
    
    return average;
}

void printOutUserOffest(int** trainingDataMatrix, double globalAverage){
    ofstream data;
    data.open(outUserOffsetBin, ios::out|ios::binary);
    
    if(!data.is_open()) {
        fprintf(stderr, "userOffset was not opened!");
    }
    
    double sum;
    int count;
    for(int i = 0; i < TOTAL_USERS; i++){
        sum = 0.0;
        count = 0;
        for(int j = 0; j < TOTAL_MOVIES; j++){
            int val = trainingDataMatrix[i][j];
            if(val != 0){
                sum += val;
                count++;
            }
        }
        
        double outVal = sum/count - globalAverage;
        data.write(reinterpret_cast<char*> (&outVal), sizeof(double));
    }
}

void printOutMovieAverage(int** trainingDataMatrix){
    std::ofstream data;
    
    data.open(outMovieAveragesBin, ios::out|ios::binary);
    
    if(!data.is_open()) {
        fprintf(stderr, "userOffset was not opened!");
    }
    
    
    for(int i = 0; i < TOTAL_MOVIES; i++){
        double sum = 0.0;
        int count = 0;
        for(int j = 0; j < TOTAL_USERS; j++){
            int val = trainingDataMatrix[j][i];
            if(val != 0){
                sum += val;
                count++;
            }
        }
        double outVal = sum/count;
        data.write(reinterpret_cast<char*> (&outVal), sizeof(double));
    }
}