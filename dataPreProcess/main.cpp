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
    
    long BASE_SIZE = 94362233;
    long ALL_SIZE = 102416306;
    int TOTAL_USERS = 458293;
    int TOTAL_MOVIES = 17770;
    
    start = clock();
    
    writeArrayToBinary(allFile, allFileBinary);
    writeArrayToBinary(file1, file1Binary);
    writeArrayToBinary(file4, file4Binary);
    writeArrayToBinary(file5, file5Binary);
    
    /*
    int * trainingData = new int[BASE_SIZE * 4];
    trainingData = readArrayFromBinary(file1Binary, BASE_SIZE, 4);
    
    int** userDataMatrix;
    int** movieDataMatrix;
    
    userDataMatrix = new int*[TOTAL_USERS];
    for(int i = 0; i < TOTAL_USERS; i++){
        userDataMatrix[i] = new int[TOTAL_MOVIES];
    }
    
    movieDataMatrix = new int*[TOTAL_MOVIES];
    for(int i = 0; i < TOTAL_MOVIES; i++){
        movieDataMatrix[i] = new int[TOTAL_USERS];
    }
    
    fillInMatrices(trainingData, userDataMatrix, movieDataMatrix);
    
    float globalAverage = calculateGlobalAverage(trainingData);
    
    delete [] trainingData;
    
    float * movieAverages = getMovieAverages(movieDataMatrix, globalAverage);
    
    for(int i = 0; i < TOTAL_MOVIES; i++){
        delete [] movieDataMatrix[i];
    }
    
    delete [] movieDataMatrix;
    
    getUserOffsets(userDataMatrix, globalAverage, movieAverages);
    
    for(int i = 0; i < TOTAL_USERS; i++){
        delete [] userDataMatrix[i];
    }
    
    delete [] userDataMatrix;
    */
    
    int * allData = new int[ALL_SIZE * 4];
    allData = readArrayFromBinary(allFileBinary, ALL_SIZE, 4);
    
    getUserTimes(allData);
    getUserFrequencies(allData);
    
    delete [] allData;
    
    end = clock();
    
    duration=(end-start)/CLOCKS_PER_SEC;
    printf("Preprocessing data took %f seconds\n",duration);
    
    
    return 0;
}
