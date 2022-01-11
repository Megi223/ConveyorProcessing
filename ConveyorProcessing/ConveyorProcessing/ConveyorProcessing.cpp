
#include <iostream>

#include "lib/Program.h"

int main()
{
    Program program;
    program.generateRandomNumbers();
    program.generateRandomFunctions();
    char input = program.initMenu();
    cout << input;
    
    return 0;
}
