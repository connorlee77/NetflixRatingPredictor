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
#include <time.h>


int main(int argc, const char * argv[]) {

    //writeArrayToBinary();
    
    float start, end;
    double duration;
    start = clock();
    
    int* trainingData = readArrayFromBinary();

    end = clock();
    duration=(end-start)/CLOCKS_PER_SEC;
    
    printf("Reading data took %f seconds\n",duration);
    
    start = clock();
    
    float globalAverage = calculateGlobalAverage(trainingData);
    
    end = clock();
    duration=(end-start)/CLOCKS_PER_SEC;
    printf("Calculating global average took %f seconds\n",duration);
    
    start = clock();
    int** sparseMatrix = createSparseMatrix(trainingData);
    
    end = clock();
    duration=(end-start)/CLOCKS_PER_SEC;
    
    printf("Storing data in sparse matrix took %f seconds\n",duration);

    start = clock();

    printOutUserOffset(sparseMatrix, globalAverage);
    
    end = clock();
    duration=(end-start)/CLOCKS_PER_SEC;
    printf("Printing User Offsets took %f seconds\n",duration);
    
    start = clock();
    printOutMovieAverage(sparseMatrix);
    end = clock();
    duration=(end-start)/CLOCKS_PER_SEC;
    printf("Printing Movie Averages took %f seconds\n",duration);

    
    return 0;
}
