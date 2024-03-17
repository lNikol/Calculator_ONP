#include "LogicComponent.h"
#include <iostream>
using namespace std;

bool LogicComponent::isNumber(const char* str) {
	for (int i = 0; str[i] != '\0'; i++) {
		if (!isdigit(str[i])) {
			return false;
		}
	}
	return true;
}


Token* LogicComponent::createToken(char* char_op, int& char_op_count) {
	const int size = 2;
	// List& stos lub List& wyjscie i dodawac do stosu/wyjscia tokeny
	char symbols[size];
	if (strcmp(char_op, "MIN") == 0)
	{
		symbols[0] = '<';
		symbols[1] = '\0';
	}
	else if (strcmp(char_op, "MAX") == 0)
	{
		symbols[0] = '>';
		symbols[1] = '\0';
	}
	else if (strcmp(char_op, "IF") == 0) {
		symbols[0] = '?';
		symbols[1] = '\0';
	}
	else if (strcmp(char_op, "N") == 0) {
		symbols[0] = '~';
		symbols[1] = '\0';
	}
	else {
		for (int i = 0; i < size; i++) {
			symbols[i] = char_op[i];
		}
	}


	Token* temp = new Token(symbols, size);
	for (int i = 0; i < char_op_count; i++) {
		//cout << char_op[i] << " ";
		char_op[i] = -52; // default undefined value for char
	}
	char_op_count = 0;
	cout << endl;
	//temp->showToken();
	return temp;
}

void LogicComponent::readInput(const char* input) {
	int licznik_otw_nawiasow = 0;
	const short int CHAR_OP_LENGTH = 4;
	char char_op[CHAR_OP_LENGTH];
	int c = 0;
	int char_op_count = 0;
	while (input[c] != '\0') {
		if (input[c] != ' ' && input[c] != '.') {
			char_op[char_op_count++] = input[c];
		}
		else if (input[c] == '\n') {
		}
		else {
			if (input[c] == '.') {
				char_op[char_op_count++] = '.';
				char_op[char_op_count++] = '\0';
			}
			else {
				char_op[char_op_count++] = '\0';
			}
			if (char_op[0] != '\0' && isNumber(char_op)) {
				inputList.push_back(createToken(char_op, char_op_count));
			}
			else {
				Token* tm = createToken(char_op, char_op_count);
				switch (tm->symbols[0]) {
				case '(': licznik_otw_nawiasow++;
				case '+': case '-':
				case '*': case '/':
				case '?': case '~':
				case '<': case '>':
				case ',': case '.':
				case ')':
				{
					short int prior = findPriority(tm->symbols[0]);
					if (prior == 1 || prior == 2) tm->counter = 2;
					inputList.push_back(tm);
					delete tm;
					break;
				}
				default:break;
				}
				//inputList.drawList();
				//cout << endl;
			}
		}
		c++;
	}
	//inputList.end()->next = inputList.begin();

}

short int LogicComponent::findPriority(const char& s) {
	switch (s) {
	case '+': case '-': return 1;
	case '*': case '/': return 2;

	case '?': case '~':
	case '<': case '>': return 3;

	case'(': case ')': return 4;
	default: return -1;
	}
}

void LogicComponent::replaceOperations(Token* token) {
	Token* tmp = stack.end();
	int tokenPrior = findPriority(token->symbols[0]);
	int stackPrior = -1;
	if (tmp != nullptr) {
		stackPrior = findPriority(tmp->symbols[0]);
	}
	else stackPrior = -1;

	while (tmp != nullptr && stackPrior != -1 && stackPrior <= 2 && stackPrior >= tokenPrior) {
		if (tokenPrior != -1) {
			if (token->symbols[0] != '~') {
				cout << "associativity==left\n";
				outputList.push_back(tmp);
				stack.pop_back();
				tmp = stack.end();
				if (tmp != nullptr) {
					stackPrior = findPriority(tmp->symbols[0]);
				}
				else stackPrior = -1;
			}
			else break;
		}
	}
	stack.push_back(token);
}

void LogicComponent::startConversion() {
	firstToken = inputList.begin();
		convertToONP(inputList.begin(), nullptr);
	//	delete& inputList;
}

void LogicComponent::pullOutOperator(Token* end) {
	outputList.push_back(end);
	stack.pop_back();
	end = stack.end();
}

void LogicComponent::convertToONP(Token* token, short int* counter_operands = nullptr) {
	int counter_operands_ = 0;
	short int function_count = 0;
	while (token != nullptr) {// && token->next != firstToken
		Token* tmp(token);
		if (tmp->symbols[0] != '\0' && isNumber(tmp->symbols)) {
			outputList.push_back(tmp);
		}
		else {
			switch (tmp->symbols[0]) {
			case '+': case '-':
			case '*': case '/':
				replaceOperations(tmp); break;
				// functions
			case '?': case '~':
			case '<': case '>':
				// brackets
			case '(':
			{
				//if (tmp == firstToken || tmp->next == firstToken || tmp->next->next == firstToken) return;

				if (findPriority(tmp->symbols[0] == 3) && tmp->next->symbols[0] == '(') {
					tmp->counter = 1;
					//convertToONP(tmp->next->next, &(tmp->counter));
					break;
				}
				//short int opTemp = findPriority(token->symbols[0]);
				//if (opTemp == 3) {
				//	Token* tmp(token);
				//	tmp->index = function_count++;
				//	operationList.push_back(tmp);
				//}
				stack.push_back(tmp);
				break;
			}
			case ',':
			{
				//if (tmp == firstToken || tmp->next == firstToken || tmp->next->next == firstToken) return;
				if(counter_operands!=nullptr) *counter_operands += 1;
				/*Token* tm_ = operationList.end();
				tm_->counter += 1;*/
				auto* end = stack.end();

				//Если стек закончился до того, как был встречен токен открывающая скобка, 
				//то в выражении пропущен разделитель аргументов функции (запятая), либо пропущена открывающая скобка.
				//Проверить это условие (написать код) !!!

				while (end != nullptr && end->symbols[0] != '(') {
					cout << endl << "while1: " << end->symbols[0] << endl;
					cout << "outputlist before : ";
					outputList.drawList();
					cout << endl;
					pullOutOperator(end);

					cout << "outputlist after : ";
					outputList.drawList();
					cout << endl;
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
					pullOutOperator(end);
					cout << "outputlist after) : ";
					outputList.drawList();
					end = stack.end();
					//cout << endl << "while2: " << end << endl;
				}
				if (end != nullptr && end->symbols[0] == '(') {
					stack.pop_back();
					end = stack.end();
				}
				if (end != nullptr) {
					int prior = findPriority(end->symbols[0]);
					if (prior == 3) {
						pullOutOperator(end);
					}
				}
				break;
			}


			default:break;
			}
			cout << "stack: ";
			stack.drawList(); cout << endl;
			cout << "outputlist: ";
			outputList.drawList(); cout << endl;

		}
		token = token->next;
	}

}
