//
//  split_set.cpp
//  netflix_project
//
//  Created by Connor Lee on 4/16/15.
//  Copyright (c) 2015 Connor Lee. All rights reserved.
//

#include "split_set.h"

split_set::split_set(std::string plan, std::string data) {
    guide = get_path(plan);
    data_set = get_path(data);

    curr_line = 0;
}


std::string split_set::get_path(std::string name) {
    return FILE_PATH + name;
}

void split_set::parse_guide_data_set() {
    
    std::ifstream plan(guide);
    if(!plan.is_open()) {
        fprintf(stderr, "index file was not opened!");
    }
    
    std::ifstream data(data_set);
    if(!data.is_open()) {
        fprintf(stderr, "data file was not opened!");
    }
    
    std::ofstream file1;
    file1.open(get_path(files[0]), std::ios::app);
    if(!file1.is_open()) {
        fprintf(stderr, "file 1 was not opened!");
    }
    
    std::ofstream file2;
    file2.open(get_path(files[1]), std::ios::app);
    if(!file2.is_open()) {
        fprintf(stderr, "file 2 was not opened!");
    }
    
    std::ofstream file3;
    file3.open(get_path(files[2]), std::ios::app);
    if(!file3.is_open()) {
        fprintf(stderr, "file 3 was not opened!");
    }
    
    std::ofstream file4;
    file4.open(get_path(files[3]), std::ios::app);
    if(!file4.is_open()) {
        fprintf(stderr, "file 4 was not opened!");
    }
    
    std::ofstream file5;
    file5.open(get_path(files[4]), std::ios::app);
    if(!file5.is_open()) {
        fprintf(stderr, "file 5 was not opened!");
    }
    
    std::string set_str;
    std::string line;
    int set_num;
    int step = 0;
    
    while(std::getline(plan, set_str) && std::getline(data, line)) {
        step++;
        if(step % 100000 == 0) {
            printf("%d\n", step);
        }
            
        set_num = std::stoi(set_str);
        if(set_num == 1) {
            file1 << line << "\n";
        } else if(set_num == 2) {
            file2 << line << "\n";
        } else if (set_num == 3) {
            file3 << line << "\n";
        } else if(set_num == 4) {
            file4 << line << "\n";
        } else if (set_num == 5) {
            file5 << line << "\n";
        }
    }
    file1.close();
    file2.close();
    file3.close();
    file4.close();
    file5.close();
    plan.close();
    data.close();
}

