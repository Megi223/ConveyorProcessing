#include "User.h"
#include <iostream>
#include <fstream>
int const VALID_SYMBOLS_COUNT = 10;
User::User()
{
}

User::~User()
{
}

int User::strLength(string str) {
	int length = 0;
	int i = 0;
	while (str[i] != '\0') {
		i++;
	}
	length = i;
	return length;
}
char User::validateInputStartMenu(string input)
{
	int length = strLength(input);
	if (length != 1) {
		return 'e';
	}
	char symbol = input[0];
	char validSymbols[VALID_SYMBOLS_COUNT] = { 'N', 'n', 'H', 'h', 'F', 'f', 'O', 'o', 'C', 'c' };
	bool isValid = false;
	for (int i = 0; i < VALID_SYMBOLS_COUNT; i++)
	{
		if (symbol == validSymbols[i]) {
			isValid = true;
		}
	}
	if (!isValid) {
		return 'e';
	}
	return symbol;
}

bool User::changeNumber(double oldNum,double newNum) {
	std::string buffer;
	//File to read from
	ifstream filein("./resources/numbers.txt"); 
	//Temporary file to write new numbers
	ofstream fileout("./resources/tempNumbers.txt"); 
	if (!filein || !fileout)
	{
		cout << "Error opening files!" << endl;
		return false;
	}
	while (getline(filein, buffer)) {
		double parsedNumber = stod(buffer);
		/*Because of the small differences in the numbers when comparing numbers
			of type double, a tolerance is needed*/
		double difference = parsedNumber - oldNum;
		double positiveDiff = difference > 0 ? difference : (-1) * difference;
		if (positiveDiff <= 0.00001) {
			fileout << newNum << endl;
		}
		else {
			fileout << parsedNumber << endl;
		}
	}
	filein.close();
	fileout.close();
	//If the file is successfully removed/renamed, a zero value is returned.
	bool removeSuccessful = remove("./resources/numbers.txt");
	bool renameSuccessful = rename("./resources/tempNumbers.txt", "./resources/numbers.txt");
	
	if (removeSuccessful || renameSuccessful) {
		return false;
	}

	return true;
}

