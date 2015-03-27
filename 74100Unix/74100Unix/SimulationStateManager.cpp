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

//returns how many subscribers are attached
int SimulationStateManager::getNumbAttachedSubscribers(){
    return _simData._numbSubscribers;
}

//set the population vector of the data object, who is passed on to subs
void SimulationStateManager::setPopulationToSendOut(std::vector<Agent> * population){
    _simData._population = population;
}

void SimulationStateManager::setTypeToSendOut(std::string type){
    _simData._populationType = type;
}

//adds new dataSub to the vector of data sub pointers AND _numbSubscribers++
void SimulationStateManager::attachDataSubscriber(DataSubscriber * newSub){
    //TODO:test this
    _simData._dataSubscribers.push_back(newSub);
    _simData._numbSubscribers++;
}
//removes *dataSub to the vector of data subs AND _numbSubscribers--
void SimulationStateManager::detatchDataSubscriber(DataSubscriber * newSub){
    //TODO:test this
    if (_simData._numbSubscribers > 0){
        _simData._numbSubscribers--;
        for (int i = 0; i < _simData._numbSubscribers; i++){ //look for the one to delete
            if (newSub == _simData._dataSubscribers[i]){ //if they both point to the same address
                _simData._dataSubscribers.erase(_simData._dataSubscribers.begin() + i); //delete and break
                break;
            }
            
        }
    }
}

//calls function update of every subscriber
void SimulationStateManager::notifyDataSubscribers(){
    for (int i = 0; i < _simData._numbSubscribers; i++){ //for each of them, call their update function
        _simData._dataSubscribers[i]->update(_simData._numbCooperativeActions, *_simData._population, _simData._populationType);
    }
}

void SimulationStateManager::incrementCooperativeActions(){
    _simData._numbCooperativeActions++;
}

//reset's counter of cooperative actions
void SimulationStateManager::resetStateForNextGeneration(){
    _simData._numbCooperativeActions = 0;
}


/** //TODO:consider deleting this I wont need this, me thinks
 SimulationStateManager::SimulationStateManager(int c, int d){
	_simData._numbCooperators = c;
	_simData._numbDefectors = d;
 }
 /**/


/** //TODO:consider deleting this I wont need this, me thinks
 //_numbCooperators++
 void SimulationStateManager::incrementCooperators(){ //+1
	_simData._numbCooperators++;
 }
 //_numbCooperators--
 void SimulationStateManager::decrementCooperators(){ //-1
	if (_simData._numbCooperators > 0) _simData._numbCooperators--;
 }
 //_numbDefectors++
 void SimulationStateManager::incrementDefectors(){ //+1
	_simData._numbDefectors++;
 }
 //_numbDefectors--
 void SimulationStateManager::decrementDefectors(){ //-1
	if (_simData._numbDefectors > 0) _simData._numbDefectors--;
 }
 /**/

//TODO: delete this
/**
 void SimulationStateManager::print(){
	std::cout << "Cooperators: " << _simData._numbCooperators << std::endl;
	std::cout << "Defectors: " << _simData._numbDefectors << std::endl;
 }
 /**/
