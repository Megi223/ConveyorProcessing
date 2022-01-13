
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
    
    if (symbol == 'H' || symbol == 'h') {
        cout << "Okay! Now please write the number you want to change" << endl;
        float currentNumber = 0.0;
        double changedNumber = 0.0;
        bool contains = false;
        do
        {
            cin >> currentNumber;
            contains = program.checkNumberContains(currentNumber);
            if (!contains) {
                cout << "Sorry, this number is not part of the list. Please select a containing one!" << endl;
            }

        } while (!contains);
    }
    
    return 0;
}
