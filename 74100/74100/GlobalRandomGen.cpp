#include "GlobalRandomGen.h"

GlobalRandomGen::GlobalRandomGen(){
    if(_seed == -1){
        //if no seed has been given, get a random seed
        _seed = _rd();
        while (_seed == -1) _seed = _rd();
    }
    //initialize Rnd Engine
    //printf("Seed used: %d \n", _seed);
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

void GlobalRandomGen::setSeed(signed int newSeed){
    printf("GlobalRand -> Set new seed: %d \n", newSeed);
    delete _gen; //delete previous engine
    _seed = newSeed;
    _gen = new std::mt19937(_seed); //setup new engine with the given seed
}

signed int GlobalRandomGen::getSeed(){
    return _seed;
}

long double GlobalRandomGen::getRandomF0Till1(){
    return _distribution0Till1(*_gen);
}

long double GlobalRandomGen::getRandomDouble0TillMax(double max){
	//TODO: there's room for optimization if we store the max value, and do an if instead of setting every time
	_distributionDouble0TillMax = std::uniform_real_distribution<double>(0.0, max);
	return _distributionDouble0TillMax(*_gen);
}

int GlobalRandomGen::getRandomI0Till100(){
    return _distribuition0Till100(*_gen);
}

int GlobalRandomGen::getRandomTillMax(int max){
	//TODO: there's room for optimization if we store the max value, and do an if instead of setting every time
    _distribuition0TillMax = std::uniform_int_distribution<int>(0, max);
    return _distribuition0TillMax(*_gen);
}