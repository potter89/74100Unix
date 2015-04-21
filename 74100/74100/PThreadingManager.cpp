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


void * runSingleSimulation(void * arg)
{
    //printf("Starting Simulation!\n");
    reinterpret_cast<Simulation *>(arg)->runSimulation();
    //printf("Simulation FINISHED!\n");
    pthread_exit(NULL);
}


//TODO: make this passing a reference
void PThreadingManager::runMultiThreadedSimulations(std::vector <Simulation *> simulations)
{
    unsigned long int numbOfSimulations = simulations.size();
    std::vector<pthread_t> my_threadArray(numbOfSimulations);
    int ret = 0;
    long id;
    
    for(id = 0; id < numbOfSimulations; id++){
        ret =  pthread_create(&my_threadArray[id], NULL,
                              &runSingleSimulation, (void *) simulations[id]);
    }
    pthread_exit(NULL);
}