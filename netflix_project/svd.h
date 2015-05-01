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
#include <assert.h>
#include <math.h>

extern const float GLOBAL_AVG_SET1;
extern const float GLOBAL_AVG_SET2;

extern const int TOTAL_USERS;
extern const int TOTAL_MOVIES;

extern const long BASE_SIZE;

extern double **user_feature_table;
extern double **movie_feature_table;


void initializeFeatureVectors();
void train();
double predictRating(int user, int movie);
void trainFeature(double learning_rate, int user, int movie, int rating, int num_feature);
//void computeSVD(double learning_rate, int num_features, int* train_data, int epochs);
void computeSVD(double learning_rate, int num_features, int* train_data, double* movieAverages, double* userOffsets, int epochs);


#endif /* defined(__netflix_project__svd__) */
