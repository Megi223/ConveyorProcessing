
#include "Program.h"
#include <iostream>
#include <fstream>

using namespace std;

// For testing purposes min value and max value are set
int const MIN_VALUE_NUMBERS = -100;
int const MAX_VALUE_NUMBERS = 100;

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

