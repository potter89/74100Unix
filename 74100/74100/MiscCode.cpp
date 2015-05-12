//
//  MiscCode.cpp
//  74100Unix
//
//  Created by Élvio Abreu on 11/05/15.
//  Copyright (c) 2015 Elvio. All rights reserved.
//

#include "MiscCode.h"

bool positiveIntCin(int & input){
    while (true) {
        if (std::cin >> input){
            if(input > 0) return true;
        }else{
            //wrong input type!
            std::cin.clear(); //clears the error flag on cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clears contents of cin
        }
        std::cout << "Please input a positive integer Number! ->> ";
    }
}

