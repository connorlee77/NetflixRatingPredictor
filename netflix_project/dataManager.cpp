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

int* fillTrainingData(){
    
    ifstream inBinFile;
    inBinFile.open(outSampleBinaryData, ios::in|ios::binary);
    
    if(!inBinFile.is_open()) {
        fprintf(stderr, "binary file was not opened!");
    }
    
    int* trainingData = new int[4 * BASE_SIZE];
    
    inBinFile.seekg (0, ios::beg);
    
    inBinFile.read(reinterpret_cast<char*> (trainingData), sizeof(int) * 4 * BASE_SIZE);
    
    inBinFile.close();
    
    return trainingData;
}

double* getMovieAverages(){
    
    ifstream inBinFile;
    inBinFile.open(movieAveragesFile, ios::in|ios::binary);
    
    if(!inBinFile.is_open()) {
        fprintf(stderr, "binary file was not opened!");
    }
    
    double* movieAverageArray = new double[TOTAL_MOVIES];
    
    inBinFile.seekg (0, ios::beg);
    
    inBinFile.read(reinterpret_cast<char*> (movieAverageArray), sizeof(double) * TOTAL_MOVIES);
    
    inBinFile.close();
    return movieAverageArray;

}

double* getUserOffsets(){
    ifstream inBinFile;
    inBinFile.open(userOffsetFile, ios::in|ios::binary);
    
    if(!inBinFile.is_open()) {
        fprintf(stderr, "binary file was not opened!");
    }
    
    double* userOffsetArray = new double[TOTAL_USERS];
    
    inBinFile.seekg (0, ios::beg);
    
    inBinFile.read(reinterpret_cast<char*> (userOffsetArray), sizeof(double) * TOTAL_USERS);
    
    inBinFile.close();
    
    return userOffsetArray;

}