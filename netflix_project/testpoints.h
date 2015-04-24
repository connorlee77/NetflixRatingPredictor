//
//  testpoints.h
//  netflix_project
//
//  Created by Connor Lee on 4/23/15.
//  Copyright (c) 2015 Connor Lee. All rights reserved.
//

#ifndef __netflix_project__testpoints__
#define __netflix_project__testpoints__

#include <stdio.h>
#include <stdlib.h>

class testPoint{

private:
    
    int userId;
    int movieId;
    int ratings;
    int dates;
    
public:
    testPoint();
    testPoint(int user, int movie, int date, int rating);
    
    int getUser();
    int getMovie();
    int getDate();
    int getRating();
    
    void setUser(int user);
    void setMovie(int movie);
    void setDate(int date);
    void setRating(int new_rating);
    
};


#endif /* defined(__netflix_project__testpoints__) */
