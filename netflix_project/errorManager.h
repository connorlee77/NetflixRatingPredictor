//
//  errorManager.h
//  netflix_project
//
//  Created by Connor Lee on 4/26/15.
//  Copyright (c) 2015 Connor Lee. All rights reserved.
//

#ifndef __netflix_project__errorManager__
#define __netflix_project__errorManager__

#include <stdlib.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "svd.h"

#define qualInFile "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/file5binary.bin"

#define qualOutFile "/Users/roshanagrawal/Documents/Caltech/Smore\ Year/Third\ Term/CS156b/UMRatingPredictor/netflix_split_data/qualOut.dta"

//#define qualDataFile "/Users/ConnorLee/Desktop/netflix/file5.dta"


void predictQual();
#endif /* defined(__netflix_project__errorManager__) */
