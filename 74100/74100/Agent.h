//
//  Agent.h
//  74100Unix
//
//  Created by Elvio on 27/03/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//

#ifndef ___4100Unix__Agent__
#define ___4100Unix__Agent__

#include <vector>
#include <iostream>

class Agent{
    
public:
    long double payoff = 0.0f;
    long double fitness = 0.0f;
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
     long double getPayoff();
     long double getFitness();
    //*/
    
private:
    int _index;
};

#endif /* defined(___4100Unix__Agent__) */
