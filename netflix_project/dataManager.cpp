//
//  dataManager.cpp
//  netflix_project
//
//  Created by Connor Lee on 4/23/15.
//  Copyright (c) 2015 Connor Lee. All rights reserved.
//

#include "dataManager.h"


void splitDataSet() {
    split_set obj = split_set("um/all.idx", "um/all.dta");
    obj.parse_guide_data_set();
    printf("%s", "done");
}


int* fillTrainingData() {
    std::ifstream data;
    std::string line;
    
    long BASE_SIZE = 94362233;
    int* trainingData = new int[4 * BASE_SIZE];
    
    data.open(inSampleDataFile, std::ios::in);
    int pointCount = 0, col = 0, val = 0;
    
    while(getline(data, line)) {
        
        std::istringstream lineIn(line);

        while(lineIn) {
            if(lineIn >> val) {
                trainingData[4 * pointCount + col] = val;
            }
            col++;
        }
        
        if((pointCount + 1) % 100000 == 0) {
            printf("%d test points inputted!\n", pointCount);
        }
        
        col = 0;
        pointCount++;
    }
    
    return trainingData;
}


double getGlobalAverage(std::vector<testPoint *> ratings) {
    
    double g_avg = 0.0;
    
    for(int i = 0; i < ratings.size(); i++) {
        g_avg += (double) ratings[i] -> getRating();
    }
    
    return g_avg / ratings.size();
}


void roundAll(std::string qual_filePath, std::string qual_out) {
    std::ifstream data;
    std::string line;
    
    std::ofstream roundOut;
    double rounded;
    
    //Connor's file path
    roundOut.open(qual_filePath, std::ios::app);
    
    if(!roundOut.is_open()) {
        fprintf(stderr, "qualOut was not opened!");
    }
    
    data.open(qual_out, std::ios::in);
    while(getline(data, line)) {
        
        std::istringstream lineIn(line);
        
        while(lineIn) {
            double val = 0;
            if(lineIn >> val) {
                rounded = std::round(val);
                roundOut << rounded << "\n";
            }
        }
        
        
    }
    roundOut.close();
}