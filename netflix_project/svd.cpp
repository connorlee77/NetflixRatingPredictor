//
//  svd.cpp
//  netflix_project
//
//  Created by Connor Lee on 4/25/15.
//  Copyright (c) 2015 Connor Lee. All rights reserved.
//

#include "svd.h"



void initialize(int num_features) {
    
    for(int i = 0; i < TOTAL_USERS; i++) {
        
        user_feature_table[i] = new double[num_features];
        
        for(int k = 0; k < num_features; k++) {
            user_feature_table[i][k] = GLOBAL_AVG_SET2 / num_features;
        }
    }
    
    for(int i = 0; i < TOTAL_MOVIES; i++) {
        
        movie_feature_table[i] = new double[num_features];
        
        for(int k = 0; k < num_features; k++) {
            movie_feature_table[i][k] = GLOBAL_AVG_SET2 / num_features;
        }
    }
}
