//
//  TestClass.cpp
//  74100Unix
//
//  Created by Elvio on 27/03/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//

#include "TestClass.h"

TestClass::TestClass(){}
TestClass::~TestClass(){}

void workerThread(){
	printf("This is worker_thread()\n");
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	printf("Finished! \n");
}

void workerThreadArg(int i){
	std::cout << "Thread " << i << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds((i*2000)));
	std::cout << "Finished " << i << std::endl;
}

void TestClass::stlSimpleThreading(){
	const int num_threads = 5;
	std::thread t[num_threads];

	//Launch a group of threads
	for (int i = 0; i < num_threads; ++i) {
		t[i] = std::thread(workerThread);
	}

	std::cout << "Launched from the main\n";

	//Join the threads with the main thread
	for (int i = 0; i < num_threads; ++i) {
		t[i].join();
	}
}

void TestClass::stlSimpleThreadingArg(){
	const int num_threads = 5;
	std::vector<std::thread> t;

	//Launch a group of threads
	for (int i = 0; i < num_threads; ++i) {
		t.push_back(std::thread(workerThreadArg,i));
	}
	std::cout << "Launched from the main\n";

	//Join the threads with the main thread
	for (int i = 0; i < num_threads; ++i) {
		t[i].join();
	}
}

void TestClass::stlThreadingArgDetach(){
	const int num_threads = 5;

	//Launch a group of threads
	for (int i = 0; i < num_threads; ++i) {
		std::thread(workerThreadArg, i).detach();
	}
	std::cout << "Launched from the main\n";
}

// ************************************************************************************************************
/*
void *worker_thread(void *arg)
{
    printf("This is worker_thread()\n");
    pthread_exit(NULL);
}

int TestClass::testThread()
{
    
    std::vector<pthread_t> my_threadArray(5);
    int ret = 0;
    long id;
    
    for(id = 0; id <= 5; id++){
        printf("In main: creating thread\n");
        ret =  pthread_create(&my_threadArray[id], NULL, &worker_thread, NULL );
        
        if(ret != 0) {
            printf("Error: pthread_create() failed\n");
            exit(EXIT_FAILURE);
        }
    }
    
    pthread_exit(NULL);
}
// ************************************************************************************************************

void *worker_thread2(void * arg)
{
    printf("This is worker_thread #%ld\n", (long)arg);
    sleep(10/((long)arg));
    printf("This is worker_thread FINISHED #%ld\n", (long)arg);
    pthread_exit(NULL);
}

int TestClass::testThreadWithArg()
{
    std::vector<pthread_t> my_thread(5);
    
    long id;
    for(id = 1; id <= 5; id++) {
        int ret =  pthread_create(&my_thread[id], NULL, &worker_thread2, (void*)id);
        if(ret != 0) {
            printf("Error: pthread_create() failed\n");
            exit(EXIT_FAILURE);
        }
    }
    
    pthread_exit(NULL);
}

void TestClass::testTime(){
    std::cout << "starting" << std::endl;
    sleep(5);
    std::cout << "finished" << std::endl;
}
*/

/* // implicit conversion of classes:
 #include <iostream>
 using namespace std;
 
 class A {};
 
 class B {
 public:
 // conversion from A (constructor):
 B (const A& x) {}
 // conversion from A (assignment):
 B& operator= (const A& x) {return *this;}
 // conversion to A (type-cast operator)
 operator A() {return A();}
 };
 
 int main ()
 {
 A foo;
 B bar = foo;    // calls constructor
 bar = foo;      // calls assignment
 foo = bar;      // calls type-cast operator
 return 0;
 } */