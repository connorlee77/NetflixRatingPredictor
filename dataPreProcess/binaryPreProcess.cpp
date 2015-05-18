//
//  binaryPreProcess.cpp
//  dataPreProcess
//
//  Created by Roshan Agrawal on 4/30/15.
//  Copyright (c) 2015 Roshan Agrawal. All rights reserved.
//

#include "binaryPreProcess.h"

long BASE_SIZE = 94362233;

void writeArrayToBinary(string inFileName, string outFileName){
    
    std::ifstream data;
    std::string line;
    
    ofstream outBinFile;
    outBinFile.open(outFileName, ios::out|ios::binary);
    
    if(!outBinFile.is_open()) {
        fprintf(stderr, "%s was not opened!", outFileName.c_str());
    }
    
    data.open(inFileName, std::ios::in);
    if(!data.is_open()) {
        fprintf(stderr, "%s was not opened!", inFileName.c_str());
    }
    int pointCount = 0, val = 0;
    
    while(getline(data, line)) {
        
        std::istringstream lineIn(line);
        
        while(lineIn) {
            if(lineIn >> val) {
                outBinFile.write (reinterpret_cast<char*> (&val), sizeof(int));
            }
        }
        
        if((pointCount + 1) % 1000000 == 0) {
            printf("%d test points written to %s\n", pointCount + 1, outFileName.c_str());
        }
        
        pointCount++;
    }
    
    printf("Write to %s successful!", outFileName.c_str());
    
    outBinFile.close();
}


int* readArrayFromBinary(string fileName, long rows, int cols){
    
    int* trainingData = new int[rows * cols];
    
    ifstream inBinFile;
    inBinFile.open(fileName, ios::in|ios::binary);
    
    if(!inBinFile.is_open()) {
        fprintf(stderr, "binary file was not opened!");
    }
    
    inBinFile.seekg (0, ios::beg);
    
    inBinFile.read(reinterpret_cast<char*> (trainingData), sizeof(int) * rows * cols);

    inBinFile.close();
    
    return trainingData;
}
