
#include "Program.h"
#include <iostream>
#include <fstream>

using namespace std;

// For testing purposes min value and max value are set
int const MIN_VALUE_NUMBERS = -100;
int const MAX_VALUE_NUMBERS = 100;
int const MIN_VALUE_OPERATIONS = 0;
int const MAX_VALUE_OPERATIONS = 6;

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

void Program::generateRandomOperations() {
	fstream operations;
	operations.open("./resources/operations.txt", std::fstream::out);
	srand(time(0));
	string operationsArr[7] = { "+","-","*","/","%","<<",">>" };
	//For testing purposes , the number of generated random operations is reduced to 6
	for (int i = 0; i < 7; i++) {
		//Generates a random number in the range of 0 to 6 - because we have 7 different possible operations
		int random = rand() % (MAX_VALUE_OPERATIONS - MIN_VALUE_OPERATIONS + 1) + MIN_VALUE_OPERATIONS;
		operations << operationsArr[random] << endl;
	}
	operations.close();
}

