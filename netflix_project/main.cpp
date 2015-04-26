//
//  main.cpp
//  netflix_project
//
//  Created by Connor Lee on 4/16/15.
//  Copyright (c) 2015 Connor Lee. All rights reserved.
//

#include <iostream>
#include "svd.h"
#include "errorManager.h"





int main(int argc, const char * argv[]) {
    std::vector<testPoint *> train_data = fillTestPoints();
    
    // epochs : set for number of features in feature vector.
    int num_features = 40;
    
    computeSVD(0.001, num_features, train_data);
    
    double err = getSampleError(train_data, num_features);
    printf("\nEin: %f\n", err);
    
    return 0;
}
