 //
//  GlobalRandomGen.h
//  74100Unix
//
//  Created by Elvio on 27/03/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//

#ifndef ___4100Unix__RandomSeedGenerator__
#define ___4100Unix__RandomSeedGenerator__
#include <random> //for a better random()

//Follows singleton pattern
//TODO: better comment for class
class GlobalRandomGen{
    static GlobalRandomGen * _globalRandomGen_instance;
    
    std::random_device _rd; //trully random seed, different everytime, even when running multiple instances at the exact same time. returns an unsigned int
    
    signed int _seed = -1;
    
    std::mt19937 * _gen; //engine
    //and distribuitions
    std::uniform_real_distribution<double> _distribution0Till1;
    std::uniform_int_distribution<int> _distribuition0Till100;
    std::uniform_int_distribution<int> _distribuition0TillMax;
    
    GlobalRandomGen();
    
public:
    static GlobalRandomGen * getInstance();
    void setSeed(signed int newSeed); //sets a seed for the generator
    signed int getSeed(); //returns current _seed
    long double getRandomF0Till1();
    int getRandomI0Till100();
    int getRandomTillMax(int max);
};

#endif /* defined(___4100Unix__RandomSeedGenerator__) */