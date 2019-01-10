/*
Author     : Adrian LaCour
Course     : CSCE 4550
Description: This header file holdes the Object class, which will hold the name and
             value of the object that is stored with the object.
*/
#pragma once
#include <iostream>
#include <string>

using namespace std;

class Object{
    public:
        string name; //Holds the name of the object
        //The current value of an object, which doesn't change unless a WRITE command is initiated
        int value = 0;

        Object(string name1)//Constructor
        {
            name = name1;
        }
};
