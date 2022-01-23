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

using namespace std;

char validInput(User user,string input) {
    char symbol;
    do {
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
            cout << "Okay! Now please write the number you want to change:" << endl;
            double currentNumber = 0.0;
            double changedNumber = 0.0;
            bool contains = false;
            string inputNumberToChange;
            bool validNumber = false;
            do {
                cin >> inputNumberToChange;
                /* This is for the cases when the user writes symbols different
                    from digits (ex.letters,special characters)*/
                validNumber = program.validateNumberFormat(inputNumberToChange);
                if (!validNumber) {
                    cout << "Sorry, this is invalid input! Please select a number!" << endl;
                    continue;
                }
                currentNumber = stod(inputNumberToChange);
                contains = program.checkNumberContains(currentNumber);
                if (!contains) {
                    cout << "Sorry, this number is not part of the list. Please select a containing one!" << endl;
                }
            } while (!contains);
            cout << "Great! Now please write your new number:" << endl;
            bool successfulChange = false;
            bool validSecondNumber = false;
            string newNumberInput;
            do {
                cin >> newNumberInput;
                /* This is for the cases when the user writes symbols different
                    from digits (ex.letters,special characters)*/
                validSecondNumber = program.validateNumberFormat(newNumberInput);
                if (!validSecondNumber) {
                    cout << "Sorry, this is invalid input! Please select a number!" << endl;
                    continue;
                }
                changedNumber = stod(newNumberInput);
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
            do {
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
            do {
                formatCorrect = program.validateFormat(newFunc);
                if (!formatCorrect) {
                    cout << "Invalid format!" << endl;
                    cin >> newFunc;
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
            string inputCarryModeStr;
            cin >> inputCarryModeStr;
            while ((inputCarryModeStr[0] != '+' && inputCarryModeStr[0] != '-') || inputCarryModeStr.size() > 1) {
                cout << "Invalid input! Please type in + for yes and - for no." << endl;
                cin >> inputCarryModeStr;
            }
            char inputCarryMode = inputCarryModeStr[0];
            cout << "Now let's choose the format of the output. Would you like it to be plain text or JSON?" << endl;
            cout << "Please choose the corresponding option:" << endl;
            cout << "1 - plain text" << endl;
            cout << "2 - JSON" << endl;
            string formatInputStr;
            cin >> formatInputStr;
            while ((formatInputStr[0] != 49 && formatInputStr[0] != 50) || formatInputStr.size() > 1) {
                cout << "Invalid input! Please choose a number (either 1 or 2)." << endl;
                cin >> formatInputStr;
            }
            int formatInput = stod(formatInputStr);
            cout << "Fantastic! And finally- would you like to save the output as a file?" << endl;
            cout << "Please type in + for yes and - for no." << endl;
            string saveFileInputStr;
            cin >> saveFileInputStr;
            while ((saveFileInputStr[0] != '+' && saveFileInputStr[0] != '-') || saveFileInputStr.size() > 1) {
                cout << "Invalid input! Please type in + for yes and - for no." << endl;
                cin >> saveFileInputStr;
            }
            char saveFileInput = saveFileInputStr[0];
            calculation.calculate(inputCarryMode, formatInput, saveFileInput);
        }
        cout << endl;
        input = program.initMenu(false);
        symbol = validInput(user, input);
    }

    cout << "Thank you for using Conveyor Processing! I hope you had great experience." << endl;
    
    return 0;
}
