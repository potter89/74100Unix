//
//  SimulationData.h
//  74100Unix
//
//  Created by Elvio on 27/03/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//

#ifndef ___4100Unix__SimulationData__
#define ___4100Unix__SimulationData__

#include <vector>
#include "Agent.h"
#include "DataSubscriber.h"
#include <string>

class SimulationData
{
public:
    SimulationData();
    ~SimulationData();
    int _numbCooperativeActions = 0;
    std::vector<Agent> * _population;
    std::string _populationType;
    
    int _numbSubscribers = 0;
    std::vector<DataSubscriber*> _dataSubscribers;
};

#endif /* defined(___4100Unix__SimulationData__) */
