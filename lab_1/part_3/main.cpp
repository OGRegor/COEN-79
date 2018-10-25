//
//  main.cpp
//  ToUpperCase
//
//  Created by gregor n limstrom on 9/21/18.
//  Copyright © 2018 SCU. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>


using namespace std;

// This program takes in a file and prints out any words larger than 9 character sin punctuation, converted to uppercase. 
// Precondition: File is valid and able to be open
// Postcondition: Outputs the strings with length greater than or equal to 10

int main(int argc, const char * argv[]) {
    // Grabs the name of the text file
    if(argc != 2) 
    {
        cout << endl << "Error: Please give the name of a text file as an argument" << endl;
        exit(1);
    }

    // Reads the file
    ifstream file_in(argv[1]);
    assert(file_in);
    string word;
    while(file_in >> word)
    {
        if(word.length() >= 10)
        {
            // Strips punctuation through a loop and capitalizes if it is not punctuation
            for(int i = 0, len = word.size(); i < len; i++) 
            {
                if(ispunct(word[i])) word.erase(i--, 1); 
                else word[i] = toupper(word[i]);
            }
            if(word.length() >= 10) cout << word << endl;
        }
    }
    file_in.close();
    return 0;
}