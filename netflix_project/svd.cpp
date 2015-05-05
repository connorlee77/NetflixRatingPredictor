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
    
    user_feature_table = new float *[TOTAL_USERS];
    movie_feature_table = new float *[TOTAL_MOVIES];
    
    ifstream inUserBinFile;
    inUserBinFile.open(userOffsetFile, ios::in|ios::binary);
    
    
    if(!inUserBinFile.is_open()) {
        fprintf(stderr, "binary file was not opened!\n");
    }
    
    inUserBinFile.seekg (0, ios::beg);
    
    for(int i = 0; i < TOTAL_USERS; i++) {
        
        user_feature_table[i] = new float[NUMFEATURES + 1];
        
        std::fill(user_feature_table[i], user_feature_table[i] + NUMFEATURES, 0.1f);
        inUserBinFile.read(reinterpret_cast<char*> (user_feature_table[i] + NUMFEATURES), sizeof(float));
    }
    
    inUserBinFile.close();
    
    
    ifstream inMovieBinFile;
    inMovieBinFile.open(movieAveragesFile, ios::in|ios::binary);
    
    if(!inMovieBinFile.is_open()) {
        fprintf(stderr, "binary file was not opened!\n");
    }
    
    inMovieBinFile.seekg (0, ios::beg);
    
    for(int i = 0; i < TOTAL_MOVIES; i++) {
        
        movie_feature_table[i] = new float[NUMFEATURES + 1];
        
        std::fill(movie_feature_table[i], movie_feature_table[i] + NUMFEATURES, 0.1f);
        inMovieBinFile.read(reinterpret_cast<char*> (movie_feature_table[i] + NUMFEATURES), sizeof(float));
    }
    
    inMovieBinFile.close();
}


float predictRating(int user, int movie) {
    
    float sum = 0.0;
    
    for(int i = 0; i < NUMFEATURES; i++) {
        sum += (user_feature_table[user - 1][i] * movie_feature_table[movie - 1][i]);
    }
    
    //printf("Baseline: %f, %f\n", user_feature_table[user - 1][NUMFEATURES], movie_feature_table[movie - 1][NUMFEATURES]);
    
    sum += user_feature_table[user - 1][NUMFEATURES] + movie_feature_table[movie - 1][NUMFEATURES];
    
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
            userVal = user_feature_table[user - 1][i];
            movieVal = movie_feature_table[movie - 1][i];
            error = LRATE * (rating - ratingPredict);
            ratingPredict -= (userVal * movieVal);
        
            adjustUser = userVal + error * movieVal;
            adjustMovie = movieVal + error * userVal;
        
            user_feature_table[user - 1][i] = adjustUser;
            movie_feature_table[movie - 1][i] = adjustMovie;
        
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
    
    
    NUMFEATURES = num_features;
    LRATE = learning_rate;
    dataArray = train_data;
    
    initializeFeatureVectors();

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
