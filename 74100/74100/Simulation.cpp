//
//  Simulation.cpp
//  74100Unix
//
//  Created by Elvio on 27/03/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//

#include "Simulation.h"

Simulation::Simulation(Population * population, int & i_maxGenerations, long double & tau, std::vector<long double> & payoffMatrix, std::vector<DataSubscriber*> & dataSubscribers) :
_maxGenerations(i_maxGenerations),
_tau(tau),
_payoffMatrix(payoffMatrix)
{
    //Initializing simulation information/data
    stateManager = SimulationStateManager();
    stateManager.setPopulation(population);
    agentsVectorPtr = stateManager.getPopulation()->getAgentsPtr();

    if (!dataSubscribers.empty()){
        for (int i = 0; i < (int)dataSubscribers.size(); i++){
            stateManager.attachDataSubscriber(dataSubscribers[i]);
        }
    }
    
    /**/ //print information at the start te the simulation
    std::cout << "Simulation created!" << std::endl;
    std::cout << "#Generations: "<< _maxGenerations << std::endl;
    std::cout << "#Tags: "<< stateManager.getPopulation()->getNumberOfTags() << std::endl;
    std::cout << "Tau: "<< _tau << std::endl;
    std::cout << "PayoffMatrix CC: "<< _payoffMatrix[0] << std::endl;
    std::cout << "PayoffMatrix CD: "<< _payoffMatrix[1] << std::endl;
    std::cout << "PayoffMatrix DC: "<< _payoffMatrix[2] << std::endl;
    std::cout << "PayoffMatrix DD: "<< _payoffMatrix[3] << std::endl;
    //TODO: print out subs as well
    //*/
    
}
Simulation::~Simulation(){}

void Simulation::runSimulation(){
    //make agents play eachother, calculate their fitness and decide if they should update their tag/strategy
    //Subscribers need to be updated at the end of each generation
    for (int i = 0; i < _maxGenerations; i++){
        gameTheoryGames(*agentsVectorPtr);
        setFittnessAndResetPayoffs(*agentsVectorPtr);
        if (stateManager.getNumbAttachedSubscribers() != 0) {
            stateManager.notifyDataSubscribers(); //update DataSubscribers
            stateManager.resetStateForNextGeneration(); //resets the variables who need to be reset each generation
        }
        evolutionaryGameTheory(*agentsVectorPtr, _tau, _payoffMatrix);
        printPercentageDone(i); //uncomment to show in console the % of generations completed
    }
}

void Simulation::oneShotInteraction(Agent & a, Agent & b){
    long double payoffA = 0.0f; //payoff earned by A in this specific game
    long double payoffB = 0.0f; //payoff earned by B in this specific game
    
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
         std::cout << "Agent " << currentAgent->getIndex() << "------------------------------------------" << std::endl;
         std::cout << currentAgent->getIndex() << " has strategy {";
         for (int x = 0; x < currentAgent->strategy.size(); x++){
         //std::cout << currentAgent->strategy[x] << ", ";
         }
         std::cout << "} and tag: " << currentAgent->tag << " and current payoff: " << currentAgent->payoff << std::endl; //*/
         
        
        for (unsigned int ii = 0; ii < (iPopulation[i].neighbors.size()); ii++){ // go through his neighbors
            nextItemInNeightbors = currentNeighbors[ii];
            if (currentAgentIndex < nextItemInNeightbors){ //if his index is lower than their's
                oneShotInteraction(*currentAgent, iPopulation[nextItemInNeightbors]);//play a oneshot game with neighbor
            }
        }
        
    }
}

//sets fitness to the accumulated payoff of the generation and sets accPayoff to 0
void Simulation::setFittnessAndResetPayoffs(std::vector<Agent> & iPopulation){
    for (unsigned int i = 0; i < iPopulation.size(); i++){ //for each agent in the population
        iPopulation[i].fitness = iPopulation[i].payoff; //set fitness = accumulatedpayoff
        iPopulation[i].payoff = 0.0f; //clear payoff, to set agent for the next generation
    }
}
//returns the highest payoff possible from the payoffMatrix
long double Simulation::highestPayoffInMatrix(std::vector<long double> & payoffMatrix){
    long double max = std::numeric_limits<long double>::min();
    for (long double i : payoffMatrix){
        if (i > max) {
            max = i;
        }
    }
    return max;
}
//returns the lowest payoff possible from the payoffMatrix
long double Simulation::lowestPayoffInMatrix(std::vector<long double> & payoffMatrix){
    long double min = std::numeric_limits<long double>::max();
    for (long double i : payoffMatrix){
        if (i < min) {
            min = i;
        }
    }
    return min;
}

long double Simulation::maxFitnessDifference(unsigned long numbNeiborsOfA, unsigned long numbNeiborsOfB, long double maxPayoffPossible, long double minPayoffPossible){
    // highest number of neighbors (between agents A and B) times the highest payoff - lowest number of neighbors (from A and B) times the lowest possible payoff
    if (numbNeiborsOfA > numbNeiborsOfB){
        return numbNeiborsOfA * maxPayoffPossible - numbNeiborsOfB * minPayoffPossible;
    }
    else{
        return numbNeiborsOfB * maxPayoffPossible - numbNeiborsOfA * minPayoffPossible;
    }
}

void Simulation::evolutionaryGameTheory(std::vector<Agent> & iPopulation, long double & tau, std::vector<long double> & payoffMatrix){
    
    long double aux_Hi_Payoff = highestPayoffInMatrix(payoffMatrix);
    long double aux_Lo_Payoff = lowestPayoffInMatrix(payoffMatrix);
    
    for (int i = 0; i < (int)iPopulation.size(); i++){ //for each agent in the population
        /**
        printf("Agent: %i -------------------------------------------------------------\n", i);
        printf("Has      fit: %Lf #Neigh: %i", iPopulation[i].fitness, (int)iPopulation[i].neighbors.size());
        printf(" tag: %i strat: ", iPopulation[i].tag);
        for (int x = 0; x < iPopulation[i].strategy.size(); x++) printf( "%d, ", iPopulation[i].strategy[x]); printf("\n"); //*/
        
        
        //pick a random neighbor
        int randomIndex = GlobalRandomGen::getInstance()->getRandomTillMax((unsigned int)iPopulation[i].neighbors.size()-1); //generates random number between 0 and sizeof vector neighbors, minus one as we want one of the indexes;
        int randomNeighborIndex = iPopulation[i].neighbors[randomIndex]; //goes to that index to get the neighbors population index
        /**
        printf("Chose: %d  fit: %Lf   #Neigh: %d  strat: ", randomNeighborIndex , iPopulation[randomNeighborIndex].fitness, (int)iPopulation[randomNeighborIndex].neighbors.size());
        for (int x = 0; x < iPopulation[randomNeighborIndex].strategy.size(); x++) printf("%d, ", iPopulation[randomNeighborIndex].strategy[x]); printf("\n"); //*/
        

        
        long double payoffDiff = iPopulation[randomNeighborIndex].fitness - iPopulation[i].fitness;
        
        if (payoffDiff > 0) { //only considers changing strategy(and tag) if the neighbor's payoff is better than his own
            
            long double p; //holds probability of imitating the other agent's strategy
            
            //p=(fitness_j-fitness_i) / (Diferenca maxima possivel entre fitness)
            p = (payoffDiff) /
            (maxFitnessDifference(iPopulation[i].neighbors.size(), iPopulation[randomNeighborIndex].neighbors.size(), aux_Hi_Payoff,aux_Lo_Payoff));
            //std::cout << "p = (" << iPopulation[randomNeighborIndex].fitness << "-" << iPopulation[i].fitness << ") / " << maxFitnessDifference(iPopulation[i].neighbors.size(), iPopulation[randomNeighborIndex].neighbors.size(), aux_Hi_Payoff, aux_Lo_Payoff) << std::endl;
            
            long double random0till1; //long double between 0.0 and 1.0, inclusive
            random0till1 = GlobalRandomGen::getInstance()->getRandomF0Till1();
            //printf("p = %Lf and random: %Lf\n", p, random0till1);
            
            if (p >= random0till1){
                //ALWAYS imitates strategy
                iPopulation[i].strategy = iPopulation[randomNeighborIndex].strategy;
                //printf("COPIED strat!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\nNow: ");

                //Imitates tag given a probability Tau
                random0till1 = GlobalRandomGen::getInstance()->getRandomF0Till1(); //long double between 0.0 and 1.0, inclusive
                //std::cout << "_tau = " << _tau << " and random:" << random0till1 << std::endl;
                if (_tau >= random0till1){
                    iPopulation[i].tag = iPopulation[randomNeighborIndex].tag;
                    //printf(" COPIED TAG@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
                }
            }
        }
    }
}

//every 10% of the generations done, prints in console the progress
void Simulation::printPercentageDone(int & iGeneration){
    
    if (_tenPercentGenerations == -1) _tenPercentGenerations = (_maxGenerations * 0.1);
    
    if (_percentage * _tenPercentGenerations == iGeneration){
        printf("%%%%  %%%%  %%%%  %%%%  -- Progress: %d%%  -- %%%%  %%%%  %%%%  %%%%\n",(_percentage * 10));
        _percentage++;
    }
}