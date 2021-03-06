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
* Calculation class implementation
*
*/

#include "Calculation.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

Calculation::Calculation() {
}

Calculation::~Calculation() {
}

void Calculation::jsonSerializer(double** matrix,string path,int numbersCount,int functionsCount) {
	fstream calc;
	calc.open("./resources/calculation.txt", std::fstream::out);
	calc << '{' << endl;
	calc << "	\"byRows\": [" << endl;
	for (int i = 0; i < numbersCount; i++) {
		calc << "		[";
		for (int j = 0; j < functionsCount; j++) {
			if (trunc(matrix[i][j]) == matrix[i][j]) {
				if (j == functionsCount - 1) {
					calc << (int)matrix[i][j];
				}
				else {
					calc << (int)matrix[i][j] << ", ";
				}
			}
			else {
				if (j == functionsCount - 1) {
					calc << fixed << setprecision(2) << matrix[i][j];
				}
				else {
					calc << fixed << setprecision(2) << matrix[i][j] << ", ";
				}
			}
		}
		if (i == numbersCount - 1) {
			calc << ']';
		}
		else {
			calc << "],";
		}
		calc << endl;
	}
	calc << "	]," << endl;
	calc << "	\"byCols\": [" << endl;
	// Finding the transponse matrix
	double** transponseMatrix = new double*[functionsCount];
	for (int i = 0; i < functionsCount; ++i) {
		transponseMatrix[i] = new double[numbersCount];
	}
	for (int fCnt = 0; fCnt < functionsCount; fCnt++) {
		for (int nCnt = 0; nCnt < numbersCount; nCnt++) {
			transponseMatrix[fCnt][nCnt] = matrix[nCnt][fCnt];
		}
	}
	for (int i = 0; i < functionsCount; i++)
	{
		calc << "		[";
		for (int j = 0; j < numbersCount; j++) {
			if (trunc(transponseMatrix[i][j]) == transponseMatrix[i][j]) {
				if (j == numbersCount - 1) {
					calc << (int)transponseMatrix[i][j];
				}
				else {
					calc << (int)transponseMatrix[i][j] << ", ";
				}
			}
			else {
				if (j == numbersCount - 1) {
					calc << fixed << setprecision(2) << transponseMatrix[i][j];
				}
				else {
					calc << fixed << setprecision(2) << transponseMatrix[i][j] << ", ";
				}
			}
		}
		if (i == functionsCount - 1) {
			calc << ']';
		}
		else {
			calc << "],";
		}
		calc << endl;
	}
	calc << "	]," << endl;
	calc << '}' << endl;
	calc.close();
	for (int i = 0; i < functionsCount; i++)
	{
		delete[] transponseMatrix[i];
	}
	delete[] transponseMatrix;
}

double Calculation::extractNumberFromFunction(string func, int startIndex) {
	string numberStr;
	// Determining what is the number standing next to the symbol for the operation
	for (int i = startIndex; i < func.size(); i++) {
		numberStr += func[i];
	}
	// Converting it from string to double
	double number = stod(numberStr);
	return number;
}

int Calculation::countLines(string path) {
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
				switch (sign) {
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
	if (formatInput == 2) {
		string path = "./resources/calculation.txt";
		jsonSerializer(matrix,path,numbersCount,functionsCount);
	}
	else {
		fstream calculation;
		calculation.open("./resources/calculation.txt", std::fstream::out);
		for (int i = 0; i < numbersCount; i++) {
			for (int j = 0; j < functionsCount; j++) {
				if (trunc(matrix[i][j]) == matrix[i][j]) {
					calculation << setw(10) << (int)matrix[i][j] << ' ';
				}
				else {
					calculation << fixed << setprecision(2) << setw(10) << matrix[i][j] << ' ';
				}
			}
			calculation << endl;
		}
		calculation.close();
	}
	fstream resultCalc;
	resultCalc.open("./resources/calculation.txt", std::fstream::in);
	string result;
	while (getline(resultCalc, result)) {
		cout << result << endl;
	}
	resultCalc.close();
	if (saveFileInput == '-') {
		try {
			bool successfulRemove = remove("./resources/calculation.txt");
		}
		catch (const std::exception&) {
			cout << "An error occured";
		}
	}
	else {
		cout << "You can find it saved as a file, too." << endl;
	}

	for (int i = 0; i < numbersCount; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
	numbers.close();
	functions.close();
}