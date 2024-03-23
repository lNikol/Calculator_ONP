#include <iostream>
#include "Token.h"
#include "List.h"
#include "LogicComponent.h"
using namespace std;

int main()
{
	LogicComponent logic;
	// sscanf() - ?

	int lines = 0;
	cin >> lines;
	cin.ignore();
	const int EQUATION_LENGTH = 250000;
	char* input = new char[EQUATION_LENGTH];

	for (int i = 0; i < lines; ++i) {
		fgets(input, EQUATION_LENGTH, stdin);
		printf("\n");
		logic.startConversion(input);
	}
}