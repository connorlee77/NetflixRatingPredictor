//
//  dataManager.cpp
//  netflix_project
//
//  Created by Connor Lee on 4/23/15.
//  Copyright (c) 2015 Connor Lee. All rights reserved.
//

#include "dataManager.h"

long BASE_SIZE = 94362233;
const int TOTAL_USERS = 458293;
const int TOTAL_MOVIES = 17770;

int* fillTrainingData() {
    std::ifstream data;
    std::string line;

    int* trainingData = new int[4 * BASE_SIZE];
    
    data.open(inSampleDataFile, std::ios::in);
    int pointCount = 0, col = 0, val = 0;
    
    while(getline(data, line) && pointCount < BASE_SIZE) {
        
        std::istringstream lineIn(line);

        while(lineIn) {
            if(lineIn >> val) {
                trainingData[4 * pointCount + col] = val;
            }
            col++;
        }
        
        if((pointCount + 1) % 1000000 == 0) {
            printf("%d test points inputted!\n", pointCount);
        }
        
        col = 0;
        pointCount++;
    }
    
    return trainingData;
}

double* getMovieAverages(){
    std::ifstream data;
    std::string line;
    
    double* movieAverageArray = new double[TOTAL_MOVIES];
    
    data.open(movieAveragesFile, std::ios::in);
    int pointCount = 0;
    double val = 0;
    
    while(getline(data, line)) {
        
        std::istringstream lineIn(line);
        
        while(lineIn) {
            if(lineIn >> val) {
                movieAverageArray[pointCount] = val;
            }
        }
        
        if((pointCount + 1) % 100000 == 0) {
            printf("%d movies inputted!\n", pointCount);
        }
        
        pointCount++;
    }
    
    return movieAverageArray;

}

double* getUserOffsets(){
    std::ifstream data;
    std::string line;
    
    double* userOffsetArray = new double[TOTAL_USERS];
    
    data.open(userOffsetFile, std::ios::in);
    int pointCount = 0;
    double val = 0;
    
    while(getline(data, line)) {
        
        std::istringstream lineIn(line);
        
        while(lineIn) {
            if(lineIn >> val) {
                userOffsetArray[pointCount] = val;
            }
        }
        
        if((pointCount + 1) % 100000 == 0) {
            printf("%d users inputted!\n", pointCount);
        }
        
        pointCount++;
    }
    
    return userOffsetArray;

}