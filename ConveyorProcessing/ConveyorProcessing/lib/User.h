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

/*changeNumber
changeFunction*/
#endif
