//
//  svd++.h
//  netflix_project
//
//  Created by Connor Lee on 5/22/15.
//  Copyright (c) 2015 Connor Lee. All rights reserved.
//

#ifndef __netflix_project__svd____
#define __netflix_project__svd____

#include <stdio.h>
#include <stdio.h>
#include <assert.h>
#include <cmath>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <iostream>
#include "dataManager.h"
#include <vector>

extern float *userBias;
extern float *movieBias;
extern float **userFeatures;
extern float **movieFeatures;
extern float **sumY;
extern float **Y;
extern float *norms;
extern int *movieCountByUser;

float sign();
void initialize(std::string file, int rows);
float predictRatingPLUS(int user, int movie);
void computeSVDPlusPlus(int num_features, int epochs, int* train_data, int* probe_data, long size);

#endif /* defined(__netflix_project__svd____) */
