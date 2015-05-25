//
//  main.cpp
//  netflix_project
//
//  Created by Connor Lee on 4/16/15.
//  Copyright (c) 2015 Connor Lee. All rights reserved.
//

#include <iostream>
#include "dataManager.h"
//#include "svd.h"
#include "svdplus.h"
#include "errorManager.h"
#include <time.h>

const long BASE_SIZE = 94362233;
const long PROBE_SIZE = 1374739;
const long IIIsize = 98291668;
const long IVsize = IIIsize + PROBE_SIZE;
int main(int argc, const char * argv[]) {

    
    float start, end;
    double duration;
    start = clock();
    
    //Store the training data in train_data
    int* trainingData = fillData(trainingDataFullFile, IIIsize, 4);
    int* probeData = fillData(probeDataFile, PROBE_SIZE, 4);
    
    end = clock();
    duration=(end-start)/CLOCKS_PER_SEC;
    printf("Reading data took %f seconds\n",duration);
    
    //Set the length of the feature vectors
    int num_features = 65;
    int epochs = 15;
    computeSVDPlusPlus(num_features, epochs, trainingData, probeData, IIIsize);
//    computeSVD(0.018, num_features, epochs, trainingData, probeData, BASE_SIZE);
    delete [] trainingData;
    
  //  predictQual();
 predictQualPlus();
    
    delete [] probeData;

    for(int i = 0; i < TOTAL_USERS; i++){
        delete [] user_feature_table[i];
        //        delete [] user_time_dependent_deviation_table[i];
        //        delete [] user_varying_time_dependent_baseline_scaling_table[i];
        //        delete [] user_frequency_table[i];
    }
    delete [] user_feature_table;
    delete [] user_rating_deviation_table;
//    //    delete [] user_mean_rating_date_table;
//    //    delete [] user_time_deviation_scaling_table;
//    //    delete [] user_time_dependent_deviation_table;
//    //    delete [] user_constant_time_dependent_baseline_scaling_table;
//    //    delete [] user_varying_time_dependent_baseline_scaling_table;
//    //    delete [] user_frequency_table;
//    
    for(int i = 0; i < TOTAL_MOVIES; i++){
        delete[] movie_feature_table[i];
        //        delete[] movie_time_changing_bias_table[i];
        //        delete[] movie_frequency_bias_table[i];
    }
    delete[] movie_feature_table;
    delete [] movie_rating_deviation_table;
//    //    delete [] movie_time_changing_bias_table;
//    //    delete[] movie_frequency_bias_table;
    return 0;
}