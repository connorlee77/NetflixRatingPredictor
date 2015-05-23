//
//  errorManager.cpp
//  netflix_project
//
//  Created by Connor Lee on 4/26/15.
//  Copyright (c) 2015 Connor Lee. All rights reserved.
//

#include "errorManager.h"

void predictQual(){
    
    long QUAL_SIZE = 2749898;
    
    ifstream inBinFile;
    inBinFile.open(qualInFile, ios::in|ios::binary);
    
    if(!inBinFile.is_open()) {
        fprintf(stderr, "binary file was not opened!");
    }
    
    int* qualData = new int[4 * QUAL_SIZE];
    
    inBinFile.seekg (0, ios::beg);
    
    inBinFile.read(reinterpret_cast<char*> (qualData), sizeof(int) * 4 * QUAL_SIZE);
    
    inBinFile.close();

    
    std::ofstream qualOut;
   
    remove(qualOutFile);
    qualOut.open(qualOutFile, std::ios::app);
    
    //Connor's file path
    //qualOut.open("/Users/ConnorLee/Desktop/netflix/qualOut.dta", std::ios::app);
    
    if(!qualOut.is_open()) {
        fprintf(stderr, "qualOut was not opened!");
    }
    
    for(int i = 0; i < QUAL_SIZE; i++){    
        float predictedRating = predictRating(qualData[i * 4], qualData[i * 4 + 1], qualData[i * 4 + 2]);
        
        if(predictedRating < 1)
            predictedRating = 1;
        else if (predictedRating > 5)
            predictedRating = 5;
        
        qualOut << predictedRating << "\n";
        
        if((i + 1) % 100000 == 0) {
            printf("%d qual points evaulated!\n", i + 1);
        }
    }

    qualOut.close();
    delete [] qualData;
}

void predictQualPlus(){
    
    long QUAL_SIZE = 2749898;
    
    ifstream inBinFile;
    inBinFile.open(qualInFile, ios::in|ios::binary);
    
    if(!inBinFile.is_open()) {
        fprintf(stderr, "binary file was not opened!");
    }
    
    int* qualData = new int[4 * QUAL_SIZE];
    
    inBinFile.seekg (0, ios::beg);
    
    inBinFile.read(reinterpret_cast<char*> (qualData), sizeof(int) * 4 * QUAL_SIZE);
    
    inBinFile.close();
    
    
    std::ofstream qualOut;
    
    remove(qualOutFile);
    qualOut.open(qualOutFile, std::ios::app);
    
    //Connor's file path
    //qualOut.open("/Users/ConnorLee/Desktop/netflix/qualOut.dta", std::ios::app);
    
    if(!qualOut.is_open()) {
        fprintf(stderr, "qualOut was not opened!");
    }
    
    for(int i = 0; i < QUAL_SIZE; i++){
        float predictedRating = predictRatingPLUS(qualData[i * 4], qualData[i * 4 + 1]);
        
        if(predictedRating < 1)
            predictedRating = 1;
        else if (predictedRating > 5)
            predictedRating = 5;
        
        qualOut << predictedRating << "\n";
        
        if((i + 1) % 100000 == 0) {
            printf("%d qual points evaulated!\n", i + 1);
        }
    }
    
    qualOut.close();
    delete [] qualData;
}
