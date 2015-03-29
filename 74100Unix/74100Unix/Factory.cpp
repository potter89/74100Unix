//
//  Factory.cpp
//  74100Unix
//
//  Created by Elvio on 27/03/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//

#include "Factory.h"
//TODO:Update with the new paths!

Factory::Factory(){}

Factory::~Factory(){}

//returns polymorphed Population, already initialized with it's ->Init
Population * Factory::createPopulation(std::string linksPath, std::string populationType, int totalTags){
    /**/
    std::string type = populationType;
    Population * retPopulation = NULL; //population to be returned
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
    return retPopulation;
}

void Factory::parseConfiguration(std::string inputPath){ //takes config file and creates a population
    //Population_Type: LATTICE
    //Links_file_Path : Networks / Lattices / 5x5
    //Generations : 10000
    //Number_of_tags : 4
    //Tau : 0.7
    //Payoff_Matrix : 1 1 5 5
    //percentages_of_tags_in_pop : 0 50 1 30 2 10 3 10
    std::ifstream myfile(inputPath);
    if (myfile.is_open())
    {
        _tempString = "";
        size_t pos = 1;
        
        getline(myfile, _tempString); pos = _tempString.find(_delimiter);//population type
        _populationType = _tempString.erase(0, pos + _delimiter.length());
        
        getline(myfile, _tempString); pos = _tempString.find(_delimiter);//links path
        _linksFilePath = _tempString.erase(0, pos + _delimiter.length());
        
        getline(myfile, _tempString); pos = _tempString.find(_delimiter); //total generations
        _totalGenerations = atoi(_tempString.erase(0, pos + _delimiter.length()).c_str());
        
        getline(myfile, _tempString); pos = _tempString.find(_delimiter);// number of tags
        _totalTags = atoi(_tempString.erase(0, pos + _delimiter.length()).c_str());
        
        getline(myfile, _tempString); pos = _tempString.find(_delimiter); //_tau
        _tau = atof(_tempString.erase(0, pos + _delimiter.length()).c_str());
        
        getline(myfile, _tempString);
        pos = _tempString.find(_delimiter);
        _tempString.erase(0, pos + _delimiter.length()); //removing the text "PayoffMatrix"
        
        while ((pos = _tempString.find(_delimiter)) != std::string::npos){ //for each of the tokens, delimited by a space
            _payOffMatrix.push_back(atof(_tempString.substr(0, pos).c_str())); //add token to vector of floats
            _tempString.erase(0, pos + _delimiter.length()); //eliminate the token and delimiter from the string
        }
        _payOffMatrix.push_back(atof(_tempString.c_str()));
        
        getline(myfile, _tempString); pos = _tempString.find(_delimiter); //TODO: percentages
        
        getline(myfile, _tempString);
        pos = _tempString.find(_delimiter);
        _tempString.erase(0, pos + _delimiter.length()); //removing the text "DataSubscribers:"
        
        while ((pos = _tempString.find(_delimiter)) != std::string::npos){ //for each of the tokens, delimited by a space
            _subscribers.push_back(_tempString.substr(0, pos)); //add token to vector of strings
            _tempString.erase(0, pos + _delimiter.length()); //eliminate the token and delimiter from the string
        }
        _subscribers.push_back(_tempString);
        /**
         std::cout << "Config File:" << std::endl;
         std::cout << "Population Type: " << _populationType << std::endl;
         std::cout << "Links File Path: " << _linksFilePath << std::endl;
         std::cout << "Total Generations: " << _totalGenerations << std::endl;
         std::cout << "Total Tags: " << _totalTags << std::endl;
         std::cout << "Tau: " << _tau << std::endl;
         
         //std::cout << "Payoff Matrix: " << pay << std::endl;
         //std::cout << "Percentages of each tag" << linksFilePath << std::endl;
         //*/
        myfile.close();
    }
    else{
        std::cout << "wrong configuration path given on-> " << inputPath << std::endl;
    }
}

Simulation * Factory::createSimulation(std::string inputPath){
    
    //parse text file
    parseConfiguration(inputPath);
    Population * popul = createPopulation(_linksFilePath, _populationType, _totalTags);
    
    Simulation * s = new Simulation(popul, _totalGenerations, _tau, _payOffMatrix, &_subscribers);
    return s;
}

Simulation * Factory::createSimulation(int totalTags, std::string linksPath, std::string popType, int i_maxGenerations, float tau, std::vector<float> payoffMatrix, std::vector<std::string> * dataSubscribers){
    Population * popul = createPopulation(linksPath, popType, totalTags);
    Simulation * s = new Simulation(popul, i_maxGenerations, tau, payoffMatrix, dataSubscribers);
    return s;
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
    std::cin >> R;
    std::cout << "Type the desired number of columns: " << std::endl;
    std::cin >> C;
    
    std::string fileNamePath = "/Users/elvio/Documents/Projects/74100Unix/74100Unix/74100Unix/Networks/l_" + std::to_string(R) + "x" + std::to_string(C) + ".txt";
    
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

//TODO:Find out name for this graph, and also change the name of the created files
//Generates a txt file containing a well Mixed Graph with the links of a population, with exact number of agents, as inputed by the user
//agents are connected to the immediate (index) two agents after and two agents behind him (PS:it loops).
void Factory::generateTwoForwardTwoBehind(){
    int i = 0; //index of the Agent
    std::string s = ""; //current agent line
    int totalNumberOfAgents; //population will have exactly this number of agents in it
    
    //ask for name of output file, to create the fileNamePath
    std::cout << "Type the desired number of agents (Must be above 5!): " << std::endl;
    std::cin >> totalNumberOfAgents;
    while (totalNumberOfAgents < 5){
        std::cout << "Must be above 5! Type the desired number of agents: " << std::endl;
        std::cin >> totalNumberOfAgents;
    }
    
    //TODO:find out name..
    //Default FileNamePath creation
    std::string fileNamePath = "/Users/elvio/Documents/Projects/74100Unix/74100Unix/74100Unix/Networks/tftb_" + std::to_string(totalNumberOfAgents) + ".txt";
    
    std::ofstream myfile;
    myfile.open(fileNamePath); //creates or overwrites existing file!
    
    myfile << totalNumberOfAgents << "\n"; //first line, has the total number of agents
    
    //agent 0
    s = "0 0 1 2";
    s += " " + std::to_string(totalNumberOfAgents - 2);
    s += " " + std::to_string(totalNumberOfAgents - 1);
    s += '\n'; //0 1 2 totalNumberOfAgents-1 totalNumberOfAgents-2
    myfile << s;
    i++; s = "";
    
    //agent 1
    s = "1 0 0 2 3";
    s += " " + std::to_string(totalNumberOfAgents - 1);
    s += '\n';
    myfile << s;
    i++; s = "";
    
    //agent 2 until totalNumberOfAgents - 3
    for (int potter = 2; potter <= totalNumberOfAgents - 3; potter++){
        s = std::to_string(i) + " 0";
        s += " " + std::to_string(i - 2);
        s += " " + std::to_string(i - 1);
        s += " " + std::to_string(i + 1);
        s += " " + std::to_string(i + 2);
        s += '\n'; //i 0 i-2 i-1 i+1 i+2
        myfile << s;
        i++; s = "";
    }
    
    //agent totalNumberOfAgents - 2
    s = std::to_string(i) + " 0 0";
    s += " " + std::to_string(i - 2);
    s += " " + std::to_string(i - 1);
    s += " " + std::to_string(i + 1);
    s += '\n'; //i 0 i-2 i-1 i+1 0
    myfile << s;
    i++; s = "";
    
    //agent totalNumberOfAgents - 1
    s = std::to_string(i) + " 0";
    s += " " + std::to_string(i - 2);
    s += " " + std::to_string(i - 1);
    s += " 0 1";
    s += '\n'; //i 0 i-2 i-1 i+1 0
    myfile << s;
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
    std::cin >> totalNumberOfAgents;
    while (totalNumberOfAgents < 2){
        std::cout << "Must be above 2! Type the desired number of agents: " << std::endl;
        std::cin >> totalNumberOfAgents;
    }
    
    //Default FileNamePath creation
    std::string fileNamePath = "/Users/elvio/Documents/Projects/74100Unix/74100Unix/74100Unix/Networks/fc_" + std::to_string(totalNumberOfAgents) + ".txt";
    
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