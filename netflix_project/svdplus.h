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
#include <sys/time.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <pthread.h>
#include <random>
#include "hogNode.h"
#include <vector>

using namespace std;

//Roshan's files
//#define userRatingDeviationFile "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/userOffsets.bin"
//#define movieRatingDeviationFile "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/movieAverages.bin"
//#define userMeanTimeRatingFile "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/userTimeAverages.bin"
//#define userFrequenciesFile "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/userFrequencies.bin"
//#define userMovieFrequenciesFile "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/userMovieFrequencies.bin"

//Connor's files
#define userRatingDeviationFile "/Users/ConnorLee/Desktop/netflix/userOffsets.bin"
#define movieRatingDeviationFile "/Users/ConnorLee/Desktop/netflix/movieAverages.bin"
#define userMeanTimeRatingFile "/Users/ConnorLee/Desktop/netflix/userTimeAverages.bin"
#define userFrequenciesFile "/Users/ConnorLee/Desktop/netflix/userFrequencies.bin"
#define userMovieFrequenciesFile "/Users/ConnorLee/Desktop/netflix/userMovieFrequencies.bin"

extern const float GLOBAL_AVG_SET1;
extern const float GLOBAL_AVG_SET2;

extern const int TOTAL_USERS;
extern const int TOTAL_MOVIES;

extern float **user_feature_table;
extern float *user_rating_deviation_table;

extern float **movie_feature_table;
extern float *movie_rating_deviation_table;

extern float **user_implicit_vector_sum_table;
extern float **movie_implicit_vector_table;
extern int *user_ratings_count_noqual_table;
extern int *user_ratings_count_withqual_table;
extern int **user_movies_table;
extern float *user_norms_table;

extern const long BASE_SIZE;
extern const long PROBE_SIZE;
extern const long IIIsize;

void initializeFeatureVectorsPlus();
float predictRatingPLUS(int user, int movie);
void *hogwildPlus(void *rates);
void computeSVDPlusPlus(int num_features, int epochs, int* train_data, int* probe_data, long data_size);

#endif /* defined(__netflix_project__svd__) */