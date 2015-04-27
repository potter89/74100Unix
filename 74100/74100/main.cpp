//
//  main.cpp
//  74100Unix
//
//  Created by Elvio on 27/03/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//

#include "Simulation.h"
#include "Factory.h"
#include "DataSubscriber.h"
#include "PThreadingManager.h"
#include <vector>
#include <string>
//TODO:delete this when it's time for release
#include "TestClass.h"


int main(int argc, const char * argv[])
{
    
    //TODO: delete memory allocations, to allow more simulations, one after the other while cleaning up
    
    //tests
    /**
    TestClass t;
	t.stlSimpleThreadingArg();
    //*/
    
    //Factory will create populations and simulations
    Factory factory;

	//factory.generateFullyConnected();
    //factory.generateTwoForwardTwoBehind();
    //factory.generateLatticeLinksTextFile();
    
    /**
     //Create a simulation for each of the input files given
     //TODO: make it work with argv instead of hardCoded AND the for each
     Simulation * a = factory.createSimulation("ConfigurationFiles/config1.txt");
    //*/
    std::vector <Simulation *> simulations;
	std::vector<std::string> dataSubscribers = 
	//{ "SimpleConsoleDataSubscriber" };
	{ "TextFileDataSubscriber" };
    
	std::vector<float> payoffMatrix = { 1.0f, 0.0f, 1.0f, 0.0f };
    const int NUMB_SIMS = 3;
    
	
	payoffMatrix[2] = 1.0f;
	simulations.push_back(factory.createSimulation(1,
													"Networks/fc_5.txt", "fc", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
	
	payoffMatrix[2] = 1.0f;
	simulations.push_back(factory.createSimulation(1,
													"Networks/fc_5.txt", "fc", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
	
	payoffMatrix[2] = 1.0f;
	simulations.push_back(factory.createSimulation(1,
													"Networks/fc_5.txt", "fc", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));

	/**
	payoffMatrix[2] = 1.0f;
    simulations.push_back(factory.createSimulation(1,
													"Networks/fc_5.txt", "fc", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
    
	payoffMatrix[2] = 1.0f;
    simulations.push_back(factory.createSimulation(1,
													"Networks/fc_5.txt", "fc", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers)); 
	
	payoffMatrix[2] = 1.0f;
    simulations.push_back(factory.createSimulation(1,
													"Networks/fc_5.txt", "fc", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));

    /**/
    PThreadingManager pTManager;
    pTManager.runMultiThreadedSimulations(simulations);

    //*/
    //simulations.clear();
	
	/**   
    for (long i = 0; i < simulations.size(); i++) {
        simulations[i]->runSimulation();
    }
	//*/

	std::cout << "Press any button to exit. ...";
	char i;
	std::cin >> i;
    
    //*/

}
/**
payoffMatrix[2] = 1.0f;
simulations.push_back(factory.createSimulation(1,
                                               "/Users/elvio/Documents/Projects/74100Unix/74100Unix/74100Unix/Networks/tftb_512.txt", "fc", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));

payoffMatrix[2] = 1.05f;
simulations.push_back(factory.createSimulation(1,
                                               "/Users/elvio/Documents/Projects/74100Unix/74100Unix/74100Unix/Networks/tftb_512.txt", "tftb", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));

payoffMatrix[2] = 1.1f;
simulations.push_back(factory.createSimulation(1,
                                               "/Users/elvio/Documents/Projects/74100Unix/74100Unix/74100Unix/Networks/tftb_512.txt", "fc", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));

payoffMatrix[2] = 1.2f;
simulations.push_back(factory.createSimulation(1,
                                               "/Users/elvio/Documents/Projects/74100Unix/74100Unix/74100Unix/Networks/tftb_512.txt", "tftb", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
payoffMatrix[2] = 1.25f;
simulations.push_back(factory.createSimulation(1,
                                               "/Users/elvio/Documents/Projects/74100Unix/74100Unix/74100Unix/Networks/tftb_512.txt", "fc", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));

payoffMatrix[2] = 1.3f;
simulations.push_back(factory.createSimulation(1,
                                               "/Users/elvio/Documents/Projects/74100Unix/74100Unix/74100Unix/Networks/tftb_512.txt", "tftb", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
payoffMatrix[2] = 1.5f;
simulations.push_back(factory.createSimulation(1,
                                               "/Users/elvio/Documents/Projects/74100Unix/74100Unix/74100Unix/Networks/tftb_512.txt", "fc", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));

 payoffMatrix[2] = -100.0f;
 simulations.push_back(factory.createSimulation(1,
 "/Users/elvio/Documents/Projects/74100Unix/74100Unix/74100Unix/Networks/tftb_512.txt", "tftb", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
 
 payoffMatrix[2] = 1.0f;
 simulations.push_back(factory.createSimulation(2,
 "/Users/elvio/Documents/Projects/74100Unix/74100Unix/74100Unix/Networks/tftb_512.txt", "fc", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
 
 payoffMatrix[2] = 1.05f;
 simulations.push_back(factory.createSimulation(2,
 "/Users/elvio/Documents/Projects/74100Unix/74100Unix/74100Unix/Networks/tftb_512.txt", "tftb", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
 
 payoffMatrix[2] = 1.1f;
 simulations.push_back(factory.createSimulation(2,
 "/Users/elvio/Documents/Projects/74100Unix/74100Unix/74100Unix/Networks/tftb_512.txt", "fc", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
 
 payoffMatrix[2] = 1.2f;
 simulations.push_back(factory.createSimulation(2,
 "/Users/elvio/Documents/Projects/74100Unix/74100Unix/74100Unix/Networks/tftb_512.txt", "tftb", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
 payoffMatrix[2] = 1.25f;
 simulations.push_back(factory.createSimulation(2,
 "/Users/elvio/Documents/Projects/74100Unix/74100Unix/74100Unix/Networks/tftb_512.txt", "fc", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
 
 payoffMatrix[2] = 1.3f;
 simulations.push_back(factory.createSimulation(2,
 "/Users/elvio/Documents/Projects/74100Unix/74100Unix/74100Unix/Networks/tftb_512.txt", "tftb", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
 payoffMatrix[2] = 1.5f;
 simulations.push_back(factory.createSimulation(2,
 "/Users/elvio/Documents/Projects/74100Unix/74100Unix/74100Unix/Networks/tftb_512.txt", "fc", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
 
 payoffMatrix[2] = -100.0f;
 simulations.push_back(factory.createSimulation(2,
 "/Users/elvio/Documents/Projects/74100Unix/74100Unix/74100Unix/Networks/tftb_512.txt", "tftb", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
 //*/
