
#include <iostream>

#include "lib/Program.h"
#include "lib/User.h"


int main()
{
    Program program;
    program.generateRandomNumbers();
    program.generateRandomFunctions();
    string input = program.initMenu();
    User user;
    char symbol;
    do
    {
        symbol = user.validateInputStartMenu(input);
        if (symbol == 'e') {
            cout << "This is an invalid operation! Please select a valid one!" << endl;
            cin >> input;
        }
    } while (symbol == 'e');
    
    cout << symbol;
    
    return 0;
}
