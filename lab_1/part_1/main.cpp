//
//  main.cpp
//  Lab 1
//
//  
//
//  Created by gregor n limstrom on 9/21/18.
//  Copyright © 2018 SCU. All rights reserved.
//

#include <iostream>
#include "counter.hpp"
#include <string>

using namespace std;

// This program counts the alphanumeric and non-alphanumeric characters in a string, ignoring whitespace.

int main(int argc, const char * argv[]) {
    cout << "put in string to be counted" << endl;
    string input;
    getline(cin, input);
    
    count(input);
    
    return 0;
}
