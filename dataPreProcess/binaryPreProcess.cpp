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
        fprintf(stderr, "binary file was not opened!");
    }
    
    data.open(inFileName, std::ios::in);
    if(!data.is_open()) {
        fprintf(stderr, "input data file was not opened!");
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
            printf("%d test points written to binary file\n", pointCount +1);
        }
        
        pointCount++;
    }
    
    outBinFile.close();
}


int* readArrayFromBinary(){
    
    int* trainingData = new int[4 * BASE_SIZE];
    
    ifstream inBinFile;
    inBinFile.open(file1Binary, ios::in|ios::binary);
    
    if(!inBinFile.is_open()) {
        fprintf(stderr, "binary file was not opened!");
    }
    
    inBinFile.seekg (0, ios::beg);
    
    inBinFile.read(reinterpret_cast<char*> (trainingData), sizeof(int) * 4 * BASE_SIZE);

    inBinFile.close();
    
    return trainingData;
}
