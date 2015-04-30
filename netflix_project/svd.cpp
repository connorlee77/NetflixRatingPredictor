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

const long BASE_SIZE = 94362233/6;

int NUMFEATURES;

double **user_feature_table;
double **movie_feature_table;


void initializeFeatureVectors() {
    
    double setVal = GLOBAL_AVG_SET2 / NUMFEATURES;
    
    user_feature_table = new double *[NUMFEATURES];
    movie_feature_table = new double *[NUMFEATURES];
    
    for(int i = 0; i < NUMFEATURES; i++) {
        
        user_feature_table[i] = new double[TOTAL_USERS];
        
        for(int k = 0; k < TOTAL_USERS; k++) {
            //user_feature_table[i][k] = 0.1;
            user_feature_table[i][k] = setVal;
        }
    }
    
    for(int i = 0; i < NUMFEATURES; i++) {
        
        movie_feature_table[i] = new double[TOTAL_MOVIES];
        
        for(int k = 0; k < TOTAL_MOVIES; k++) {
            //movie_feature_table[i][k] = 0.1;
            movie_feature_table[i][k] = setVal;
        }
    }
}


double predictRating(int user, int movie) {
    
    double sum = 0.0;
    
    for(int i = 0; i < NUMFEATURES; i++) {
        sum += (user_feature_table[i][user - 1] * movie_feature_table[i][movie - 1]);
    }
    
    assert(isfinite(sum));
    
    return sum;
}


/* Train feature #num_features */
void trainFeature(double learning_rate, int user, int movie, int rating, int num_feature) {
    
    double error = rating - predictRating(user, movie);
    
    double temp_user_feature = user_feature_table[num_feature][user - 1];
    user_feature_table[num_feature][user - 1] += learning_rate * error * movie_feature_table[num_feature][movie - 1];
    movie_feature_table[num_feature][movie - 1] += learning_rate * error * temp_user_feature;
    
    assert(user_feature_table[num_feature][user - 1] < 50 && user_feature_table[num_feature][user - 1] > -50);
    assert(movie_feature_table[num_feature][movie - 1] < 50 && movie_feature_table[num_feature][movie - 1] > -50);
}


void computeSVD(double learning_rate, int num_features, int* train_data, int epochs) {
    
    NUMFEATURES = num_features;
    
    initializeFeatureVectors();
    
    int user, movie, rating;
    double curr_rmse;

    for(int i = 0; i < epochs; i++) {
        double sum = 0.0;
        for(int j = 0; j < BASE_SIZE; j++) {
            
            user = train_data[4 * j];
            movie = train_data[4 * j + 1];
            rating = train_data[4 * j + 3];
            
            for(int i = 0; i < num_features; i++) {
                trainFeature(learning_rate, user, movie, rating, i);
            }
            sum += pow((rating - predictRating(user, movie)), 2);
            
        }
        
        curr_rmse = sqrt((sum / BASE_SIZE));
        printf("Epoch %d, rsme: %f\n", i, curr_rmse);
    }

}
