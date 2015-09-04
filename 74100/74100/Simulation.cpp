//
//  Simulation.cpp
//  74100Unix
//
//  Created by Elvio on 27/03/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//

#include "Simulation.h"

Simulation::Simulation(Population * population, int & i_maxGenerations,
	long double & tauTag, long double & tauStrat, long double & noiseStrat, long double & noiseTag, std::vector<long double> & payoffMatrix, std::vector<DataSubscriber*> & dataSubscribers)
{
    //Initializing simulation information/data
    stateManager = SimulationStateManager();
    stateManager.setSimulationData(population, i_maxGenerations, tauTag, tauStrat, noiseStrat, noiseTag, payoffMatrix);
    
    //core vector with the agents
    agentsVectorPtr = stateManager.getPopulation()->getAgentsPtr();

    //attaching data subs
    if (!dataSubscribers.empty()){
        for (int i = 0; i < (int)dataSubscribers.size(); i++){
            stateManager.attachDataSubscriber(dataSubscribers[i]);
        }
    }
    
    /**/ //print information at the start te the simulation
    std::cout << "Simulation created!" << std::endl;
    std::cout << "#Generations: "<< *stateManager.getMaxGenerations() << std::endl;
    std::cout << "#Tags: "<< stateManager.getPopulation()->getNumberOfTags() << std::endl;
	std::cout << "TauTag: " << *stateManager.getTauTag() << std::endl;
	std::cout << "TauStrat: " << *stateManager.getTauStrat() << std::endl;
	std::cout << "NoiseStrat: " << *stateManager.getNoiseStrat() << std::endl;
	std::cout << "NoiseTag: " << *stateManager.getNoiseTag() << std::endl;
    std::cout << "PayoffMatrix CC: "<< stateManager.getPayoffMatrix()->at(0) << std::endl;
    std::cout << "PayoffMatrix CD: "<< stateManager.getPayoffMatrix()->at(1) << std::endl;
    std::cout << "PayoffMatrix DC: "<< stateManager.getPayoffMatrix()->at(2) << std::endl;
    std::cout << "PayoffMatrix DD: "<< stateManager.getPayoffMatrix()->at(3) << std::endl;
    //*/
}

Simulation::~Simulation(){
    printf("Deleting simulation\n");
}

//TODO: add comment
void Simulation::runSimulation(){
    aux_Hi_Payoff = highestPayoffInMatrix(*stateManager.getPayoffMatrix()); //caching both these variables
    aux_Lo_Payoff = lowestPayoffInMatrix(*stateManager.getPayoffMatrix());
    
    
    if (*stateManager.getMaxGenerations() > 0) {
        //run for specific number of generations
        for (int i = 0; i < *stateManager.getMaxGenerations(); i++){
            runOneGeneration();
            printPercentageDone(i); //show in console the % of generations completed
        }
        
    }else{
        //run until a certain number of StrategyChanges
        unsigned int maxStrategyChanges = 10000 * stateManager.getPopulation()->getSize();
        
        while (*stateManager.getStrategyChangeCounter() <= maxStrategyChanges) {
            runOneGeneration();
            printPercentageStrategyChangesDone(*stateManager.getStrategyChangeCounter());
			if (continuosEquilibrium()){
				printf("Reached equilibrium!!!!! -> %i \n", previousNumberOfCooperationActions);
				printf("Generations done -> %i \n", stateManager.getCurrentGenerationCounter());
				break;
			}
        }
        std::cout << "Number of strategy changes: " << *stateManager.getStrategyChangeCounter() << std::endl;
    }
    
    //inform datasubs that the simulation is over
    stateManager.notifyDataSubscribersGameOver();    
}

//make agents play eachother, calculate their fitness and decide if they should update their tag/strategy
void Simulation::runOneGeneration(){
    stateManager.incCurrentGeneration(); //So data subs know which generation it is. First calls makes it start at zero
    gameTheoryGames(*agentsVectorPtr);
    setFittnessAndResetPayoffs(*agentsVectorPtr);
    if (stateManager.getNumbAttachedSubscribers() != 0) {
        stateManager.notifyDataSubscribers(); //update DataSubscribers
        stateManager.resetStateForNextGeneration(); //resets the variables who need to be reset each generation related to data subscribers
    }
    evolutionaryGameTheory(*agentsVectorPtr, *stateManager.getTauTag(), *stateManager.getTauStrat(), *stateManager.getNoiseStrat(), *stateManager.getNoiseTag(), *stateManager.getPayoffMatrix());
}

//updates the payoffs of the two agents, simulating a one shot game theory interaction
void Simulation::oneShotInteraction(Agent & a, Agent & b){
    long double payoffA = 0.0f; //payoff earned by A in this specific game
    long double payoffB = 0.0f; //payoff earned by B in this specific game
    
    int aStrategyPlayingOther = a.strategy[b.tag];
    int bStrategyPlayingOther = b.strategy[a.tag];

    /**
     std::cout << b.getIndex() << " has strategy {";
     for (int x = 0; x < b.strategy.size(); x++){
        std::cout << b.strategy[x] << ", ";
     }
     std::cout << "} and tag: " << b.tag << " and current payoff: " << b.payoff << std::endl;
     //*/
    
    //_payoffMatrix[0] = C and C  3
    //_payoffMatrix[1] = C and D  0
    //_payoffMatrix[2] = D and C  5
    //_payoffMatrix[3] = D and D  1
    
    std::vector<long double> * _payoffMatrix = stateManager.getPayoffMatrix();
    
    if (aStrategyPlayingOther == bStrategyPlayingOther){
        if (aStrategyPlayingOther == 0){
            //C C
            payoffA = _payoffMatrix->at(0);
            payoffB = _payoffMatrix->at(0);
            if (stateManager.getNumbAttachedSubscribers() != 0){
                stateManager.incrementCooperativeActions();
                stateManager.incrementCooperativeActions();
            }
        }
        else{
            //D D
            payoffA = _payoffMatrix->at(3);
            payoffB = _payoffMatrix->at(3);
        }
    }
    else{
        if (aStrategyPlayingOther == 0){
            //C D
            payoffA = _payoffMatrix->at(1);
            payoffB = _payoffMatrix->at(2);
            if (stateManager.getNumbAttachedSubscribers() != 0){
                stateManager.incrementCooperativeActions();
            }
        }
        else{
            //D C
            payoffA = _payoffMatrix->at(2);
            payoffB = _payoffMatrix->at(1);
            if (stateManager.getNumbAttachedSubscribers() != 0){
                stateManager.incrementCooperativeActions();
            }
        }
    }
    
    a.payoff += payoffA;
    b.payoff += payoffB;
    /**
     std::cout << a.getIndex() << " receives Payoff: " << payoffA << " totaling: " << a.payoff << ".";
     std::cout << "And " << b.getIndex() << " receives:" << payoffB << " totaling: " << b.payoff << "." << std::endl; //*/
}

//population plays games between neighbors, once
void Simulation::gameTheoryGames(std::vector<Agent> & iPopulation){
    Agent * currentAgent = nullptr;
    int currentAgentIndex;
    std::vector<int> currentAgentsNeighbours;
    int nextIndexInNeightbours;
    
    for (int i = 0; i < (int)iPopulation.size(); i++){ //for each agent in the population
        currentAgent = &iPopulation[i];
        currentAgentIndex = currentAgent->getIndex();
        currentAgentsNeighbours = currentAgent->neighbors;
        /**
         std::cout << "Agent " << currentAgent->getIndex() << "------------------------------------------" << std::endl;
         std::cout << currentAgent->getIndex() << " has strategy {";
         for (int x = 0; x < currentAgent->strategy.size(); x++){
             std::cout << currentAgent->strategy[x] << ", ";
         }
         std::cout << "} and tag: " << currentAgent->tag << " and current payoff: " << currentAgent->payoff << std::endl; //*/
         
        
        for (unsigned int ii = 0; ii < (iPopulation[i].neighbors.size()); ii++){ // go through each of his neighbors
            nextIndexInNeightbours = currentAgentsNeighbours[ii];
            if (currentAgentIndex < nextIndexInNeightbours){ //if his index is lower than their's (to make sure there are no repetiting interactions)
                oneShotInteraction(*currentAgent, iPopulation[nextIndexInNeightbours]);//play a oneshot game with neighbour
            }
        }
    }
}

//sets fitness to the accumulated payoff of the generation and sets accPayoff to 0
void Simulation::setFittnessAndResetPayoffs(std::vector<Agent> & iPopulation){
    for (unsigned int i = 0; i < iPopulation.size(); i++){ //for each agent in the population
        iPopulation[i].fitness = iPopulation[i].payoff; //set fitness = accumulatedpayoff
        iPopulation[i].payoff = 0.0f; //clear payoff, to set agent for the next generation
    }
}
//returns the highest payoff possible from the payoffMatrix
long double Simulation::highestPayoffInMatrix(std::vector<long double> & payoffMatrix){
    long double max = std::numeric_limits<long double>::min();
    for (long double i : payoffMatrix){
        if (i > max) {
            max = i;
        }
    }
    return max;
}
//returns the lowest payoff possible from the payoffMatrix
long double Simulation::lowestPayoffInMatrix(std::vector<long double> & payoffMatrix){
    long double min = std::numeric_limits<long double>::max();
    for (long double i : payoffMatrix){
        if (i < min) {
            min = i;
        }
    }
    return min;
}

long double Simulation::maxFitnessDifference(unsigned long numbNeiborsOfA, unsigned long numbNeiborsOfB, long double maxPayoffPossible, long double minPayoffPossible){
    // highest number of neighbors (between agents A and B) times the highest payoff - lowest number of neighbors (from A and B) times the lowest possible payoff
    if (numbNeiborsOfA > numbNeiborsOfB){
        return numbNeiborsOfA * maxPayoffPossible - numbNeiborsOfB * minPayoffPossible;
    }
    else{
        return numbNeiborsOfB * maxPayoffPossible - numbNeiborsOfA * minPayoffPossible;
    }
}

void Simulation::copyNeighboursStrategy(Agent & agent, Agent & neighbour, long double & noiseStrat){
    long double probabilityOfNoise = 0;
    int randomNumber = 0;
    
    //for each of the strategies, induce noise given probability noiseStrat
    for (unsigned int i = 0; i < agent.strategy.size(); i++) {
        probabilityOfNoise = GlobalRandomGen::getInstance()->getRandomF0Till1();
        //printf("noiseStrat = %Lf and random: %Lf\n", noiseStrat, probabilityOfNoise);
        
        if (noiseStrat >= probabilityOfNoise) {
            //include noise
            randomNumber = GlobalRandomGen::getInstance()->getRandomTillMax(1);
            agent.strategy[i] = randomNumber;
        }else{
            //simply copy STRAT[i] from neighbour
            //printf("%i index changed from %i to %i\n", i, agent.strategy[i], neighbour.strategy[i]);
            agent.strategy[i] = neighbour.strategy[i];
        }
    }
}

void Simulation::copyNeighboursTag(Agent & agent, Agent & neighbour, int numberOfAvailableTags, long double & noiseTag){
    long double probabilityOfNoise = 0;
    int randomNumber = 0;

    if (numberOfAvailableTags > 0) {
        //induce noise
        probabilityOfNoise = GlobalRandomGen::getInstance()->getRandomF0Till1();
        //printf("noiseTag = %Lf and random: %Lf\n", noiseTag, probabilityOfNoise);
        
        if (noiseTag >= probabilityOfNoise) {
            //include noise, random EXISTING tag
            randomNumber = GlobalRandomGen::getInstance()->getRandomTillMax(numberOfAvailableTags-1);
            agent.tag = randomNumber;
        }else{
            //simply copy TAG from neighbour
            //printf("Copying tag! From %i to %i\n", agent.tag, neighbour.tag);
            agent.tag = neighbour.tag;
        }
    }
}

void Simulation::imitationProcessSingleTau(Agent & agent, Agent & neighbour, long double & noiseStrat, long double & noiseTag){
    //ALWAYS imitates strategy and tag
    copyNeighboursStrategy(agent, neighbour, noiseStrat);
    stateManager.incrementStrategyChangeCounter();
    
    copyNeighboursTag(agent, neighbour, stateManager.getPopulation()->getNumberOfTags(), noiseTag);
}

//TODO: continue comment -> This imitation process allows the study of the timescale of
void Simulation::imitationProcessAlpha(Agent & agent, Agent & neighbour, long double & tauTag, long double & tauStrat, long double & noiseStrat, long double & noiseTag){
    
    //TODO:create a new random gen for this, performance?
    long double random0tillTauStratPlusTauTag = GlobalRandomGen::getInstance()->getRandomDouble0TillMax(tauTag + tauStrat);
    
    //std::cout << "tauStrat: " << tauStrat << " tauTag: " << tauTag << " random0tillTauStratPlusTauTag: " << random0tillTauStratPlusTauTag << std::endl;
    
    //only imitates tag OR strat
    if (tauStrat > random0tillTauStratPlusTauTag){
        //copy ONLY the strat
        copyNeighboursStrategy(agent, neighbour, noiseStrat);
        stateManager.incrementStrategyChangeCounter();
    }
    else{
        //copy only the tag  (if there's more than one)
        copyNeighboursTag(agent, neighbour, stateManager.getPopulation()->getNumberOfTags(), noiseTag);
    }
}

void Simulation::imitationProcess(Agent & agent, Agent & neighbour, long double & tauTag, long double & tauStrat, long double & noiseStrat, long double & noiseTag, std::vector<long double> & payoffMatrix){
    
    long double payoffDiff = neighbour.fitness - agent.fitness;
    if (payoffDiff > 0) { //only considers changing strategy OR tag, if the neighbor's payoff is better than his own
        
        long double imitationProbability; //holds probability of imitating the other agent (his strategy OR tag his tag)
        
        //imitationProbability = (fitness_j-fitness_i) / (Diferenca maxima possivel entre fitness)
        imitationProbability = (payoffDiff) /
        (maxFitnessDifference(agent.neighbors.size(), neighbour.neighbors.size(), aux_Hi_Payoff, aux_Lo_Payoff));
        //std::cout << "imitationProbability = (" << neighbour.fitness << "-" << agent.fitness << ") / " << maxFitnessDifference(agent.neighbors.size(), neighbour.neighbors.size(), aux_Hi_Payoff, aux_Lo_Payoff) << std::endl;
        
        long double random0till1; //long double between 0.0 and 1.0, inclusive
        random0till1 = GlobalRandomGen::getInstance()->getRandomF0Till1();
        //printf("p = %Lf and random: %Lf\n", imitationProbability, random0till1);
        
        //choose which evolutionary copying process to use
        if (imitationProbability >= random0till1){
            if (tauStrat == 0 && tauTag == 0) {
                //Copy strat AND tag
                imitationProcessSingleTau(agent, neighbour, noiseStrat, noiseTag);
            }else{
                //copy strat OR copy tag, "imitationProcessAlpha"
                imitationProcessAlpha(agent, neighbour, tauTag, tauStrat, noiseStrat, noiseStrat);
            }
        }
    }
}


void Simulation::evolutionaryGameTheory(std::vector<Agent> & iPopulation, long double & tauTag, long double & tauStrat, long double & noiseStrat, long double & noiseTag, std::vector<long double> & payoffMatrix){
    for (int i = 0; i < (int)iPopulation.size(); i++){ //for each agent in the population
        /**
        printf("Agent: %i -------------------------------------------------------------\n", i);
        printf("Has      fit: %Lf #Neigh: %i", iPopulation[i].fitness, (int)iPopulation[i].neighbors.size());
        printf(" tag: %i strat: ", iPopulation[i].tag);
        for (int x = 0; x < iPopulation[i].strategy.size(); x++) printf( "%d, ", iPopulation[i].strategy[x]); printf("\n"); //*/
        
        
        //pick a random neighbor
        int randomIndex = GlobalRandomGen::getInstance()->getRandomTillMax((unsigned int)iPopulation[i].neighbors.size()-1); //generates random number between 0 and sizeof vector neighbors, minus one as we want one of the indexes;
        int randomNeighborIndex = iPopulation[i].neighbors[randomIndex]; //goes to that index to get the neighbors population index
        /**
        printf("Chose: %d  fit: %Lf   #Neigh: %d  strat: ", randomNeighborIndex , iPopulation[randomNeighborIndex].fitness, (int)iPopulation[randomNeighborIndex].neighbors.size());
        for (int x = 0; x < iPopulation[randomNeighborIndex].strategy.size(); x++) printf("%d, ", iPopulation[randomNeighborIndex].strategy[x]); printf("\n"); //*/
        
        imitationProcess(iPopulation[i], iPopulation[randomNeighborIndex], tauTag, tauStrat, noiseStrat, noiseTag, payoffMatrix);

    }
}

//if the number of cooperative actions has been the same for xAmount of times, return true
bool Simulation::continuosEquilibrium(){
	if (stateManager.getPrevNumberCooperativeActions() == previousNumberOfCooperationActions){
		counter++;
		if (counter >= 3000){
			return true;
		}
	}
	else{
		previousNumberOfCooperationActions = stateManager.getPrevNumberCooperativeActions();
		counter = 0;
	}
	return false;
}

//GOAL is hitting a certain number of generations - > every 10% of the generations done, prints in console the progress
void Simulation::printPercentageDone(int & iGeneration){
    
    if (_tenPercentGenerations == -1) _tenPercentGenerations = (int)((*stateManager.getMaxGenerations()) * 0.1);
    
    if (_percentage * _tenPercentGenerations == iGeneration){
        printf("%%%%  %%%%  %%%%  %%%%  -- Progress: %d%%  -- %%%%  %%%%  %%%%  %%%%\n",(_percentage * 10));
        _percentage++;
    }
}

//GOAL is hitting a certain number of strategy changes - > every 10% of the generations done, prints in console the progress
void Simulation::printPercentageStrategyChangesDone(int currentNumberChanges){
    if (_tenPercentGenerations == -1) _tenPercentGenerations = (stateManager.getPopulation()->getSize()) * 1000;
    
    int nextMilestoneGeneration = _percentage * _tenPercentGenerations; //milestone representing 10%
    
    if (nextMilestoneGeneration <= currentNumberChanges){
        printf("%%%%  %%%%  %%%%  %%%%  -- Progress: %d%%  -- %%%%  %%%%  %%%%  %%%%\n",(_percentage * 10));
        _percentage++;
    }
}