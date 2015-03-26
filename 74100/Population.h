#pragma once
#include "Agent.h"
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>



//Pure virtual class
class Population
{
public:
	Population();
	~Population();

	int getSize();
	int getNumberOfTags();
	std::string getType();

	//TODO maybe fix this with () const?  to prevent ppl with this pointer to change the pop
	std::vector<Agent> * getPopulationPtr ();
	//TODO: This needs to go to a start function and whatnot, not ok like this. the tags = 0; for example needs to be changed
	virtual void init(std::string source, int totalNumberOfTags, std::string type) = 0;
	

protected:
	std::vector<Agent> agentsInPop;
	int _numberOfTags = 0;
	std::string _type = "";
};

class LatticePopulation : public Population {
public:
	LatticePopulation();
	~LatticePopulation();
	void init(std::string source, int totalNumberOfTags, std::string type);
	void generateLinks(std::string source);
	void generateRandomStrategies(int totalNumberOfTags);
};