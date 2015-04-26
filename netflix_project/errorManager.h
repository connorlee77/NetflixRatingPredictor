//
//  errorManager.h
//  netflix_project
//
//  Created by Connor Lee on 4/26/15.
//  Copyright (c) 2015 Connor Lee. All rights reserved.
//

#ifndef __netflix_project__errorManager__
#define __netflix_project__errorManager__

#include <stdio.h>
#include <vector>
#include "testpoints.h"
#include "svd.h"
#include <math.h>

std::vector<double> predictSet(std::vector<testPoint *> inputData, int num_features);
std::vector<double> getSquareResiduals(std::vector<testPoint *> inputData, int num_features);

double calcSampleError(std::vector<double> residuals);
double getSampleError(std::vector<testPoint *> inputData, int num_features);

#endif /* defined(__netflix_project__errorManager__) */
