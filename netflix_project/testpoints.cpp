//
//  testpoints.cpp
//  netflix_project
//
//  Created by Connor Lee on 4/23/15.
//  Copyright (c) 2015 Connor Lee. All rights reserved.
//

#include "testpoints.h"

testPoint::testPoint() {
    userId = 0;
    movieId = 0;
    dates = 0;
    ratings = 0;
}

testPoint::testPoint(int user, int movie, int date, int rating) {
    userId = user;
    movieId = movie;
    dates = date;
    ratings = rating;
}

int testPoint::getUser() {
    return userId;
}

int testPoint::getMovie() {
    return movieId;
}

int testPoint::getDate() {
    return dates;
}

int testPoint::getRating() {
    return ratings;
}



void testPoint::setUser(int user) {
    userId = user;
}

void testPoint::setMovie(int movie) {
    movieId = movie;
}

void testPoint::setDate(int date) {
    dates = date;
}

void testPoint::setRating(int new_rating) {
    ratings = new_rating;
}