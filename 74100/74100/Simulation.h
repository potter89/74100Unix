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
#include "DataSubscriber.h"

//TODO:delete this, testing the observer thing. should be in factory!!!
#include "DataSubscriber.h"

class Simulation
{
    std::string s_linksSourcePath = "";
    int _maxGenerations;
    long double _tau;
    std::vector<long double> _payoffMatrix;
    std::vector<Agent> * agentsVectorPtr;
    
    Population * _population = NULL; //holds pointers to one of the various types of classes parented by pure virtual class Population
    
    SimulationStateManager stateManager;

    void oneShotInteraction(Agent & a, Agent & b);
    void gameTheoryGames(std::vector<Agent> & iPopulation);
    void evolutionaryGameTheory(std::vector<Agent> & iPopulation, long double & tau, std::vector<long double> & payoffMatrix);
    
    void setFittnessAndResetPayoffs(std::vector<Agent> & iPopulation);
    
    long double highestPayoffInMatrix(std::vector<long double> & payoffMatrix);
    long double lowestPayoffInMatrix(std::vector<long double> & payoffMatrix);
    long double maxFitnessDifference(unsigned long numbNeiborsA, unsigned long numbNeiborsB, long double maxPayoffPossible, long double minPayoffPossible); //maxFitnessDifference between two agents

	void printPercentageDone(int & iGeneration);
	int _percentage = 0; //how much percentage of work has been calculated already
	int _tenPercentGenerations = -1; //how many generations need to be calculated to achieve 10% of their total

public:
    Simulation(Population * population, int i_maxGenerations, long double tau, std::vector<long double> payoffMatrix, std::vector<DataSubscriber*> & dataSubscribers);
    ~Simulation();
    
    void runSimulation();
};

#endif /* defined(___4100Unix__Simulation__) */
