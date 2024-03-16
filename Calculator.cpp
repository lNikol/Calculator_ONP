#include <iostream>
#include "Token.h"
#include "List.h"
using namespace std;


struct OperationPriority {
	char op;
	short int priority;
	char associativity[6];
};

OperationPriority findPriority(OperationPriority ops[], char op) {
	for (int i = 0; i < sizeof(ops[0]); i++) {
		if (ops[i].op == op) {
			return ops[i];
		}
	}
	OperationPriority t = { 'A', -1, "none" };
	return t;
}

bool isNumber(const char* str) {
	for (int i = 0; str[i] != '\0'; i++) {
		if (!isdigit(str[i])) {
			return false;
		}
	}
	return true;
}


void replaceOperations(OperationPriority ops[], List& stack, List& output, Token* token) {
	Token* tmp = stack.end();
	char left[6] = "left";
	OperationPriority tokenOp = findPriority(ops, token != nullptr ? token->symbols[0] : 'A');
	OperationPriority stackOp;
	if (tmp != nullptr) { stackOp = findPriority(ops, tmp->symbols[0]); }
	else stackOp = { 'A', -1, "none" };

	while (tmp != nullptr && stackOp.priority != -1 && stackOp.priority <= 2 && stackOp.priority >= tokenOp.priority) {
		if (tokenOp.priority != -1) {
			if (strcmp(tokenOp.associativity, left) == 0) {
				cout << "associativity==left\n";
				output.push_back(tmp);
				stack.pop_back();
				tmp = stack.end();
				if (tmp != nullptr) { stackOp = findPriority(ops, tmp->symbols[0]); }
				else stackOp = { 'A', -1, "none" };
			}
			else break;
		}
	}
	stack.push_back(token);
}


Token* createToken(char* char_op, int& char_op_count) {
	// List& stos lub List& wyjscie i dodawac do stosu/wyjscia tokeny

	Token* temp = new Token(char_op, char_op_count);
	for (int i = 0; i < char_op_count; i++) {
		//cout << char_op[i] << " ";
		char_op[i] = -52; // default undefined value for char
	}
	char_op_count = 0;
	cout << endl;
	temp->showToken();
	return temp;
}
int main()
{

	// sscanf() - ?
	OperationPriority operations[] = {
		{'+', 1, "left"},
		{'-', 1, "left"},
		{'*', 2, "left"},
		{'/', 2, "left"},
		{'?', 3, "left"}, // IF
		{'~', 3, "right"}, // N - negacja, unarna operacja (right associativity)
		{'<', 3, "left"}, // MIN
		{'>', 3, "left"}, // MAX
		{'(', 4, "left"},
		{')', 4, "left"},
	};

	const int EQUATION_LENGTH = 10000; // zamienic
	//char* input = new char[EQUATION_LENGTH];

	char input[] = "MIN ( 3 - 9 * 2 / 7 , IF ( 2 + 7 , 0 - 6 , 8 + 0 ) , IF ( 6 * 5 , ( 5 / 8 ) , N ( 6 ) ) , MAX ( 4 , 4 , 4 , 1 ) / 7 * 1 , MIN ( MIN ( 7 , 6 , 0 , 0 , 6 ) , ( 0 * 3 ) , ( 6 * 1 ) , ( 8 + 1 ) ) , ( 7 - 5 + N 4 ) ) .";//
	int amount_of_lines = 0;

	List outputList;
	List stack;

	/*
	* zrob cin linijki i for dla tych linijek (wiecej niz 1 linijka wejscia)
	*
	*/





	/*
	* Sprawdzic notacje, bo są nawiasy, chociaz nie musza byc teoretycznie
	* Dodac funkcje min,max,if,N
	*/






	const short int CHAR_OP_LENGTH = 4;
	char char_op[CHAR_OP_LENGTH];
	int char_op_count = 0;
	int outputIndex = 0;
	int c = 0;

	int count = 0;

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
			char_op[char_op_count++] = '\0';

			if (char_op[0] != '\0' && isNumber(char_op)) {
				//cout << "S";

				//for (int i = 0; i < char_op_count; i++) {
				//	cout << char_op[i] << " ";
				//}
				outputList.push_back(createToken(char_op, char_op_count));
			}
			else {
				Token* tm = createToken(char_op, char_op_count);
				switch (tm->symbols[0]) {
				case '+':
				case '-':
				case '*':
				case '/':
					replaceOperations(operations, stack, outputList, tm); break;
				// functions
				case '?':
				case '~':
				case '<':
				case '>':
				case '(':
				{
					stack.push_back(tm);
					break;
				}
				case ',':
				{
					count++;
					auto* end = stack.end();

					//Если стек закончился до того, как был встречен токен открывающая скобка, 
					//то в выражении пропущен разделитель аргументов функции (запятая), либо пропущена открывающая скобка.
					//Проверить это условие (написать код) !!!

					while (end != nullptr && end->symbols[0] != '(') {
						cout << endl << "while1: " << end->symbols[0] << endl;
						cout << "outputlist before: ";
						outputList.drawList();
						cout << endl;
						outputList.push_back(end);
						cout << "outputlist after: ";
						outputList.drawList();
						cout << endl;
						stack.pop_back();
						end = stack.end();
					}
					// if(end != nullptr && end->symbols[0] == '(') stack.pop_back(); // not sure
					break;
				}
				case ')': {
					//Если стек закончился до того, как был встречен токен открывающая скобка, то в выражении пропущена скобка.
					// Проверить условия (написать код) !!!
					auto* end = stack.end();
					while (end != nullptr && end->symbols[0] != '(') {
						cout << endl << "while2) : " << end->symbols[0] << endl;
						cout << "outputlist before) : ";
						outputList.drawList();
						cout << endl;
						outputList.push_back(end);
						cout << "outputlist after) : ";
						outputList.drawList();
						cout << endl;
						stack.pop_back();
						end = stack.end();
						//cout << endl << "while2: " << end << endl;
					}
					if (end != nullptr && end->symbols[0] == '(') {
						stack.pop_back();
						end = stack.end();
					}
					if (end != nullptr) {
						int prior = findPriority(operations, end->symbols[0]).priority;
						if (prior != -1 && prior == 3) {
							outputList.push_back(end);
							stack.pop_back();
							end = stack.end();
						}
					}
					break;
				}


				default:break;
				}
				cout << "stack: ";
				stack.drawList(); cout << endl;

			}
		}
		c++;
	}
	cout << count;
	cout << endl;
	outputList.drawList(); cout << endl;
	auto* end = stack.end();
	cout << "Poza glownym while\n";
	while (end != nullptr) {
		cout << "Cos jest: " << end->symbols[0] << endl;
		outputList.push_back(end);
		stack.pop_back();
		end = stack.end();
	}
	cout << endl;
	
}