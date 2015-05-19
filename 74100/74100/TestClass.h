//
//  TestClass.h
//  74100Unix
//
//  Created by Elvio on 27/03/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//

#ifndef ___4100Unix__TestClass__
#define ___4100Unix__TestClass__

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <thread>
#include <fstream>
#include "GlobalRandomGen.h" //for GlobalRandom
#include <cstdlib> //for atof

class TestClass
{
public:
    TestClass();
    ~TestClass();

    void stlSimpleThreading();
	void stlSimpleThreadingArg();
	void stlThreadingArgDetach();

	//comented due to using posix threading, which only works in Unix systems
    // int testThread(); 
    // int testThreadWithArg();

	void generateRand();
	void generateRand(unsigned int inSeed);
    
    void testTime();

	void testGSL();
    
    void concurrentFileOpen(unsigned int seed);
    
    void testGlobalRand();
    void testGlobalRandInt();
    void testGenerateRandMax();
    
    void testdoubleatof();
    
};

#endif /* defined(___4100Unix__TestClass__) */
