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

#define movieAveragesFile "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/movieAverages.bin"
#define userOffsetFile "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/userOffsets.bin"
#define outUserTimeAverages "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/userTimeAverages.bin"

extern const float GLOBAL_AVG_SET1;
extern const float GLOBAL_AVG_SET2;

extern const int TOTAL_USERS;
extern const int TOTAL_MOVIES;

extern const long BASE_SIZE;

extern float **user_feature_table;
extern float **movie_feature_table;

void initializeFeatureVectors();
float predictRating(int user, int movie, int date);
void computeSVD(float learning_rate, int num_features, int* train_data, int epochs);


#endif /* defined(__netflix_project__svd__) */
