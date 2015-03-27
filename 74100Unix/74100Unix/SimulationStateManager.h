//
//  SimulationStateManager.h
//  74100Unix
//
//  Created by Elvio on 27/03/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//

#ifndef ___4100Unix__SimulationStateManager__
#define ___4100Unix__SimulationStateManager__

#include<vector>
#include "DataSubscriber.h"
#include "Agent.h"
#include "SimulationData.h"

class SimulationStateManager
{
    SimulationData _simData;
    
public:
    SimulationStateManager();
    SimulationStateManager(int c, int d);
    ~SimulationStateManager();
    
    int getNumbAttachedSubscribers();
    
    //setup simdata
    void setPopulationToSendOut(std::vector<Agent> * population);
    void setTypeToSendOut(std::string type);
    
    //setup subs
    void attachDataSubscriber(DataSubscriber * newSub);
    void detatchDataSubscriber(DataSubscriber * newSub);
    void notifyDataSubscribers();
    
    //simulation changes updating functions
    void incrementCooperativeActions();
    void resetStateForNextGeneration();
    
};

#endif /* defined(___4100Unix__SimulationStateManager__) */
