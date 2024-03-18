#include <iostream>
#include "Token.h"
#include "List.h"
#include "LogicComponent.h"
using namespace std;

int main()
{
	LogicComponent logic;
	// sscanf() - ?

	int lines;
	cin >> lines;
	cin.ignore();
	const int EQUATION_LENGTH = 10000; // zamienic
	char* input = new char[EQUATION_LENGTH];
	for (int i = 0; i < lines; i++) {
		fgets(input, EQUATION_LENGTH, stdin);
		logic.readInput(input);
		logic.startConversion();
		cout << endl;
	}



	//char input[] = "MIN ( 3 - 9 * 2 / 7 , IF ( 2 + 7 , 0 - 6 , 8 + 0 ) , IF ( 6 * 5 , ( 5 / 8 ) , N ( 6 ) ) , MAX ( 4 , 4 , 4 , 1 ) / 7 * 1 , MIN ( MIN ( 7 , 6 , 0 , 0 , 6 ) , ( 0 * 3 ) , ( 6 * 1 ) , ( 8 + 1 ) ) , ( 7 - 5 + N 4 ) ) .";//
	//logic.readInput(input);
}