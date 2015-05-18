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
#include <cmath>
#include <time.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

//Roshan's files
//#define userRatingDeviationFile "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/userOffsets.bin"
//#define movieRatingDeviationFile "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/movieAverages.bin"
//#define userMeanTimeRatingFile "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/userTimeAverages.bin"
//#define userFrequenciesFile "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/userFrequencies.bin"

//Connor's files
#define userRatingDeviationFile "/Users/ConnorLee/Desktop/netflix/userOffsets.bin"
#define movieRatingDeviationFile "/Users/ConnorLee/Desktop/netflix/movieAverages.bin"
#define userMeanTimeRatingFile "/Users/ConnorLee/Desktop/netflix/userTimeAverages.bin"
#define userFrequenciesFile "/Users/ConnorLee/Desktop/netflix/userFrequencies.bin"

extern const float GLOBAL_AVG_SET1;
extern const float GLOBAL_AVG_SET2;

extern const int TOTAL_USERS;
extern const int TOTAL_MOVIES;

extern float **user_feature_table;
extern float *user_rating_deviation_table;
extern float *user_mean_rating_date_table;
extern float *user_time_deviation_scaling_table;
extern float **user_time_dependent_deviation_table;
extern float *user_constant_time_dependent_baseline_scaling_table;
extern float **user_varying_time_dependent_baseline_scaling_table;
extern int **user_frequency_table;

extern float **movie_feature_table;
extern float *movie_rating_deviation_table;
extern float **movie_time_changing_bias_table;
extern float **movie_frequency_bias_table;

extern const long BASE_SIZE;
extern const long PROBE_SIZE;

void initializeFeatureVectors();
float predictRating(int user, int movie, int date);
void computeSVD(float learning_rate, int num_features, int epochs, int* train_data, int* probe_data);


#endif /* defined(__netflix_project__svd__) */
