//
//  svd.cpp
//  netflix_project
//
//  Created by Connor Lee on 4/25/15.
//  Copyright (c) 2015 Connor Lee. All rights reserved.
//

#include "svd.h"

const float GLOBAL_AVG_SET1 = 3.608609;
const float GLOBAL_AVG_SET2 = 3.608859;

const int TOTAL_USERS = 458293;
const int TOTAL_MOVIES = 17770;
const int TOTAL_DAYS = 2243;

float LRATE;
int NUMFEATURES;
float BETA = 0.4;

float **user_feature_table;
float **movie_feature_table;

int *dataArray;

const float REG_A = 0.0255;
const float LEARNING_A = 2 * 0.00267;

const float REG_B = 3.95;
const float LEARNING_B = 2 * 0.00000311;

const float REG_C = 0.00231;
const float LEARNING_C = 2 * 0.00257;

const float REG_D = 0.0255;
const float LEARNING_D = 2 * 0.000488;

const float REG_E = 0.0929;
const float LEARNING_E = 2 * 0.000115;

float CURR_TIME_DEV;
int CURR_BIN_LOC;
float CURR_USER_BASE;
float CURR_USER_ALPHA;
float CURR_USER_DATE_BIAS;
float CURR_MOVIE_BASE;
float CURR_MOVIE_BIN_BIAS;

void initializeFeatureVectors() {
    srand (static_cast <unsigned> (time(0)));
    float randInit;
    user_feature_table = new float *[TOTAL_USERS];
    movie_feature_table = new float *[TOTAL_MOVIES];
    
    ifstream inUserBinFile;
    ifstream inUserTimesBinFile;
    inUserBinFile.open(userOffsetFile, ios::in|ios::binary);
    inUserTimesBinFile.open(outUserTimeAverages, ios::in|ios::binary);
    
    if(!inUserBinFile.is_open()) {
        fprintf(stderr, "user binary file was not opened!\n");
    }
    if(!inUserTimesBinFile.is_open()) {
        fprintf(stderr, "user times binary file was not opened!\n");
    }
    inUserBinFile.seekg (0, ios::beg);
    inUserTimesBinFile.seekg (0, ios::beg);
    
    for(int i = 0; i < TOTAL_USERS; i++) {
        /*
         * indices 0 through NUMFEATURES - 1: vector features
         * index NUMFEATURES: user rating baseline
         * index NUMFEATURES + 1: user time deviation coefficient baseline
         * index NUMFEATURES + 2: user time average
         * index NUMFEATURES + 3 through NUMFEATURES + 3 + TOTAL_DAYS - 1: user day baselines
         */
        user_feature_table[i] = new float[NUMFEATURES + 3 + TOTAL_DAYS];
        
        randInit = static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(0.1f)));
        
        std::fill(user_feature_table[i], user_feature_table[i] + NUMFEATURES, randInit);
        inUserBinFile.read(reinterpret_cast<char*> (user_feature_table[i] + NUMFEATURES), sizeof(float));
        std::fill(user_feature_table[i] + NUMFEATURES + 1, user_feature_table[i] + NUMFEATURES + TOTAL_DAYS, 0);
        inUserTimesBinFile.read(reinterpret_cast<char*> (user_feature_table[i] + NUMFEATURES + 2), sizeof(float));
    }
    
    inUserBinFile.close();
    inUserTimesBinFile.close();
    
    /*
    for(int i = 0; i < NUMFEATURES + 3 + TOTAL_DAYS; i++) {
        printf("%f ", user_feature_table[TOTAL_USERS - 1][i]);
    }
    printf("\n");
    */
    
    ifstream inMovieBinFile;
    inMovieBinFile.open(movieAveragesFile, ios::in|ios::binary);
    
    if(!inMovieBinFile.is_open()) {
        fprintf(stderr, "binary file was not opened!\n");
    }
    
    inMovieBinFile.seekg (0, ios::beg);
    
    for(int i = 0; i < TOTAL_MOVIES; i++) {
        /*
         * indices 0 through NUMFEATURES - 1: vector features
         * index NUMFEATURES: movie rating baseline
         * index NUMFEATURES + 1 through NUMFEATURES + 30: movie time bin baselines
         */
        movie_feature_table[i] = new float[NUMFEATURES + 31];
        
        randInit = static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(0.1f)));
        std::fill(movie_feature_table[i], movie_feature_table[i] + NUMFEATURES, randInit);
        inMovieBinFile.read(reinterpret_cast<char*> (movie_feature_table[i] + NUMFEATURES), sizeof(float));
        std::fill(movie_feature_table[i] + NUMFEATURES + 1, movie_feature_table[i] + NUMFEATURES + 32, 0);
    }
    
    inMovieBinFile.close();
    
    /*
    for(int i = 0; i < NUMFEATURES + 31; i++) {
        printf("%f ", movie_feature_table[TOTAL_MOVIES - 1][i]);
    }
    printf("\n");
    */
}


float predictRating(int user, int movie, int date) {
    int sign;
    float sum = 0.0;
    
    for(int i = 0; i < NUMFEATURES; i++) {
        sum += (user_feature_table[user - 1][i] * movie_feature_table[movie - 1][i]);
    }
    
    CURR_USER_BASE = user_feature_table[user - 1][NUMFEATURES];
    CURR_USER_ALPHA = user_feature_table[user - 1][NUMFEATURES + 1];
    CURR_USER_DATE_BIAS = user_feature_table[user - 1][NUMFEATURES + 2 + date];
    
    CURR_MOVIE_BASE = movie_feature_table[movie - 1][NUMFEATURES];
    CURR_BIN_LOC = (date/TOTAL_DAYS) * 30 + 1;
    CURR_MOVIE_BIN_BIAS = movie_feature_table[movie - 1][NUMFEATURES + CURR_BIN_LOC];
    
    float timeDiff = date - user_feature_table[user - 1][NUMFEATURES + 2];
    
    if(timeDiff < 0)
        sign = -1;
    else
        sign = 1;
    
    CURR_TIME_DEV = (float) sign * powf(abs(timeDiff), BETA);
    
    sum += CURR_USER_BASE + CURR_USER_ALPHA * CURR_TIME_DEV + CURR_USER_DATE_BIAS + CURR_MOVIE_BASE + CURR_MOVIE_BIN_BIAS + GLOBAL_AVG_SET1;
    
    return sum;
}

void computeSVD(float learning_rate, int num_features, int* train_data, int epochs) {
    LRATE = 2 * learning_rate;
    NUMFEATURES = num_features;
    dataArray = train_data;
    
    initializeFeatureVectors();

    float start, end;
    float duration;
    
    float sum, error, userVal, adjustUser, adjustMovie;
    int user, movie, rating, date, randUser, randFeature, randMovie;
    
    for(int k = 0; k < epochs; k++) {
        start = clock();
        printf("Training epoch %d\n", k + 1);
        for(int j = 0; j < BASE_SIZE; j++) {
            user = dataArray[4 * j];
            movie = dataArray[4 * j + 1];
            date = dataArray[4 * j + 2];
            rating = dataArray[4 * j + 3];
            
            error = rating - predictRating(user, movie, date);
            
            //Train vector features (user and movie indices: 0 through NUMFEATURES - 1)
            for(int i = 0; i < NUMFEATURES; i++){
                userVal = user_feature_table[user - 1][i];
                
                user_feature_table[user - 1][i] += LRATE * error * movie_feature_table[movie - 1][i];
                movie_feature_table[movie - 1][i] += LRATE * error * userVal;
            }
            
            //Train user rating baseline (user index: NUMFEATURES)
            user_feature_table[user - 1][NUMFEATURES] += LEARNING_A * (error - REG_A * CURR_USER_BASE);
            
            //Train user time deviation baseline (user index: NUMFEATURES + 1)
            user_feature_table[user - 1][NUMFEATURES + 1] += LEARNING_B * (CURR_TIME_DEV * error - REG_B * CURR_USER_ALPHA);
            
            //Train user day baseline (user index: somewhere in NUMFEATURES + 3 through NUMFEATURES + 2 + TOTAL_DAYS)
            user_feature_table[user - 1][NUMFEATURES + 2 + date] += LEARNING_C * (error - REG_C * CURR_USER_DATE_BIAS);
            
            //Train movie rating baseline (movie index: NUMFEATURES)
            movie_feature_table[movie - 1][NUMFEATURES] += LEARNING_D * (error - REG_D * CURR_MOVIE_BASE);
            
            //Train movie time bin baseline (movie index: somewhere in NUMFEATURES + 1 through NUMFEATURES + 30)
            movie_feature_table[movie - 1][NUMFEATURES + CURR_BIN_LOC] += LEARNING_E * (error - REG_E * CURR_MOVIE_BIN_BIAS);
            
            if((j + 1) % 1000000 == 0) {
                printf("%d test points trained.\n", j + 1);
            }
        }
        
        /*
        sum = 0.0;
        
        for (int j = 0; j < BASE_SIZE; j++) {
            user = dataArray[4 * j];
            movie = dataArray[4 * j + 1];
            date = dataArray[4 * j + 2];
            rating = dataArray[4 * j + 3];
            sum += powf(rating - predictRating(user, movie, date), 2);
        }
        */
        
        for(int i = 0; i < 10000; i++){
            randUser = rand() % TOTAL_USERS;
            randMovie = rand() % TOTAL_MOVIES;
            randFeature = rand() % (NUMFEATURES + 1);
            
            adjustUser = user_feature_table[randUser][randFeature];
            assert(adjustUser < 50 && adjustUser > -50);
            
            adjustMovie = movie_feature_table[randMovie][randFeature];
            assert(adjustMovie < 50 && adjustMovie > -50);
        }
        end = clock();
        duration=(end-start)/CLOCKS_PER_SEC;
        //printf("Epoch %d took %f seconds. Its RMSE is %f\n",k + 1, duration, powf(sum/BASE_SIZE, 0.5));
        printf("Epoch %d took %f seconds.\n",k + 1, duration);
        
        LRATE = 0.9 * LRATE;
    }
}
