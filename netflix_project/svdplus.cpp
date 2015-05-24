//
//  svd++.cpp
//  netflix_project
//
//  Created by Connor Lee on 5/22/15.
//  Copyright (c) 2015 Connor Lee. All rights reserved.
//

#include "svdplus.h"

/* CHANGE THESE NUMBERS */
int FEATURES;
int GLOBALAVG = 3.6033;

//float LRATE_UF_BASE = 0.006;
//float REG_UF = 0.080;
//float C_FACTOR_UF = 0.01;
//int TAU_UF = 10;
//
//float LRATE_MF_BASE = 0.011;
//float REG_MF = 0.006;
//float C_FACTOR_MF = 0.01;
//int TAU_MF = 10;
//
//float LRATE_M_BASE = 0.003;
//float REG_M = 0.0;
//float C_FACTOR_M = 0.01;
//int TAU_M = 10;
//
//float LRATE_U_BASE = 0.012;
//float REG_U = 0.030;
//float C_FACTOR_U = 0.01;
//int TAU_U = 10;
//
//float LRATE_W_BASE = 0.001;
//float REG_Y = 0.030;
//float C_FACTOR_W = 0.01;
//int TAU_W = 10;


float LRATE_UF_BASE = 0.018;
float REG_UF = 0.0015;
float C_FACTOR_UF = 0.02;
int TAU_UF = 10;

float LRATE_MF_BASE = 0.018;
float REG_MF = 0.0015;
float C_FACTOR_MF = 0.02;
int TAU_MF = 10;

float LRATE_M_BASE = 0.01;
float REG_M = 0.005;
float C_FACTOR_M = 0.01;
int TAU_M = 10;

float LRATE_U_BASE = 0.01;
float REG_U = 0.005;
float C_FACTOR_U = 0.01;
int TAU_U = 10;

float LRATE_W_BASE = 0.007;
float REG_Y = 0.015;
float C_FACTOR_W = 0.01;
int TAU_W = 10;


int ptrainRMSE = 1;
int debug = 0;

const int TOTAL_USERS = 458293;
const int TOTAL_MOVIES = 17770;
const int TOTAL_DAYS = 2243;
const long BASE_SIZE = 94362233;
const long PROBE_SIZE = 1374739;
const long IIIsize = 98291668;

float *userBias;
float *movieBias;
float **userFeatures;
float **movieFeatures;
float **sumY;
float **Y;
float *norms;
int *movieCountByUser;

float pickrandom() {
    return (0.001 + (rand() / ( RAND_MAX / (0.01 - 0.001))));
}

float bwZ1() {
    return  ((float) rand() / (RAND_MAX)) / 10.0;
}

float sign()
{
    if(((float) rand() / (RAND_MAX)) > 0.5) {
        return -1.0;
    } else {
        return 1.0;
    }
}

void initialize(int *train_data, int rows) {
    
    float check;
    
    /* Initialize user features */
    userFeatures = new float *[TOTAL_USERS];
    for(int i = 0; i < TOTAL_USERS; i++) {
        userFeatures[i] = new float [FEATURES];
        for(int j = 0; j < FEATURES; j++) {
            check = (rand() % 14000 + 2000) * 0.000001235f;
            userFeatures[i][j] = check;
            assert(check != 0 && check < 10 && check > -10);
        }
    }
    
    
    /* Initialize movie features */
    movieFeatures = new float *[TOTAL_MOVIES];
    for(int i = 0; i < TOTAL_MOVIES; i++) {
        movieFeatures[i] = new float [FEATURES];
        for(int j = 0; j < FEATURES; j++) {
            check = (rand() % 14000 + 2000) * -0.000001235f;
            movieFeatures[i][j] = check;
            assert(check != 0 && check < 10 && check > -10);
        }
    }
    
    
    /* Initialize user bias */
    userBias = new float [TOTAL_USERS];
    for(int i = 0; i < TOTAL_USERS; i++) {
        check = pickrandom();
        userBias[i] = 0.0;
        assert(check != 0 && check < 10 && check > -10);
    }
    
    
    /* Initialize movie bias */
    movieBias = new float [TOTAL_MOVIES];
    for(int i = 0; i < TOTAL_MOVIES; i++) {
        check = pickrandom();
        movieBias[i] = 0.0;
        assert(check != 0 && check < 10 && check > -10);
    }
    
//    
//    /* Initialize movie weights */
//    Y = new float *[TOTAL_MOVIES];
//    for(int i = 0; i < TOTAL_MOVIES; i++) {
//        Y[i] = new float [FEATURES];
//        for(int j = 0; j < FEATURES; j++) {
//            check = pickrandom();
//            Y[i][j] = check;
//            assert(check != 0 && check < 10 && check > -10);
//        }
//    }
//    
//    /* Initialize sum of movie weights */
//    sumY = new float *[TOTAL_USERS];
//    for(int i = 0; i < TOTAL_USERS; i++) {
//        sumY[i] = new float [FEATURES];
//        for(int j = 0; j < FEATURES; j++) {
//            sumY[i][j] = 0.0;
//        }
//    }
//    
//    
//    /* Compute norms */
//    movieCountByUser = new int[TOTAL_USERS];
//    norms = new float[TOTAL_USERS];
//    
//    for(int i = 0; i < TOTAL_USERS; i++) {
//        movieCountByUser[i] = 0;
//    }
//    
//    for(int i = 0; i < rows; i++) {
//        movieCountByUser[train_data[4 * i] - 1] += 1;
//    }
//    
//    for(int i = 0; i < TOTAL_USERS; i++) {
//        float curr = (float) movieCountByUser[i];
//        norms[i] = sqrt(curr);
//    }
    printf("Done initializing\n\n");
}



float predictRatingPLUS(int user, int movie) {

    float sum = 0.0;
    for(int i = 0; i < FEATURES; i++) {

//        sum += movieFeatures[movie - 1][i] * (userFeatures[user - 1][i] + norms[user - 1] * sumY[user - 1][i]);
        sum += (movieFeatures[movie - 1][i] * userFeatures[user - 1][i]);
    }

    return (sum + GLOBALAVG + userBias[user - 1] + movieBias[movie - 1]);
}


void computeSVDPlusPlus(int num_features, int epochs, int* train_data, int* probe_data, long size) {
    FEATURES = num_features;
    initialize(train_data, size);
    
    int user, movie, rating, *dataArray = train_data, userVal, movieVal, k;
    float *temp_sum, error, userBiasVal, movieBiasVal, start, end, sum, oldTrainRMSE = 2.0, newTrainRMSE = 2.0, newProbeRMSE = 2.0,
    oldProbeRMSE= 2.0, adjustLearn;
    vector<int> moviesRatedByCurrUser;
    
//    temp_sum = new float[FEATURES];
    
    int epoch_trained = 0;
    while(epoch_trained < epochs) {
        float LRATE_UF = LRATE_UF_BASE;
        float LRATE_MF = LRATE_MF_BASE;
        float LRATE_M = LRATE_M_BASE;
        float LRATE_U = LRATE_U_BASE;
        float LRATE_W = LRATE_W_BASE;
        k = epoch_trained + 1;
        adjustLearn = (C_FACTOR_UF / LRATE_UF_BASE) * ((float) k / TAU_UF);
        LRATE_UF = LRATE_UF_BASE * (1 + adjustLearn) / (1 + adjustLearn + (float) (k * k) / TAU_UF);
        
        adjustLearn = (C_FACTOR_MF / LRATE_MF_BASE) * ((float) k / TAU_MF);
        LRATE_MF = LRATE_MF_BASE * (1 + adjustLearn) / (1 + adjustLearn + (float) (k * k) / TAU_MF);
        
        adjustLearn = (C_FACTOR_M / LRATE_M_BASE) * ((float) k / TAU_M);
        LRATE_M = LRATE_M_BASE * (1 + adjustLearn) / (1 + adjustLearn + (float) (k * k) / TAU_M);
        
        adjustLearn = (C_FACTOR_U / LRATE_U_BASE) * ((float) k / TAU_U);
        LRATE_U = LRATE_U_BASE * (1 + adjustLearn) / (1 + adjustLearn + (float) (k * k) / TAU_U);
        
        adjustLearn = (C_FACTOR_W/LRATE_W_BASE) * ((float) k / TAU_W);
        LRATE_W = LRATE_W_BASE * (1 + adjustLearn) / (1 + adjustLearn + (float) (k * k) / TAU_W);
        
        printf("Starting Epoch %d!\n", epoch_trained + 1);
        start = clock();
        
        int prev_user = 1, userCount = 0;
        
        
//        for(int f = 0; f < FEATURES; f++) {
//            temp_sum[f] = 0.0;
//        }
        
        /* Loop through all data points */
        for(int i = 0; i < size; i++) {
            user = dataArray[4 * i];
            movie = dataArray[4 * i + 1];
            rating = dataArray[4 * i + 3];
            
            /* Get error */
            error = rating - predictRatingPLUS(user, movie);
            
            /* If user has changed */
//            if(prev_user == user) {
//                userCount++;
//                moviesRatedByCurrUser.push_back(movie);
//            } else {
//                userCount = 1;
//                moviesRatedByCurrUser.clear();
//                moviesRatedByCurrUser.push_back(movie);
//            }
//            
//            float *currSumY = sumY[user - 1];
            
            /* Iteration of stochastic gradient descent */
            for(int k = 0; k < FEATURES; k++) {
                userVal = userFeatures[user - 1][k];
                movieVal = movieFeatures[movie - 1][k];
//                float curr_norm = norms[user - 1];
                
                
                userFeatures[user - 1][k] += LRATE_UF * (error * movieVal - REG_UF * userVal);
//                movieFeatures[movie - 1][k] += LRATE_MF * (error * (userVal + curr_norm * currSumY[k]) - REG_MF * movieVal);
                movieFeatures[movie - 1][k] += LRATE_MF * (error * userVal - REG_MF * movieVal);
//                temp_sum[k] += (error * curr_norm * movieVal);
            }
            
            /* Store  */
            userBiasVal = userBias[user - 1];
            movieBiasVal = movieBias[movie - 1];
            
            /* Tune biases */
            movieBias[movie - 1] += LRATE_M * (error - REG_M * movieBiasVal);
            userBias[user - 1] += LRATE_U * (error - REG_U * userBiasVal);
            
//            int movie_count = movieCountByUser[user - 1];
//            if(userCount == movie_count) {
//                for(int j = 0; j < movie_count; j++) {
//                    
//                    float *currY = Y[moviesRatedByCurrUser[j] - 1];
//                    
//                    for(int k = 0; k < FEATURES; k++) {
//                        float old = currY[k];
//                        currY[k] += LRATE_W * (temp_sum[k] - REG_Y * old);
//                        currSumY[k] += (currY[k] - old);
//                    }
//                }
//                
//                for(int z = 0; z < FEATURES; z++) {
//                    temp_sum[z] = 0.0;
//                }
//            }
//            
//            prev_user = user;
        }
        
        end = clock();
        printf("Epoch %d took %f seconds!\n", epoch_trained + 1, (end - start) / CLOCKS_PER_SEC);

        if(ptrainRMSE){
            sum = 0.0;
            for (int j = 0; j < size; j++) {
                user = dataArray[4 * j];
                movie = dataArray[4 * j + 1];
                rating = dataArray[4 * j + 3];
                sum += powf(rating - predictRatingPLUS(user, movie), 2);
            }
            
            newTrainRMSE = powf(sum/(size), 0.5);
            
            printf("Training RMSE, old: %f, new %f\n", oldTrainRMSE, newTrainRMSE);
            if(newTrainRMSE - oldTrainRMSE > 0){
                fprintf(stderr, "Training set RMSE went up, exiting.\n");
                exit(0);
            }
            
            oldTrainRMSE = newTrainRMSE;
        }
        
        sum = 0.0;
        
        for (int j = 0; j < PROBE_SIZE; j++) {
            user = probe_data[4 * j];
            movie = probe_data[4 * j + 1];
            rating = probe_data[4 * j + 3];
            sum += powf(rating - predictRatingPLUS(user, movie), 2);
        }
        
        newProbeRMSE = powf(sum/(PROBE_SIZE), 0.5);
        
        printf("Probe RMSE, old: %f, new %f\n\n", oldProbeRMSE, newProbeRMSE);
        
        if(oldProbeRMSE - newProbeRMSE < 0.00001){
            fprintf(stderr, "Probe RMSE drop is miniscule. Training done.\n");
            break;
        }
        
        oldProbeRMSE = newProbeRMSE;
        epoch_trained++;
        
        
        LRATE_UF_BASE *= 0.9;
        LRATE_MF_BASE *= 0.9;
        LRATE_M_BASE *= 0.9;
        LRATE_U_BASE *= 0.9;
        LRATE_W_BASE *= 0.9;

    }
    
    delete []movieCountByUser;
    
    for(int i = 0; i < TOTAL_MOVIES; i++) {
        delete Y[i];
    }
    delete [] Y;
    delete [] temp_sum;
}










