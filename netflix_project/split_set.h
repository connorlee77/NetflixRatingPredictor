//
//  split_set.h
//  netflix_project
//
//  Created by Connor Lee on 4/16/15.
//  Copyright (c) 2015 Connor Lee. All rights reserved.
//

#ifndef __netflix_project__split_set__
#define __netflix_project__split_set__
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#define FILE_PATH "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/"

class split_set{
    
private:
    
    std::string guide;
    std::string data_set;
    int curr_line;
    std::string files[5] = {"file1.dta", "file2.dta", "file3.dta", "file4.dta", "file5.dta"};
    
public:
    split_set(std::string guide, std::string data_set);
    void parse_guide_data_set();
    std::string get_path(std::string name);
};


#endif /* defined(__netflix_project__split_set__) */
