//
//  main.cpp
//  netflix_project
//
//  Created by Connor Lee on 4/16/15.
//  Copyright (c) 2015 Connor Lee. All rights reserved.
//

#include <iostream>
#include "dataManager.h"






int main(int argc, const char * argv[]) {
    
    //test dataManager's make test point objects
    std::vector<testPoint*>* dataSet = fillTestPoints();
    printf("%d", dataSet -> at(1900000) -> getUser());
    
    return 0;
}
