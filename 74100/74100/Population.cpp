#include "Population.h"

//Population cl@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ss
Population::Population(){}
Population::~Population(){}

int Population::getSize(){
	return agentsInPop.size();
}
int Population::getNumberOfTags(){
	return _numberOfTags;
}
std::string Population::getType(){
	return _type;
}
std::vector<Agent> * Population::getPopulationPtr(){
	return &agentsInPop;
}



//Lattice cl@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ss
LatticePopulation::LatticePopulation(){}
LatticePopulation::~LatticePopulation(){}

//generates random tag, from 0 to totalNumberOfTags, and fills <_strategy> with random 0 and 1's
void LatticePopulation::generateRandomStrategies(int totalNumberOfTags){
	//TODO: use a better random gen
	/* initialize random seed: */
	int totNumberOfTags = totalNumberOfTags;
	
	srand(time(NULL));
	int randomNumber;

	for (int i = 0; i < (int)agentsInPop.size(); i++){
		//random tag
		if (totNumberOfTags != 0){
			randomNumber = rand() % totNumberOfTags;
			agentsInPop[i].tag = randomNumber;
		}
		else{
			agentsInPop[i].tag = 0;
		}

		//0 tags should be the same as 1 tag!!!
		if (totNumberOfTags < 1) totNumberOfTags = 1;

		//random strategy for each tag available
		for (int x = 0; x < totNumberOfTags; x++){
			/* generate secret number between 0 and 1 */
			randomNumber = rand() % 2;
			agentsInPop[i].strategy.push_back(randomNumber);
		}
	}
}

//Parse agents from a text file, filling the population vector
void LatticePopulation::generateLinks(std::string source){
	int populationSize; //number of agents in the network, specified at the first line of the file
	std::vector<Agent> tempPopulation; //stores the parsed agents, will be returned
	std::vector<int> tempNeighbors; //stores a list of neighbors of the current parsed agent
	int tempIndex; //index for the current parsed agent
	int tempTag; //Tag for the current parsed agent

	std::ifstream myfile(source);
	if (myfile.is_open())
	{
		std::string populationSizeString = "";

		//DO NOT DELETE - read first line, looking for the number of agents to include -
		getline(myfile, populationSizeString);
		populationSize = atoi(populationSizeString.c_str());

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
		std::cout << "Not links txt not found!" << std::endl;
	}
}

//parse input text file with networks, and define initial strategies
//Initialization:
//	parse input text file with networks, and define initial strategies
//	gives a random strategy for each of the population's agents, either 0 or 1
//	Parse agents from a text file to create a population
void LatticePopulation::init(std::string source, int totalNumberOfTags, std::string type){
	_numberOfTags = totalNumberOfTags;
	_type = type;
	generateLinks(source);
	generateRandomStrategies(totalNumberOfTags);
}