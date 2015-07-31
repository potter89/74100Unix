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
    
    int maxGenerations;
	long double tauTag;
	long double tauStrat;
	long double noiseStrat;
	long double noiseTag;

    std::vector<long double> payoffMatrix;
    Population * population;
    
    int currentGeneration = -1;
    int numbCooperativeActions = 0;
};

#endif /* defined(___4100Unix__SimulationData__) */