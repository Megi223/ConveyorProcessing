
#include "Program.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
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
		// For testing purposes a limit to 2 decimal places is set
		numbers << fixed << setprecision(2) << randomInRange << endl;
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
			functions << functionsArr[random] << fixed << setprecision(2) << floatingRandomInRange << endl;
		}
		else {
			functions << functionsArr[random] << fixed << setprecision(2) << floatingRandomInRange << endl;
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
			if (i == 1 && currentSymbol == '-') {
				continue;
			}
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

int Program::checkFunctionContains(string func) {
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
	int iter = 0;
	int rowFound = -1;
	while (getline(functions, buffer)) {
		iter++;
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
					rowFound = iter;
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
				rowFound = iter;
				break;
			}
		}		
	}
	functions.close();
	return rowFound;
}

int countLines(string path) {
	fstream file;
	file.open(path, std::fstream::in);
	int counter = 0;
	string buffer;
	while (getline(file, buffer)) {
		counter++;
	}
	file.close();
	return counter;
}

double extractNumberFromFunction(string func, int startIndex) {
	string numberStr;
	// Determining what is the number standing next to the symbol for the operation
	for (int i = startIndex; i < func.size(); i++)
	{
		numberStr += func[i];
	}
	// Converting it from string to double
	double number = stod(numberStr);
	return number;
}

void Program::jsonSerializer(double** matrix) {

}

void Program::calcWithoutCarryMode(int formatInput, char saveFileInput) {
	fstream numbers;
	numbers.open("./resources/numbers.txt", std::fstream::in);
	fstream functions;
	functions.open("./resources/functions.txt", std::fstream::in);
	/* In this particular case, for testing purposes we have already set the number 
		of both functions and numbers files- but in order for it to work in the general
		case and with different numbers these functions are needed*/
	int numbersCount = countLines("./resources/numbers.txt");
	int functionsCount = countLines("./resources/functions.txt");
	string currentNumberStr;
	string currentFunctionStr;
	int counterRows = 0;
	int counterCols = 0;
	double** matrix = new double* [numbersCount];
	for (int i = 0; i < numbersCount; ++i) {
		matrix[i] = new double[functionsCount];
	}
	vector<string> funcs;
	while (getline(functions, currentFunctionStr)) {
		funcs.push_back(currentFunctionStr);
	}
	while (getline(numbers, currentNumberStr)) {
		double currentNumber = stod(currentNumberStr);
		for (int cntFuncs = 0; cntFuncs < functionsCount; ++cntFuncs) {
			string currentFunc = funcs[cntFuncs];
			char sign = currentFunc[0];
			double result = 0;
			double numberAfterSign = 0;
			if (sign == '+' || sign == '-' || sign == '*' || sign == '/' || sign == '%') {
				numberAfterSign = extractNumberFromFunction(currentFunc, 1);
				switch (sign)
				{
				case '+': result = currentNumber + numberAfterSign; break;
				case '-': result = currentNumber - numberAfterSign; break;
				case '*': result = currentNumber * numberAfterSign; break;
				case '/': result = currentNumber / numberAfterSign; break;
				default:
					break;
				}
				if (sign == '%') {
					/*Checking if the number on which we will perform the operation
						is an integer - if it is not, the operation is invalid
						If successful, trunc returns an integer value of x,
						rounded towards zero.*/
					if (trunc(currentNumber) == currentNumber) {
						/* When generating random numbers, we have ensured that
							the number after % will be an integer, so such checking
							isn't necessary to be performed on it*/
						result = (int)currentNumber % (int)numberAfterSign;
					}
					else {
						result = 0;
					}
				}
			}
			
			else if (sign == '>') {
				numberAfterSign = extractNumberFromFunction(currentFunc, 2);
				if (trunc(currentNumber) == currentNumber) {
					/* When generating random numbers, we have ensured that
						the number after >> will be an integer, so such checking
						isn't necessary to be performed on it*/
					result = (int)currentNumber >> (int)numberAfterSign;
				}
				else {
					result = 0;
				}
			}
			else if (sign == '<') {
				numberAfterSign = extractNumberFromFunction(currentFunc, 2);
				if (trunc(currentNumber) == currentNumber) {
					/* When generating random numbers, we have ensured that
						the number after << will be an integer, so such checking
						isn't necessary to be performed on it*/
					result = (int)currentNumber << (int)numberAfterSign;
				}
				else {
					result = 0;
				}
			}
			matrix[counterRows][counterCols] = (double)result;
			counterCols++;
		}
		counterCols = 0;
		counterRows++;
	}
	fstream calculation;
	calculation.open("./resources/calculation.txt", std::fstream::out);
	if (formatInput == 2) {
		// to be implemented
		jsonSerializer(matrix);
	}
	else {
		for (int i = 0; i < numbersCount; i++)
		{
			for (int j = 0; j < functionsCount; j++)
			{
				if (trunc(matrix[i][j]) == matrix[i][j]) {
					calculation  << setw(10) << (int)matrix[i][j] << ' ';
				}
				else {
					calculation << fixed << setprecision(2) << setw(10) << matrix[i][j] << ' ';
				}
			}
			calculation << endl;
		}
	}
	calculation.close();
	fstream resultCalc;
	resultCalc.open("./resources/calculation.txt", std::fstream::in);
	string result;
	while (getline(resultCalc, result)) {
		cout << result << endl;
	}
	resultCalc.close();
	if (saveFileInput == '-') {
		try
		{
			bool successfulRemove = remove("./resources/calculation.txt");
		}
		catch (const std::exception&)
		{
			cout << "An error occured";
		}
	}
	else {
		cout << "You can find it saved as a file, too." << endl;
	}

	for (int i = 0; i < numbersCount; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
	numbers.close();
	functions.close();

}

