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

const long BASE_SIZE = 94362233;

double **user_feature_table = new double *[TOTAL_USERS];
double **movie_feature_table = new double *[TOTAL_MOVIES];


void initializeFeatureVectors(int num_features) {
    
    for(int i = 0; i < TOTAL_USERS; i++) {
        
        user_feature_table[i] = new double[num_features];
        
        for(int k = 0; k < num_features; k++) {
            //user_feature_table[i][k] = 0.1;
            user_feature_table[i][k] = GLOBAL_AVG_SET2 / num_features;
        }
    }
    
    for(int i = 0; i < TOTAL_MOVIES; i++) {
        
        movie_feature_table[i] = new double[num_features];
        
        for(int k = 0; k < num_features; k++) {
            //movie_feature_table[i][k] = 0.1;
            movie_feature_table[i][k] = GLOBAL_AVG_SET2 / num_features;
        }
    }
}


double predictRating(int user, int movie, int num_features) {
    
    double sum = 0.0;
    
    for(int i = 0; i < num_features; i++) {
        sum += (user_feature_table[user - 1][i] * movie_feature_table[movie - 1][i]);
    }
    
    assert(isfinite(sum));
    
    return sum;
}


/* Train feature #num_features */
void trainFeature(double learning_rate, int user, int movie, int rating, int num_feature, int num_features) {
    
    double error = rating - predictRating(user, movie, num_features);
    
    double temp_user_feature = user_feature_table[user - 1][num_feature];
    user_feature_table[user - 1][num_feature] += learning_rate * error * movie_feature_table[movie - 1][num_feature];
    movie_feature_table[movie - 1][num_feature] += learning_rate * error * temp_user_feature;
    
    assert(user_feature_table[user - 1][num_feature] < 50 && user_feature_table[user - 1][num_feature] > -50);
    assert(movie_feature_table[movie - 1][num_feature] < 50 && movie_feature_table[movie - 1][num_feature] > -50);
}


void computeSVD(double learning_rate, int num_features, int* train_data, int epochs) {
    
    initializeFeatureVectors(num_features);
    
    int user, movie, rating;
    double curr_rmse;

    for(int i = 0; i < epochs; i++) {
        double sum = 0.0;
        for(int j = 0; j < BASE_SIZE; j++) {
            
            user = train_data[4 * j];
            movie = train_data[4 * j + 1];
            rating = train_data[4 * j + 3];
            
            for(int i = 0; i < num_features; i++) {
                trainFeature(learning_rate, user, movie, rating, i, num_features);
            }
            sum += pow((rating - predictRating(user, movie, num_features)), 2);
            
        }
        
        curr_rmse = sqrt((sum / BASE_SIZE));
        printf("Epoch %d, rsme: %f\n", i, curr_rmse);
    }

}
