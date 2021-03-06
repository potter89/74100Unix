//
//  Factory.cpp
//  74100Unix
//
//  Created by Elvio on 27/03/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//

#include "Factory.h"
//TODO: in case it cant parse a file, etc, whole program should close
Factory::Factory(){}
Factory::~Factory(){}

Simulation * Factory::createSimulation(int totalTags, std::string linksPath, std::string popType, int i_maxGenerations, long double tauTag, long double tauStrat, long double noiseStrat, long double noiseTag, std::vector<long double> payoffMatrix, std::vector<std::string> & dataSubscribers){
    Population * popul = createPopulation(linksPath, popType, totalTags);
    //Parse DataSubscribers, from text to known datasub types and store it in _subscribersParsed
    parseDataSubscribers(dataSubscribers, totalTags, popType, popul->getSize(), i_maxGenerations, tauTag, tauStrat, noiseStrat, noiseTag, payoffMatrix);
	Simulation * s = new Simulation(popul, i_maxGenerations, tauTag, tauStrat, noiseStrat, noiseTag, payoffMatrix, _subscribersParsed);
    clearParsedVariables();
    return s;
}

//returns polymorphed Population, already initialized with it's ->Init
Population * Factory::createPopulation(std::string linksPath, std::string populationType, int totalTags){
    /**/
    std::string type = populationType;
    Population * retPopulation = nullptr; //population to be returned
    std::string path = linksPath;
    /**
     //TODO: if we are not going to have different types of population, this needs to be reviewed
     bool isTypeRecognized = false;
     while (!isTypeRecognized){ //either have a valid type or die trying
     
     if (type == "LATTICE"){
     retPopulation = new LatticePopulation();
     retPopulation->init(linksPath, totalTags, type);
     return retPopulation;
     }
     else{
     std::cout << "Error!! Population type not found! Input valid type: " << std::endl;
     std::cin >> type;
     }
     }
     //*/
    //TODO: meanwhile, everything should work with a lattice population type class
    retPopulation = new LatticePopulation();
    retPopulation->init(path, totalTags, type);
	if (retPopulation->getSize() <= 0){
		printf("Error creating the population\n");
		char i;	std::cin >> i;
		exit(false); //error creating the population, shouldn't continue running sim
	} 
    return retPopulation;
}

//auxiliar function that creates the filename to the files, to avoid code duplication on parseDataSubscribers
std::string createFileName(const int totalTags, const std::string popType, const int sizePop, const int i_maxGenerations, long double tauTag, long double tauStrat, long double noiseStrat, long double noiseTag, const std::vector<long double> payoffMatrix){
    std::string filename = "";
    filename += std::to_string(totalTags) + "__";
    filename += popType + "_" + std::to_string(sizePop) + "__";
    filename += std::to_string(i_maxGenerations) + "__";
	filename += std::to_string(tauTag) + "__";
	filename += std::to_string(tauStrat) + "__";
	filename += std::to_string(noiseStrat) + "__";
	filename += std::to_string(noiseTag) + "__";
    for (unsigned int i = 0; i < payoffMatrix.size(); i++){
        filename += std::to_string(payoffMatrix[i]) + "_";
    }
    filename += "__#";
    //std::cout << "TextFile filename parsed: " << filename << std::endl;
    
    return filename;
}

//takes in strings parsed into _subscribers and creates known corresponding DataSubscriber
void Factory::parseDataSubscribers(const std::vector<std::string> & subscribers, const int totalTags, const std::string popType, const int sizePop, const int i_maxGenerations, 
	long double tauTag, long double tauStrat, long double noiseStrat, long double noiseTag, const std::vector<long double> payoffMatrix){
    //TODO: this shouldn't be here....
    _subscribersParsed.clear();
    if (!subscribers.empty()){
        for (unsigned int i = 0; i < subscribers.size(); i++){
            if (subscribers[i] == "TextFileDataSubscriber"){
                //1__fc_128__15000__1.0__1.0_0.0_1.0_0.0__#1.txt
				std::string filename = createFileName(totalTags, popType, sizePop, i_maxGenerations, tauTag, tauStrat, noiseStrat, noiseTag, payoffMatrix);
                _subscribersParsed.push_back(new TextFileDataSubscriber(filename));
            }
            if (subscribers[i] == "AverageTextFileDataSubscriber"){
                //1__fc_128__15000__1.0__1.0_0.0_1.0_0.0__#1.txt
				std::string filename = createFileName(totalTags, popType, sizePop, i_maxGenerations, tauTag, tauStrat, noiseStrat, noiseTag, payoffMatrix);
                _subscribersParsed.push_back(new AverageTextFileDataSubscriber(filename, i_maxGenerations));
            }
            if (subscribers[i] == "tds"){
                //1__fc_128__15000__1.0__1.0_0.0_1.0_0.0__#1.txt
				std::string filename = createFileName(totalTags, popType, sizePop, i_maxGenerations, tauTag, tauStrat, noiseStrat, noiseTag, payoffMatrix);
                _subscribersParsed.push_back(new AverageLastThousandDataSubscriber(filename));
            }
            if (subscribers[i] == "ConsoleDataSubscriber"){
                _subscribersParsed.push_back(new ConsoleDataSubscriber());
            }
			if (subscribers[i] == "SimpleConsoleDataSubscriber"){
				_subscribersParsed.push_back(new SimpleConsoleDataSubscriber());
			}
			//TODO:think about this name
			if (subscribers[i] == "tagsDist"){
				//tagsDist_1__fc_128__15000__1.0__1.0_0.0_1.0_0.0__#1.txt
				std::string filename = "tagsDist_" + createFileName(totalTags, popType, sizePop, i_maxGenerations, tauTag, tauStrat, noiseStrat, noiseTag, payoffMatrix);
				_subscribersParsed.push_back(new TagDiversityDataSubscriber(filename));
			}
        }
    }
    else{
        std::cout << "No subscribers connected." << std::endl;
    }
}


//Links Generation!*****************************************************************************************************************************************Links Generation
//Generates a txt file containing lattice with the links of a population, with R rows and C columns, inputed by the user
void Factory::generateLatticeLinksTextFile(){
    int i = 0; //index of the Agent
    std::string s = ""; //current agent line
    int R; //desired number of rows
    int C; //desired number of columns
    
    //ask for name of output file, to create the fileNamePath
    std::cout << "Type the desired number of rows: " << std::endl;
    positiveIntCin(R);
    std::cout << "Type the desired number of columns: " << std::endl;
    positiveIntCin(C);
    
    std::string fileNamePath = "Networks/l_" + std::to_string(R) + "x" + std::to_string(C) + ".txt";
    
    std::ofstream myfile;
    myfile.open(fileNamePath);
    
    myfile << R * C << "\n"; //first line, has the total number of agents
    
    //first row
    s = std::to_string(i) + " 0";
    s += " " + std::to_string(i + 1);
    s += " " + std::to_string(i + C);
    s += '\n'; //i 0 i+1 i+C
    myfile << s;
    i++; s = "";
    for (int x = 0; x < (C - 2); x++){ //i 0 i-1 i+1 i+C
        s += std::to_string(i) + " 0";
        s += " " + std::to_string(i - 1);
        s += " " + std::to_string(i + 1);
        s += " " + std::to_string(i + C);
        s += '\n';
        myfile << s;
        i++; s = "";
    }
    s += std::to_string(i) + " 0";
    s += " " + std::to_string(i - 1);
    s += " " + std::to_string(i + C);
    s += '\n'; //i 0 i-1 i+C
    myfile << s;
    i++; s = "";
    
    //second till R-1 row
    for (int y = 0; y < (R - 2); y++){
        s += std::to_string(i) + " 0";
        s += " " + std::to_string(i - C);
        s += " " + std::to_string(i + 1);
        s += " " + std::to_string(i + C);
        s += '\n'; //i 0 i-C i+1 i+C
        myfile << s;
        i++; s = "";
        for (int x = 0; x < (C - 2); x++){ //i 0 i-C i-1 i+1 i+C
            s += std::to_string(i) + " 0";
            s += " " + std::to_string(i - C);
            s += " " + std::to_string(i - 1);
            s += " " + std::to_string(i + 1);
            s += " " + std::to_string(i + C);
            s += '\n';
            myfile << s;
            i++; s = "";
        }
        s += std::to_string(i) + " 0";
        s += " " + std::to_string(i - C);
        s += " " + std::to_string(i - 1);
        s += " " + std::to_string(i + C);
        s += '\n'; //i 0 i-c i-1 i+C
        myfile << s;
        i++; s = "";
    }
    //Last row
    s += std::to_string(i) + " 0";
    s += " " + std::to_string(i - C);
    s += " " + std::to_string(i + 1);
    s += '\n'; //i 0 i-C i+1
    myfile << s;
    i++; s = "";
    for (int x = 0; x < (C - 2); x++){ //i 0 i-C i-1 i+1
        s += std::to_string(i) + " 0";
        s += " " + std::to_string(i - C);
        s += " " + std::to_string(i - 1);
        s += " " + std::to_string(i + 1);
        s += '\n';
        myfile << s;
        i++; s = "";
    }
    s += std::to_string(i) + " 0";
    s += " " + std::to_string(i - C);
    s += " " + std::to_string(i - 1);
    s += '\n'; //i 0 i-C i-1
    myfile << s;
    //THE END i++; s = "";
    myfile.close();
}

//Generates a txt file containing a well Mixed Graph with the links of a population, with exact number of agents, and average connectivity Z as inputed by the user
//agents are connected to the immediate (index) half agents after and two agents behind him (PS:it loops!)
void Factory::generateForwardBehind(){
    int z; //average connectivity of the network
    int halfZ; //cache how many forward and behind an agent will connect to
    int totalNumberOfAgents; //population will have exactly this number of agents in it
    
    std::cout << "Type the desired average connectivity z (should be a pair number): " << std::endl;
    positiveIntCin(z);
    int zPair = z % 2;
    
    while( zPair != 0) {
        std::cout << "Please enter a non odd number (such as 2 or 4, etc): " << std::endl;
        positiveIntCin(z);
        zPair = z % 2;
    }
    halfZ = z/2;
    
    std::cout << "Type the desired number of agents (Must be above " + std::to_string(z+1) + "): " << std::endl;
    positiveIntCin(totalNumberOfAgents);
    while (totalNumberOfAgents < z+1){
        std::cout << "Must be above " + std::to_string(z+1) + "! Type the desired number of agents: " << std::endl;
        positiveIntCin(totalNumberOfAgents);
    }
    
    //Default FileNamePath creation
    std::string fileNamePath = "Networks/fb_z" + std::to_string(z) + "_" + std::to_string(totalNumberOfAgents) + ".txt";
    
    std::ofstream myfile;
    myfile.open(fileNamePath); //creates or overwrites existing file!
    
    myfile << totalNumberOfAgents << "\n"; //first line, has the total number of agents
    
    int index = 0; //index of the Agent
    std::string s = ""; //current agent line
    int it; //needed for helping knowing how many forward and back we have went already in picking neighbors
    int neighbIndex; //sometimes subtracting or adding when calculating the neighbors index goes over the max number of agents or below zero, which means it completed the circle so it needs adjustment
    std::vector<int> neighborIndexes; //its filled with unordered neighbor indexes
    
    //agent #index
    //index 0 index-halfZ index-halfZ-1 index-halfZ-2 ... index-halfZ index+1 index+2 ... index+halfZ
    //        -------------     back     ---------------------------- ---------   forward   ---------
    
    //for each agent, totalNumberOfAgents times generate his string which contains his neighbors indexes
    for (index = 0; index < totalNumberOfAgents; index++){
        s += std::to_string(index) + " 0";
        for (it = 0; it < halfZ; it++) { // back part
            neighbIndex = index - halfZ + it;
            if(neighbIndex < 0) neighborIndexes.push_back(totalNumberOfAgents+neighbIndex);
            else neighborIndexes.push_back(neighbIndex);
        }
        for (it = 0; it < halfZ; it++) { // forward part
            neighbIndex = index + 1 + it;
            if(neighbIndex >= totalNumberOfAgents) neighborIndexes.push_back(neighbIndex-totalNumberOfAgents);
            else neighborIndexes.push_back(neighbIndex);
        }
        //order vector
        std::sort(neighborIndexes.begin(),neighborIndexes.end());

        //create string
        for (unsigned int it = 0; it < neighborIndexes.size(); it++) {
            s += " " + std::to_string(neighborIndexes.at(it));
        }
        s += '\n';
        myfile << s;
        s=""; neighborIndexes.clear();
    }
    myfile.close();
}

//Generates a txt file containing a well Mixed Graph with the links of a population, with exact number of agents, as inputed by the user
//agents are connected to all the others in the population.
void Factory::generateFullyConnected(){
    int i = 0; //index of the Agent
    int auxI = 0; //aux index of neighbors
    std::string s = ""; //current agent line
    int totalNumberOfAgents; //population will have exactly this number of agents in it
    
    //ask for name of output file, to create the fileNamePath
    std::cout << "Type the desired number of agents (Must be above 2!): " << std::endl;
    positiveIntCin(totalNumberOfAgents);
    while (totalNumberOfAgents < 2){
        std::cout << "Must be above 2! Type the desired number of agents: " << std::endl;
        positiveIntCin(totalNumberOfAgents);
    }
    
    //Default FileNamePath creation
    std::string fileNamePath = "Networks/fc_" + std::to_string(totalNumberOfAgents) + ".txt";
    
    std::ofstream myfile;
    myfile.open(fileNamePath); //creates or overwrites existing file!
    
    myfile << totalNumberOfAgents << "\n"; //first line, has the total number of agents
    for (i = 0; i < totalNumberOfAgents; i++){ //for each agent
        s = "";
        s += std::to_string(i) + " 0"; //i 0
        for (auxI = 0; auxI < totalNumberOfAgents; auxI++){ //append the rest of the population as well
            if (i != auxI){ //except himself
                s += " " + std::to_string(auxI);
            }
        }
        if (i != (totalNumberOfAgents-1)) s += '\n';
        myfile << s; //inserting
    }
    
    /**/
    myfile.close();
}

void Factory::generateShellScript(){
    //fields that need to be inputted
    int numbTags = 0, generations = 0;
    std::string fullPathToExecFolder = "", networkFilePath = "", popType = "", dataSubs = "";
    signed int seed;
    
    //prompt user for input
    std::cout << "Creating a shell file, please input values for the given fields:" << std::endl;
    
    std::cout << "(string)Full path to Folder with Unix Executable: " << std::endl;
    customCin(fullPathToExecFolder);
    std::cout << "(int)Number of Tags: " << std::endl;
    positiveIntCin(numbTags);
    std::cout << "(int)Number of Generations: " << std::endl;
    positiveIntCin(generations);
    std::cout << "(string)Population Type: " << std::endl;
    customCin(popType);
    std::cout << "(string)Links file: Networks/xxxxxx.xxxx ";
    customCin(networkFilePath);
    std::string simpleFP = networkFilePath;
    networkFilePath = "Networks/" + networkFilePath; std::cout << std::endl;
    std::cout << "(Uint)Seed (input 0 for random seed):  ";
    customCin(seed);
    
    //TODO: accept more than one datasub
    std::cout << "(string)Data Subscriber: " << std::endl;
    std::cin >> dataSubs;
    
    //Default FileNamePath for ShellScripts
    std::string fileNamePath = "Scripts/" + std::to_string(numbTags) + "_" +
    std::to_string(generations) + "_" +
    popType + "_" + simpleFP + ".sh";
    
    
    std::ofstream myfile;
    myfile.open(fileNamePath); //creates or overwrites existing file!
    
    if (myfile.is_open()) {
        std::string const firstLine = "osascript -e 'tell application \"Terminal\" to activate' -e 'tell application \"System Events\" to tell process \"Terminal\" to keystroke \"n\" using command down'\n";
        std::string const secondLine = "osascript -e 'tell application \"Terminal\" to do script \"cd ";
        std::string const secondLineEnding = "\" in selected tab of the front window'\n";
        std::string tempLine = "";
        
        for (int b = 100; b <= 200; b += 5) { //after division by 100.0f, b goes from 1.0 to 2.0, with increments of 0.05f, without loss of precision
            myfile << firstLine;
            tempLine = secondLine + fullPathToExecFolder + "; ./74100Unix " + std::to_string(numbTags) + " " + networkFilePath + " " + popType + " " + std::to_string(generations) + " 1 1 0 " + std::to_string((b/100.0f)) + " 0 " + std::to_string(seed) + " " + dataSubs + secondLineEnding;
            myfile << tempLine;
        }
        myfile.close();
        std::cout << "Created shell script on " << fileNamePath << std::endl;
    }else{
        std::cout << "ERROR: Could not create shell file in requested path!" << std::endl;
    }
}

//These variables are reused for the various factory creations, they need to be reset after each creation
void Factory::clearParsedVariables(){
    _populationType = "";
    _linksFilePath = "";
    _totalGenerations = 0;
    _totalTags = 0;
    _tau = 0.0f;
    _payOffMatrix.clear();
    _percentages.clear();
    _subscribers.clear();
    _subscribersParsed.clear();
    _tempString = "";
}