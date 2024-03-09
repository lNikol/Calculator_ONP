#include <iostream>
#include "Token.h"
#include "List.h"
using namespace std;


struct OperationPriority {
	char op;
	short int priority;
};

int findPriority(OperationPriority ops[], char op) {
	for (int i = 0; i < sizeof(ops) / sizeof(ops[0]); i++) {
		if (ops[i].op == op) {
			return ops[i].priority;
		}
	}
	return -1;
}

Token* createToken(char* char_op, int& char_op_count, List& list) { 
	char_op[char_op_count++] = '\0';
	// List& stos lub List& wyjscie i dodawac do stosu/wyjscia tokeny

	Token* temp = new Token(char_op, char_op_count);
	for (int i = 0; i < char_op_count; i++) {
		char_op[i] = -52; // default undefined value for char
	}
	char_op_count = 0;
	temp->showToken();
	return temp;
}
int main()
{

	// sscanf() - ?
	OperationPriority operations[] = {
		{'+', 1},
		{'-', 1},
		{'*', 2},
		{'/', 2},
		{'?', 3}, // IF
		{'~', 3}, // N - negacja, unarna operacja
		{'<', 3}, // MIN
		{'>', 3}, // MAX
		{'(', 4},
		{')', 4},
	};

	const int EQUATION_LENGTH = 10000; // zamienic
	//char* equation = new char[EQUATION_LENGTH];

	char input[] = "1 2 3 4 5 6 7";//MIN ( 100 , MAX ( 1 , 34 , 2 ) , 80 ,  MIN ( 66 , 36  , 35 , 77 ) , 50 , 60 ) .
	char output[EQUATION_LENGTH];

	List list;

	/*
	* zrob cin linijki i for dla tych linijek
	* 
	*/

	const short int CHAR_OP_LENGTH = 4;
	char char_op[CHAR_OP_LENGTH];
	int char_op_count = 0;
	int outputIndex = 0;
	int c = 0;

	while (input[c] != '\0') {
		if (input[c] != ' ') {
			char_op[char_op_count++] = input[c];
			if (input[c + 1] == '\0') list.push_back(createToken(char_op, char_op_count, list));
		}
		else if (input[c] == '\n') {

		}
		//(input[c] == 'M' || input[c] == 'A' || input[c] == 'X' || input[c] == 'I' || input[c] == 'N')
		else {
			list.push_back(createToken(char_op, char_op_count, list));
		}
		c++;
		/*if (isdigit(input[c])) {
			output[outputIndex++] = input[c];
		}*/
	}
	cout << endl;
	list.drawList();

	//while (test[length] != '\0' || (int)test[length] > 0) {
	//	if (isdigit(test[length])) {
	//		output[outputIndex] = test[length];
	//		outputIndex++;
	//	}
	//	else if (test[length] == ' ') {}
	//	else {
	//		switch (test[length]) {
	//		case ')':
	//			stos.pop_back();
	//			char temp_operation[4];
	//			int temp_count = 0;
	//			add_before_open(output, stos, outputIndex);
	//			
	//			if (stos.size() > 0) stos.pop_back();
	//			else {

	//			}
	//			break;
	//		default: 
	//			auto end = stos.end();
	//			end--;
	//			char previous = *end;
	//			if (findPriority(operations, previous) >= findPriority(operations, test[length])) {
	//				output[outputIndex] = stos.back();
	//				outputIndex++;
	//				stos.pop_back();
	//				stos.push_back(test[length]);
	//			}
	//			else {
	//				stos.push_back(test[length]);
	//			}
	//			break;
	//		}
	//	}
	//	cout << test[length];
	//	length++;
	//}

	//// teraz trzeba odczytac output i zrobic operacje

	//while (output[outputIndex] != '\0' || outputIndex < 0) {
	//	outputIndex--;
	//}
		

	int amount_of_lines = 0;
	//cin >> amount_of_lines;

	//for (int i = 0; i < amount_of_lines; i++) {
		//cin.getline(equation, EQUATION_LENGTH);
	//}
	
}