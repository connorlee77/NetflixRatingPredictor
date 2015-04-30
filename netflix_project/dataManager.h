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

#include "split_set.h"
#include "testpoints.h"

#include <vector>
#include <cmath>


// change in sample data file here!

// Roshan's path
//#define inSampleDataFile "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/file1.dta"

// Connor's path
#define inSampleDataFile "/Users/ConnorLee/Desktop/netflix/file1.dta"


void splitDataSet();
std::vector<testPoint*> fillTrainingData();
double getGlobalAverage(std::vector<testPoint *> ratings);
void roundAll(std::string qual_filePath, std::string qual_out);

#endif /* defined(__netflix_project__dataManager__) */
