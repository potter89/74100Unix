#include "GlobalRandomGen.h"

GlobalRandomGen::GlobalRandomGen(){
    if(_seed == -1){
        //if no seed has been given, get a random seed
        printf("GlobalRand -> No seed given! ");
        _seed = _rd();
        while (_seed == -1) _seed = _rd();
    }
    //initialize Rnd Engine
    printf("Seed used: %d \n", _seed);
    _gen = new std::mt19937(_seed); //mt19937 is an engine than generates high quality random numbers
    _distribution0Till1 = std::uniform_real_distribution<double>(0.0,1.0);
    _distribuition0Till100 = std::uniform_int_distribution<int>(0,100);
}

//Instantiates (AND ensures only one) instance of the Random Generator exists
GlobalRandomGen * GlobalRandomGen::getInstance(){
    if (!_globalRandomGen_instance){
        _globalRandomGen_instance = new GlobalRandomGen();
    }
    return _globalRandomGen_instance;
}

void GlobalRandomGen::setSeed(unsigned int newSeed){
    printf("GlobalRand -> Set new seed: %d \n", newSeed);
    delete _gen;
    _gen = new std::mt19937(newSeed);
}

unsigned int GlobalRandomGen::getSeed(){
    return _seed;
}

long double GlobalRandomGen::getRandomF0Till1(){
    return _distribution0Till1(*_gen);
}

int GlobalRandomGen::getRandomI0Till100(){
    return _distribuition0Till100(*_gen);
}

int GlobalRandomGen::getRandomTillMax(int max){
    _distribuition0TillMax = std::uniform_int_distribution<int>(0, max);
    return _distribuition0TillMax(*_gen);
}