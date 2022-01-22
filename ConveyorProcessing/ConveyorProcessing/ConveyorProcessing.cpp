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
* Main() function file
*
*/

#include <iostream>
#include <cstring>
#include "lib/Program.h"
#include "lib/User.h"
#include "lib/Calculation.h"

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
    Calculation calculation;
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
        }
        else if (symbol == 'N' || symbol == 'n') {
            program.showNumbers();
        }
        else if (symbol == 'F' || symbol == 'f') {
            program.showFunctions();
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
        }
        else if (symbol == 'C' || symbol == 'c') {
            /* When selecting this option the user will be able to choose from multiple 
                other options regarding the output - first we clarify them and then 
                we pass them as parameters in order to get the desired result*/
            cout << "Great! But first let's clarify some options" << endl;
            cout << "Would you like to activate carry mode? Please type in + for yes and - for no." << endl;
            char inputCarryMode;
            cin >> inputCarryMode;
            while (inputCarryMode != '+' && inputCarryMode != '-')
            {
                cout << "Invalid symbol! Please type in + for yes and - for no.";
                cin >> inputCarryMode;
            }
            cout << "Now let's choose the format of the output. Would you like it to be plain text or JSON?" << endl;
            cout << "Please choose the corresponding option:" << endl;
            cout << "1 - plain text" << endl;
            cout << "2 - JSON" << endl;
            int formatInput = 0;
            cin >> formatInput;
            while (cin.fail()) {
                cout << "Invalid input! Please choose a number (either 1 or 2)." << endl;
                cin >> formatInput;
            }
            while (formatInput != 1 && formatInput != 2) {
                cout << "Invalid input! " << formatInput << " is neither 1 nor 2" << endl;
                cin >> formatInput;
            }
            cout << "Fantastic! And finally- would you like to save the output as a file?" << endl;
            cout << "Please type in + for yes and - for no." << endl;
            char saveFileInput;
            cin >> saveFileInput;
            while (saveFileInput != '+' && saveFileInput != '-')
            {
                cout << "Invalid symbol! Please type in + for yes and - for no.";
                cin >> saveFileInput;
            }
            calculation.calculate(inputCarryMode, formatInput, saveFileInput);
        }
        cout << endl;
        input = program.initMenu(false);
        symbol = validInput(user, input);
    }

    cout << "Thank you for using Conveyor Processing! I hope you had great experience." << endl;
    
    return 0;
}
