//
//  PThreadingManager.h
//  74100Unix
//
//  Created by Elvio on 31/03/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//

#ifndef ___4100Unix__PThreadingManager__
#define ___4100Unix__PThreadingManager__

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <vector>
#include "Simulation.h"

class PThreadingManager
{
public:
    PThreadingManager();
    ~PThreadingManager();

    void runMultiThreadedSimulations(std::vector <Simulation *> simulations);
};


#endif /* defined(___4100Unix__PThreadingManager__) */
