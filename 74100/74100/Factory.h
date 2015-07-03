//
//  Factory.h
//  74100Unix
//
//  Created by Elvio on 27/03/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//

#ifndef ___4100Unix__Factory__
#define ___4100Unix__Factory__

#include "Population.h"
#include "Simulation.h"
#include "MiscCode.h" //for custom Cin
#include <fstream>


class Factory
{
public:
    Factory();
    ~Factory();
    
    
    Simulation * createSimulation(std::string inputPath);
    Simulation * createSimulation(int totalTags, std::string linksPath, std::string popType, int i_maxGenerations, long double tau, std::vector<long double> payoffMatrix, std::vector<std::string> & dataSubscribers);

    void generateLatticeLinksTextFile();
    void generateForwardBehind();
    void generateFullyConnected();
    void generateShellScript();
    
private:
    std::string _populationType = "";
    std::string _linksFilePath = "";
    int _totalGenerations = 0;
    int _totalTags = 0;
    long double _tau = 0.0f;
    std::vector<long double> _payOffMatrix;
    std::vector<int> _percentages;
    std::vector<std::string> _subscribers;
	std::vector<DataSubscriber *> _subscribersParsed;
    
    std::string _tempString = "";
    std::string const _delimiter = " ";

	void parseConfiguration(std::string inputPath);
	void parseDataSubscribers(const std::vector<std::string> & subscribers, const int totalTags, const std::string popType, const int sizePop, const int i_maxGenerations, const long double tau, const std::vector<long double> payoffMatrix);

	Population * createPopulation(std::string linksPath, std::string populationType, int totalTags);

	void clearParsedVariables();
};

#endif /* defined(___4100Unix__Factory__) */
