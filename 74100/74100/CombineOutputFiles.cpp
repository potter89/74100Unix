//
//  CombineOutputFiles.cpp
//  74100Unix
//
//  Created by Élvio Abreu on 30/06/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//

#include "CombineOutputFiles.h"

void combine210OutputFiles(std::string folder){
    //HARDCODED constants
    const int numbDuplicates = 100;
    const int lineWithCoopActions = 2; //line which holds the number with coop actions
    
    std::vector<int> valuesToAvg;
    
    //extract the initial start of the names(folder name should be the start of the files' names)
    // Results/1__bara.z4_500__10000__1.000000
    std::string folderName = folder; //initialized like this in case it's in the root of the project and no '/' is used
    //std::cout << "Searching on path: " << folderPath << std::endl;
   
    /** won't need this anymore, since we are now asking for just the folder name inside of folder Results
    std::string s = folderPath;
    std::string const delimiter = "/";
    size_t pos = 0;
    
    while ((pos = s.find(delimiter)) != std::string::npos) {
        folderName = s.substr(0, pos);
        s.erase(0, pos + delimiter.length());
    }
    folderName = s.substr(0, pos);
    std::cout << "Folder name: " << folderName << std::endl;
    
    */
    
    //create and open a new combinedOutput textfile
    std::ofstream combinedOutputFile;
    std::string fullCombinedNamePath = "Results/combOut_" + folderName + ".txt";
    combinedOutputFile.open(fullCombinedNamePath); //TODO:check if this works for setting the filename
    if (combinedOutputFile.is_open()) {
        std::ifstream auxSimulationFile; std::string auxString = "", auxFileName = "";
        //for each value of b (cheater's advantage), from 1.0 to 2.0, inclusive
        for (int b = 100; b <= 200; b += 5) { //after division by 100.0f, b goes from 1.0 to 2.0, with increments of 0.05f, without loss of precision
            //look for all the repeated files of the same b
            for (int i=1; i <= numbDuplicates; i++) {
                //1__bara.z4_500__10000__1.000000__1.000000_0.000000_1.000000_0.000000___#1.txt
                auxFileName = "Results/" + folderName + "/" + folderName + "__1.000000_0.000000_" + std::to_string((b/100.0f)) + "_0.000000___#" + std::to_string(i) + ".txt";
                
                auxSimulationFile.open(auxFileName);
                if (auxSimulationFile.is_open()) {
                    //store their values, which are kept in the last line of the file, on the second line
                    for (int it = 1; it <= lineWithCoopActions; it++) getline(auxSimulationFile, auxString); //only the content of the line with coop actions ends up in auxString
                    valuesToAvg.push_back(atoi(auxString.c_str()));
                    auxSimulationFile.close();
                }else{
                    std::cout << "Failed in opening file -> b:" << (b/100.0f) << "  #" << i << std::endl;
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
    }else{
        std::cout << "Could not create the combined file" << std::endl;
    }
}

//TODO: find ou what happens if the path is root, with no / in it

int calculateAverage(std::vector<int> & vec){
    int result = 0;
    if(vec.size() > 0){
        for (double i=0; i<vec.size(); i++){
            result += vec[i];
        }
        result = result/vec.size();
    }else{
        std::cout << "Error calculating avg, empty vector!!!" << std::endl;
    }
    return result;
}