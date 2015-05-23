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

float LRATE_UF = 0.006;
float REG_UF = 0.080;

float LRATE_MF = 0.011;
float REG_MF = 0.006;

float LRATE_M = 0.003;
float REG_M = 0.0;

float LRATE_U = 0.012;
float REG_U = 0.030;

float LRATE_W = 0.001;
float REG_Y = 0.030;

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
    return (0.001 + (rand() / ( RAND_MAX / (0.01 - 0.001)))) * sign();
}

float sign()
{
    if(rand() / (RAND_MAX + 1.) > 0.5) {
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
            check = pickrandom();
            userFeatures[i][j] = check;
            assert(check != 0 && check < 10 && check > -10);
        }
    }
    
    
    /* Initialize movie features */
    movieFeatures = new float *[TOTAL_MOVIES];
    for(int i = 0; i < TOTAL_MOVIES; i++) {
        movieFeatures[i] = new float [FEATURES];
        for(int j = 0; j < FEATURES; j++) {
            check = pickrandom();
            movieFeatures[i][j] = check;
            assert(check != 0 && check < 10 && check > -10);
        }
    }
    
    
    /* Initialize user bias */
    userBias = new float [TOTAL_USERS];
    for(int i = 0; i < TOTAL_USERS; i++) {
        check = pickrandom();
        userBias[i] = check;
        assert(check != 0 && check < 10 && check > -10);
    }
    
    
    /* Initialize movie bias */
    movieBias = new float [TOTAL_MOVIES];
    for(int i = 0; i < TOTAL_MOVIES; i++) {
        check = pickrandom();
        movieBias[i] = check;
        assert(check != 0 && check < 10 && check > -10);
    }
    
    
    /* Initialize movie weights */
    Y = new float *[TOTAL_MOVIES];
    for(int i = 0; i < TOTAL_MOVIES; i++) {
        Y[i] = new float [FEATURES];
        for(int j = 0; j < FEATURES; j++) {
            check = pickrandom();
            Y[i][j] = check;
            assert(check != 0 && check < 10 && check > -10);
        }
    }
    
    /* Initialize sum of movie weights */
    sumY = new float *[TOTAL_USERS];
    for(int i = 0; i < TOTAL_USERS; i++) {
        sumY[i] = new float [FEATURES];
        for(int j = 0; j < FEATURES; j++) {
            check = pickrandom();
            sumY[i][j] = 0.0;
        }
    }
    
    
    /* Compute norms */
    movieCountByUser = new int[TOTAL_USERS];
    norms = new float[TOTAL_USERS];
    
    for(int i = 0; i < TOTAL_USERS; i++) {
        movieCountByUser[i] = 0;
    }
    
    for(int i = 0; i < rows; i++) {
        movieCountByUser[train_data[4 * i] - 1] += 1;
    }
    
    for(int i = 0; i < TOTAL_USERS; i++) {
        float curr = (float) movieCountByUser[i];
        norms[i] = sqrt(curr);
    }
    printf("Done initializing\n\n");
}



float predictRatingPLUS(int user, int movie) {
    
    if(debug) {
        printf("\n\npredictRating has been called!\n");
    }
    float sum = 0.0;
    for(int i = 0; i < FEATURES; i++) {
        if(debug) {
            printf("userFeatures[user - 1][i]: %f\n", userFeatures[user - 1][i]);
            printf("movieFeatures[movie - 1][i]: %f\n", movieFeatures[movie - 1][i]);
            printf("sumY[user - 1][i]: %f\n", sumY[user - 1][i]);
        }
        sum += userFeatures[user - 1][i] * movieFeatures[movie - 1][i] + norms[user - 1] * sumY[user - 1][i];
    }
    if(debug) {
        printf("userBias[user - 1]: %f\n", userBias[user - 1]);
        printf("movieBias[movie - 1]: %f\n", movieBias[movie - 1]);
    }
    
    return sum + GLOBALAVG + userBias[user - 1] + movieBias[movie - 1];
}


void computeSVDPlusPlus(int num_features, int epochs, int* train_data, int* probe_data, long size) {
    FEATURES = num_features;
    initialize(train_data, size);
    
    int user, movie, rating, *dataArray = train_data, userVal, movieVal;
    float *temp_sum, error, userBiasVal, movieBiasVal, start, end, sum, oldTrainRMSE = 2.0, newTrainRMSE = 2.0, newProbeRMSE = 2.0, oldProbeRMSE= 2.0;
    vector<int> moviesRatedByCurrUser;
    
    temp_sum = new float[FEATURES];
    
    int epoch_trained = 0;
    while(epoch_trained < epochs) {
        printf("Starting Epoch %d!\n", epoch_trained);
        start = clock();
        
        int prev_user = 1, userCount = 0;
        
        
        for(int f = 0; f < FEATURES; f++) {
            temp_sum[f] = 0.0;
        }
            
        /* Loop through all data points */
        for(int i = 0; i < size; i++) {
            user = dataArray[4 * i];
            movie = dataArray[4 * i + 1];
            rating = dataArray[4 * i + 3];
            
            /* Get error */
            error = rating - predictRatingPLUS(user, movie);
            
            /* Store  */
            userBiasVal = userBias[user - 1];
            movieBiasVal = movieBias[movie - 1];
            
            /* Tune biases */
            movieBias[movie - 1] += LRATE_M * (error - REG_M * movieBiasVal);
            userBias[user - 1] += LRATE_U * (error - REG_U * userBiasVal);
            
            /* If user has changed */
            if(prev_user == user) {
                userCount++;
                moviesRatedByCurrUser.push_back(movie);
            } else {
                userCount = 1;
                moviesRatedByCurrUser.clear();
                moviesRatedByCurrUser.push_back(movie);
            }
            
            /* Iteration of stochastic gradient descent */
            for(int k = 0; k < FEATURES; k++) {
                userVal = userFeatures[user - 1][k];
                movieVal = movieFeatures[movie - 1][k];
                
                userFeatures[user - 1][k] += LRATE_UF * (error * movieVal - REG_UF * userVal);
                movieFeatures[movie - 1][k] += LRATE_MF * (error * (userVal + norms[user - 1] * sumY[user - 1][k]) - REG_MF * movieVal);
                
                temp_sum[k] += (error * norms[user - 1] * movieVal);
                
                
                if(userCount == movieCountByUser[user - 1]) {
                    float totalSum = 0.0;
                    for(int j = 0; j < movieCountByUser[user-1]; j++) {
                        float *currY = Y[moviesRatedByCurrUser.at(j) - 1];
                        
                        float old = currY[k];
                        currY[k] += LRATE_W * (temp_sum[k] - REG_Y * currY[k]);
                        totalSum += (currY[k] - old);
                    }
                    sumY[user - 1][k] += totalSum;
                }
            }
            
            if(userCount == movieCountByUser[user - 1]) {
                for(int z = 0; z < FEATURES; z++) {
                    temp_sum[z] = 0.0;
                }
            }
            
            prev_user = user;
            
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
        
        if(oldProbeRMSE - newProbeRMSE < 0.00005){
            fprintf(stderr, "Probe RMSE drop is miniscule. Training done.\n");
            break;
        }
        epoch_trained++;
    }
    
    delete []movieCountByUser;
    
    for(int i = 0; i < TOTAL_MOVIES; i++) {
        delete Y[i];
    }
    delete [] Y;
    delete [] temp_sum;
}










