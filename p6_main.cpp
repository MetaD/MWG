/*
 Main module. From Project 5
 */

#define NDEBUG

#include "Controller.h"


#include <iostream>

using namespace std;

// The main function simply creates the Controller object and tells it to run.
int main ()
{
    // Set output to show two decimal places
    //	cout << fixed << setprecision(2) << endl;
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    
    // create the Controller object and go
    Controller controller;
    
    controller.run();
}


