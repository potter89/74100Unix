//
//  Agent.cpp
//  74100Unix
//
//  Created by Elvio on 27/03/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//

#include "Agent.h"

Agent::Agent(){}

Agent::Agent(int indexNumber, int tagNumber, std::vector<int> neighborsIndexes){
    _index = indexNumber;
    tag = tagNumber;
    neighbors = neighborsIndexes;
}
/** //BEFORE
 Agent::Agent(Agent &o){
	_index = o.getIndex();
	payoff = o.payoff;
	fitness = o.fitness;
	strategy = o.strategy;
	tag = o.tag;
	neighbors = o.neighbors;
 }
 //*/
Agent::Agent(const Agent &o){
    _index = o._index;
    payoff = o.payoff;
    fitness = o.fitness;
    strategy = o.strategy;
    tag = o.tag;
    neighbors = o.neighbors;
}

Agent::~Agent(){
    //printf("Deleting agent\n");
}

int Agent::getIndex(){
    return _index;
}

/**
 void Agent::printNeighbors(){
	std::cout << "Agent " << index << " has neighbors: ";
	for (int i = 0; i < (int)(neighbors.size()); i++){
 std::cout << neighbors[i] << " ";
	}
	std::cout << std::endl;
 }
 //*/