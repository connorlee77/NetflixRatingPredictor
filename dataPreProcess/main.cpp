//
//  main.cpp
//  dataPreProcess
//
//  Created by Roshan Agrawal on 4/30/15.
//  Copyright (c) 2015 Roshan Agrawal. All rights reserved.
//

#include <iostream>
#include "split_set.h"
#include "averages.h"
#include "binaryPreProcess.h"

int main(int argc, const char * argv[]) {

    //writeArrayToBinary();
    
    int* trainingData = readArrayFromBinary();
    
    int BASE_SIZE = 94362233;
    
    printf("%d %d %d %d\n", trainingData[(BASE_SIZE - 1) * 4], trainingData[(BASE_SIZE - 1) * 4 + 1], trainingData[(BASE_SIZE - 1) * 4 + 2], trainingData[(BASE_SIZE - 1) * 4 + 3]);
    
    int** sparseMatrix = createSparseMatrix(trainingData);
    
    double globalAverage = calculateGlobalAverage(trainingData);
    
    //printOutUserOffest(sparseMatrix, globalAverage);
    //printOutMovieAverage(sparseMatrix);
    
    return 0;
}
