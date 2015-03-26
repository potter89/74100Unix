#pragma once
#include "Population.h"
#include "Simulation.h"
#include <fstream>


class Factory
{
public:
	Factory();
	~Factory();

	Population * createPopulation(std::string linksPath, std::string populationType, int totalTags);
	Simulation * createSimulation(std::string inputPath);
	Simulation * createSimulation(int totalTags, std::string linksPath, std::string popType, int i_maxGenerations, float tau, std::vector<float> payoffMatrix, std::vector<std::string> * dataSubscribers);

	void generateLatticeLinksTextFile();
	void generateTwoForwardTwoBehind();
	void generateFullyConnected();

private:
	void parseConfiguration(std::string inputPath);
	
	std::string _populationType = "";
	std::string _linksFilePath = "";
	int _totalGenerations = 0;
	int _totalTags = 0;
	float _tau = 0.0f;
	std::vector<float> _payOffMatrix;
	std::vector<int> _percentages;
	std::vector<std::string> _subscribers;

	std::string _tempString = "";
	std::string const _delimiter = " ";
};