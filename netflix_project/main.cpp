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

const long BASE_SIZE = 94362233;
const long PROBE_SIZE = 1374739;

int main(int argc, const char * argv[]) {
    
    
    float start, end;
    double duration;
    start = clock();
    
    //Store the training data in train_data
    int* trainingData = fillData(trainingDataFile, BASE_SIZE, 4);
    int* probeData = fillData(probeDataFile, PROBE_SIZE, 4);
    
    end = clock();
    duration=(end-start)/CLOCKS_PER_SEC;
    printf("Reading data took %f seconds\n",duration);
    
    //Set the length of the feature vectors
    int num_features = 20;
    int epochs = 40;
    computeSVD(0.008, num_features, epochs, trainingData, probeData);
    
    predictQual();

    delete [] trainingData;
    return 0;
}
