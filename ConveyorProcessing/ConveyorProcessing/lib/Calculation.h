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
};

#endif
