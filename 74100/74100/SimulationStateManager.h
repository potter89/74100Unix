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
    
    int _numbSubscribers = 0;
    std::vector<DataSubscriber*> _dataSubscribers;
    
    int getNumbAttachedSubscribers();
    
    //setters of _simdata
    void setSimulationData(Population * population, int & i_maxGenerations, long double & tau, std::vector<long double> & payoffMatrix);
    void incCurrentGeneration();
    
    //getters of _simdata
    Population * getPopulation();
    int * getMaxGenerations();
    long double * getTau();
    std::vector<long double> * getPayoffMatrix();

    
    //setup subs
    void attachDataSubscriber(DataSubscriber * newSub);
    void detatchDataSubscriber(DataSubscriber * newSub);
    void notifyDataSubscribers();
    
    //simulation changes updating functions
    void incrementCooperativeActions();
    void resetStateForNextGeneration();
    
};

#endif /* defined(___4100Unix__SimulationStateManager__) */
