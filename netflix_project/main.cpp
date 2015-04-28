//
//  main.cpp
//  netflix_project
//
//  Created by Connor Lee on 4/16/15.
//  Copyright (c) 2015 Connor Lee. All rights reserved.
//

#include <iostream>
#include "svd.h"
#include "errorManager.h"

int main(int argc, const char * argv[]) {
    
    //Store the training data in train_data
    std::vector<testPoint *> train_data = fillTrainingData();
    //Set the length of the feature vectors
    int num_features = 40;
    int epochs = 40;
    computeSVD(0.001, num_features, train_data, epochs);
    printf("test: %f\n", predictRating(1, 1109, num_features));
    
    double err = getSampleError(train_data, num_features);
    printf("\nEin: %f\n", err);
    
    
    //predictQual(num_features);
    
    return 0;
}
