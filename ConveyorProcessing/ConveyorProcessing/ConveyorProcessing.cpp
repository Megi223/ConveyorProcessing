
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
            /* This is for the cases when the user writes symbols different 
                from digits (ex.letters,special characters)*/
            if (!cin) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Sorry, this is invalid input! Please select a number!" << endl;
                continue;
            }
            contains = program.checkNumberContains(currentNumber);
            if (!contains) {
                cout << "Sorry, this number is not part of the list. Please select a containing one!" << endl;
            }
        } while (!contains);
        cout << "Great! Now please write your new number:" << endl;
        bool successfulChange = false;
        do
        {
            cin >> changedNumber;
            /* This is for the cases when the user writes symbols different
                from digits (ex.letters,special characters)*/
            if (!cin) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Sorry, this is invalid input! Please select a number!" << endl;
                continue;
            }
            successfulChange = user.changeNumber(currentNumber, changedNumber);
            if (!successfulChange) {
                cout << "Sorry, an error occured. Please write your number again" << endl;
            }

        } while (!successfulChange);
        cout << "You successfully changed the number " << currentNumber << " with " << changedNumber << endl;
    }
    
    return 0;
}
