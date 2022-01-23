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
* Calculation class declaration
*
*/

#ifndef CALCULATION
#define CALCULATION

#include <iostream>
#include <cstring>

using namespace std;
class Calculation {
public:
    Calculation();
    ~Calculation();
    void calculate(char carryMode, int formatInput, char saveFileInput);
private:
    void jsonSerializer(double** matrix,string path,int numbersCnt,int funcCnt);
    double extractNumberFromFunction(string func, int startIndex);
    int countLines(string path);
};

#endif
