#pragma once
#include<vector>
#include "DataSubscriber.h"
#include "Agent.h"
#include "SimulationData.h"

class SimulationStateManager
{
	SimulationData _simData;

public:
	SimulationStateManager();
	SimulationStateManager(int c, int d);
	~SimulationStateManager();

	int getNumbAttachedSubscribers();

	//setup simdata
	void setPopulationToSendOut(std::vector<Agent> * population);
	void setTypeToSendOut(std::string type);

	//setup subs
	void attachDataSubscriber(DataSubscriber * newSub);
	void detatchDataSubscriber(DataSubscriber * newSub);
	void notifyDataSubscribers();

	//simulation changes updating functions
	void incrementCooperativeActions();
	void resetStateForNextGeneration();

};