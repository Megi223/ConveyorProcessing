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
};

#endif
