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
    
    std::cout << "--> 2: Generate a new xForwardxBehind population" << std::endl << std::endl;
    
    std::cout << "--> 3: Generate a new FullyConnected population" << std::endl << std::endl;
    
    std::cout << "--> 4: Generate a new ShellScript" << std::endl << std::endl;
    
    std::cout << "--> 5: Combine simulation files (x100, b interval = 0.05)" << std::endl << std::endl;

	std::cout << "--> 6: (Mini B) Combine simulation files (x100, b interval = 0.25)" << std::endl << std::endl;
    
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
        exit(EXIT_SUCCESS);
    }
    else if (inputByUser == 1) {
        factory.generateLatticeLinksTextFile();
    }
    else if (inputByUser == 2){
        factory.generateForwardBehind();
    }
    else if (inputByUser == 3){
        factory.generateFullyConnected();
    }
    else if (inputByUser == 4){
        factory.generateShellScript();
	}
	else if (inputByUser == 5 || inputByUser == 6){
		int bIncrement = 0; //when combining output files in folders, we need to know the range of b that was used
		if (inputByUser == 5) bIncrement = 5;
		else if (inputByUser == 6) bIncrement = 25;

		std::cout << "Use input file? y or n" << std::endl; //
		std::string usrInput = ""; std::cin >> usrInput;
		if (usrInput == "y"){
			multipleCombineOutputFiles(bIncrement); //assumes there's a file called folderNames.txt with the names of all the folders
		} else{
			while (true){ //keep combining until the word stop is typed in
				std::string pathToFolder = "";
				std::cout << "Type \"stop\" or Please enter the name of the folder (should be inside Results): " << std::endl;
				std::cout << "Results/";
				customCin(pathToFolder);
				if (pathToFolder == "stop") break;
				else{
					combineOutputFiles(pathToFolder, bIncrement);
				}
			}
		}
	}else{
        //command not found
        std::cout << "Command not recognized! Please try again!" << std::endl;
    }
}