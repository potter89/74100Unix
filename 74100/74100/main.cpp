//
//  main.cpp
//  74100Unix
//
//  Created by Elvio on 27/03/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//

#include "Simulation.h"
#include "Factory.h"
#include "PThreadingManager.h"
#include <time.h>
#include <vector>
#include <string>
#include "TestClass.h"

int main(int argc, const char * argv[])
{
    unsigned int seedRand = time(NULL);
	srand(seedRand);
    
    //tests
	/**
	TestClass t;
    t.concurrentFileOpen(seedRand);
	//*/

    //for (int i=0; i< argc; i++) std::cout << argv[i] << std::endl; //print arguments passed
    
    /**/
	if (argc == 1){
		printf("No input :( Ejecting now -> ");
	}
    
	else{
		//Factory will create populations and simulations
		Factory factory;

		//main simulation to execute
		Simulation * simulation;

		//TODO: code a way to access this
		//factory.generateFullyConnected();
		//factory.generateTwoForwardTwoBehind();d
		//factory.generateLatticeLinksTextFile();

        //depending of 
		if (argc == 2){
			//parse config.txt file path
			std::string configFilePath = argv[1];
			simulation = factory.createSimulation(configFilePath);
			simulation->runSimulation();
		}
		else if (argc >= 10){
			//parse command line arguments
			int numbTags = atoi(argv[1]);
			std::string linksPath = argv[2];
			std::string populationType = argv[3];
			int numbGenerations = atoi(argv[4]);
			
            float tau = atof(argv[5]);
            
			std::vector<float> payoffMatrix;
			for (int i = 0; i < 4; i++){
				payoffMatrix.push_back(atof(argv[(i + 6)]));
			}
            
			std::vector<std::string> dataSubscribers;
			for (int i = 10; i < argc; i++){
				dataSubscribers.push_back(argv[i]);
			}

			simulation = factory.createSimulation(numbTags, linksPath, populationType, numbGenerations, tau, payoffMatrix, dataSubscribers);
			simulation->runSimulation();

			//PThreadingManager pTManager;
			//pTManager.runMultiThreadedSimulations(simulations);
			//for (long i = 0; i < simulations.size(); i++) {
			//	simulations[i]->runSimulation();
			//}
		}
	}
	//*/

	printf("Input any char to exit. Thank you for flying with us :) ... ");
	char i;
	std::cin >> i;

	return 0;
}