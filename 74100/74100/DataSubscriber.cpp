//
//  DataSubscriber.cpp
//  74100Unix
//
//  Created by Elvio on 27/03/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//

#include "DataSubscriber.h"

#include <iostream>
//DataSubscriber cl@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
DataSubscriber::DataSubscriber(){}
DataSubscriber::~DataSubscriber(){}


//Console Subscriber cl@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
ConsoleDataSubscriber::ConsoleDataSubscriber(){}
ConsoleDataSubscriber::~ConsoleDataSubscriber(){}


void ConsoleDataSubscriber::update(const SimulationData & simData) {
    //Prints the number of cooperative actions performed in the console
    printf("\n\n"); //separation from what might be in the console
    printf("Update! Cooperative actions made last generation: %d\n", simData.numbCooperativeActions);
    if (simData.population->getType() == "l"){
        //If they have 1 or 0 tags, prints strategy and current fitness
        //C-3 D-7 D-2
        //C- D- D-
        //C- D- D-
        //
        //2 or more tags, prints tag, startegy and fitness
        //4_{0,1,0,1,0,}-3 2_{0,1,0,1,0,}-3
        //etc.....
        Agent * auxAgent;
        bool lastInRow = true;
        int index = 0;
        int auxStratSize = 0;
        
        for (index = 0; index < simData.population->getSize(); index++){ //for each agent
            auxAgent = &simData.population->getAgentsPtr()->at(index);
            
            //print his strategy
            auxStratSize = (int)auxAgent->strategy.size();
            if (auxStratSize == 1){
                if (auxAgent->strategy[0] == 0){
                    printf("C");
                }
                else
                {
                    printf("D");
                }
            }
            else{
                printf("%d_{", auxAgent->tag);
                for (int i = 0; i < auxStratSize; i++){
                    std::cout << auxAgent->strategy.at(i);
                    if (i != (auxStratSize - 1)) std::cout << ",";
                }
                std::cout << "}";
            }
            if (auxAgent->fitness - (int)auxAgent->fitness > 0.0) { //for better allignment of values with decimals
                std::cout << "-" << auxAgent->fitness << " "; //print his fitness
            }else{
                std::cout << "-" << auxAgent->fitness << "   "; //print his fitness
            }
            if (auxAgent->fitness < 10) std::cout << " "; //just to better align
            
            
            //if it's the last one, include an endl
            lastInRow = true;
            for (int z = 0; z < auxAgent->neighbors.size(); z++){ //check each of auxAgent neighbors
                if ((index + 1) == auxAgent->neighbors.at(z)) {
                    lastInRow = false; //if any of them has index directly
                    break;
                }
            }
            if (lastInRow){
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
    else{
        //Generic console print of unkown/unhandeled (:PPP) pop type
        //If they have 1 or 0 tags, prints index, strategy and current fitness
        //0C-3
        //1D-5
        //2C-3
        //
        //2 or more tags, prints index, tag, startegy and fitness
        //0_4_{0,1,0,1,0,}-3
        //1_2_{0,1,0,1,0,}-3
        //etc.....
        Agent * auxAgent;
        int index = 0; //agents index
        int auxStratSize = 0;
        const int MAXAgentsPerLine = 5; //max agents printed per line in the console
        int agentsPerLineCounter = 0; //counts how many have been placed already
        for (index = 0; index < simData.population->getSize(); index++){ //for each agent
            auxAgent = &simData.population->getAgentsPtr()->at(index);
            std::cout << index << "_";
            //print his strategy
            auxStratSize = (int)auxAgent->strategy.size();
            if (auxStratSize == 1){
                if (auxAgent->strategy[0] == 0){
                    std::cout << "C";
                }
                else
                {
                    std::cout << "D";
                }
            }
            else{
                std::cout << auxAgent->tag << "_{";
                for (int i = 0; i < auxStratSize; i++){
                    std::cout << auxAgent->strategy.at(i);
                    if (i != (auxStratSize - 1)) std::cout << ",";
                }
                std::cout << "}";
            }
            std::cout << "-" << auxAgent->fitness << " "; //print his fitness
            if (auxAgent->fitness < 10) std::cout << " "; //just to better align
            if (agentsPerLineCounter >= (MAXAgentsPerLine-1)){//making sure only MAXAgentsPerLine are printed per line
                std::cout << std::endl;
                agentsPerLineCounter = 0;
            }
            else agentsPerLineCounter++;
        }
    }
}


//Simple Console Subscriber
SimpleConsoleDataSubscriber::SimpleConsoleDataSubscriber(){}
SimpleConsoleDataSubscriber::~SimpleConsoleDataSubscriber(){}

void SimpleConsoleDataSubscriber::update(SimulationData const & simData){
	//Prints the number of cooperative actions performed in the console
    if (refreshRateCounter <= 0){ //only prints once in REFRESHRATE times
        printf("Update! Cooperative actions made last generation: %i \n", simData.numbCooperativeActions);
        refreshRateCounter = REFRESHRATE;
    }
    else{
        refreshRateCounter--;
    }
}


//Text File Subscriber cl@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
TextFileDataSubscriber::TextFileDataSubscriber(std::string filename) : 
_paramFileName(filename)
{
	setNonDuplicateOutputFileName();
}
TextFileDataSubscriber::~TextFileDataSubscriber(){}

bool TextFileDataSubscriber::emptyFile(std::string filename){
	std::ifstream possibleExistingFile(filename);
	std::string tempString = "";
	getline(possibleExistingFile, tempString);
	if (tempString == ""){

		//non existing file
		//std::cout << "Non duplicate file! #" << _tentativeFileIndex << std::endl;
		possibleExistingFile.close();
		return true;
	}
	//else
		//file exists, try a different index at the end of the file
	//std::cout << "Duplicate file! #" << _tentativeFileIndex << std::endl;
		possibleExistingFile.close();
		tempString = "";
		return false;
}

//sets non Duplicate filename for the current simulation in _fileName
void TextFileDataSubscriber::setNonDuplicateOutputFileName(){
	//tries to open #1 for the first time for reading, to check for existing file with the same name
    _fileName = "Results/" + _paramFileName + std::to_string(_tentativeFileIndex) + ".txt";
	while (!emptyFile(_fileName)){
		_tentativeFileIndex++;
		_fileName = "Results/" + _paramFileName + std::to_string(_tentativeFileIndex) + ".txt";
	}
	//creates file
	_outputTxtFile.open(_fileName);
	
    std::cout << "Seed: " + std::to_string(GlobalRandomGen::getInstance()->getSeed()) << std::endl;
    
    if (_outputTxtFile.is_open()){
		_outputTxtFile << _fileName + " Seed: " + std::to_string(GlobalRandomGen::getInstance()->getSeed()) << " \n";
		_outputTxtFile.close();
	}
	else{
		std::cout << "Couldn't write to file" << std::endl;
	}
}


//Writes the updates to a text file
void TextFileDataSubscriber::update(const SimulationData & simData){
	//1__fc_128__15000__1.0__1.0_0.0_1.0_0.0__#1.txt
	//std::cout << _fileName << " with index:" << _tentativeFileIndex << std::endl;
	if (!_outputTxtFile.is_open()){
		_outputTxtFile.open(_fileName, std::ios::app);
	}
	_outputTxtFile << simData.numbCooperativeActions << "\n";
    _outputTxtFile.close();
	//std::cout << _tentativeFileIndex << " writing " << std::endl;
}

//AVERAGE Text File Subscriber cl@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
AverageTextFileDataSubscriber::AverageTextFileDataSubscriber(std::string filename, int totalGenerations) 
: TextFileDataSubscriber(filename)
{
	(totalGenerations >= 100) ? 
		_refreshRate = totalGenerations * 0.01 : // to print 100 times only
		_refreshRate = 0; //else prints at all times
}
AverageTextFileDataSubscriber::~AverageTextFileDataSubscriber(){}

//returns the average value of the contents of the vector
int AverageTextFileDataSubscriber::calculateAverage(std::list<int> & inList){
    signed long long avr = 0;
    unsigned long size = inList.size();
    for (auto it=inList.begin(); it!=inList.end(); it++){
        avr += *it;
    }
    if (size > 0){
        avr = avr / size;
        return (int)avr;
    }
    else{
        return -1;
    }
}


//1__fc_128__15000__1.0__1.0_0.0_1.0_0.0__#1.txt
void AverageTextFileDataSubscriber::update(const SimulationData & simData){
    //TODO: IMP!! test if this line works, it totally shouldn't!!!!!!
    //simData.population->getAgentsPtr()->at(1).payoff = 69;
    
    if (_refreshRateCounter <= 0){ //only prints once in REFRESHRATE times
		//std::cout << _fileName << " with index:" << _tentativeFileIndex << std::endl;
		if (!_outputTxtFile.is_open()){
			_outputTxtFile.open(_fileName, std::ios::app);
		}

		if (_average == -1){// if running for the first time, dont store average, store the first number of coop actions
			std::cout << _fileName << " with index:" << _tentativeFileIndex << std::endl;
			_outputTxtFile << simData.numbCooperativeActions << "\n";
		}
		else{
			_outputTxtFile << calculateAverage(_valuesToAverage) << "\n";
		}
        _outputTxtFile.close();
		//std::cout << _tentativeFileIndex << " writing " << std::endl;
		_average = 0;
		_valuesToAverage.clear();
		_refreshRateCounter = _refreshRate;
	}else{
		_valuesToAverage.push_back(simData.numbCooperativeActions);
		_refreshRateCounter--;
	}
}


//Average LAST thousand Text File Subscriber cl@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
AverageLastThousandDataSubscriber::AverageLastThousandDataSubscriber(std::string fileName)
: TextFileDataSubscriber(fileName){}
AverageLastThousandDataSubscriber::~AverageLastThousandDataSubscriber(){}

void AverageLastThousandDataSubscriber::update(const SimulationData & simData){
    if (lastThousand == -1) {
        //if it's being updated for the first time, it needs to initialize when the lastThousand starts
        if (simData.maxGenerations >= 1000) lastThousand = simData.maxGenerations - 1000;
        else lastThousand = 0;
    }else{
        //fills the vector only with the last thousand generation's values
        if (simData.currentGeneration >= lastThousand) {
            _valuesToAverage.push_back(simData.numbCooperativeActions);
            if ((simData.currentGeneration+1) == simData.maxGenerations) { //if it's the last generation, average values and print to file
                int avg = calculateAverage(_valuesToAverage);
                
                if (!_outputTxtFile.is_open()){
                    _outputTxtFile.open(_fileName, std::ios::app);
                }
                _outputTxtFile << avg << "\n";
                _outputTxtFile.close();
            }
        }
    }
}

//returns the average value of the contents of the vector
int AverageLastThousandDataSubscriber::calculateAverage(std::list<int> & inList){
    signed long long avr = 0;
    unsigned long size = inList.size();
    for (auto it=inList.begin(); it!=inList.end(); it++){
        avr += *it;
    }
    if (size > 0){
        avr = avr / size;
        return (int)avr;
    }
    else{
        return -1;
    }
}


















