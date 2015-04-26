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


std::vector<testPoint*> fillTestPoints() {
    
    std::vector<testPoint*> trainingData;
    std::ifstream data;
    std::string line;
    
    data.open(inSampleDataFile, std::ios::in);
    int pointCount = 1;
    while(getline(data, line)) {
        
        int col = 0;
        std::istringstream lineIn(line);
        testPoint *pt = new testPoint();
        
        while(lineIn) {
            int val = 0;
            
            if(lineIn >> val) {
                
                if(col == 0) {
                    pt -> setUser(val);
                } else if(col == 1){
                    pt -> setMovie(val);
                } else if(col == 2) {
                    pt -> setDate(val);
                } else if(col == 3) {
                    pt -> setRating(val);
                }
            }
            
            col++;
        }
        
        if(pointCount % 100000 == 0) {
            printf("%d test points inputted!\n", pointCount);
        }
        pointCount++;
        
        trainingData.push_back(pt);
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




