
#include "Program.h"
#include <iostream>
#include <fstream>
#include <string>
//using namespace std;

// For testing purposes min value and max value are set
const double MIN_VALUE_NUMBERS = -100;
const double MIN_VALUE_POSITIVE_NUMBERS = 0;
const double MAX_VALUE_NUMBERS = 100;
const int MIN_VALUE_FUNCTIONS = 0;
const int MAX_VALUE_FUNCTIONS = 6;

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
		double random = (double)rand() / RAND_MAX;
		double randomInRange = MIN_VALUE_NUMBERS + random * (MAX_VALUE_NUMBERS - MIN_VALUE_NUMBERS);
		numbers << randomInRange << endl;
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
		double floatingRandom = (double)rand() / RAND_MAX;
		double floatingRandomInRange = MIN_VALUE_NUMBERS + random * (MAX_VALUE_NUMBERS - MIN_VALUE_NUMBERS);
		int positiveIntegerRandom = rand() % ((int)MAX_VALUE_NUMBERS - (int)MIN_VALUE_POSITIVE_NUMBERS + 1) + (int)MIN_VALUE_POSITIVE_NUMBERS;
		
		if (functionsArr[random] == "%" || functionsArr[random] == ">>" || functionsArr[random] == "<<") {
			functions << functionsArr[random] << positiveIntegerRandom << endl;
		}
		else if (functionsArr[random] == "/") {
			while (positiveIntegerRandom == 0) {
				int positiveIntegerRandom = rand() % ((int)MAX_VALUE_NUMBERS - (int)MIN_VALUE_POSITIVE_NUMBERS + 1) + (int)MIN_VALUE_POSITIVE_NUMBERS;
			}
			functions << functionsArr[random] << positiveIntegerRandom << endl;
		}
		else {
			functions << functionsArr[random] << floatingRandomInRange << endl;
		}
	}
	functions.close();
}

string Program::initMenu(bool first) {
	if (first) {
		cout << "Welcome to Conveyor Processing project!" << endl;
	}
	fstream commands;
	commands.open("./resources/commands.txt", std::fstream::in);
	std::string buffer;
	while (getline(commands, buffer)) {
		std::cout << buffer << "\n";
	}
	string input;
	cin >> input;
	commands.close();
	return input;
}

bool Program::checkNumberContains(double number) {
	fstream numbers;
	numbers.open("./resources/numbers.txt", std::fstream::in);
	std::string buffer;
	bool contains = false;
	while (getline(numbers, buffer)) {
		double parsedNumber = stod(buffer);
		/*Because of the small differences in the numbers when comparing numbers 
			of type double, a tolerance is needed*/
		double difference = parsedNumber - number;
		double positiveDiff = difference > 0 ? difference : (-1) * difference;
		if (positiveDiff <= 0.00001) {
			contains = true;
		}
	}
	numbers.close();
	return contains;
}

void Program::showNumbers() {
	//ifstream numbers("./resources/numbers.txt");
	cout << "The numbers are:" << endl;
	fstream numbers;
	numbers.open("./resources/numbers.txt", std::fstream::in);
	std::string buffer;
	while (getline(numbers, buffer)) {
		cout << buffer << endl;
	}
	numbers.close();
}

