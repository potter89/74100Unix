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
#include <vector>
#include <string>
//TODO:delete this when it's time for release
#include "TestClass.h"

int main(int argc, const char * argv[])
{
    
    //TODO: delete memory allocations, to allow more simulations, one after the other while cleaning up
    
    //Factory will create populations and simulations
    Factory factory;
    /**/
     //factory.generateFullyConnected();
     //factory.generateTwoForwardTwoBehind();
    /**/
    /**
     //Create a simulation for each of the input files given
     //TODO: make it work with argv instead of hardCoded AND the for each
     Simulation * a = factory.createSimulation("ConfigurationFiles/config1.txt");
    /**/
    /**
    std::vector <Simulation *> simulations;
    std::vector<std::string> * dataSubscribers = nullptr;
    std::vector<float> payoffMatrix = { 1.0f, 0.0f, 1.0f, 0.0f };
    const int NUMB_SIMS = 150000;
    /**
     payoffMatrix[2] = 1.0f;
     simulations.push_back(factory.createSimulation(1,
     "Networks/WellMixed/FullyConnected_512.txt", "OTHER", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
     
     payoffMatrix[2] = 1.025f;
     simulations.push_back(factory.createSimulation(1,
     "Networks/WellMixed/FullyConnected_512.txt", "OTHER", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
     
     payoffMatrix[2] = 1.1f;
     simulations.push_back(factory.createSimulation(1,
     "Networks/WellMixed/FullyConnected_512.txt", "OTHER", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
     
     payoffMatrix[2] = 1.15f;
     simulations.push_back(factory.createSimulation(1,
     "Networks/WellMixed/FullyConnected_512.txt", "OTHER", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
     
     payoffMatrix[2] = 1.2f;
     simulations.push_back(factory.createSimulation(1,
     "Networks/WellMixed/FullyConnected_512.txt", "OTHER", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
     //asdkjfhalkjhflasdgflajshdgflajhsdgf
     payoffMatrix[2] = 1.0f;
     simulations.push_back(factory.createSimulation(1,
     "Networks/WellMixed/TwoForwardTwoBehind_512.txt", "OTHER2", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
     
     payoffMatrix[2] = 1.025f;
     simulations.push_back(factory.createSimulation(1,
     "Networks/WellMixed/TwoForwardTwoBehind_512.txt", "OTHER2", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
     
     payoffMatrix[2] = 1.1f;
     simulations.push_back(factory.createSimulation(1,
     "Networks/WellMixed/TwoForwardTwoBehind_512.txt", "OTHER2", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
     
     payoffMatrix[2] = 1.15f;
     simulations.push_back(factory.createSimulation(1,
     "Networks/WellMixed/TwoForwardTwoBehind_512.txt", "OTHER2", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
     
     payoffMatrix[2] = 1.2f;
     simulations.push_back(factory.createSimulation(1,
     "Networks/WellMixed/TwoForwardTwoBehind_512.txt", "OTHER2", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
     //********************************************************************************
     payoffMatrix[2] = 1.0f;
     simulations.push_back(factory.createSimulation(2,
     "Networks/WellMixed/FullyConnected_512.txt", "OTHER", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
     
     payoffMatrix[2] = 1.025f;
     simulations.push_back(factory.createSimulation(2,
     "Networks/WellMixed/FullyConnected_512.txt", "OTHER", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
     
     payoffMatrix[2] = 1.1f;
     simulations.push_back(factory.createSimulation(2,
     "Networks/WellMixed/FullyConnected_512.txt", "OTHER", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
     
     payoffMatrix[2] = 1.15f;
     simulations.push_back(factory.createSimulation(2,
     "Networks/WellMixed/FullyConnected_512.txt", "OTHER", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
     
     payoffMatrix[2] = 1.2f;
     simulations.push_back(factory.createSimulation(2,
     "Networks/WellMixed/FullyConnected_512.txt", "OTHER", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
     //asdkjfhalkjhflasdgflajshdgflajhsdgf
     payoffMatrix[2] = 1.0f;
     simulations.push_back(factory.createSimulation(2,
     "Networks/WellMixed/TwoForwardTwoBehind_512.txt", "OTHER2", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
     
     payoffMatrix[2] = 1.025f;
     simulations.push_back(factory.createSimulation(2,
     "Networks/WellMixed/TwoForwardTwoBehind_512.txt", "OTHER2", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
     
     payoffMatrix[2] = 1.1f;
     simulations.push_back(factory.createSimulation(2,
     "Networks/WellMixed/TwoForwardTwoBehind_512.txt", "OTHER2", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
     
     payoffMatrix[2] = 1.2f;
     simulations.push_back(factory.createSimulation(2,
                                                   "/Users/elvio/Documents/Projects/74100Unix/74100Unix/74100Unix/Networks/WellMixed/TwoForwardTwoBehind_512.txt", "OTHER2", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
    payoffMatrix[2] = 1.1f;
    simulations.push_back(factory.createSimulation(1,
                                                   "/Users/elvio/Documents/Projects/74100Unix/74100Unix/74100Unix/Networks/Lattices/32x32.txt", "LATTICE", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
    payoffMatrix[2] = 1.05f;
    simulations.push_back(factory.createSimulation(1,
                                                   "/Users/elvio/Documents/Projects/74100Unix/74100Unix/74100Unix/Networks/Lattices/32x32.txt", "LATTICE", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
    /**/
}