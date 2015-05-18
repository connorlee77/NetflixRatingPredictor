//
//  binaryPreProcess.h
//  dataPreProcess
//
//  Created by Roshan Agrawal on 4/30/15.
//  Copyright (c) 2015 Roshan Agrawal. All rights reserved.
//

#ifndef __dataPreProcess__binaryPreProcess__
#define __dataPreProcess__binaryPreProcess__

#include <stdio.h>

#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// change in sample data file here!

// Roshan's paths
#define file1 "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/file1.dta"
#define file4 "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/file4.dta"
#define file5 "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/file5.dta"
#define allFile "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/all.dta"
#define file1Binary "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/file1binary.bin"
#define file5Binary "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/file5binary.bin"
#define file4Binary "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/file4binary.bin"
#define allFileBinary "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/allBinary.bin"

// Connor's path
//#define inSampleDataFile "/Users/ConnorLee/Desktop/netflix/file1.dta"

void writeArrayToBinary(string inFileName, string outFileName);
int* readArrayFromBinary(string fileName, long rows, int cols);
#endif /* defined(__dataPreProcess__binaryPreProcess__) */
