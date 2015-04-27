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

//TODO: confirm that we are merely getting a COPY of the population
void ConsoleDataSubscriber::update(int numberOfCooperativeActions, std::vector<Agent> populationAgents, std::string popType){
    //Prints the number of cooperative actions performed in the console
    std::cout << std::endl << std::endl; //separation from what might be in the console
    std::cout << "Update! There were " <<
    numberOfCooperativeActions << " cooperative actions made last generation!" << std::endl;
    
    if (popType == "LATTICE"){
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
        
        for (index = 0; index < populationAgents.size(); index++){ //for each agent
            auxAgent = &(populationAgents.at(index));
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
        for (index = 0; index < populationAgents.size(); index++){ //for each agent
            auxAgent = &(populationAgents.at(index));
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

void SimpleConsoleDataSubscriber::update(int numberOfCooperativeActions, std::vector<Agent> populationAgents, std::string popType){
    //Prints the number of cooperative actions performed in the console
    if (refreshRateCounter <= 0){ //only prints once in REFRESHRATE times
        std::cout << "Update! " <<
        numberOfCooperativeActions << " cooperative actions made last generation!" << std::endl;
        refreshRateCounter = REFRESHRATE;
    }
    else{
        refreshRateCounter--;
    }
}
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
	if (_outputTxtFile.is_open()){
		_outputTxtFile << "Results: \n";
		_outputTxtFile.close();
	}
	else{
		std::cout << "Couldn't write to file" << std::endl;
	}
}

TextFileDataSubscriber::TextFileDataSubscriber(std::string filename) : 
_paramFileName(filename)
{
	setNonDuplicateOutputFileName();
}
TextFileDataSubscriber::~TextFileDataSubscriber(){

}

//Writes the updates to a text file
void TextFileDataSubscriber::update(int numberOfCooperativeActions, std::vector<Agent> populationAgents, std::string popType){
	//1__fc_128__15000__1.0__1.0_0.0_1.0_0.0__#1.txt
	//std::cout << _fileName << " with index:" << _tentativeFileIndex << std::endl;
	if (!_outputTxtFile.is_open()){
		_outputTxtFile.open(_fileName, std::ios::app);
	}
	_outputTxtFile << numberOfCooperativeActions << "\n";
	//std::cout << _tentativeFileIndex << " writing " << std::endl;
}