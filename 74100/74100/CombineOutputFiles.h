//
//  CombineOutputFiles.h
//  74100Unix
//
//  Created by Élvio Abreu on 30/06/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//

#ifndef ___4100Unix__CombineOutputFiles__
#define ___4100Unix__CombineOutputFiles__

#include "string"
#include <fstream> // file creation, writing
#include <iostream> // std::cout
#include <vector>
#include <stdlib.h> // atoi
#include <list>

void combineOutputFiles(std::string folderPath, int bIncrement);
void multipleCombineOutputFiles(int bIncrement);
int calculateAverage(std::list<int> & vec);

#endif /* defined(___4100Unix__CombineOutputFiles__) */
