//
//  MiscCode.h
//  74100Unix
//
//  Created by Élvio Abreu on 11/05/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//

#ifndef ___4100Unix__MiscCode__
#define ___4100Unix__MiscCode__

#include <iostream> //for CIN, et all
#include <limits> //to clean cin to the fullest
#include <string>
#include <stdlib.h> //at

bool positiveIntCin(int & input);

template<typename T>
bool customCin(T & input){
    while (true) {
        if (std::cin >> input){
            return true;
        }else{
            //wrong input type!
            std::cin.clear(); //clears the error flag on cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clears contents of cin
        }
        std::cout << "Please input a correct value! ->> ";
    }
}

#endif /* defined(___4100Unix__MiscCode__) */