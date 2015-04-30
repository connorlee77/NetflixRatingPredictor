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

int main(int argc, const char * argv[]) {

    int **sparseMatrix = createSparseMatrix();
    double globalAverage = calculateGlobalAverage(sparseMatrix);
    
    printOutMovieAverage(sparseMatrix, globalAverage);
    printOutUserOffest(sparseMatrix, globalAverage);
    
    return 0;
}
