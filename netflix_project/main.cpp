//
//  main.cpp
//  netflix_project
//
//  Created by Connor Lee on 4/16/15.
//  Copyright (c) 2015 Connor Lee. All rights reserved.
//

#include <iostream>
#include "svd.h"






int main(int argc, const char * argv[]) {
    
    // Parse file and store test points as testPoint objects
    std::vector<testPoint*> dataSet = fillTestPoints();
    
    
    // Get global average of data set
    
    /*
    double avg = getGlobalAverage(dataSet);
    printf("%f", avg);
     */
    initialize(30);
    
    for(int i = 0; i < TOTAL_USERS; i++) {
        printf("%f\n", user_feature_table[i][0]);
    }
    
    return 0;
}
