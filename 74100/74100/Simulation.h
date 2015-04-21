//
//  Simulation.h
//  74100Unix
//
//  Created by Elvio on 27/03/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//

#ifndef ___4100Unix__Simulation__
#define ___4100Unix__Simulation__

#include <string>
#include <vector>
#include "Population.h"
#include "SimulationStateManager.h"

//TODO:delete this, testing the observer thing. should be in factory!!!
#include "DataSubscriber.h"

class Simulation
{
    std::string s_linksSourcePath = "";
    int _maxGenerations;
    float _tau;
    std::vector<float> _payoffMatrix;
    std::vector<Agent> * agentsVectorPtr;
    
    Population * _population = NULL; //holds pointers to one of the various types of classes parented by pure virtual class Population
    
    SimulationStateManager stateManager;
    bool _hasAttachedSubscribers; //flag to enable skipping code related to graphics subscribers
    //TODO:delete this, testing the observer thing. should be in factory!!!
    DataSubscriber * dataSub = NULL;
    
    
    void oneShotInteraction(Agent & a, Agent & b);
    void gameTheoryGames(std::vector<Agent> & iPopulation);
    void evolutionaryGameTheory(std::vector<Agent> & iPopulation, float & tau, std::vector<float> & payoffMatrix);
    
    void setFittnessAndResetPayoffs(std::vector<Agent> & iPopulation);
    
    float highestPayoffInMatrix(std::vector<float> & payoffMatrix);
    float lowestPayoffInMatrix(std::vector<float> & payoffMatrix);
    float maxFitnessDifference(int numbNeiborsA, int numbNeiborsB, float maxPayoffPossible, float minPayoffPossible); //maxFitnessDifference between two agents
    //TODO: ^\ investigate int vs float
public:
    Simulation(Population * population, int i_maxGenerations, float tau, std::vector<float> payoffMatrix, std::vector<std::string> * dataSubscribers);
    ~Simulation();
    
    
    void runSimulation();
    void gatherInitialData();
    void gatherFinalData();
    
};

#endif /* defined(___4100Unix__Simulation__) */
