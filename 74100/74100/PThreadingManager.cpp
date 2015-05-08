//
//  PThreadingManager.cpp
//  74100Unix
//
//  Created by Elvio on 31/03/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//

#include "PThreadingManager.h"

PThreadingManager::PThreadingManager(){}
PThreadingManager::~PThreadingManager(){}


void runSingleSimulation(Simulation * sim)
{
	sim->runSimulation();
}


//TODO: make this passing a reference
void PThreadingManager::runMultiThreadedSimulations(std::vector <Simulation *> simulations)
{
    signed long int numbOfSimulations = simulations.size();
	std::vector<std::thread *> threads;
    long id;
    
    for(id = 0; id < (int)numbOfSimulations; ++id){
		std::thread * t = new std::thread(runSingleSimulation, simulations[id]);
		threads.push_back(t);
    }

	//Join the threads with the main thread
	for (int i = 0; i < (int)numbOfSimulations; ++i) {
		threads[i]->join();
		delete threads[i];
	}
}