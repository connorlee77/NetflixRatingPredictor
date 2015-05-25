//
//  main.cpp
//  dataPreProcess
//
//  Created by Roshan Agrawal on 4/30/15.
//  Copyright (c) 2015 Roshan Agrawal. All rights reserved.
//

#include <iostream>
#include "split_set.h"
#include "averages.h"
#include "binaryPreProcess.h"
#include <time.h>


int main(int argc, const char * argv[]) {

    float start, end;
    double duration;
    
    long BASE_SIZE = 94362233;
    long ALL_SIZE = 102416306;
    int TOTAL_USERS = 458293;
    int TOTAL_MOVIES = 17770;
    
    start = clock();
    
    splitDataSet();
    writeArrayToBinary(file123, file123Binary);
    writeArrayToBinary(file1234, file1234Binary);
    
    end = clock();
    
    duration=(end-start)/CLOCKS_PER_SEC;
    printf("Preprocessing data took %f seconds\n",duration);
    
    
    return 0;
}
