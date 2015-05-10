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
const int TOTAl_DAYS = 2243;
int NUMFEATURES;

float **user_feature_table;
float **movie_feature_table;
float *movieTimeBins;

int *dataArray;

float LRATE;

float REG_A = 0.0255;
float LEARNING_A = 2 * 0.00267;

float REG_D = 0.0255;
float LEARNING_D = 2 * 0.000488;

float REG_E = 0.1;
float LEARNING_E = 2 * 0.00005;

void initializeFeatureVectors() {
    srand (static_cast <unsigned> (time(0)));
    float randInit;
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
        
        randInit = static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(0.1f)));
        
        std::fill(user_feature_table[i], user_feature_table[i] + NUMFEATURES, randInit);
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
        
        randInit = static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(0.1f)));
        std::fill(movie_feature_table[i], movie_feature_table[i] + NUMFEATURES, randInit);
        inMovieBinFile.read(reinterpret_cast<char*> (movie_feature_table[i] + NUMFEATURES), sizeof(float));
    }
    
    inMovieBinFile.close();
    
    movieTimeBins = new float[30];
    randInit = static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(0.1f)));
    std::fill(movieTimeBins, movieTimeBins + 30, randInit);
}


float predictRating(int user, int movie, int date) {
    
    float sum = 0.0;
    
    for(int i = 0; i < NUMFEATURES; i++) {
        sum += (user_feature_table[user - 1][i] * movie_feature_table[movie - 1][i]);
    }
    
    sum += user_feature_table[user - 1][NUMFEATURES] + movie_feature_table[movie - 1][NUMFEATURES] + GLOBAL_AVG_SET1 + movieTimeBins[(int) (date/TOTAl_DAYS) * 30];
    
    assert(isfinite(sum));
    
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
    int user, movie, rating, date, randUser, randFeature, randMovie, movieBin;
    
    for(int k = 0; k < epochs; k++) {
        start = clock();
        printf("Training epoch %d\n", k + 1);
        for(int j = 0; j < BASE_SIZE; j++) {
            user = dataArray[4 * j];
            movie = dataArray[4 * j + 1];
            date = dataArray[4 * j + 2];
            rating = dataArray[4 * j + 3];
            
            error = rating - predictRating(user, movie, date);
            for(int i = 0; i < NUMFEATURES; i++){
                userVal = user_feature_table[user - 1][i];
                
                user_feature_table[user - 1][i] += LRATE * error * movie_feature_table[movie - 1][i];
                movie_feature_table[movie - 1][i] += LRATE * error * userVal;
            }
            
            user_feature_table[user - 1][NUMFEATURES] += LEARNING_A * (error - REG_A * user_feature_table[user - 1][NUMFEATURES]);
            movie_feature_table[movie - 1][NUMFEATURES] += LEARNING_D * (error - REG_D * movie_feature_table[movie - 1][NUMFEATURES]);
            
            movieBin = (date/TOTAl_DAYS) * 30;
            movieTimeBins[movieBin] += LEARNING_E * (error - REG_E * movieTimeBins[movieBin]);
            
            if((j + 1) % 1000000 == 0) {
                printf("%d test points trained.\n", j + 1);
            }
        }
        
        /*
        sum = 0.0;
        
        for (int j = 0; j < BASE_SIZE; j++) {
            user = dataArray[4 * j];
            movie = dataArray[4 * j + 1];
            rating = dataArray[4 * j + 3];
            sum += powf(rating - predictRating(user, movie), 2);
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
