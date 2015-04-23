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

class TestClass
{
public:
    TestClass();
    ~TestClass();

    void stlSimpleThreading();
	void stlSimpleThreadingArg();
	void stlThreadingArgDetach();

	//comented due to using posix threading
    // int testThread(); 
    // int testThreadWithArg();

	
    
    void testTime();
    
};

#endif /* defined(___4100Unix__TestClass__) */
