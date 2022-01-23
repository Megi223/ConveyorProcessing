/**
*
* Solution to course project 1
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2021/2022
*
* @author Miglena Dimitrova
* @idnumber 2MI0600053
* @compiler VC
*
* Program class declaration
*
*/

#ifndef PROGRAM
#define PROGRAM

#include <iostream>
#include <cstring>

using namespace std;
class Program {
public:
    Program();
    ~Program();
    void generateRandomNumbers();
    void generateRandomFunctions();
    string initMenu(bool first);
    bool checkNumberContains(double number);
    void showNumbers();
    void showFunctions();
    bool validateFormat(string str);
    int checkFunctionContains(string func);
    bool validateNumberFormat(string inputNum);
};

#endif
