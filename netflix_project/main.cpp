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
#include <time.h>

int main(int argc, const char * argv[]) {
    
    
    float start, end;
    double duration;
    start = clock();
    
    //Store the training data in train_data
    int* trainingData = fillTrainingData();
    
    end = clock();
    duration=(end-start)/CLOCKS_PER_SEC;
    printf("Reading data took %f seconds\n",duration);
    
    //Set the length of the feature vectors
    int num_features = 15;
    int epochs = 1;
    computeSVD(0.001, num_features, trainingData, epochs);
    
    predictQual();

    return 0;
}
