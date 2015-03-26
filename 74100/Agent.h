#pragma once
#include <vector>
#include <iostream>

class Agent{

public:	
	
	float payoff = 0.0f;
	float fitness = 0.0f;
	int tag = 0;
	std::vector<int> strategy; //index for each tag, 0 means cooperation, 1 means defection to that tag
	std::vector<int> neighbors; //index of his neighbors
	
	Agent();
	Agent(int indexNumber, int tagNumber, std::vector<int> neighborsIndexes);
	Agent(const Agent &o);
	~Agent();

	int getIndex();
	//TODO: finish this, set things to private..
	/**
	int getTag();
	float getPayoff();
	float getFitness();
	/**/

private:
	int _index;
};