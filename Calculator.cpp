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

bool isNumber(const char* str) {
	for (int i = 0; str[i] != '\0'; i++) {
		if (!isdigit(str[i])) {
			return false;
		}
	}
	return true;
}


Token* createToken(char* char_op, int& char_op_count) { 
	// List& stos lub List& wyjscie i dodawac do stosu/wyjscia tokeny

	Token* temp = new Token(char_op, char_op_count);
	for (int i = 0; i < char_op_count; i++) {
		cout << char_op[i] << " ";
		char_op[i] = -52; // default undefined value for char
	}
	char_op_count = 0;
	cout << endl;
	//temp->showToken();
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

	char input[] = "MIN ( 3 - 9 * 2 / 7 , IF ( 2 + 7 , 0 - 6 , 8 + 0 ) , IF ( 6 * 5 , ( 5 / 8 ) , N ( 6 ) ) , MAX ( 4 , 4 , 4 , 1 ) / 7 * 1 , MIN ( MIN ( 7 , 6 , 0 , 0 , 6 ) , ( 0 * 3 ) , ( 6 * 1 ) , ( 8 + 1 ) ) , ( 7 - 5 + N 4 ) ) .";//

	List inputList;
	List outputList;
	List stack;

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
			//if (input[c + 1] == '\0' && input[c] != '.') {
			//	char_op[char_op_count++] = '\0';
			//	cout << "dzialam\n";
			//}
		}
		else if (input[c] == '\n') {

		}
		else if (input[c] == '.') {
		}
		else {
			if (input[c + 1] == '.') {
				cout << "KROPKA\n";
			}
			char_op[char_op_count++] = '\0';

			if (char_op[0] != '\0' && isNumber(char_op)) {
				//cout << "S";
				outputList.push_back(createToken(char_op, char_op_count));
			}
			else {
				if (char_op[0] == '.') cout << "Kr\n";
				Token* tm = createToken(char_op, char_op_count);
				switch (tm->symbols[0]) {
				case '+': stack.push_back(tm); break;
				case '-': stack.push_back(tm); break;
				case '*': stack.push_back(tm); break;
				case '/': stack.push_back(tm); break;
				case '?': stack.push_back(tm); break;
				case '~': stack.push_back(tm); break;
				case '<': stack.push_back(tm); break;
				case '>': stack.push_back(tm); break;
				case '(': stack.push_back(tm); break;
				case ',': 
				{
					//delete tm;
					auto* end = stack.end();
					//Token* tmp = end;
					// Nie jestem pewien czy poprawnie dziala usuniecie wskaznika. mysle ze gdzies moga byc wycieki pamieci
					//cout << "B" << end <<" "<<end->symbols[0];
					while (end != nullptr && end->symbols[0] != '(') {
						//cout << endl << "while1: " << end << endl;
						outputList.push_back(end);
						stack.pop_back();
						end = stack.end();
						//cout << endl << "while2: " << end << endl;

					}
					break;
				}
					
				
				default:break;
				}
				stack.drawList(); cout << endl;
				//inputList.push_back(tm); - jakis problem z tm

			}
		}
		c++;
		/*if (isdigit(input[c])) {
			output[outputIndex++] = input[c];
		}*/
	}
	cout << endl;
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