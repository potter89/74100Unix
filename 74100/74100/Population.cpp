//
//  Population.cpp
//  74100Unix
//
//  Created by Elvio on 27/03/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//

#include "Population.h"

//Population cl@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ss
Population::Population(){}
Population::~Population(){}

int Population::getSize(){
    return (int)agentsInPop.size();
}
int Population::getNumberOfTags(){
    return _numberOfTags;
}
std::string Population::getType(){
    return _type;
}
std::vector<Agent> * Population::getAgentsPtr(){
    return &agentsInPop;
}



//Lattice cl@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ss
LatticePopulation::LatticePopulation(){}
LatticePopulation::~LatticePopulation(){
    printf("Deleting Population\n");
}

//generates random tag, from 0 to totalNumberOfTags-1, and fills <_strategy> with random 0 and 1's
void LatticePopulation::generateRandomStrategies(int totalNumberOfTags){
    int totNumberOfTags = totalNumberOfTags;
    int randomNumber;
    
    //for each agent int the pop
    for (int i = 0; i < (int)agentsInPop.size(); i++){
        if (totNumberOfTags != 0){
            //assign random tag
            randomNumber = GlobalRandomGen::getInstance()->getRandomTillMax(totNumberOfTags-1); //if there is two tags, they will be tag 0 and 1, hence the -1
            agentsInPop[i].tag = randomNumber;
        }
        else{
            agentsInPop[i].tag = 0;
        }
        
        int strategyVectorSize = totNumberOfTags; //this variable will help populate the strategy vector of an agent with a correct size
        if (strategyVectorSize == 0) strategyVectorSize += 1; //for the case where it has only one tag
        
        //random strategy for each tag
        for (int x = 0; x < strategyVectorSize; x++){
            //generate random number between 0 and 1, as they can cooperate or defect
            randomNumber = GlobalRandomGen::getInstance()->getRandomTillMax(1);
            agentsInPop[i].strategy.push_back(randomNumber);
        }
    }
}

void LatticePopulation::parseDotLinksFile(std::string i_source){
    int populationSize; //number of agents in the network, specified at the first line of the file
    std::vector<Agent> tempPopulation; //stores the parsed agents, will be returned
    std::vector<int> tempNeighbors; //stores a list of neighbors of the current parsed agent
    int tempIndex; //index for the current parsed agent
    int tempTag; //Tag for the current parsed agent
    
    std::string source = i_source;
    std::ifstream myfile(source);
    if (myfile.is_open())
    {
        std::string populationSizeString = "";
        
        //DO NOT DELETE - read first line, looking for the number of agents to include -
        getline(myfile, populationSizeString);
        
        //parsing each line, for each agent.
        //Format:AgentIndex NumbNeighbors SignalBit  NeighborIndex NeighborIndex ... (two spaces!!)
        std::string currentAgentLine;
        std::string delimiter = " ";
        
        size_t pos = 0;
        std::vector<std::string> tokens;
        
        while (getline(myfile, currentAgentLine)){ //for each line to read, break it down into tokens and add to a vector to be handled afterwards
            while ((pos = currentAgentLine.find(delimiter)) != std::string::npos){ //for each of the tokens, delimited by a space
                tokens.push_back(currentAgentLine.substr(0, pos)); //add token to vector of strings
                //std::cout << "Adding " << currentAgentLine.substr(0, pos) << " token!" << std::endl;
                currentAgentLine.erase(0, pos + delimiter.length()); //eliminate the token and delimiter from the string
            }
            tokens.push_back(currentAgentLine);
            
            //create the neigbors vector to be used in the constructor of this new agent.
            for (int i = 4; i < (tokens.size()); i++){ //neighbor's indexes start at pos 4, and end
                if (tokens[i] != "") {
                    tempNeighbors.push_back(atoi(tokens[i].c_str()));
                }
            }
            //create agent with the line read
            tempIndex = atoi(tokens[0].c_str());
            tempTag = atoi(tokens[2].c_str()); //tag is at position 2
            
            //TODO: change to pointers
            agentsInPop.push_back(Agent(tempIndex, tempTag, tempNeighbors));
            
            tempNeighbors.clear();
            tokens.clear();
        }
        myfile.close();
    }
    else{
        std::cout << "Links txt not found! -> " << source << std::endl;
    }

}

void LatticePopulation::parseDotTxtLinksFile(std::string i_source){
    int populationSize; //number of agents in the network, specified at the first line of the file
    std::vector<Agent> tempPopulation; //stores the parsed agents, will be returned
    std::vector<int> tempNeighbors; //stores a list of neighbors of the current parsed agent
    int tempIndex; //index for the current parsed agent
    int tempTag; //Tag for the current parsed agent
    
    std::string source = i_source;
    std::ifstream myfile(source);
    if (myfile.is_open())
    {
        std::string populationSizeString = "";
        
        //DO NOT DELETE - read first line, looking for the number of agents to include -
        getline(myfile, populationSizeString);
        
        //parsing each line, for each agent.
        //Format:AgentIndex SignalBit NeighborIndex NeighborIndex ...
        std::string currentAgentLine;
        std::string delimiter = " ";
        
        size_t pos = 0;
        std::vector<std::string> tokens;
        
        while (getline(myfile, currentAgentLine)){ //for each line to read, break it down and add to a vector
            while ((pos = currentAgentLine.find(delimiter)) != std::string::npos){ //for each of the tokens, delimited by a space
                tokens.push_back(currentAgentLine.substr(0, pos)); //add token to vector of strings
                //std::cout << "Adding " << currentAgentLine.substr(0, pos) << " token!" << std::endl;
                currentAgentLine.erase(0, pos + delimiter.length()); //eliminate the token and delimiter from the string
            }
            tokens.push_back(currentAgentLine); //TODO: understand this better, why is it needed a last time?
            
            //create the neigbors vector to be used in the constructor of this new agent.
            for (int i = 2; i < (int)tokens.size(); i++){
                tempNeighbors.push_back(atoi(tokens[i].c_str()));
            }
            //create agent with the line read
            tempIndex = atoi(tokens[0].c_str());
            tempTag = atoi(tokens[1].c_str());
            
            //TODO: change to pointers
            agentsInPop.push_back(Agent(tempIndex, tempTag, tempNeighbors));
            
            tempNeighbors.clear();
            tokens.clear();
        }
        myfile.close();
    }
    else{
        std::cout << "Links txt not found! -> " << source << std::endl;
    }
}

//Delegates the creation of the population to correct function, who can handle the given file extension type
void LatticePopulation::generateLinks(std::string i_source){
    //find out which type of file we are dealig with, by finding out the name of the extension
    std::string filePath = i_source;
    std::string delimiter = "."; //extension name comes after the last .
    size_t pos = 0;
    std::string fileTypeName = ""; //stores the file type name

    while ((pos = filePath.find(delimiter)) != std::string::npos){ //erases everything before the last delimiter
        filePath.erase(0, pos + delimiter.length());
    }
    fileTypeName = filePath; //gets what's left from the file, after the last delimiter
    
    //for each kind of known file type, there is a function that can parse it
    if (fileTypeName == "txt") {
        //parse txt with links
        parseDotTxtLinksFile(i_source);
    }else if (fileTypeName == "links"){
        //parse links file
        parseDotLinksFile(i_source);
    }else
        printf("Links file type extension not recognized! -> %s", fileTypeName.c_str());

}

//parse input text file with networks, and define initial strategies
//Initialization:
//	parse input text file with networks, and define initial strategies
//	gives a random strategy for each of the population's agents, either 0 or 1
//	Parse agents from a text file to create a population
void LatticePopulation::init(std::string source, int totalNumberOfTags, std::string type){
	//0 tags should be the same as 1 tag!!!
	if (totalNumberOfTags <= 1) //0 tags should be the same as 1 tag!!!
		_numberOfTags = 0; 
	else
		_numberOfTags = totalNumberOfTags;
    _type = type;
    generateLinks(source);
    generateRandomStrategies(totalNumberOfTags);
}