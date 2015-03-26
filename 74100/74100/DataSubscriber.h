#pragma once
#include "Agent.h"
#include <vector>


class DataSubscriber
{
public:
	DataSubscriber();
	~DataSubscriber();

	virtual void update(int numberOfCooperativeActions, std::vector<Agent> populationAgents, std::string popType) = 0;
};

class ConsoleDataSubscriber : public DataSubscriber
{
public:
	void update(int numberOfCooperativeActions, std::vector<Agent> populationAgents, std::string popType);
	ConsoleDataSubscriber();
	~ConsoleDataSubscriber();
};

class SimpleConsoleDataSubscriber : public DataSubscriber
{
private:
	const int REFRESHRATE = 15000;
	int refreshRateCounter = 0;

public:
	void update(int numberOfCooperativeActions, std::vector<Agent> populationAgents, std::string popType);
	SimpleConsoleDataSubscriber();
	~SimpleConsoleDataSubscriber();
};