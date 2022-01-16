
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
		//Generates a double random number (as we can work with real numbers)
		double floatingRandom = (double)rand() / RAND_MAX;
		double floatingRandomInRange = MIN_VALUE_NUMBERS + floatingRandom * (MAX_VALUE_NUMBERS - MIN_VALUE_NUMBERS);
		//Generates a positive random integer for the cases where we can only work with such numbers
		int positiveIntegerRandom = rand() % ((int)MAX_VALUE_NUMBERS - (int)MIN_VALUE_POSITIVE_NUMBERS + 1) + (int)MIN_VALUE_POSITIVE_NUMBERS;
		
		if (functionsArr[random] == "%" || functionsArr[random] == ">>" || functionsArr[random] == "<<") {
			functions << functionsArr[random] << positiveIntegerRandom << endl;
		}
		else if (functionsArr[random] == "/") {
			//Since we cannot divide by zero, if the generated number is 0, we should change it
			while (floatingRandomInRange == 0) {
				floatingRandomInRange = MIN_VALUE_NUMBERS + floatingRandomInRange * (MAX_VALUE_NUMBERS - MIN_VALUE_NUMBERS);
			}
			functions << functionsArr[random] << floatingRandomInRange << endl;
		}
		else {
			functions << functionsArr[random] << floatingRandomInRange << endl;
		}
	}
	functions.close();
}

string Program::initMenu(bool first) {
	// If it is the first initialization of the menu, a title should be included too
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
	cout << "The numbers are:" << endl;
	fstream numbers;
	numbers.open("./resources/numbers.txt", std::fstream::in);
	std::string buffer;
	while (getline(numbers, buffer)) {
		cout << buffer << endl;
	}
	numbers.close();
}

void Program::showFunctions() {
	cout << "The functions are:" << endl;
	fstream functions;
	functions.open("./resources/functions.txt", std::fstream::in);
	std::string buffer;
	while (getline(functions, buffer)) {
		cout << buffer << endl;
	}
	functions.close();
}

bool Program::validateFormat(string arr) {
	bool correct = true;
	int length = arr.size();
	if (length < 2) {
		correct = false;
		return correct;
	}
	if (arr[0] == '+' || arr[0] == '-' || arr[0] == '*' || arr[0] == '/' || arr[0] == '%')
	{
		for (int i = 1; i < length; i++)
		{
			char currentSymbol = arr[i];
			// Checking if it is a digit or dot (ascii table values) - if it isn't- the input becomes invalid
			if ((currentSymbol < 48 || currentSymbol > 57) && currentSymbol != '.') {
				correct = false;
				break;
			}
		}
	}
	else if ((arr[0] == '>' && arr[1] == '>') || (arr[0] == '<' && arr[1] == '<')) {
		// The next (length-2) symbols should be a valid number in order for the whole input to be valid
		for (int i = 2; i < length; i++)
		{
			char currentSymbol = arr[i];
			// Checking if it is a digit or dot (ascii table values) - if it isn't- the input becomes invalid
			if (currentSymbol < 48 || currentSymbol > 57) {
				correct = false;
				break;
			}
		}
	}
	else {
		// If it starts with other symbol- the input is invalid
		correct = false;
	}
	return correct;
}

bool Program::checkFunctionContains(string func) {
	bool contains = false;
	int length = func.size();
	string numberStr;
	fstream functions;
	functions.open("./resources/functions.txt", std::fstream::in);
	std::string buffer;
	double result = 0;
	if (func[0] == '+' || func[0] == '-' || func[0] == '*' || func[0] == '/' || func[0] == '%') 
	{
		// Determining what is the number standing next to the symbol for the operation
		for (int i = 1; i < length; i++)
		{
			numberStr += func[i];
		}
		// Converting it from string to double
		double number = stod(numberStr);
		result = number;
		
	}
	// The operators ">>" and "<<" take up 2 characters and thus are separated into different cases
	else if ((func[0] == '>' && func[1] == '>') || (func[0] == '<' && func[1] == '<')) {
		// Determining what is the number standing next to the symbol for the operation
		for (int i = 2; i < length; i++)
		{
			numberStr += func[i];
		}
		// Converting it from string to int (they work only with integers)
		int number = stod(numberStr);
		result = number;
	}

	while (getline(functions, buffer)) {
		char currentFunc = buffer[0];
		string currentNumberStr;
		if (currentFunc == '+' || currentFunc == '-' || currentFunc == '*' || currentFunc == '/' || currentFunc == '%') {
			if (currentFunc == func[0]) {
				// Determining what is the number standing next to the symbol for the operation
				for (int i = 1; i < length; i++)
				{
					currentNumberStr += buffer[i];
				}
				// Converting it from string to double
				double currentNumber = stod(currentNumberStr);
				/*Because of the small differences in the numbers when comparing numbers
				of type double, a tolerance is needed*/
				double difference = result - currentNumber;
				double positiveDiff = difference > 0 ? difference : (-1) * difference;
				if (positiveDiff <= 0.00001) {
					contains = true;
					break;
				}
			}
		}
		else if (currentFunc == '>' || currentFunc == '<') {
			// Determining what is the number standing next to the symbol for the operation
			for (int i = 2; i < length; i++)
			{
				currentNumberStr += buffer[i];
			}
			// Converting it from string to integer (they work only with integers)
			int currentNumber = stod(currentNumberStr);
			if ((func[0]==currentFunc && func[1]==buffer[1]) && currentNumber == (int)result) {
				contains = true;
				break;
			}
		}		
	}
	functions.close();
	return contains;
}

