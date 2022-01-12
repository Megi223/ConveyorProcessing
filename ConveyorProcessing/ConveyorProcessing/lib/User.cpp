#include "User.h"
#include <iostream>

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

