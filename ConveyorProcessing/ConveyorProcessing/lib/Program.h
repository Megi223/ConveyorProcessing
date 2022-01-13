#ifndef PROGRAM
#define PROGRAM

#include <iostream>
#include <string>

using namespace std;
class Program {
public:
    Program();
    ~Program();
    void generateRandomNumbers();
    void generateRandomFunctions();
    string initMenu();
    bool checkNumberContains(double number);
};

#endif
