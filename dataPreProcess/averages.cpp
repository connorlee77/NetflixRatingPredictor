//
//  averages.cpp
//  dataPreProcess
//
//  Created by Roshan Agrawal on 4/30/15.
//  Copyright (c) 2015 Roshan Agrawal. All rights reserved.
//

#include "averages.h"

int TOTAL_USERS = 458293;
int TOTAL_MOVIES = 17770;
int TOTAL_DAYS = 2243;

double LAMBDA_ONE = 25;
double LAMBDA_TWO = 10;

void fillInMatrices(int* trainingData, int** userDataMatrix, int** movieDataMatrix){
    
    long BASE_SIZE = 94362233;
    int user, movie, rating;
    for(int i = 0; i < BASE_SIZE; i++){
        user = trainingData[i * 4];
        movie = trainingData[i * 4 + 1];
        rating = trainingData[i * 4 + 3];
        userDataMatrix[user - 1][movie - 1] = rating;
        movieDataMatrix[movie - 1][user - 1] = rating;
        
        if((i + 1) % 1000000 == 0) {
            printf("%d test points added to sparse matrices\n", i + 1);
        }
    }
}


float calculateGlobalAverage(int* trainingData){
    long BASE_SIZE = 94362233;
    int sum = 0;
    for(int i = 0; i < BASE_SIZE; i++){
        sum += trainingData[i * 4 + 3];
        //printf("%d\n", trainingData[i * 4 + 3]);
    }
    
    float average = (float) sum/BASE_SIZE;
    
    printf("%f\n", average);
    
    return average;
}

float* getMovieAverages(int** trainingDataMatrix, float globalAverage){
    
    float* movieAverages = new float[TOTAL_MOVIES];
    std::ofstream data;
    
    remove(outMovieAveragesBin);
    data.open(outMovieAveragesBin, ios::out|ios::binary);
    
    if(!data.is_open()) {
        fprintf(stderr, "userOffset was not opened!");
    }
    
    float sum;
    int count, val;
    
    for(int i = 0; i < TOTAL_MOVIES; i++){
        sum = 0.0;
        count = 0;
        for(int j = 0; j < TOTAL_USERS; j++){
            val = trainingDataMatrix[i][j];
            if(val != 0){
                sum += (float) (val - globalAverage);
                count++;
            }
        }
        float outVal = (float) sum/(count + LAMBDA_ONE);
        movieAverages[i] = outVal;
        data.write(reinterpret_cast<char*> (&outVal), sizeof(float));
        
        if((i + 1) % 1000 == 0) {
            printf("%d movie baselines calculated\n", i + 1);
            printf("Sample prediction: %f\n",outVal);
        }
    }
    
    data.close();
    
    return movieAverages;
}

void getUserOffsets(int** trainingDataMatrix, float globalAverage, float* movieAverages){
    ofstream data;
    
    remove(outUserOffsetBin);
    data.open(outUserOffsetBin, ios::out|ios::binary);
    
    if(!data.is_open()) {
        fprintf(stderr, "userOffset was not opened!");
    }
    
    float sum;
    int val, count;
    for(int i = 0; i < TOTAL_USERS; i++){
        sum = 0.0;
        count = 0;
        for(int j = 0; j < TOTAL_MOVIES; j++){
            val = trainingDataMatrix[i][j];
            if(val != 0){
                sum += (float) (val - globalAverage - movieAverages[j]);
                count++;
            }
        }
        
        float outVal = (float) sum/(count + LAMBDA_TWO);
        data.write(reinterpret_cast<char*> (&outVal), sizeof(float));
        
        if((i + 1) % 10000 == 0) {
            printf("%d user baselines calculated\n", i + 1);
            printf("Sample prediction: %f\n",outVal);
        }
    }
    
    data.close();
}

void getUserTimes(int* allData){
    ofstream data;
    
    remove(outUserTimeAverages);
    data.open(outUserTimeAverages, ios::out|ios::binary);
    
    if(!data.is_open()) {
        fprintf(stderr, "outUserTimeAverages was not opened!");
    }

    long All_SIZE = 102416306;
    
    int * userTimeSums = new int[TOTAL_USERS];
    int * userTimeCounts = new int[TOTAL_USERS];
    int user, date;
    float outVal;
    for(int i = 0; i < All_SIZE; i++){
        user = allData[i * 4];
        date = allData[i * 4 + 2];
        userTimeSums[user - 1] += date;
        userTimeCounts[user - 1]++;
    }
    
    for(int i = 0; i < TOTAL_USERS; i++){
        outVal = (float) userTimeSums[i]/userTimeCounts[i];
        data.write(reinterpret_cast<char*> (&outVal), sizeof(float));
        
        if((i + 1) % 10000 == 0) {
            printf("%d user time averages calculated\n", i + 1);
            printf("Sample average: %f\n",outVal);
        }
    }
    
    delete [] userTimeSums;
    delete [] userTimeCounts;
    
    data.close();
}

void getUserFrequencies(int* allData){
    ofstream data;
    
    remove(userFrequencies);
    data.open(userFrequencies, ios::out|ios::binary);
    
    if(!data.is_open()) {
        fprintf(stderr, "userFrequencies was not opened!");
    }
    
    long All_SIZE = 102416306;
    
    int **userTimeFrequencies = new int*[TOTAL_USERS];
    
    for (int i = 0; i < TOTAL_USERS; i++) {
        userTimeFrequencies[i] = new int[TOTAL_DAYS];
    }
    
    int user, date;
    int outVal = 0;
    int highVal = 0;
    for(int i = 0; i < All_SIZE; i++){
        user = allData[i * 4];
        date = allData[i * 4 + 2];
        userTimeFrequencies[user - 1][date - 1]++;
        
        if((i + 1) % 1000000 == 0) {
            printf("%d values inputted\n", i + 1);
        }
    }
    
    for(int i = 0; i < TOTAL_USERS; i++){
        for(int j = 0; j < TOTAL_DAYS; j++){
            outVal = userTimeFrequencies[i][j];
            data.write(reinterpret_cast<char*> (&outVal), sizeof(int));
            if(outVal > highVal){
                highVal = outVal;
            }
        }
        if((i + 1) % 1000000 == 0) {
            printf("%d user frequencies calculated\n", i + 1);
            printf("Sample frequency: %d\n", outVal);
        }
    }
    
    printf("The highest frequency encounter was %d\n", highVal);
    
    
    for (int i = 0; i < TOTAL_USERS; i++) {
        delete userTimeFrequencies[i];
    }
    delete [] userTimeFrequencies;
    
    data.close();
}