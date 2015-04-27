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
    
    computeSVD(0.0001, num_features, train_data);
    
    /*
    double err = getSampleError(train_data, num_features);
    printf("\nEin: %f\n", err);
    */
    
    predictQual(num_features);
    
    return 0;
}
