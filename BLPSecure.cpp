/*
Author     : Adrian LaCour
Course     : CSCE 4550
Description: This header file contains the ReferenceMonitor class. This class will hold
             and objectValue, subject and object name, 2d vectors to store the security
             level for each subject and object, and strings for the input, and strings
             to store this input seperately.

             Bell-LaPadula = no read up; no write down.
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include<bits/stdc++.h>
#include "Object.h"
#include "Subject.h"
#include "referenceMonitor.cpp"

using namespace std;

vector<string> split(string s, char delimiter);

int main(int argc, char *argv[])
{
    if(argc != 2)//If there are an innapropriate amount of arguments given, output error message and exit
    {
        cout << "Usage: ./blpsecure instructionList\n";
        return 0;
    }

    ReferenceMonitor referenceMonitor;
    int numberOfActions = 0;//Initializes varibale to know when to print the state
    bool checker = 0;

    string inputString = "";//String used to store the line from the file
    vector<string> inputStringTokens;//Vector to store the input line in tokenized form

    //Opens file, and checks if there is an error opening it. If there is, output a message and exit
    ifstream inputFile;
    inputFile.open(argv[1]);
    if(!inputFile)
    {
        cout << "Unable to open " << argv[1] << " file. Terminating...\n";
        return 0;
    }

    //Get 1 line at a time from the file
    while(getline(inputFile, inputString, '\n'))
    {
        /*cout << "poop61: \n";
        for(char& c : inputString)
        {
            cout << c << endl;
        }*/

        //Convert the lin to all lowercase
        transform(inputString.begin(), inputString.end(), inputString.begin(), ::tolower);

        //tokenize the string and return as a vector
        inputStringTokens = split(inputString, ' ');

        /*poop //parse through the lines of input and determines if they are syntactically legal
        //if the number of tokens within the command are greater than 4, it is not a syntactically valid command
        if(inputStringTokens.size() > 4)
        {
            cout  << "Bad Instruction : " << inputString << endl;
            checker = 1;
        }*/
        //If the first token is syntactically correct
        if(inputStringTokens[0].compare("addsub") == 0 || inputStringTokens[0].compare("addobj") == 0 ||
           inputStringTokens[0].compare("read") == 0 || inputStringTokens[0].compare("write") == 0)
        {
            //Check the addsub command syntax
            if(inputStringTokens[0].compare("addsub") == 0)
            {
                if(inputStringTokens.size() != 3)
                {
                    cout  << "Bad Instruction : " << inputString << endl;
                }
                //Second token name doesnt matter, as it can be any string.
                //So, the program will just check if the security level token is valid
                if(inputStringTokens[2].compare("high") == 0 || inputStringTokens[2].compare("medium") == 0 || inputStringTokens[2].compare("low") == 0)
                {
                    referenceMonitor.parsePassedInstruction(inputStringTokens);
                }
            }
            //Check the addobj command syntax
            else if(inputStringTokens[0].compare("addobj") == 0)
            {
                if(inputStringTokens.size() != 3)
                {
                    cout  << "Bad Instruction : " << inputString << endl;
                }
                //Second token name doesnt matter, as it can be any string.
                //So, the program will just check if the security level token is valid
                if(inputStringTokens[2].compare("high") == 0 || inputStringTokens[2].compare("medium") == 0 ||
                   inputStringTokens[2].compare("low") == 0)
                   {
                       referenceMonitor.parsePassedInstruction(inputStringTokens);
                   }
            }
            //Check the read command syntax
            else if(inputStringTokens[0].compare("read") == 0)
            {
                if(inputStringTokens.size() != 3)
                {
                    cout  << "Bad Instruction : " << inputString << endl;
                }
                else
                {
                    referenceMonitor.parsePassedInstruction(inputStringTokens);
                }
            }
            else if(inputStringTokens[0].compare("write") == 0)
            {
                if(inputStringTokens.size() != 4)
                {
                    cout  << "Bad Instruction : " << inputString << endl;
                }
                else if(inputStringTokens.size() == 4)
                {
                    //Test if the input Value is valid
                    string tempString = "";
                    int tempInt = 0;

                    tempString = inputStringTokens[3];

                    //If no conversion could be made
                    try{
                        tempInt = stoi(tempString);
                    }
                    catch(invalid_argument& e)
                    {
                        cout  << "Bad Instruction : " << inputString << endl;
                        goto passFucntion;
                    }

                    referenceMonitor.parsePassedInstruction(inputStringTokens);
                }
            }
        }
        else//If the first token is not a valid instruction
        {
             cout  << "Bad Instruction : " << inputString << endl;
        }

        passFucntion: numberOfActions++;//Increments number of actions
        //When numberOfActions % 10 == 0, execute printState
        if(numberOfActions % 10 == 0)
        {
            referenceMonitor.printState();
        }

        inputStringTokens.clear();
        checker = 0;
    }

    //after the whole file has been parsed, print a final state
    cout << "+-----Final State-----+\n";
    referenceMonitor.printState();

    inputFile.close();//Close the file

    return 0;
}

//Function to parse the string into individual parts. Each component can be accessed
//by specifying the location in the returned tokens vector.
vector<string> split(string s, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);

    while(getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }

    return tokens;
}
