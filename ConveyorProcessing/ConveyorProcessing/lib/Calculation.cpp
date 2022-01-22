#include "Calculation.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

Calculation::Calculation()
{
}

Calculation::~Calculation()
{
}

void Calculation::jsonSerializer(double** matrix) {

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

void Calculation::calculate(char carryMode, int formatInput, char saveFileInput) {
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
	double previousResult = 0;
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
		double numberInFile = currentNumber;
		for (int cntFuncs = 0; cntFuncs < functionsCount; ++cntFuncs) {
			string currentFunc = funcs[cntFuncs];
			char sign = currentFunc[0];
			double result = 0;
			double numberAfterSign = 0;
			if (counterCols != 0 && carryMode == '+') {
				previousResult = matrix[counterRows][counterCols - 1];
				currentNumber = numberInFile + previousResult;
			}

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
					calculation << setw(10) << (int)matrix[i][j] << ' ';
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



