//
//  TextUIManager.h
//  74100Unix
//
//  Created by Élvio Abreu on 11/05/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//

#ifndef ___4100Unix__TextUIManager__
#define ___4100Unix__TextUIManager__

#include <stdio.h>
#include <iostream>
#include <stdlib.h> //for exiting the program
#include "Factory.h" //for generating the various options
//#include <limits> //for the ignore of cin stream, on wront input

void handleUIRequest(Factory & factory);
void printOptions();

#endif /* defined(___4100Unix__TextUIManager__) */