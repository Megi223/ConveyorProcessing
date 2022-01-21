#ifndef CALCULATION
#define CALCULATION

#include <iostream>
#include <cstring>

using namespace std;
class Calculation {
public:
    Calculation();
    ~Calculation();
    void calcWithoutCarryMode(int formatInput, char saveFileInput);
    void calcWithCarryMode(int formatInput, char saveFileInput);
private:
    void jsonSerializer(double** matrix);
};

#endif
