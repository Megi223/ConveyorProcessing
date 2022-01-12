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
private: 
    int strLength(string str);
};

/*changeNumber
changeFunction*/
#endif
