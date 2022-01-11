
#include "Program.h"
#include <iostream>
#include <fstream>
#include <string>
//using namespace std;

// For testing purposes min value and max value are set
int const MIN_VALUE_NUMBERS = -100;
int const MAX_VALUE_NUMBERS = 100;
int const MIN_VALUE_FUNCTIONS = 0;
int const MAX_VALUE_FUNCTIONS = 6;

Program::Program()
{
}

Program::~Program()
{
}

void Program::generateRandomNumbers()
{
	fstream numbers;
	numbers.open("./resources/numbers.txt", std::fstream::out);
	srand(time(0));
	
	//For testing purposes , the number of generated random numbers is reduced to 5
	for (int i = 0; i < 5; i++) {
		//Generates a random number in the range of min and max value
		int random = rand() % (MAX_VALUE_NUMBERS - MIN_VALUE_NUMBERS + 1) + MIN_VALUE_NUMBERS;
		numbers << random << endl;
	}
	numbers.close();
}

void Program::generateRandomFunctions() {
	fstream functions;
	functions.open("./resources/functions.txt", std::fstream::out);
	srand(time(0));
	string functionsArr[7] = { "+","-","*","/","%","<<",">>" };
	//For testing purposes , the number of generated random operations is reduced to 6
	for (int i = 0; i < 7; i++) {
		//Generates a random number in the range of 0 to 6 - because we have 7 different possible operations
		int random = rand() % (MAX_VALUE_FUNCTIONS - MIN_VALUE_FUNCTIONS + 1) + MIN_VALUE_FUNCTIONS;
		functions << functionsArr[random] << endl;
	}
	functions.close();
}

char Program::initMenu() {
	fstream welcome;
	welcome.open("./resources/welcome.txt", std::fstream::in);
	std::string buffer;
	while (getline(welcome, buffer)) {
		std::cout << buffer << "\n";
	}
	char input;
	cin >> input;
	return input;
}

