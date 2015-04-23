//
//  DataSubscriber.h
//  74100Unix
//
//  Created by Elvio on 27/03/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//

#ifndef ___4100Unix__DataSubscriber__
#define ___4100Unix__DataSubscriber__

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
    const int REFRESHRATE = 150;
    int refreshRateCounter = 0;
    
public:
    void update(int numberOfCooperativeActions, std::vector<Agent> populationAgents, std::string popType);
    SimpleConsoleDataSubscriber();
    ~SimpleConsoleDataSubscriber();
};

class TextFileDataSubscriber : public DataSubscriber{
	void update(int numberOfCooperativeActions, std::vector<Agent> populationAgents, std::string popType);
	TextFileDataSubscriber();
	~TextFileDataSubscriber();
};

#endif /* defined(___4100Unix__DataSubscriber__) */
