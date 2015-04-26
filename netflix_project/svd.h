//
//  svd.h
//  netflix_project
//
//  Created by Connor Lee on 4/25/15.
//  Copyright (c) 2015 Connor Lee. All rights reserved.
//

#ifndef __netflix_project__svd__
#define __netflix_project__svd__

#include <stdio.h>
#include "dataManager.h"

const float GLOBAL_AVG_SET1 = 3.608609;
const float GLOBAL_AVG_SET2 = 3.608859;

const int TOTAL_USERS = 458293;
const int TOTAL_MOVIES = 17770;

double **user_feature_table = new double *[TOTAL_USERS];
double **movie_feature_table = new double *[TOTAL_MOVIES];


void initialize(int num_features);
void train();
double predictRating(int user, int movie); 




#endif /* defined(__netflix_project__svd__) */
