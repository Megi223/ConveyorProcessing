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
* User class declaration
*
*/

#ifndef USER
#define USER

#include <iostream>
#include <string>

using namespace std;
class User {
public:
    User();
    ~User();
    char validateInputStartMenu(string input);
    bool changeNumber(double oldNum, double newNum);
    bool substituteFunction(string newFunc, int row);

private: 
    int strLength(string str);
};
#endif
