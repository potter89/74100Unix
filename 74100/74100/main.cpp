//
//  main.cpp
//  74100
//
//  Created by Elvio on 17/03/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//
// main.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Simulation.h"
#include "Factory.h"
#include "DataSubscriber.h"
#include <vector>
#include <string>

int main(int argc, const char * argv[])
{
    //TODO: delete memory allocations, to allow more simulations, one after the other while cleaning up
    
    //Factory will create populations and simulations
    Factory factory;
    /**
     factory.generateFullyConnected();
     factory.generateTwoForwardTwoBehind();
     
     /**/
    /**
     //Create a simulation for each of the input files given
     //TODO: make it work with argv instead of hardCoded AND the for each
     Simulation * a = factory.createSimulation("ConfigurationFiles/config1.txt");
     /**/
    /**/
    std::vector <Simulation *> simulations;
    std::vector<std::string> * dataSubscribers = nullptr;
    std::vector<float> payoffMatrix = { 100.0f, 0.0f, 1.0f, 0.0f };
    const int NUMB_SIMS = 1500000;
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
     /**/
    payoffMatrix[2] = 1.15f;
    simulations.push_back(factory.createSimulation(2,
                                                   "Networks/WellMixed/TwoForwardTwoBehind_512.txt", "OTHER2", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
    
    payoffMatrix[2] = 1.2f;
    simulations.push_back(factory.createSimulation(2,
                                                   "Networks/WellMixed/TwoForwardTwoBehind_512.txt", "OTHER2", NUMB_SIMS, 1.0f, payoffMatrix, dataSubscribers));
    /**/
}