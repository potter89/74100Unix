//
//  SimulationStateManager.cpp
//  74100Unix
//
//  Created by Elvio on 27/03/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//

#include "SimulationStateManager.h"

SimulationStateManager::SimulationStateManager(){}

SimulationStateManager::~SimulationStateManager(){}




//set the population to b used in this simulation, and also passed on to subs
void SimulationStateManager::setPopulation(Population * population){
    _simData.population = population;
}
Population * SimulationStateManager::getPopulation(){
    return _simData.population;
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

//calls function update of every subscriber
void SimulationStateManager::notifyDataSubscribers(){
    for (int i = 0; i < _numbSubscribers; i++){ //for each of them, call their update function
        _dataSubscribers[i]->update(_simData);
    }
}

void SimulationStateManager::incrementCooperativeActions(){
    _simData.numbCooperativeActions++;
}

//reset's counter of cooperative actions
void SimulationStateManager::resetStateForNextGeneration(){
    _simData.numbCooperativeActions = 0;
}