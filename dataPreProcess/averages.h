//
//  averages.h
//  dataPreProcess
//
//  Created by Roshan Agrawal on 4/30/15.
//  Copyright (c) 2015 Roshan Agrawal. All rights reserved.
//

#ifndef __dataPreProcess__averages__
#define __dataPreProcess__averages__

#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

// change in sample data file here!

// Roshan's path
#define inSampleDataFile "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/file1.dta"
#define outUserSampleDataFile "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/userOffsets.dta"
#define outMovieSampleDataFile "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/movieAverages.dta"

// Connor's path
//#define inSampleDataFile "/Users/ConnorLee/Desktop/netflix/file1.dta"

int** createSparseMatrix();
double calculateGlobalAverage(int** trainingDataMatrix);
void printOutUserOffest(int** trainingDataMatrix, double globalAverage);
void printOutMovieAverage(int** trainingDataMatrix, double globalAverage);

#endif /* defined(__dataPreProcess__averages__) */
