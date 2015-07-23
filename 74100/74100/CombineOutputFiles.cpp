//
//  CombineOutputFiles.cpp
//  74100Unix
//
//  Created by Élvio Abreu on 30/06/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//

#include "CombineOutputFiles.h"

void combineOutputFiles(std::string folder, int bIncrement){
	//HARDCODED constants
	const int numbDuplicates = 100;
	const int lineWithCoopActions = 2; //line which holds the number with coop actions

	std::list<int> valuesToAvg;

	//extract the initial start of the names(folder name should be the start of the files' names)
	// Results/1__bara.z4_500__10000__1.000000
	std::string folderName = folder; //initialized like this in case it's in the root of the project and no '/' is used
	//std::cout << "Searching on path: " << folderPath << std::endl;


	//create and open a new combinedOutput textfile
	std::ofstream combinedOutputFile;
	std::string fullCombinedNamePath = "Results/combOut_" + folderName + ".txt";
	combinedOutputFile.open(fullCombinedNamePath); //TODO:check if this works for setting the filename
	if (combinedOutputFile.is_open()) {
		std::ifstream auxSimulationFile; std::string auxString = "", auxFileName = "";
		//for each value of b (cheater's advantage), from 1.0 to 2.0, inclusive
		for (int b = 100; b <= 200; b += bIncrement) { //after division by 100.0f, b goes from 1.0 to 2.0, with increments of 0.05f (when bIncrement=5), without loss of precision
			//look for all the repeated files of the same b
			for (int i = 1; i <= numbDuplicates; i++) {
				//1__bara.z4_500__10000__1.000000__1.000000_0.000000_1.000000_0.000000___#1.txt
				auxFileName = "Results/" + folderName + "/" + folderName + "__1.000000_0.000000_" + std::to_string((b / 100.0f)) + "_0.000000___#" + std::to_string(i) + ".txt";

				auxSimulationFile.open(auxFileName);
				if (auxSimulationFile.is_open()) {
					//store their values, which are kept in the last line of the file, on the second line
					for (int it = 1; it <= lineWithCoopActions; it++) getline(auxSimulationFile, auxString); //only the content of the line with coop actions ends up in auxString
					valuesToAvg.push_back(atoi(auxString.c_str()));
					auxSimulationFile.close();
				}
				else{
					std::cout << std::endl << "Failed in opening file -> b:" << (b / 100.0f) << "  #" << i << std::endl << std::endl;
				}
			}
			//average the values
			int avg = calculateAverage(valuesToAvg);
			//print to the final combinedOutput
			combinedOutputFile << avg << "\n";
			valuesToAvg.clear();
		}
		//close combinedOutput textfile
		combinedOutputFile.close();
		std::cout << "All done!" << std::endl;
	}
	else{
		std::cout << "Could not create the combined file" << std::endl;
	}

}

void multipleCombineOutputFiles(int bIncrement){
	std::ifstream myfile("Results/folderNames.txt");
	std::string auxFolderName = "";

	if (myfile.is_open())
	{
		while (getline(myfile, auxFolderName)){
			std::cout << "Combining " + auxFolderName << std::endl;
			combineOutputFiles(auxFolderName, bIncrement);
		}
		std::cout << "All files processed. Press any key to continue..." << std::endl;
		int aux; std::cin >> aux;
	}
	else{
		std::cout << "folderNames text file not found!! Press any key to continue..." << std::endl;
		int aux; std::cin >> aux;
	}
}
/*
void combineOutputFilesTagsDist(std::string folder, int bIncrement){
	//HARDCODED constants
	const int numbDuplicates = 100;

	std::list<int> valuesToAvg;

	//extract the initial start of the names(folder name should be the start of the files' names)
	// Results/1__bara.z4_500__10000__1.000000
	std::string folderName = folder; //initialized like this in case it's in the root of the project and no '/' is used
	//std::cout << "Searching on path: " << folderPath << std::endl;


	//create and open a new combinedOutput textfile
	std::ofstream combinedOutputFile;
	std::string fullCombinedNamePath = "Results/combOut_" + folderName + ".txt";
	combinedOutputFile.open(fullCombinedNamePath); //TODO:check if this works for setting the filename
	if (combinedOutputFile.is_open()) {
		std::ifstream auxSimulationFile; std::string auxString = "", auxFileName = "";
		//for each value of b (cheater's advantage), from 1.0 to 2.0, inclusive
		for (int b = 100; b <= 200; b += bIncrement) { //after division by 100.0f, b goes from 1.0 to 2.0, with increments of 0.05f (when bIncrement=5), without loss of precision
			//look for all the repeated files of the same b
			for (int i = 1; i <= numbDuplicates; i++) {
				//1__bara.z4_500__10000__1.000000__1.000000_0.000000_1.000000_0.000000___#1.txt
				auxFileName = "Results/" + folderName + "/" + folderName + "__1.000000_0.000000_" + std::to_string((b / 100.0f)) + "_0.000000___#" + std::to_string(i) + ".txt";

				auxSimulationFile.open(auxFileName);
				if (auxSimulationFile.is_open()) {
					//store their values, which are kept in the last line of the file, on the second line
					for (int it = 1; it <= lineWithCoopActions; it++) getline(auxSimulationFile, auxString); //only the content of the line with coop actions ends up in auxString
					valuesToAvg.push_back(atoi(auxString.c_str()));
					auxSimulationFile.close();
				}
				else{
					std::cout << std::endl << "Failed in opening file -> b:" << (b / 100.0f) << "  #" << i << std::endl << std::endl;
				}
			}
			//average the values
			int avg = calculateAverage(valuesToAvg);
			//print to the final combinedOutput
			combinedOutputFile << avg << "\n";
			valuesToAvg.clear();
		}
		//close combinedOutput textfile
		combinedOutputFile.close();
		std::cout << "All done!" << std::endl;
	}
	else{
		std::cout << "Could not create the combined file" << std::endl;
	}

}
*/
int calculateAverage(std::list<int> & list){
    int result = 0;
    if(list.size() > 0){
        for (auto iterator = list.begin();iterator != list.end();iterator++){
            result += *iterator;
        }
        result = result/list.size();
    }else{
        std::cout << "Error calculating avg, empty vector!!!" << std::endl;
    }
    return result;
}