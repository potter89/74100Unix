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
    //tests, whithin local scope
    //TestClass t;
    
    /**/
    //Factory will create populations and simulations
    Factory factory;
    
    //main simulation to execute
    Simulation * simulation = nullptr;
    
	if (argc == 1){
        //no input, prompt input
        handleUIRequest(factory);
	}
	else{        
        if (argc >= 10){
			//PARSE command line arguments
			//./74100Unix				   2                Networks / fc_512.txt fc                10000         2.0	    1.0		  0.0 	      0.0       1 0 1.05 0     0          AverageTextFileDataSubscriber SimpleConsoleDataSubscriber
			//argv[0]:path to executable   Number_of_tags   Links_file_Path       Population_Type   Generations   TauTag	TauStrat  NoiseStrat  NoiseTag	Payoff_Matrix  RandSeed   DataSubscribers
			
			//0								1				2						3				4				5	    6		  7           8         9              10         11

			int argvIndex = 0; //to store the last position of argv parsed
            
            int numbTags = atoi(argv[++argvIndex]);
			std::string linksPath = argv[++argvIndex];
			std::string populationType = argv[++argvIndex];
			int numbGenerations = atoi(argv[++argvIndex]);

            long double tauTag = atof(argv[++argvIndex]);
			long double tauStrat = atof(argv[++argvIndex]);
			long double noiseStrat = atof(argv[++argvIndex]);
			long double noiseTag = atof(argv[++argvIndex]);
            
			std::vector<long double> payoffMatrix;
			for (int i = 0; i < 4; i++){ //4 payoff matrix numbers
				payoffMatrix.push_back(atof(argv[(++argvIndex)]));
			}
            //TODO: use something different here. atoi isnt good for negative numbers
            signed int seed = std::stoi(argv[++argvIndex]);
            
            if (seed != 0) {
                //use the given seed
                GlobalRandomGen::getInstance()->setSeed(seed);
            }//else, when called for the first time, it will generate a true random seed
            
			std::vector<std::string> dataSubscribers;
			for (int i = argvIndex; i < argc-1; i++){ //from the current index, until the end of the command arg, must all be datasubs
				dataSubscribers.push_back(argv[++argvIndex]);
			}

			simulation = factory.createSimulation(numbTags, linksPath, populationType, numbGenerations, tauTag, tauStrat, noiseStrat, noiseTag, payoffMatrix, dataSubscribers);
			
            simulation->runSimulation();
            
            delete simulation; //free up dynamic memory
		}
	}
	//*/

	printf("Input any char to exit. Thank you for flying with us :) ... ");
	char i;	std::cin >> i;

	return 0;
}