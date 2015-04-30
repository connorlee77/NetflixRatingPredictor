//
//  errorManager.cpp
//  netflix_project
//
//  Created by Connor Lee on 4/26/15.
//  Copyright (c) 2015 Connor Lee. All rights reserved.
//

#include "errorManager.h"

void predictQual(int num_features){
    
    std::ifstream data;
    std::string line;
    
    std::ofstream qualOut;
    
    //Roshan's file path
   
    //qualOut.open("/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/qualOut.dta", std::ios::app);
    
    //Connor's file path
    qualOut.open("/Users/ConnorLee/Desktop/netflix/qualOut.dta", std::ios::app);
    
    if(!qualOut.is_open()) {
        fprintf(stderr, "qualOut was not opened!");
    }
    
    data.open(qualDataFile, std::ios::in);
    int pointCount = 1;
    while(getline(data, line)) {
        
        int col = 0;
        std::istringstream lineIn(line);
        
        int user = 0, movie = 0;
        
        while(lineIn) {
            int val = 0;
            
            if(lineIn >> val) {
                
                if(col == 0) {
                    user = val;
                }
                else if(col == 1){
                    movie = val;
                }
            
            }
            col++;
        }
        
        if(pointCount % 100000 == 0) {
            printf("%d testing points evaluated!\n", pointCount);
        }
        pointCount++;
        
        double predictedRating = predictRating(user, movie);
        if(predictedRating < 1)
            predictedRating = 1;
        else if (predictedRating > 5)
            predictedRating = 5;
        qualOut << predictedRating << "\n";
    }
    qualOut.close();
}
