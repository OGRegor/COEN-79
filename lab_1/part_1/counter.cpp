//
//  counter.cpp
//  Lab 1
//
//  Created by gregor n limstrom on 9/21/18.
//  Copyright © 2018 OCU. All rights reserved.
//

#include "counter.hpp"
#include <iostream>
#include <string>

using namespace std;

// This function takes a string in and counts the total number of alphanumeric and nonalpha numeric characters by comparing their ascii values, then prints out the corresponding totals
// Precondition: string is valid object, is not null
// Post condition: outputs the count of alphanum and nonalphanum characters in a string

void count(string input)
{
    int alpha_tot = 0;
    int other_tot = 0;
    
    // Loops through the input string and checks the typing of the character, then adds respectively
    for(int i = 0; i < input.length(); i++)
    {
        if(isalnum(input[i]))
        {
            alpha_tot++;
            continue;
        }
        else if (input[i] != ' ')
        {
            other_tot++;
        }
    }
    std::cout << "alphanum: " << alpha_tot << std::endl;
    std::cout << "other: " << other_tot << std::endl;
}