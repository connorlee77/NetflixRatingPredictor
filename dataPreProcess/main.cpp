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

    float start, end;
    double duration;
    
    /*
    start = clock();
    writeArrayToBinary(file5, file5Binary);
    
    end = clock();
    duration=(end-start)/CLOCKS_PER_SEC;
    
    
    printf("Converting data to binary took %f seconds\n",duration);
     */
    
    start = clock();
    
    int* trainingData = readArrayFromBinary();

    end = clock();
    duration=(end-start)/CLOCKS_PER_SEC;
    
    printf("Reading data took %f seconds\n",duration);
    
    /*
    start = clock();
    
    float globalAverage = calculateGlobalAverage(trainingData);
    
    end = clock();
    duration=(end-start)/CLOCKS_PER_SEC;
    printf("Calculating global average took %f seconds\n",duration);
    
    */
    
    float globalAverage = 3.608609;
    
    start = clock();
    int** userSparseMatrix = createUserSparseMatrix(trainingData);
    int** movieSparseMatrix = createMovieSparseMatrix(trainingData);
    
    end = clock();
    duration=(end-start)/CLOCKS_PER_SEC;
    
    printf("Storing data in sparse matrices took %f seconds\n",duration);

    start = clock();
    float * movieAverages = getMovieAverages(movieSparseMatrix, globalAverage);
    end = clock();
    duration=(end-start)/CLOCKS_PER_SEC;
    printf("Getting Movie Averages took %f seconds\n",duration);
    
    start = clock();

    getUserOffsets(userSparseMatrix, globalAverage, movieAverages);
    
    end = clock();
    duration=(end-start)/CLOCKS_PER_SEC;
    printf("Getting User Offsets took %f seconds\n",duration);
    
    return 0;
}
