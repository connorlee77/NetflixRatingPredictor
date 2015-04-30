//
//  main.cpp
//  netflix_project
//
//  Created by Connor Lee on 4/16/15.
//  Copyright (c) 2015 Connor Lee. All rights reserved.
//

#include <iostream>
#include "dataManager.h"
#include "svd.h"
#include "errorManager.h"

int main(int argc, const char * argv[]) {
    
    //Store the training data in train_data
    int* trainingData = fillTrainingData();
    
    double* movieAverages = getMovieAverages();
    double* userOffsets = getUserOffsets();
    
    //Set the length of the feature vectors
    int num_features = 15;
    int epochs = 80;
    computeSVD(0.001, num_features, trainingData, movieAverages, userOffsets, epochs);
    
    
    predictQual(num_features);

    return 0;
}
