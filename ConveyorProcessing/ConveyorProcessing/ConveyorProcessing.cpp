
#include <iostream>
#include <cstring>
#include "lib/Program.h"
#include "lib/User.h"

char validInput(User user,string input) {
    char symbol;
    do
    {
        symbol = user.validateInputStartMenu(input);
        if (symbol == 'e') {
            cout << "This is an invalid operation! Please select a valid one!" << endl;
            cin >> input;
        }
    } while (symbol == 'e');
    return symbol;
}


int main()
{
    Program program;
    program.generateRandomNumbers();
    program.generateRandomFunctions();
    string input = program.initMenu(true);
    User user;
    char symbol = validInput(user,input);
    while (symbol != 'A' && symbol != 'a') {
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
            cout << endl;
            input = program.initMenu(false);
            symbol = validInput(user, input);
        }
        else if (symbol == 'N' || symbol == 'n') {
            program.showNumbers();
            cout << endl;
            input = program.initMenu(false);
            symbol = validInput(user, input);
        }
        else if (symbol == 'F' || symbol == 'f') {
            program.showFunctions();
            cout << endl;
            input = program.initMenu(false);
            symbol = validInput(user, input);
        }
        else if (symbol == 'O' || symbol == 'o') {
            cout << "Okay! Now please write the function you want to change:" << endl;
            string funcToChange;
            cin >> funcToChange;
            bool correct = false;
            // Represents the row in which the function can be found - if it is not part of the list this index will be -1 (invalid)
            int contains = -1;
            do
            {
               correct = program.validateFormat(funcToChange);
               if (!correct) {
                   cout << "Invalid format!" << endl;
                   cin >> funcToChange;
                   continue;
               }
               contains = program.checkFunctionContains(funcToChange);
               if (contains == -1) {
                   cout << "Sorry, this function is not part of the list. Please select a containing one!" << endl;
                   cin >> funcToChange;
                   continue;
               }
            } while ((!correct) || (contains == -1));
            cout << "Great! Now please write the new function:" << endl;
            string newFunc;
            cin >> newFunc;
            bool formatCorrect = false;
            do
            {
                formatCorrect = program.validateFormat(funcToChange);
                if (!correct) {
                    cout << "Invalid format!" << endl;
                    cin >> funcToChange;
                    continue;
                }
            } while (!formatCorrect);
            bool successful = user.substituteFunction(newFunc, contains);
            while (!successful) {
                cout << "Sorry, an error occured." << endl;
            }
            if (successful) {
                cout << "Congratulations! You successfully changed function " << funcToChange << " with " << newFunc << endl;
            }
            cout << endl;
            input = program.initMenu(false);
            symbol = validInput(user, input);
        }
    }

    return 0;
}
