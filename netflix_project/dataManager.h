//
//  dataManager.h
//  netflix_project
//
//  Created by Connor Lee on 4/23/15.
//  Copyright (c) 2015 Connor Lee. All rights reserved.
//

#ifndef __netflix_project__dataManager__
#define __netflix_project__dataManager__


#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// change in sample data file here!

// Roshan's paths
#define inSampleDataFile "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/file1.dta"
#define trainingDataFile "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/file1binary.bin"
#define trainingDataFullFile "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/file123.bin"
#define trainingDataWithProbe "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/file1234.bin"
#define movieAveragesFile "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/movieAverages.bin"
#define userOffsetFile "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/userOffsets.bin"
#define trainingDataFile "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/file1binary.bin"
#define probeDataFile "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/file4binary.bin"

// Connor's path
//#define inSampleDataFile "/Users/ConnorLee/Desktop/netflix/file1.dta"
//#define trainingDataFile "/Users/ConnorLee/Desktop/netflix/file1binary.bin"
//#define trainingDataFullFile "/Users/ConnorLee/Desktop/netflix/file123.bin"
//#define trainingDataWithProbe "/Users/ConnorLee/Desktop/netflix/file1234.bin"
//#define userOffsetFile "/Users/ConnorLee/Desktop/netflix/userOffsets.bin"
//#define movieAveragesFile "/Users/ConnorLee/Desktop/netflix/movieAverages.bin"
//#define probeDataFile "/Users/ConnorLee/Desktop/netflix/file4binary.bin"


int* fillData(string file, int rows, int cols);
float* getMovieAverages();
float* getUserOffsets();

#endif /* defined(__netflix_project__dataManager__) */
