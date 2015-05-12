//
//  averages.h
//  dataPreProcess
//
//  Created by Roshan Agrawal on 4/30/15.
//  Copyright (c) 2015 Roshan Agrawal. All rights reserved.
//

#ifndef __dataPreProcess__averages__
#define __dataPreProcess__averages__

using namespace std;

#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

// change in sample data file here!

// Roshan's path
#define inSampleDataFile "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/file1.dta"
#define outUserOffsetBin "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/userOffsets.bin"
#define outMovieAveragesBin "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/movieAverages.bin"
#define outUserTimeAverages "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/userTimeAverages.bin"
#define userFrequencies "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/userFrequencies.bin"

// Connor's path
//#define inSampleDataFile "/Users/ConnorLee/Desktop/netflix/file1.dta"

void fillInMatrices(int* trainingData, int** userDataMatrix, int** movieDataMatrix);
float calculateGlobalAverage(int* trainingData);
float* getMovieAverages(int** trainingDataMatrix, float globalAverage);
void getUserOffsets(int** trainingDataMatrix, float globalAverage, float* movieAverages);
void getUserTimes(int* allData);
void getUserFrequencies(int* allData);
#endif /* defined(__dataPreProcess__averages__) */
