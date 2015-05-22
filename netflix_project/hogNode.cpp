//
//  hogNode.cpp
//  netflix_project
//
//  Created by Connor Lee on 5/21/15.
//  Copyright (c) 2015 Connor Lee. All rights reserved.
//

#include "hogNode.h"

hogNode::hogNode(float LRATE, float LEARNING_A, float LEARNING_D, int start, int stop) {
    this->LRATE = LRATE;
    this->LEARNING_A = LEARNING_A;
    this->LEARNING_D = LEARNING_D;
    this->start = start;
    this->stop = stop;
}

float hogNode::getLRATE() {
    return this->LRATE;
}

float hogNode::getA() {
    return this->LEARNING_A;
}

float hogNode::getD() {
    return this->LEARNING_D;
}

int hogNode::getStart() {
    return this->start;
}

int hogNode::getStop() {
    return this->stop;
}