//
//  svd.cpp
//  netflix_project
//
//  Created by Connor Lee on 4/25/15.
//  Copyright (c) 2015 Connor Lee. All rights reserved.
//

#include "svd.h"
#include <limits.h>

const float GLOBAL_AVG_SET1 = 3.608609;
const float GLOBAL_AVG_SET2 = 3.608859;

const int TOTAL_USERS = 458293;
const int TOTAL_MOVIES = 17770;

int NUMFEATURES;
float LRATE;

float **user_feature_table;
float **movie_feature_table;

int *dataArray;

void initializeFeatureVectors() {
    
    user_feature_table = new float *[NUMFEATURES + 1];
    movie_feature_table = new float *[NUMFEATURES + 1];
    
    for(int i = 0; i < NUMFEATURES; i++) {
        
        user_feature_table[i] = new float[TOTAL_USERS];
        
        std::fill(user_feature_table[i], user_feature_table[i] + TOTAL_USERS, 0.1);
    }
    
    ifstream inUserBinFile;
    inUserBinFile.open(userOffsetFile, ios::in|ios::binary);
    
    if(!inUserBinFile.is_open()) {
        fprintf(stderr, "binary file was not opened!");
    }
    
    user_feature_table[NUMFEATURES] = new float[TOTAL_USERS];
    
    inUserBinFile.seekg (0, ios::beg);
    
    inUserBinFile.read(reinterpret_cast<char*> (user_feature_table[NUMFEATURES]), sizeof(float) * TOTAL_USERS);
    
    inUserBinFile.close();
    
    for(int i = 0; i < NUMFEATURES; i++) {
        
        movie_feature_table[i] = new float[TOTAL_MOVIES];
        
        std::fill(movie_feature_table[i], movie_feature_table[i] + TOTAL_MOVIES, 0.1);
    }
    
    ifstream inMovieBinFile;
    inMovieBinFile.open(movieAveragesFile, ios::in|ios::binary);
    
    if(!inMovieBinFile.is_open()) {
        fprintf(stderr, "binary file was not opened!");
    }
    
    movie_feature_table[NUMFEATURES] = new float[TOTAL_MOVIES];
    
    inMovieBinFile.seekg (0, ios::beg);
    
    inMovieBinFile.read(reinterpret_cast<char*> (movie_feature_table[NUMFEATURES]), sizeof(float) * TOTAL_MOVIES);
    
    inMovieBinFile.close();
}


float predictRating(int user, int movie) {
    
    float sum = 0.0;
    
    for(int i = 0; i < NUMFEATURES; i++) {
        sum += (user_feature_table[i][user - 1] * movie_feature_table[i][movie - 1]);
    }
    
    sum += user_feature_table[NUMFEATURES][user - 1] + movie_feature_table[NUMFEATURES][movie - 1];
    
    assert(isfinite(sum));
    
    return sum;
}

void trainFeatures() {
    float error, userVal, movieVal, adjustUser, adjustMovie, ratingPredict;
    int user, movie, rating;
    
    for(int j = 0; j < BASE_SIZE; j++) {
        user = dataArray[4 * j];
        movie = dataArray[4 * j + 1];
        rating = dataArray[4 * j + 3];
    
        ratingPredict = predictRating(user, movie);
        for(int i = 0; i < NUMFEATURES; i++){
            userVal = user_feature_table[i][user - 1];
            movieVal = movie_feature_table[i][movie - 1];
            error = LRATE * (rating - ratingPredict);
            ratingPredict -= (userVal * movieVal);
        
            adjustUser = userVal + error * movieVal;
            adjustMovie = movieVal + error * userVal;
        
            user_feature_table[i][user - 1] = adjustUser;
            movie_feature_table[i][movie - 1] = adjustMovie;
        
            ratingPredict += (adjustUser * adjustMovie);
        
            assert(adjustUser < 50 && adjustUser > -50);
            assert(adjustMovie < 50 && adjustMovie > -50);
        }
        
        if((j + 1) % 1000000 == 0) {
            printf("%d test points trained!\n", j + 1);
        }
        
    }
}

void computeSVD(float learning_rate, int num_features, int* train_data, int epochs) {
    
    long BASE_SIZE = 94362233;
    
    NUMFEATURES = num_features;
    LRATE = learning_rate;
    dataArray = train_data;
    
    initializeFeatureVectors();
    
    int user, movie, rating;
    float curr_rmse;

    float start, end;
    float duration;
    
    for(int i = 0; i < epochs; i++) {
        start = clock();
        printf("Training epoch %d\n", i + 1);
        trainFeatures();
        
        end = clock();
        
        duration=(end-start)/CLOCKS_PER_SEC;
        printf("Epoch %d took %f seconds\n",i + 1, duration);
        //curr_rmse = sqrt((sum / BASE_SIZE));
        //printf("Epoch %d, rsme: %f\n", i + 1, curr_rmse);
    }
}
