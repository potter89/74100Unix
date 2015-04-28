//
//  Simulation.cpp
//  74100Unix
//
//  Created by Elvio on 27/03/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//

#include "Simulation.h"

//Simulation*************************************************************************************************************************************Simulation

Simulation::Simulation(Population * population, int i_maxGenerations, float tau, std::vector<float> payoffMatrix, std::vector<DataSubscriber*> & dataSubscribers) :
//Initializing simulation parameters
_maxGenerations(i_maxGenerations),
_tau(tau),
_payoffMatrix(payoffMatrix)
{
    _population = population;
    
    //initializing stateManagerObject
    agentsVectorPtr = _population->getPopulationPtr();
    stateManager.setPopulationToSendOut(agentsVectorPtr);
    stateManager.setTypeToSendOut(_population->getType());
	if (!dataSubscribers.empty()){
		for (int i = 0; i < (int)dataSubscribers.size(); i++){
			stateManager.attachDataSubscriber(dataSubscribers[i]);
		}
	}
}
    Simulation::~Simulation(){}

void Simulation::runSimulation(){
    //EVOLVE -- EVOLVE -- EVOLVE -- EVOLVE -- EVOLVE -- EVOLVE -- EVOLVE -- EVOLVE -- EVOLVE -- EVOLVE -- EVOLVE -- EVOLVE -- EVOLVE -- EVOLVE
    //
    //make agents play eachother, calculate their fitness and decide if they should update their tag/strategy
    //Currently updates subscribers at the end of each generation
    //TODO: consider making vector of agents public? this doesnt look right
    //std::cout << "Simulation STARTED! Type: " << _population->getType() << " #Tag: " << _population->getNumberOfTags() << " b = " << _payoffMatrix[2] << " ######################" << std::endl;
    
    for (int i = 0; i < _maxGenerations; i++){
        gameTheoryGames(*agentsVectorPtr);
        setFittnessAndResetPayoffs(*agentsVectorPtr);
        if (stateManager.getNumbAttachedSubscribers() != 0) {
			stateManager.notifyDataSubscribers(); //update DataSubscribers
            stateManager.resetStateForNextGeneration(); //resets the variables who need to be reset each generation
			
		}
        evolutionaryGameTheory(*agentsVectorPtr, _tau, _payoffMatrix);
    }
}

void Simulation::oneShotInteraction(Agent & a, Agent & b){
    float payoffA = 0.0f; //payoff earned by A in this specific game
    float payoffB = 0.0f; //payoff earned by B in this specific game
    
    int aStrategyPlayingOther = a.strategy[b.tag];
    int bStrategyPlayingOther = b.strategy[a.tag];
    
    /**
     std::cout << b.getIndex() << " has strategy {";
     for (int x = 0; x < b.strategy.size(); x++){
     std::cout << b.strategy[x] << ", ";
     }
     std::cout << "} and tag: " << b.tag << " and current payoff: " << b.payoff << std::endl;
     //*/
    
    //_payoffMatrix[0] = C and C  3
    //_payoffMatrix[1] = C and D  0
    //_payoffMatrix[2] = D and C  5
    //_payoffMatrix[3] = D and D  1
    
    if (aStrategyPlayingOther == bStrategyPlayingOther){
        if (aStrategyPlayingOther == 0){
            //C C
            payoffA = _payoffMatrix[0];
            payoffB = _payoffMatrix[0];
			if (stateManager.getNumbAttachedSubscribers() != 0){
                stateManager.incrementCooperativeActions();
                stateManager.incrementCooperativeActions();
            }
        }
        else{
            //D D
            payoffA = _payoffMatrix[3];
            payoffB = _payoffMatrix[3];
        }
    }
    else{
        if (aStrategyPlayingOther == 0){
            //C D
            payoffA = _payoffMatrix[1];
            payoffB = _payoffMatrix[2];
			if (stateManager.getNumbAttachedSubscribers() != 0){
                stateManager.incrementCooperativeActions();
            }
        }
        else{
            //D C
            payoffA = _payoffMatrix[2];
            payoffB = _payoffMatrix[1];
			if (stateManager.getNumbAttachedSubscribers() != 0){
                stateManager.incrementCooperativeActions();
            }
        }
    }
    
    a.payoff += payoffA;
    b.payoff += payoffB;
    /**
     std::cout << a.getIndex() << " receives Payoff: " << payoffA << " totaling: " << a.payoff << ".";
     std::cout << "And " << b.getIndex() << " receives:" << payoffB << " totaling: " << b.payoff << "." << std::endl;
     //*/
}

//population plays games between neighbors, once
void Simulation::gameTheoryGames(std::vector<Agent> & iPopulation){
    Agent * currentAgent;
    int currentAgentIndex;
    std::vector<int> currentNeighbors;
    int nextItemInNeightbors;
    
    for (int i = 0; i < (int)iPopulation.size(); i++){ //for each agent in the population
        //TODO: change to pointers
        currentAgent = &iPopulation[i];
        currentAgentIndex = currentAgent->getIndex();
        currentNeighbors = currentAgent->neighbors;
        /**
         std::cout << "Agent " << currentAgent->getIndex() << "-----------------------------------------------------------------" << std::endl;
         std::cout << currentAgent->getIndex() << " has strategy {";
         for (int x = 0; x < currentAgent->strategy.size(); x++){
         //std::cout << currentAgent->strategy[x] << ", ";
         }
         std::cout << "} and tag: " << currentAgent->tag << " and current payoff: " << currentAgent->payoff << std::endl;
         //*/
        
        for (int ii = 0; ii < (int)(iPopulation[i].neighbors.size()); ii++){ // go through his neighbors
            nextItemInNeightbors = currentNeighbors[ii];
            if (currentAgentIndex < nextItemInNeightbors){ //if his index is lower than their's
                oneShotInteraction(*currentAgent, iPopulation[nextItemInNeightbors]);//play a oneshot game with neighbor
            }
        }

    }
}

//sets fitness to the accumulated payoff of the generation and sets accPayoff to 0
void Simulation::setFittnessAndResetPayoffs(std::vector<Agent> & iPopulation){
    for (int i = 0; i < (int)iPopulation.size(); i++){ //for each agent in the population
        iPopulation[i].fitness = iPopulation[i].payoff; //set fitness = accumulatedpayoff
        iPopulation[i].payoff = 0.0f; //clear payoff, to set agent for the next generation
    }
}
//returns the highest payoff possible from the payoffMatrix
float Simulation::highestPayoffInMatrix(std::vector<float> & payoffMatrix){
    float max = std::numeric_limits<float>::min();
    for (float i : payoffMatrix){
        if (i > max) {
            max = i;
        }
    }
    return max;
}
//returns the lowest payoff possible from the payoffMatrix
float Simulation::lowestPayoffInMatrix(std::vector<float> & payoffMatrix){
    float min = std::numeric_limits<float>::max();
    for (float i : payoffMatrix){
        if (i < min) {
            min = i;
        }
    }
    return min;
}

float Simulation::maxFitnessDifference(int numbNeiborsOfA, int numbNeiborsOfB, float maxPayoffPossible, float minPayoffPossible){
    // highest number of neighbors (between agents A and B) times the highest payoff - lowest number of neighbors (from A and B) times the lowest possible payoff
    if (numbNeiborsOfA > numbNeiborsOfB){
        return numbNeiborsOfA * maxPayoffPossible - numbNeiborsOfB * minPayoffPossible;
    }
    else{
        return numbNeiborsOfB * maxPayoffPossible - numbNeiborsOfA * minPayoffPossible;
    }
}

void Simulation::evolutionaryGameTheory(std::vector<Agent> & iPopulation, float & tau, std::vector<float> & payoffMatrix){
    //IMP: test all of this again!!!!!!!
    //TODO: use a better random gen
    
    float aux_Hi_Payoff = highestPayoffInMatrix(payoffMatrix);
    float aux_Lo_Payoff = lowestPayoffInMatrix(payoffMatrix);
    
    srand(time(NULL)); //initialize random seed
    for (int i = 0; i < (int)iPopulation.size(); i++){ //for each agent in the population
        /**
         std::cout << "Agent: " << i << "-------------------------------------------------------------" << std::endl;
         std::cout << "Has      fit: " << iPopulation[i].fitness << " #Neigh: " << iPopulation[i].neighbors.size();
         std::cout << " s: ";
         for (int x = 0; x < iPopulation[i].strategy.size(); x++){
         std::cout << iPopulation[i].strategy[x] << ", ";
         }
         std::cout << std::endl;
         //*/
        int randomNumber = rand();
        
        //pick a random neighbor
        int randomIndex = randomNumber % iPopulation[i].neighbors.size(); //generates random number between 0 and sizeof vector neighbors;
        int randomNeighborIndex = iPopulation[i].neighbors[randomIndex]; //goes to that index to get the neighbors population index
        /**
         std::cout << "Chose: " << randomNeighborIndex << " fit: " << iPopulation[randomNeighborIndex].fitness << " #Neigh: " << iPopulation[randomNeighborIndex].neighbors.size();
         std::cout << " s: ";
         for (int x = 0; x < iPopulation[randomNeighborIndex].strategy.size(); x++){
         std::cout << iPopulation[randomNeighborIndex].strategy[x] << ", ";
         }
         std::cout << std::endl;
         //*/
        
        float p; //holds probability of imitating the other agent's strategy
        //p=(fitness_j-fitness_i)* (Diferenca maxima possivel entre fitness)
        p = (iPopulation[randomNeighborIndex].fitness - iPopulation[i].fitness) /
        (maxFitnessDifference((int)iPopulation[i].neighbors.size(), (int)iPopulation[randomNeighborIndex].neighbors.size(), aux_Hi_Payoff,aux_Lo_Payoff));
        //std::cout << "p = (" << iPopulation[randomNeighborIndex].fitness << "-" << iPopulation[i].fitness << ") / " << maxFitnessDifference(iPopulation[i].neighbors.size(), iPopulation[randomNeighborIndex].neighbors.size(), aux_Hi_Payoff, aux_Lo_Payoff) << std::endl;
        
        float random0till1; //float between 0.0 and 1.0, inclusive
        random0till1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        //std::cout << "p = " << p << " and random:" << random0till1 << std::endl;
        
        if (p >= random0till1){
            //ALWAYS imitates strategy
            iPopulation[i].strategy = iPopulation[randomNeighborIndex].strategy;
            /**
             std::cout << " COPIED strat!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl << "Now: ";
             for (int x = 0; x < iPopulation[i].strategy.size(); x++){
             std::cout << iPopulation[i].strategy[x] << ", ";
             }
             std::cout << std::endl;
            //*/
            //Imitates tag given a probability Tau
            random0till1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); //float between 0.0 and 1.0, inclusive
            //std::cout << "_tau = " << _tau << " and random:" << random0till1 << std::endl;
            if (_tau >= random0till1){
                iPopulation[i].tag = iPopulation[randomNeighborIndex].tag;
                //std::cout << " COPIED TAG@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
            }
        }
    }
}
