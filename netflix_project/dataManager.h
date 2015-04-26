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



// change in sample data file here!
#define inSampleDataFile "/Users/ConnorLee/Desktop/netflix/file1.dta"

void splitDataSet();
std::vector<testPoint*> fillTestPoints();
double getGlobalAverage(std::vector<testPoint *> ratings);



#endif /* defined(__netflix_project__dataManager__) */
