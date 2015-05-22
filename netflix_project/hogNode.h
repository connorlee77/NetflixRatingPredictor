//
//  hogNode.h
//  netflix_project
//
//  Created by Connor Lee on 5/21/15.
//  Copyright (c) 2015 Connor Lee. All rights reserved.
//

#ifndef __netflix_project__hogNode__
#define __netflix_project__hogNode__

#include <stdio.h>

class hogNode {
    
private:
    float LRATE, LEARNING_A, LEARNING_D;
    int start;
    int stop;

public:
    hogNode(float LRATE, float LEARNING_A, float LEARNING_D, int start, int stop);
    float getLRATE();
    float getA();
    float getD();
    int getStart();
    int getStop();
};

#endif /* defined(__netflix_project__hogNode__) */
