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
#include <fstream>
#include <iostream>
#include <string>
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
    const int REFRESHRATE = 0;
    int refreshRateCounter = 0;
    
public:
    void update(int numberOfCooperativeActions, std::vector<Agent> populationAgents, std::string popType);
    SimpleConsoleDataSubscriber();
    ~SimpleConsoleDataSubscriber();
};

class TextFileDataSubscriber : public DataSubscriber{
protected:
	std::string _fileName = ""; //final, non duplicate, file name
	std::string _paramFileName = ""; //untouched parsed filename
	std::ofstream _outputTxtFile;
	int _tentativeFileIndex = 1; //sets apart different simulation output files, giving a different index at the end
	
	void setNonDuplicateOutputFileName();
	bool emptyFile(std::string filename);

public:
	void update(int numberOfCooperativeActions, std::vector<Agent> populationAgents, std::string popType);	
	TextFileDataSubscriber(std::string fileName);
	~TextFileDataSubscriber();
};

//This DataSub writes 100 times to a file, averaging the current 
class AverageTextFileDataSubscriber : public TextFileDataSubscriber{
private:
	int _refreshRate;
	int _refreshRateCounter = 0;// starting at 0 forces the first write immediately
	int _average = -1; //starts at -1 to distinguish first write from the others
	std::vector<int> _valuesToAverage;

	int calculateAverage(std::vector<int> inVec);

public:
	void update(int numberOfCooperativeActions, std::vector<Agent> populationAgents, std::string popType);
	AverageTextFileDataSubscriber(std::string fileName, int totalGenerations);
	~AverageTextFileDataSubscriber();
};
#endif /* defined(___4100Unix__DataSubscriber__) */
