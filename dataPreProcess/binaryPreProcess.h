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

#define file123 "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/file123.dta"
#define file1234 "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/file1234.dta"
#define file123Binary "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/file123.bin"
#define file1234Binary "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/file1234.bin"

// Connor's path
//#define file1 "/Users/ConnorLee/Desktop/netflix/file1.dta"
//#define file4 "/Users/ConnorLee/Desktop/netflix/file4.dta"
//#define file5 "/Users/ConnorLee/Desktop/netflix/file5.dta"
//#define allFile "/Users/ConnorLee/Desktop/netflix/all.dta"
//#define file1Binary "/Users/ConnorLee/Desktop/netflix/file1binary.bin"
//#define file5Binary "/Users/ConnorLee/Desktop/netflix/file5binary.bin"
//#define file4Binary "/Users/ConnorLee/Desktop/netflix/file4binary.bin"
//#define allFileBinary "/Users/ConnorLee/Desktop/netflix/allBinary.bin"

//#define file123 "/Users/ConnorLee/Desktop/netflix/file123.dta"
//#define file1234 "/Users/ConnorLee/Desktop/netflix/file1234.dta"
//#define file123Binary "/Users/ConnorLee/Desktop/netflix/file123.bin"
//#define file1234Binary "/Users/ConnorLee/Desktop/netflix/file1234.bin"

void writeArrayToBinary(string inFileName, string outFileName);
int* readArrayFromBinary(string fileName, long rows, int cols);
#endif /* defined(__dataPreProcess__binaryPreProcess__) */
