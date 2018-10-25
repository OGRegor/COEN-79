//
//  main.cpp
//  Lab 1 Pattern
//
//  Created by gregor n limstrom on 9/21/18.
//  Copyright © 2018 SCU. All rights reserved.
//

#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// This program outputs a set pattern given to us in the lab, incrementing a space with each output and using setw() to space between the outputs
// Precondition: you have a computer with cpp installed
// Postcondition: Outputs the given pattern

int main(int argc, const char * argv[]) {
    // Loops through the pattern based on the index of displacement
    for(int i = 0; i < 10; i++)
    {
        cout << "0123456789\n " << setw(10 + i) << "9876543210" << setw(21 + i++);
    }
    cout << endl;
    return 0;
}
