//
//  dataManager.cpp
//  netflix_project
//
//  Created by Connor Lee on 4/23/15.
//  Copyright (c) 2015 Connor Lee. All rights reserved.
//

#include "dataManager.h"
const int TOTAL_USERS = 458293;
const int TOTAL_MOVIES = 17770;

int* fillData(string file, int rows, int cols){
    
    ifstream inBinFile;
    inBinFile.open(file, ios::in|ios::binary);
    
    if(!inBinFile.is_open()) {
        fprintf(stderr, "binary file was not opened!");
        exit(0);
    }
    
    int* dataArray = new int[rows * cols];
    
    inBinFile.seekg (0, ios::beg);
    
    inBinFile.read(reinterpret_cast<char*> (dataArray), sizeof(int) * rows * cols);
    
    inBinFile.close();
    
    return dataArray;
}

float* getMovieAverages(){
    
    ifstream inBinFile;
    inBinFile.open(movieAveragesFile, ios::in|ios::binary);
    
    if(!inBinFile.is_open()) {
        fprintf(stderr, "binary file was not opened!");
    }
    
    float* movieAverageArray = new float[TOTAL_MOVIES];
    
    inBinFile.seekg (0, ios::beg);
    
    inBinFile.read(reinterpret_cast<char*> (movieAverageArray), sizeof(float) * TOTAL_MOVIES);
    
    inBinFile.close();
    return movieAverageArray;

}

float* getUserOffsets(){
    ifstream inBinFile;
    inBinFile.open(userOffsetFile, ios::in|ios::binary);
    
    if(!inBinFile.is_open()) {
        fprintf(stderr, "binary file was not opened!");
    }
    
    float* userOffsetArray = new float[TOTAL_USERS];
    
    inBinFile.seekg (0, ios::beg);
    
    inBinFile.read(reinterpret_cast<char*> (userOffsetArray), sizeof(float) * TOTAL_USERS);
    
    inBinFile.close();
    
    return userOffsetArray;

}