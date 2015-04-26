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
        
        // absolute value error
        if(rating < 0) {
            rating *= -1;
        }
        
        // squared error
        //rating *= rating;
        
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
    
    return sum / residuals.size();
}

double getSampleError(std::vector<testPoint *> inputData, int num_features) {
    return calcSampleError(getSquareResiduals(inputData, num_features));
}







