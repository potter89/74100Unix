//
//  SimulationStateManager.cpp
//  74100Unix
//
//  Created by Elvio on 27/03/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//

#include "SimulationStateManager.h"

SimulationStateManager::SimulationStateManager(){}

SimulationStateManager::~SimulationStateManager(){
   std::cout << "Deleting statemanager" << std::endl;
    for (auto it=_dataSubscribers.begin(); it!=_dataSubscribers.end(); it++) {
        delete *it;
    }
}




//set the population to b used in this simulation, and also passed on to subs
void SimulationStateManager::setSimulationData(Population * newPopulation, int & i_maxGenerations,
	long double & tauTag, long double & tauStrat, long double & noiseStrat, long double & noiseTag, std::vector<long double> & payoffMatrix){
    _simData.population = newPopulation;
    _simData.maxGenerations = i_maxGenerations;
	_simData.tauTag = tauTag;
	_simData.tauStrat = tauStrat;
	_simData.noiseStrat = noiseStrat;
	_simData.noiseTag = noiseTag;
    _simData.payoffMatrix = payoffMatrix;
}

Population * SimulationStateManager::getPopulation(){
    return _simData.population;
}

int * SimulationStateManager::getMaxGenerations(){
    return &_simData.maxGenerations;
}

long double * SimulationStateManager::getTauTag(){
	return &_simData.tauTag;
}
long double * SimulationStateManager::getTauStrat(){
	return &_simData.tauStrat;
}
long double * SimulationStateManager::getNoiseStrat(){
	return &_simData.noiseStrat;
}
long double * SimulationStateManager::getNoiseTag(){
	return &_simData.noiseTag;
}

std::vector<long double> * SimulationStateManager::getPayoffMatrix(){
    return &_simData.payoffMatrix;
}

unsigned int * SimulationStateManager::getStrategyChangeCounter(){
    return &_simData.strategyChangeCounter;
}
int * SimulationStateManager::getCurrentGenerationCounter(){
    return &_simData.currentGeneration;
}

//returns how many subscribers are attached
int SimulationStateManager::getNumbAttachedSubscribers(){
    return _numbSubscribers;
}
//adds new dataSub to the vector of data sub pointers AND _numbSubscribers++
void SimulationStateManager::attachDataSubscriber(DataSubscriber * newSub){
    _dataSubscribers.push_back(newSub);
    _numbSubscribers++;
}
//removes *dataSub to the vector of data subs AND _numbSubscribers--
void SimulationStateManager::detatchDataSubscriber(DataSubscriber * newSub){
    if (_numbSubscribers > 0){
        _numbSubscribers--;
        for (int i = 0; i < _numbSubscribers; i++){ //look for the one to delete
            if (newSub == _dataSubscribers[i]){ //if they both point to the same address
                _dataSubscribers.erase(_dataSubscribers.begin() + i); //delete and break
                break;
            }
        }
    }
}

//updates the number of the current generation
void SimulationStateManager::incCurrentGeneration(){
    _simData.currentGeneration++;
}

//calls function update of every subscriber
void SimulationStateManager::notifyDataSubscribers(){
    for (int i = 0; i < _numbSubscribers; i++){ //for each of them, call their update function
        _dataSubscribers[i]->update(_simData);
    }
}

//calls function updateAfterFinish of every subscriber
void SimulationStateManager::notifyDataSubscribersGameOver(){
    for (int i = 0; i < _numbSubscribers; i++){ //for each of them, call their update function
        _dataSubscribers[i]->updateAfterFinish(_simData);
    }
}


void SimulationStateManager::incrementCooperativeActions(){
    _simData.numbCooperativeActions++;
}

//reset's counter of cooperative actions
void SimulationStateManager::resetStateForNextGeneration(){
    _simData.numbCooperativeActions = 0;
}

void SimulationStateManager::incrementStrategyChangeCounter(){
    _simData.strategyChangeCounter++;
}