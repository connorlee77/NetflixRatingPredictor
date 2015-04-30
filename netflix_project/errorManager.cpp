//
//  errorManager.cpp
//  netflix_project
//
//  Created by Connor Lee on 4/26/15.
//  Copyright (c) 2015 Connor Lee. All rights reserved.
//

#include "errorManager.h"



std::vector<double> predictSet(std::vector<testPoint *> inputData, int num_features) {
    
    std::vector<double> predictions;
    int user, movie;
    for(int i = 0; i < inputData.size(); i++) {
        user = inputData[i] -> getUser();
        movie = inputData[i] -> getMovie();
        double rating = predictRating(user, movie, num_features);
        predictions.push_back(rating);
    }
    return predictions;
}

std::vector<double> getSquareResiduals(std::vector<testPoint *> inputData, int num_features) {
    
    std::vector<double> residuals;
    int user, movie, rating;
    double predicted_rating;
    for(int i = 0; i < inputData.size(); i++) {
        
        user = inputData[i] -> getUser();
        movie = inputData[i] -> getMovie();
        rating = inputData[i] -> getRating();
        
        predicted_rating = predictRating(user, movie, num_features);
        
        rating = rating - predicted_rating;
        
        // squared error
        rating = pow(rating, 2);
        assert(rating >= 0.0);
        assert(isfinite(rating));
        residuals.push_back(rating);
    }
    return residuals;
}


double calcSampleError(std::vector<double> residuals) {
    
    assert(residuals.size() != 0);
    
    double sum = 0.0;
    
    for(int i = 0; i < residuals.size(); i++) {
        sum += residuals[i];
    }
    
    return sqrt(sum / residuals.size());
}

double getSampleError(std::vector<testPoint *> inputData, int num_features) {
    return calcSampleError(getSquareResiduals(inputData, num_features));
}

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
            printf("%d testing points evaluated!\n", pointCount);
        }
        pointCount++;
        
        double predictedRating = predictRating(pt->getUser(), pt->getMovie(), num_features);
        qualOut << predictedRating << "\n";
    }
    qualOut.close();
}
