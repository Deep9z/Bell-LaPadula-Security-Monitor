/*
Author     : Adrian LaCour
Course     : CSCE 4550
Description: This header file contains the ReferenceMonitor class. This class will hold
             and objectValue, subject and object name, 2d vectors to store the security
             level for each subject and object, and strings for the input, and strings
             to store this input seperately.
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include "Object.h"
#include "Subject.h"

using namespace std;

//Struct to hold the name of the subject or object and their associated security level
struct Security{
    string name = "";
    string securityLabel = "";

    Security(string name1, string securityLabel1)
    {
        name = name1;
        securityLabel = securityLabel1;
    }
};

class ReferenceMonitor{
    public:
        int objectValue = 0;
        string instruction = "";
        string subjectName = "";
        string objectName = "";
        string securityLabel = "";
        string securityLabel1 = "";

        //Vectors of class objects to store the created objects and subjects
        vector<Subject> subjectVector;
        vector<Object> objectVector;

        //vectors to store the object name and security level, and the subject name and secrutiy level
        //They have strong tranquility, so they cannot be changed once they are defined
        vector<Security> subjectSecurityVector;
        vector<Security> objectSecurityVector;

        //Prints the names and current values of all subjects and objects every ten actions
        //The fucntion is called every ten instructions, and at the end.
        void printState()
        {
            cout << "+----Current State----+\n";
            cout << "|--Subject--|---temp--|\n";
            for(int i = 0; i < subjectVector.size(); i++)
            {
                cout << left;
                cout << "| " << setw(9) << subjectVector[i].name << " | ";
                cout << right;
                cout << setw(7) << subjectVector[i].temp << " |\n";
            }

            cout << "|---Object--|--Value--|\n";
            for(int i = 0; i < objectVector.size(); i++)
            {
                cout << left;
                cout << "| " << setw(9) << objectVector[i].name << " | ";
                cout << right;
                cout << setw(7) << objectVector[i].value << " |\n";
            }

            cout << "+---------------------+\n";
        }

        //This fucntion adds a subject object, as well as stores the security information
        void addSubject(string subjectName, string securityLabel)
        {
            //Assigns the subject name to a new subject class object within the vector
            subjectVector.emplace_back(subjectName);

            //Creates a position for the subject security object within the vector, and assigns
            //the proper data
            subjectSecurityVector.emplace_back(subjectName, securityLabel);
        }

        //This fucntion adds an Object object, as well as stores the security information
        void addObject(string objectName, string securityLabel)
        {
            //Assigns the objects name to the objectVector, adding another object to the vector
            objectVector.emplace_back(objectName);

            //Creates a position for the object's security level within the appropriate vector
            objectSecurityVector.emplace_back(objectName, securityLabel);
        }

        //This function executes the read command, allowing a valid subject to read a vald object
        void executeRead(int i, int j)
        {
            subjectVector[i].readObject(objectVector[j]);
        }

        //This function executes the write command, allowing a valid subject to write a value to a vald object
        void executeWrite(int i, int j, int objectValue1)
        {
            subjectVector[i].writeObject(objectVector[j], objectValue1);
        }

        //This fucntion takes the valid string from BLPsecure.cpp and checks the security levels.
        //If it is valid, it will call the valid class to perform the requested action
        //and then outputs if the instruction is allowed by the security, or disallowed
        //by the security labels (or if the subject or object does not exist).
        void parsePassedInstruction(vector<string> tokens)
        {
            instruction = tokens[0];//Assigns the inputted instruction, which will be used to branch operations

            //If the instruction is addsub
            if(instruction.compare("addsub") == 0)
            {
                //Assigns the variables from the input string into individual variables
                subjectName = tokens[1];
                securityLabel = tokens[2];

                //Check if the subject name already exists. If it does, output an error and end the function
                for(int i = 0; i < subjectSecurityVector.size(); i++)
                {
                    if(subjectSecurityVector[i].name.compare(subjectName) == 0)
                    {
                        //If the command is syntactically correct, but a bad instruction
                        cout << "Bad Instruction : ";
                        for(int i = 0; i < tokens.size(); i++)
                        {
                            cout << tokens[i] << " ";
                        }
                        cout << endl;

                        return;
                    }
                }

                //Call the addSubject function, as no security checks are needed
                addSubject(subjectName, securityLabel);

                //Output success message
                cout << "Subject Added   : ";
                for(int i = 0; i < tokens.size(); i++)
                {
                    cout << tokens[i] << " ";
                }
                cout << endl;
            }
            else if(instruction.compare("addobj") == 0)//If the instruction is addobj
            {
                //Assigns the variables from the input string into individual variables
                objectName = tokens[1];
                securityLabel = tokens[2];

                //Check if the object name already exists. If it does, output an error and end the function
                for(int i = 0; i < objectSecurityVector.size(); i++)
                {
                    if(objectSecurityVector[i].name.compare(objectName) == 0)
                    {
                        //If the command is syntactically correct, but a bad instruction
                        cout << "Bad Instruction : ";
                        for(int i = 0; i < tokens.size(); i++)
                        {
                            cout << tokens[i] << " ";
                        }
                        cout << endl;

                        return;
                    }
                }

                //Call the addObject function, as no security checks are needed
                addObject(objectName, securityLabel);

                //Output success message
                cout << "Object Added    : ";
                for(int i = 0; i < tokens.size(); i++)
                {
                    cout << tokens[i] << " ";
                }
                cout << endl;
            }
            else if(instruction.compare("read") == 0)//If the instruction is read
            {
                //Assigns the variables from the input string into individual variables
                subjectName = tokens[1];
                objectName = tokens[2];

                //Check if the name is subject exists. If it does not, output an error and end the function
                for(int i = 0; i < subjectSecurityVector.size(); i++)
                {
                    if(subjectSecurityVector[i].name.compare(subjectName) != 0 && (i == subjectSecurityVector.size() - 1))
                    {
                        //If the command is syntactically correct, but a bad instruction
                        cout << "Bad Instruction : ";
                        for(int i = 0; i < tokens.size(); i++)
                        {
                            cout << tokens[i] << " ";
                        }
                        cout << endl;

                        return;
                    }
                    else if(subjectSecurityVector[i].name.compare(subjectName) == 0)
                    {
                        break;
                    }
                }

                //poop this sections is not registering, for some reason
                //Check if the name is object exists. If it does not, output an error and end the function
                for(int i = 0; i < objectSecurityVector.size(); i++)
                {
                    if(objectSecurityVector[i].name.compare(objectName) != 0 && (i == objectSecurityVector.size() - 1))
                    {
                        //If the command is syntactically correct, but a bad instruction
                        cout << "Bad Instruction : ";
                        for(int i = 0; i < tokens.size(); i++)
                        {
                            cout << tokens[i] << " ";
                        }
                        cout << endl;

                        return;
                    }
                    else if(objectSecurityVector[i].name.compare(objectName) == 0)
                    {
                        break;
                    }
                }

                //Read the current value of the object and save the value into the
                //subject's temp variable
                for(int i = 0; i < subjectVector.size(); i++)
                {//Iterate thgrough the entire subjectVector to find the right name
                    if(subjectVector[i].name.compare(subjectName) == 0)
                    {//If the subject exists
                        for(int j = 0; j < objectVector.size(); j++)
                        {
                            if(objectVector[j].name.compare(objectName) == 0)
                            {//If the object exists
                                //If the instruction follows the "no read up" rule for the subject having "high" clearance
                                if(subjectSecurityVector[i].securityLabel.compare("high") == 0 &&
                                (objectSecurityVector[j].securityLabel.compare("high") == 0 ||
                                objectSecurityVector[j].securityLabel.compare("medium") == 0 ||
                                objectSecurityVector[j].securityLabel.compare("low") == 0))
                                {
                                    executeRead(i, j);
                                    //subjectVector[i].readObject(objectVector[j], j);
                                    //Output success message
                                    cout << "Access Granted  : ";
                                    for(int i = 0; i < tokens.size(); i++)
                                    {
                                        cout << tokens[i] << " ";
                                    }
                                    cout << endl;
                                }
                                //If the instruction follows the "no read up" rule for the subject having "medium" clearance
                                else if(subjectSecurityVector[i].securityLabel.compare("medium") == 0 &&
                                (objectSecurityVector[j].securityLabel.compare("high") != 0 &&
                                (objectSecurityVector[j].securityLabel.compare("medium") == 0 ||
                                objectSecurityVector[j].securityLabel.compare("low") == 0)))
                                {
                                    executeRead(i, j);
                                    //subjectVector[i].temp = objectVector[j].value;
                                    //Output success message
                                    cout << "Access Granted  : ";
                                    for(int i = 0; i < tokens.size(); i++)
                                    {
                                        cout << tokens[i] << " ";
                                    }
                                    cout << endl;
                                }
                                //If the instruction follows the "no read up" rule for the subject having "low" clearance
                                else if(subjectSecurityVector[i].securityLabel.compare("low") == 0 &&
                                (objectSecurityVector[j].securityLabel.compare("high") != 0 &&
                                objectSecurityVector[j].securityLabel.compare("medium") != 0 &&
                                objectSecurityVector[j].securityLabel.compare("low") == 0))
                                {
                                    executeRead(i, j);
                                    //subjectVector[i].temp = objectVector[j].value;
                                    //Output success message
                                    cout << "Access Granted  : ";
                                    for(int i = 0; i < tokens.size(); i++)
                                    {
                                        cout << tokens[i] << " ";
                                    }
                                    cout << endl;
                                }
                                else
                                {
                                    //Output success message
                                    cout << "Access Denied   : ";
                                    for(int i = 0; i < tokens.size(); i++)
                                    {
                                        cout << tokens[i] << " ";
                                    }
                                    cout << endl;
                                    return;
                                }
                            }
                        }
                    }
                    else
                    {   //MAY NEED TO MOVE OUTSIDE OF FOR LOOP, SINCE THE SUBJECT/OBJECT COULD NOT BE FOUND
                        //cout << "Bad Instruction : " << tokens[0] << " " << tokens[1] << " " << tokens[2] << endl;
                    }
                }

            }
            else if(instruction.compare("write") == 0)//If the instruction is read
            {
                //Assigns the variables from the input string into individual variables
                subjectName = tokens[1];
                objectName = tokens[2];
                objectValue = stoi(tokens[3]);

                //Check if the name is subject exists. If it does not, output an error and end the function
                for(int i = 0; i < subjectSecurityVector.size(); i++)
                {
                    if(subjectSecurityVector[i].name.compare(subjectName) != 0 && (i == subjectSecurityVector.size() - 1))
                    {
                        //If the command is syntactically correct, but a bad instruction
                        cout << "Bad Instruction : ";
                        for(int i = 0; i < tokens.size(); i++)
                        {
                            cout << tokens[i] << " ";
                        }
                        cout << endl;

                        return;
                    }
                    else if(subjectSecurityVector[i].name.compare(subjectName) == 0)
                    {
                        break;
                    }
                }

                //Check if the name is object exists. If it does not, output an error and end the function
                for(int i = 0; i < objectSecurityVector.size(); i++)
                {
                    if(objectSecurityVector[i].name.compare(objectName) != 0 && (i == objectSecurityVector.size() - 1))
                    {
                        //If the command is syntactically correct, but a bad instruction
                        cout << "Bad Instruction : ";
                        for(int i = 0; i < tokens.size(); i++)
                        {
                            cout << tokens[i] << " ";
                        }
                        cout << endl;

                        return;
                    }
                    else if(objectSecurityVector[i].name.compare(objectName) == 0)
                    {
                        break;
                    }
                }

                //Write the given value, from an authorized user, to the objects value
                for(int i = 0; i < subjectVector.size(); i++)
                {//Iterate through the subjectName to find the right name that wishes to write to the object
                    if(subjectVector[i].name.compare(subjectName) == 0)
                    {//If the subject exists
                        for(int j = 0; j < objectVector.size(); j++)
                        {   //If the object exists
                            if(objectVector[j].name.compare(objectName) == 0)
                            {
                                //If the instruction follows the "no write down" rule for the subject having "high" clearance
                                if(subjectSecurityVector[i].securityLabel.compare("high") == 0 &&
                                (objectSecurityVector[j].securityLabel.compare("high") == 0 &&
                                objectSecurityVector[j].securityLabel.compare("medium") != 0 &&
                                objectSecurityVector[j].securityLabel.compare("low") != 0))
                                {
                                    executeWrite(i, j, objectValue);
                                    ///Output success message
                                    cout << "Access Granted  : ";
                                    for(int i = 0; i < tokens.size(); i++)
                                    {
                                        cout << tokens[i] << " ";
                                    }
                                    cout << endl;
                                }
                                //If the instruction follows the "no write down" rule for the subject having "medium" clearance
                                else if(subjectSecurityVector[i].securityLabel.compare("medium") == 0 &&
                                ((objectSecurityVector[j].securityLabel.compare("high") == 0 ||
                                objectSecurityVector[j].securityLabel.compare("medium") == 0) &&
                                objectSecurityVector[j].securityLabel.compare("low") != 0))
                                {
                                    executeWrite(i, j, objectValue);
                                    ///Output success message
                                    cout << "Access Granted  : ";
                                    for(int i = 0; i < tokens.size(); i++)
                                    {
                                        cout << tokens[i] << " ";
                                    }
                                    cout << endl;
                                }
                                //If the instruction follows the "no write down" rule for the subject having "low" clearance
                                else if(subjectSecurityVector[i].securityLabel.compare("low") == 0 &&
                                (objectSecurityVector[j].securityLabel.compare("high") == 0 ||
                                objectSecurityVector[j].securityLabel.compare("medium") == 0 ||
                                objectSecurityVector[j].securityLabel.compare("low") == 0))
                                {
                                    executeWrite(i, j, objectValue);
                                    ///Output success message
                                    cout << "Access Granted  : ";
                                    for(int i = 0; i < tokens.size(); i++)
                                    {
                                        cout << tokens[i] << " ";
                                    }
                                    cout << endl;
                                }
                                else
                                {
                                    //Output success message
                                    cout << "Access Denied   : ";
                                    for(int i = 0; i < tokens.size(); i++)
                                    {
                                        cout << tokens[i] << " ";
                                    }
                                    cout << endl;
                                }
                            }//end of object compare if statement
                        }//end of second for loop
                    }//end of subjectName if statement
                }//end of  frist for loop
            }//end of else if
            /*poop else
            {
                //If the command is syntactically correct, but a bad instruction
                cout << "Bad Instruction : ";
                for(int i = 0; i < tokens.size(); i++)
                {
                    cout << tokens[i] << " ";
                }
                cout << endl;
            }*/
        }
};
