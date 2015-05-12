//
//  TextUIManager.cpp
//  74100Unix
//
//  Created by Élvio Abreu on 11/05/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//

#include "TextUIManager.h"

void printOptions(){
    //TODO: create text that explains that opening the program like this won't run a simulation
    std::cout << "You're in Factory Mode! Please input a numbered option:" << std::endl << std::endl << std::endl;
    
    std::cout << "--> 1: Generate a new Lattice population" << std::endl << std::endl;
    
    std::cout << "--> 2: Generate a new TwoForwardTwoBehind population" << std::endl << std::endl;
    
    std::cout << "--> 3: Generate a new FullyConnected population" << std::endl << std::endl;
    
    std::cout << "--> 4: Generate a new ShellScript" << std::endl << std::endl;
    
    std::cout << "--> 9: EXIT!" << std::endl << std::endl;
    
    std::cout << std::endl << "Input-> ";
}

//process the input entered by the user int the console and generate the desired files
void handleUIRequest(Factory & factory){
    
    //present the options
    printOptions();
    
    int inputByUser;
    positiveIntCin(inputByUser);
    
    if (inputByUser == 9) {
        //close program
        exit(0);
    }
    else if (inputByUser == 1) {
        factory.generateLatticeLinksTextFile();
    }
    else if (inputByUser == 2){
        factory.generateTwoForwardTwoBehind();
    }
    else if (inputByUser == 3){
        factory.generateFullyConnected();
    }
    else if (inputByUser == 4){
        factory.generateShellScript();
    }else{
        //command not found
        std::cout << "Command not recognized! Please try again!" << std::endl;
    }
}