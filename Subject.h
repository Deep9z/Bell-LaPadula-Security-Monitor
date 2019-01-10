/*
Author     : Adrian LaCour
Course     : CSCE 4550
Description: This header file holdes the Subject class, which will hold the name and
             temporary value of the object that is stored with the object. It also
             contains the function to readObject and writeObject.
*/
#pragma once
#include <iostream>
#include <string>
#include "Object.h"

using namespace std;

class Subject{
    public:
        string name; //Holds the name of the object
        //The current value of a subject, which is recorded from the value most recently read
        int temp = 0;

        Subject(string name1)//Constructor
        {
            name = name1;
        }

        //Store read object's value in temp
        void readObject(Object& cla)
        {
            temp = cla.value;
        }

        //Update the value store in the object to the given value
        void writeObject(Object& cla, int newValue)
        {
            cla.value = newValue;
        }
};
