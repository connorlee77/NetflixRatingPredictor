
//  svd.cpp
//  netflix_project
//
//  Created by Connor Lee on 4/25/15.
//  Copyright (c) 2015 Connor Lee. All rights reserved.
//

#include "svdplus.h"

const int NUMTHREADS = 7;
int DATASIZE;
int NUMFEATURES;
int NUMPARAMS = TOTAL_USERS + TOTAL_MOVIES;

const float GLOBAL_AVG_SET1 = 3.608609;
const float GLOBAL_AVG_SET2 = 3.608859;
const long IVsize = IIIsize + PROBE_SIZE;

const int TOTAL_USERS = 458293;
const int TOTAL_MOVIES = 17770;
const int TOTAL_DAYS = 2243;
float GLOBAL_AVERAGE;

float LRATE_MF;
float LRATE_BASE_MF = 0.018;
const float TAU = 8;
const float C_FACTOR = 0.02;
float REG_MF = 0.0015;

float LRATE_UF;
float LRATE_BASE_UF = 0.018;
float REG_UF = 0.0015;

float LEARNING_A;
float LEARNING_A_BASE = 0.01;
float C_FACTOR_A = 0.01;
float REG_A = 0.007;

float LEARNING_D;
float LEARNING_D_BASE = 0.01;
const float C_FACTOR_D = 0.01;
float REG_D = 0.012;

float LRATE_W;
float LRATE_W_BASE = 0.004;
float REG_Y = 0.005;
float C_FACTOR_W = 0.01;

float **user_feature_table;
float *user_rating_deviation_table;

float **movie_feature_table;
float *movie_rating_deviation_table;

float **user_implicit_vector_sum_table;
float **movie_implicit_vector_table;
int *user_ratings_count_noqual_table;
int *user_ratings_count_withqual_table;
int **user_movies_table;
float *user_norms_table;

int *dataArray;

float * global_deviations = new float[NUMPARAMS];
float * global_variances= new float[NUMPARAMS];
float * global_hessians= new float[NUMPARAMS];
float * global_finite_variances= new float[NUMPARAMS];
float * global_times= new float[NUMPARAMS];

float * new_global_deviations = new float[NUMPARAMS];
float * new_global_variances = new float[NUMPARAMS];
float * new_global_hessians = new float[NUMPARAMS];
float * new_global_finite_variances = new float[NUMPARAMS];
float * new_global_times = new float[NUMPARAMS];

bool printVectorInitInfo = 0;
bool printPredictionInfo = 0;
bool printTrainRMSE = 0;

float getRandom() {
    return ((float) rand() / (RAND_MAX)) * 0.000001235f;
}

void initializeFeatureVectorsPlus() {
    GLOBAL_AVERAGE = GLOBAL_AVG_SET1;
    
    srand (static_cast <unsigned> (time(0)));
    
    /*
     * Initialize user_feature_table
     */
    user_feature_table = new float *[TOTAL_USERS];
    
    float randomAcc;
    for(int i = 0; i < TOTAL_USERS; i++) {
        user_feature_table[i] = new float[NUMFEATURES];
        
        for(int j = 0; j < NUMFEATURES; j++) {
            randomAcc = getRandom();
            user_feature_table[i][j] = randomAcc;
        }
        
    }
    /*
     * End initialization of user_feature_table
     */
    
    
    /*
     * Initialize user_implicit_vector_sum_table
     */
    user_implicit_vector_sum_table = new float*[TOTAL_USERS];
    for(int i = 0; i < TOTAL_USERS; i++) {
        user_implicit_vector_sum_table[i] = new float[NUMFEATURES];
    }
    /*
     * End initialization of user_implicit_vector_sum_table
     */
    
    
    /*
     * Initialize user_ratings_count_noqual_table
     */
    user_ratings_count_noqual_table = new int[TOTAL_USERS];
    
    for(int i = 0; i < DATASIZE; i++) {
        user_ratings_count_noqual_table[dataArray[4 * i] - 1]++;
    }
    /*
     * End initialization of user_ratings_count_noqual_table
     */
    
    
    /*
     * Initialize user_movies_table and user_ratings_count_withqual_table
     */
    user_movies_table = new int*[TOTAL_USERS];
    user_ratings_count_withqual_table = new int[TOTAL_USERS];
    
    int numMovies;
    
    ifstream userMovieStream;
    userMovieStream.open(userMovieFrequenciesFile, ios::in|ios::binary);
    if(!userMovieStream.is_open()) {
        fprintf(stderr, "user rating deviation binary file was not opened!\n");
        exit(0);
    }
    userMovieStream.seekg (0, ios::beg);
    
    for(int i = 0; i < TOTAL_USERS; i++){
        userMovieStream.read(reinterpret_cast<char*> (&numMovies), sizeof(int));
        user_ratings_count_withqual_table[i] = numMovies;
        user_movies_table[i] = new int[numMovies];
        userMovieStream.read(reinterpret_cast<char*> (user_movies_table[i]), sizeof(int) * numMovies);
    }
    userMovieStream.close();
    /*
     * End initialization of user_ratings_count_noqual_table and user_ratings_count_withqual_table
     */
    
    /*
     * Initialize user_norms_table
     */
    user_norms_table = new float[TOTAL_USERS];
    
    for(int i = 0; i < TOTAL_USERS; i++) {
        float curr = (float) user_ratings_count_withqual_table[i];
        user_norms_table[i] = 1.0/sqrt(curr);
    }
    /*
     * End initialization of user_norms_table
     */


    /*
     * Initialize user_rating_deviation_table
     */
    user_rating_deviation_table = new float[TOTAL_USERS];
    /*
     * End initialization user_rating_deviation_table
     */
    
    
    /*
     * Initialize movie_feature_table
     */
    movie_feature_table = new float *[TOTAL_MOVIES];
    for(int i = 0; i < TOTAL_MOVIES; i++) {
        movie_feature_table[i] = new float[NUMFEATURES];
        
        for(int j = 0; j < NUMFEATURES; j++) {
            randomAcc = (rand() % 14000 + 2000) * -0.000001235f;
            movie_feature_table[i][j] = randomAcc;
        }
    }
    /*
     * End initialization of movie_feature_table
     */
    
    /*
     * Initialize movie_implicit_vector_table
     */
    movie_implicit_vector_table = new float *[TOTAL_MOVIES];
    for(int i = 0; i < TOTAL_MOVIES; i++) {
        movie_implicit_vector_table[i] = new float [NUMFEATURES];
    }
    /*
     * End initialization of movie_implicit_vector_table
     */
        
    /*
     * Initialize movie_rating_deviation_table
     */
    movie_rating_deviation_table = new float[TOTAL_MOVIES];
}

float predictRatingPLUS(int user, int movie) {
    float sum = GLOBAL_AVERAGE;
    
    /*
     * Include prediction using user and movie features
     */
    for(int i = 0; i < NUMFEATURES; i++) {
        sum += (movie_feature_table[movie - 1][i] * (user_feature_table[user - 1][i] + user_norms_table[user - 1] * user_implicit_vector_sum_table[user - 1][i]));
    }
    
    sum += user_rating_deviation_table[user - 1] + movie_rating_deviation_table[movie - 1];
    return sum;
}

float predictRatingAdjusted(int user, int movie, float * deviations) {
    float sum = GLOBAL_AVERAGE;
    
    /*
     * Include prediction using user and movie features
     */
    for(int i = 0; i < NUMFEATURES; i++) {
        sum += (movie_feature_table[movie - 1][i] * (user_feature_table[user - 1][i] + user_norms_table[user - 1] * user_implicit_vector_sum_table[user - 1][i]));
    }
    
    sum += (user_rating_deviation_table[user - 1] + deviations[user - 1]) + (movie_rating_deviation_table[movie - 1] + deviations[TOTAL_USERS + movie - 1]);
    return sum;
}

void *hogwildPlus(void *rates) {
    int user, movie, date, rating, currMovie, currIndex;
    float error, adjustedError, userVal, movieVal, curr_norm, curr_hessian, origDev, adjustDev, learningRate;
    
    float * deviations = new float[NUMPARAMS];
    float * variances = new float[NUMPARAMS];
    float * hessians = new float[NUMPARAMS];
    float * finite_variances = new float[NUMPARAMS];
    float * times = new float[NUMPARAMS];
    
    memcpy(deviations, global_deviations, NUMPARAMS * sizeof(float));
    memcpy(variances, global_variances, NUMPARAMS * sizeof(float));
    memcpy(hessians, global_hessians, NUMPARAMS * sizeof(float));
    memcpy(finite_variances, global_finite_variances, NUMPARAMS * sizeof(float));
    memcpy(times, global_times, NUMPARAMS * sizeof(float));
    
    hogNode *curr = (hogNode *)rates;
    
    int prev_user = dataArray[4 * curr->getStart()], movieCount = 0;
    
    for(int j = curr->getStart(); j < curr->getStop(); j++) {
        user = dataArray[4 * j];
        movie = dataArray[4 * j + 1];
        date = dataArray[4 * j + 2];
        rating = dataArray[4 * j + 3];
        
        int USER_DEV_INDEX = user - 1;
//        printf("user index: %d\n", USER_DEV_INDEX);
        int MOVIE_DEV_INDEX = TOTAL_USERS + movie - 1;
//        printf("movie index: %d\n", MOVIE_DEV_INDEX);
        
        if(prev_user == user) {
            movieCount++;
        } else {
            movieCount = 1;
        }
        
        error = rating - predictRatingPLUS(user, movie);
        adjustedError = rating - predictRatingAdjusted(user, movie, deviations);

        //Train user rating deviation
        currIndex = USER_DEV_INDEX;
        origDev = 2 * error - REG_A * user_rating_deviation_table[user - 1];
//        printf("error: %f\n", origDev);
        adjustDev = 2 * adjustedError - REG_A * (user_rating_deviation_table[user - 1] + deviations[currIndex]);
//        printf("adjusted error: %f\n", adjustDev);
        
        curr_hessian = abs((origDev - adjustDev)/deviations[currIndex]);
        
//        printf("Sample User hessian: %f\n", curr_hessian);
        
        if(abs(origDev - deviations[currIndex]) > 2 * pow(variances[currIndex] - pow(deviations[currIndex],2),0.5) || (curr_hessian - hessians[currIndex]) > 2 * pow(finite_variances[currIndex] - pow(hessians[currIndex], 2), 0.5)){
            times[currIndex]++;
        }
        
        deviations[currIndex] = (1 - 1.0/times[currIndex]) * deviations[currIndex] + origDev * 1.0/times[currIndex];
        variances[currIndex] = (1 - 1.0/times[currIndex]) * variances[currIndex] + pow(origDev, 2) * 1.0/times[currIndex];
        hessians[currIndex] = (1 - 1.0/times[currIndex]) * hessians[currIndex] + curr_hessian * 1.0/times[currIndex];
        finite_variances[currIndex] = (1 - 1.0/times[currIndex]) * finite_variances[currIndex] + curr_hessian * curr_hessian * 1.0/times[currIndex];
        
        times[currIndex] = times[currIndex] * (1 - (pow(deviations[currIndex], 2)/variances[currIndex])) + 1;
        
        learningRate = (hessians[currIndex]/finite_variances[currIndex]) * pow(deviations[currIndex], 2)/(variances[currIndex]);
        
//        if(j % 10000000 == 0)
//            printf("Sample User Learning rate: %f\n", learningRate);
        
        user_rating_deviation_table[user - 1] += learningRate * origDev;
        
        //Train movie rating deviation
        currIndex = MOVIE_DEV_INDEX;
        origDev = 2 * error - REG_D * movie_rating_deviation_table[movie - 1];
        adjustDev = 2 * adjustedError - REG_D * (user_rating_deviation_table[movie - 1] + deviations[currIndex]);
        
        curr_hessian = abs((origDev - adjustDev)/deviations[currIndex]);
        
        if(abs(origDev - deviations[currIndex]) > 2 * pow(variances[currIndex] - pow(deviations[currIndex],2),0.5) || (curr_hessian - hessians[currIndex]) > 2 * pow(finite_variances[currIndex] - pow(hessians[currIndex], 2), 0.5)){
            times[currIndex]++;
        }
        
        deviations[currIndex] = (1 - 1.0/times[currIndex]) * deviations[currIndex] + origDev * 1.0/times[currIndex];
        variances[currIndex] = (1 - 1.0/times[currIndex]) * variances[currIndex] + pow(origDev, 2) * 1.0/times[currIndex];
        hessians[currIndex] = (1 - 1.0/times[currIndex]) * hessians[currIndex] + curr_hessian * 1.0/times[currIndex];
        finite_variances[currIndex] = (1 - 1.0/times[currIndex]) * finite_variances[currIndex] + curr_hessian * curr_hessian * 1.0/times[currIndex];
        
        times[currIndex] = times[currIndex] * (1 - (pow(deviations[currIndex], 2)/variances[currIndex])) + 1;
        
        learningRate = (hessians[currIndex]/finite_variances[currIndex]) * pow(deviations[currIndex], 2)/(variances[currIndex]);
        
//        if(j % 10000000 == 0)
//            printf("Sample movie Learning rate: %f\n\n", learningRate);
        
        movie_rating_deviation_table[movie - 1] += learningRate * origDev;
        
        //Train user and movie features
        curr_norm = user_norms_table[user - 1];
        for(int i = 0; i < NUMFEATURES; i++){
            userVal = user_feature_table[user - 1][i];
            movieVal = movie_feature_table[movie - 1][i];
            
            if(movieCount == user_ratings_count_noqual_table[user - 1] || j == curr->getStop() - 1){
                user_implicit_vector_sum_table[user - 1][i] = 0;
                for(int j = 0; j < user_ratings_count_withqual_table[user - 1]; j++){
                    currMovie = user_movies_table[user - 1][j];
                    float * currImplicitVector = &movie_implicit_vector_table[currMovie - 1][i];
                    *currImplicitVector += LRATE_W_BASE * (movieVal * curr_norm * error - REG_Y * *currImplicitVector);
                    user_implicit_vector_sum_table[user - 1][i] += *currImplicitVector;
                }
            }
            
            user_feature_table[user - 1][i] += LRATE_UF * (error * movieVal - REG_UF * userVal);
            movie_feature_table[movie - 1][i] += LRATE_MF * (error * (userVal + curr_norm * user_implicit_vector_sum_table[user - 1][i]) - REG_MF * movieVal);
        }
    }
    
    for(int i = 0; i < NUMPARAMS; i++){
        new_global_deviations[i] += deviations[i];
        new_global_variances[i] += variances[i];
        new_global_hessians[i] += hessians[i];
        new_global_finite_variances[i] += finite_variances[i];
        new_global_times[i] += times[i];
    }
    
    delete [] deviations;
    delete [] variances;
    delete [] hessians;
    delete [] finite_variances;
    delete [] times;
    
    return 0;
}

void computeSVDPlusPlus(int num_features, int epochs, int* train_data, int* probe_data, long data_size) {
    NUMFEATURES = num_features;
    dataArray = train_data;
    DATASIZE = (int) data_size;
    
    float start, end;
    float duration;
    
    random_device rd;     // only used once to initialise (seed) engine
    mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    uniform_int_distribution<int> uni(0, DATASIZE - 1); // guaranteed unbiased
    
    start = clock();
    initializeFeatureVectorsPlus();
    end = clock();
    duration=(end-start)/CLOCKS_PER_SEC;
    
    printf("Feature initialization took %f seconds\n", duration);
    
    float sum, error, adjustUser, adjustMovie, oldTrainRMSE = 2.0f, newTrainRMSE, oldProbeRMSE = 2.0f, newProbeRMSE, adjustLearn, deviation = 0, variance = 0;
    int user, movie, rating, date, randUser, randFeature, randMovie;
    
    for(int j = 0; j < 0.01 * DATASIZE; j++){
        int user = dataArray[4 * j];
        int movie = dataArray[4 * j + 1];
        int rating = dataArray[4 * j + 3];
        
        error = rating - predictRatingPLUS(user, movie);
        deviation += 2 * error;
        variance += pow(2 * error, 2);
    }
    
    
    
    printf("deviation: %f, variance: %f\n", deviation/(0.01 * DATASIZE), variance/(0.01 * DATASIZE));
    
    fill(global_times, global_times + NUMPARAMS, 50.0);
    fill(global_deviations, global_deviations + NUMPARAMS, 0.01 * deviation/(0.01 * DATASIZE));
    fill(global_variances, global_variances + NUMPARAMS, 0.01 * variance/(0.01 * DATASIZE));
    for(int k = 0; k < epochs; k++) {
        adjustLearn = (C_FACTOR / LRATE_BASE_UF) * ((float) k / TAU);
        LRATE_UF = LRATE_BASE_UF * (1 + adjustLearn) / (1 + adjustLearn + (float) (k * k) / TAU);
        
        adjustLearn = (C_FACTOR / LRATE_BASE_MF) * ((float) k / TAU);
        LRATE_MF = LRATE_BASE_MF * (1 + adjustLearn) / (1 + adjustLearn + (float) (k * k) / TAU);
        
        adjustLearn = (C_FACTOR/LRATE_W_BASE) * ((float) k / TAU);
        LRATE_W = LRATE_W_BASE * (1 + adjustLearn) / (1 + adjustLearn + (float) (k * k) / TAU);
        
        adjustLearn = (C_FACTOR_A / LEARNING_A_BASE) * ((float) k / TAU);
        LEARNING_A = LEARNING_A_BASE * (1 + adjustLearn) / (1 + adjustLearn + (float) (k * k) / TAU);
        
        adjustLearn = (C_FACTOR_D / LEARNING_D_BASE) * ((float) k / TAU);
        LEARNING_D = LEARNING_D_BASE * (1 + adjustLearn) / (1 + adjustLearn + (float) (k * k) / TAU);
        if(oldProbeRMSE < 0.94) {
            REG_UF = 0.08;
            REG_MF = 0.006;
            REG_A = 0.03;
            REG_D = 0.0025;
            REG_Y = 0.03;
            
            LRATE_BASE_MF = 0.003 * 0.9 * 0.9;
            LRATE_BASE_UF = 0.006 * 0.9 * 0.9;
            LEARNING_A_BASE = 0.003 * 0.9 * 0.9;
            LEARNING_D_BASE = 0.012 * 0.9 * 0.9;
            LRATE_W_BASE = 0.001 * 0.9 * 0.9;
        }
        
        start = clock();
        printf("Training epoch %d\n", k + 1);
        /*
         * Train on every data point
         */

        /* Hogwild here */
        std::vector<hogNode*> nodes(NUMTHREADS);
        
        pthread_t threads[NUMTHREADS];
        
        int starting = 0, ending = 0;
        
        for(int i = 0; i < NUMTHREADS; i++){
            starting = ending;
            ending = (i + 1) * DATASIZE/NUMTHREADS;
            
            nodes[i] = new hogNode(0, 0, 0, starting, ending);
            pthread_create(&threads[i], NULL, hogwildPlus, (void *) nodes[i]);
        }
        
        for(int i = 0; i < NUMTHREADS; i++){
            pthread_join(threads[i], NULL);
        }
        
        for(int i = 0; i < NUMTHREADS; i++){
            delete nodes[i];
        }
        
        for(int i = 0; i < NUMPARAMS; i++){
            global_deviations[i] = new_global_deviations[i]/NUMTHREADS;
            new_global_deviations[i] = 0;
            
            global_variances[i] = new_global_variances[i]/NUMTHREADS;
            new_global_variances[i] = 0;
            
            global_hessians[i] = new_global_hessians[i]/NUMTHREADS;
            new_global_hessians[i] = 0;
            
            global_finite_variances[i] = new_global_finite_variances[i]/NUMTHREADS;
            new_global_finite_variances[i] = 0;
            
            global_times[i] = new_global_times[i]/NUMTHREADS;
            new_global_times[i] = 0;
        }
        
        /*
         * Check to make sure magnitude of features aren't too large.
         */
        for(int i = 0; i < 10000; i++){
            randUser = rand() % TOTAL_USERS;
            randMovie = rand() % TOTAL_MOVIES;
            randFeature = rand() % NUMFEATURES;
            
            adjustUser = user_feature_table[randUser][randFeature];
            assert(adjustUser < 50 && adjustUser > -50);
            
            adjustMovie = movie_feature_table[randMovie][randFeature];
            assert(adjustMovie < 50 && adjustMovie > -50);
        }
        end = clock();
        duration=(end-start)/CLOCKS_PER_SEC;
        
        printf("Epoch %d took %f seconds\n",k + 1, duration);
        
        if(printTrainRMSE){
            sum = 0.0;
            for (int j = 0; j < DATASIZE; j++) {
                user = dataArray[4 * j];
                movie = dataArray[4 * j + 1];
                date = dataArray[4 * j + 2];
                rating = dataArray[4 * j + 3];
                sum += powf(rating - predictRatingPLUS(user, movie), 2);
            }
            
            newTrainRMSE = powf(sum/(DATASIZE), 0.5);
            
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
            date = probe_data[4 * j + 2];
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
    }
}