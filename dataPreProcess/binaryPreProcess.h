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

// change in sample data file here!

// Roshan's path
#define inSampleDataFile "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/file1.dta"
#define outSampleBinaryData "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/file1binary.bin"

// Connor's path
//#define inSampleDataFile "/Users/ConnorLee/Desktop/netflix/file1.dta"

void writeArrayToBinary();
int* readArrayFromBinary();
#endif /* defined(__dataPreProcess__binaryPreProcess__) */
