//
//  SimulationData.h
//  74100Unix
//
//  Created by Elvio on 27/03/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//

#ifndef ___4100Unix__SimulationData__
#define ___4100Unix__SimulationData__

#include "Population.h"

class SimulationData
{
    
    
public:
    SimulationData();
    ~SimulationData();
    
    int numbCooperativeActions = 0;
    Population * population;
};

#endif /* defined(___4100Unix__SimulationData__) */
