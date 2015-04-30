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

int** createSparseMatrix() {
    std::ifstream data;
    std::string line;
    
    long BASE_SIZE = 94362233;
    
    int **trainingDataMatrix = new int *[TOTAL_USERS];
    
    for(int i = 0; i < TOTAL_USERS; i++) {
        trainingDataMatrix[i] = new int [TOTAL_MOVIES];
    }
    
    data.open(inSampleDataFile, std::ios::in);
    int pointCount = 0, col = 0, val = 0;
    
    while(getline(data, line) && pointCount < BASE_SIZE) {
        
        std::istringstream lineIn(line);
        
        int user = 0, movie = 0, rating = 0;
        
        while(lineIn) {
            int val = 0;
            
            if(lineIn >> val) {
                
                if(col == 0) {
                    user = val;
                }
                else if(col == 1){
                    movie = val;
                }
                else if(col == 3){
                    rating = val;
                }
                
            }
            col++;
        }
        
        trainingDataMatrix[user - 1][movie  - 1] = rating;
        
        if((pointCount + 1) % 100000 == 0) {
            printf("%d test points inputted!\n", pointCount);
        }
        
        
        col = 0;
        pointCount++;
    }
    
    return trainingDataMatrix;
}

double calculateGlobalAverage(int** trainingDataMatrix){
    double sum = 0.0;
    double count = 0.0;
    for(int i = 0; i < TOTAL_USERS; i++){
        for(int j = 0; j < TOTAL_MOVIES; j++){
            int val = trainingDataMatrix[i][j];
            if(val != 0){
                sum += val;
                count++;
            }
        }
    }
    
    return sum/count;
}

void printOutUserOffest(int** trainingDataMatrix, double globalAverage){
    std::ofstream data;

    data.open(outUserSampleDataFile, std::ios::app);
    
    if(!data.is_open()) {
        fprintf(stderr, "userOffset was not opened!");
    }
    
    
    for(int i = 0; i < TOTAL_USERS; i++){
        double sum = 0.0;
        int count = 0;
        for(int j = 0; j < TOTAL_MOVIES; j++){
            int val = trainingDataMatrix[i][j];
            if(val != 0){
                sum += val;
                count++;
            }
        }
        data << (sum/count - globalAverage) << "\n";
    }
}

void printOutMovieAverage(int** trainingDataMatrix, double globalAverage){
    std::ofstream data;
    
    data.open(outMovieSampleDataFile, std::ios::app);
    
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
        data << (sum/count) << "\n";
    }
}