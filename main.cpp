#include <iostream>
#include "Token.h"
#include "List.h"
#include "LogicComponent.h"
using namespace std;

int main()
{
	LogicComponent logic;
	// sscanf() - ?


	//int lines;
	//cin >> lines;
	//const int EQUATION_LENGTH = 10000; // zamienic
	//char* input = new char[EQUATION_LENGTH];
	//for (int i = 0; i < lines; i++) {
	//	cin >> input;
	//	logic.readInput(input);
	//}



	char input[] = "MIN ( 100 , MAX ( 1 , 34 , 2 ) , 80 ,  MIN ( 66 , 36  , 35 , 77 ) , 50 , 60 ) .";//
	logic.readInput(input);
	logic.startConversion();
}