#pragma once
#include <vector>
#include "Agent.h"
#include "DataSubscriber.h"
#include <string>

class SimulationData
{
public:
	SimulationData();
	~SimulationData();
	int _numbCooperativeActions = 0;
	std::vector<Agent> * _population;
	std::string _populationType;

	int _numbSubscribers = 0;
	std::vector<DataSubscriber*> _dataSubscribers;
};