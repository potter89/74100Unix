//
//  main.cpp
//  74100Unix
//
//  Created by Elvio on 27/03/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//

#include "Simulation.h"
#include "Factory.h"
#include <time.h>
#include <vector>
#include <string>
#include "TextUIManager.h"
#include "TestClass.h"
#include "GlobalRandomGen.h" //for GlobalRandom


// Allocating and initializing GlobalClass's
// static data member.  The pointer is being
// allocated - not the object inself.
GlobalRandomGen * GlobalRandomGen::_globalRandomGen_instance = 0;

int main(int argc, const char * argv[])
{
    //tests
	/**
    TestClass t;
    t.testGenerateRandMax();
    //*/    
    
    /**/
    //Factory will create populations and simulations
    Factory factory;
    
    //main simulation to execute
    Simulation * simulation;
    
	if (argc == 1){
        //no input, prompt input
        handleUIRequest(factory);
	}
	else{
        if (argc == 2){
			//parse config.txt file path
			std::string configFilePath = argv[1];
			simulation = factory.createSimulation(configFilePath);
			simulation->runSimulation();
		}
        else if (argc >= 10){
			//PARSE command line arguments
            int argvIndex = 0; //to store the last position of argv parsed
            
            int numbTags = atoi(argv[++argvIndex]);
			std::string linksPath = argv[++argvIndex];
			std::string populationType = argv[++argvIndex];
			int numbGenerations = atoi(argv[++argvIndex]);

            float tau = atof(argv[++argvIndex]);
            
			std::vector<float> payoffMatrix;
			for (int i = 0; i < 4; i++){ //4 payoff matrix numbers
				payoffMatrix.push_back(atof(argv[(++argvIndex)]));
			}
            
            unsigned int seed = atoi(argv[++argvIndex]);
            if (seed != 0) {
                //use the given seed
                GlobalRandomGen::getInstance()->setSeed(seed);
            }//else, when called for the first time, it will generate a true random seed
            
			std::vector<std::string> dataSubscribers;
			for (int i = argvIndex; i < argc-1; i++){ //from the current index, until the end of the command arg, must all be datasubs
				dataSubscribers.push_back(argv[++argvIndex]);
			}

			simulation = factory.createSimulation(numbTags, linksPath, populationType, numbGenerations, tau, payoffMatrix, dataSubscribers);
			simulation->runSimulation();
		}
	}
	//*/

	printf("Input any char to exit. Thank you for flying with us :) ... ");
	char i;
	std::cin >> i;

	return 0;
}