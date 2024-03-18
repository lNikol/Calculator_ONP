﻿#include "LogicComponent.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

// Переписать методы и класс!
// getCharNumber - naprawic metode, jako argument wysylac countDigits(num) + 1

short int countDigits(int number) {
	if (number == 0) return 1;
	int count = number > 0 ? 0 : 1;
	while (number != 0) {
		number /= 10;
		count++;
	}
	return count;
}

void getCharNumber(char* buff, const short int& length, int& res) {
	buff = new char[length];
	sprintf_s(buff, length, "%d", res);
}

void insertionSort(int arr[], const short int& n)
{
	short int i, key, j;
	for (i = 1; i < n; i++) {
		key = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}

bool LogicComponent::isNumber(const char* str) {
	for (int i = 0; str[i] != '\0'; i++) {
		if (!isdigit(str[i])) {
			return false;
		}
	}
	return true;
}

Token* LogicComponent::createToken(char* char_op, int& char_op_count) {
	int size = 2;
	char* symbols = new char[size];
	
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
		delete[] symbols;
		size = char_op_count;
		symbols = new char[size];
		for (int i = 0; i < size; i++) {
			symbols[i] = char_op[i];
		}
	}


	Token* temp = new Token(symbols, size);
	for (int i = 0; i < char_op_count; i++) {
		char_op[i] = -52; // default undefined value for char
	}
	char_op_count = 0;
	delete[] symbols;
	return temp;
}

void LogicComponent::readInput(const char* input) {
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
				case '+': case '-':
				case '*': case '/':
				case '?': case '~':
				case '<': case '>':
				case ',': case '.':
				case '(': case ')': 
				{
					short int prior = findPriority(tm->symbols[0]);
					if (prior == 1 || prior == 2) tm->arguments = 2;
					if (tm->symbols[0] == '~') tm->arguments = 1;
					inputList.push_back(tm);
					delete tm;
					break;
				}
				default:break;
				}
			}
		}
		c++;
	}
}

short int LogicComponent::findPriority(const char& s) {
	switch (s) {
	case '+': case '-': return 1;
	case '*': case '/': return 2;

	case '?': case '<': case '~': case '>': return 3; // negacja right associative

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

void LogicComponent::pullOutOperator(Token* end) {
	while (end != nullptr && end->symbols[0] != '(') {
		cout << endl << "while: " << end->symbols[0] << endl;
		cout << "outputlist before : ";
		outputList.drawList();
		cout << "\nstack before :";
		stack.drawList();
		cout << endl;
		outputList.push_back(end);
		stack.pop_back();
		cout << "outputlist after : ";
		outputList.drawList();
		cout << endl;
		end = stack.end();
	}
	end = stack.end();
	if (end != nullptr && end->symbols[0] == '(') {
		stack.pop_back();
		end = stack.end();
	}
	if (end != nullptr) {
		int prior = findPriority(end->symbols[0]);
		if (prior == 3) {
			outputList.push_back(end);
			stack.pop_back();
			end = stack.end();
		}
	}
}

void LogicComponent::startConversion() {
	convertToONP(inputList.begin(), false, false, nullptr);
}

Token* LogicComponent::convertToONP(Token* token, bool callFromConvert,
	bool isInsideFunction, short int* counter_operands = nullptr) {
	short int function_count = 0;
	Token* functionPointer = nullptr;
	short int functionArgs = 0;

	while (token != nullptr) {
		if (token->symbols[0] != '\0' && isNumber(token->symbols)) {
			outputList.push_back(token);
		}
		else {
			switch (token->symbols[0]) {
			case '+': case '-':
			case '*': case '/':
			case '~':
				replaceOperations(token); break;
				// functions
			case '?': 
			case '<': case '>':
			{
				functionPointer = new Token(*token);
				functionArgs = 0;
				break;
			}
			case '(':
			{
				token = convertToONP(token->next, true,
					functionPointer != nullptr, &functionArgs);
				if (functionPointer) {
					functionPointer->arguments = functionArgs;
					stack.push_back(functionPointer);
					delete functionPointer;
				}
				functionPointer = nullptr;
				if (token->symbols[0] == ')') {
					pullOutOperator(stack.end());
				}
				break;
			}
			case ')': {

				// Если стек закончился до того, как был встречен токен открывающая скобка, то в выражении пропущена скобка.
				// Проверить условия (написать код) !!!
				auto* end = stack.end();
				pullOutOperator(stack.end());
				
				if (isInsideFunction && counter_operands) *counter_operands += 1;
				if (callFromConvert) return token;
				break;
			}

			case ',':
			{
				if (isInsideFunction && counter_operands) *counter_operands += 1;
				//Если стек закончился до того, как был встречен токен открывающая скобка, 
				//то в выражении пропущен разделитель аргументов функции (запятая), либо пропущена открывающая скобка.
				//Проверить это условие (написать код) !!!
				pullOutOperator(stack.end());
				break;
			}
			case '.': {
				cout << "\n\n.\n";
				cout << "outputList:\n";
				outputList.drawList();
				cout << "\nstack:\n";
				stack.drawList();
				doDalculations(); break;
			}
			default:
				break;
			}
			cout << "stack: ";
			stack.drawList(); cout << endl;
			cout << "outputlist: ";
			outputList.drawList(); cout << endl;
		}
		token = token->next;
	}

	cout << "After while stack: " << endl;
	stack.drawList();

	pullOutOperator(stack.end());
	cout << endl;
	cout << "After while ouputlist: " << endl;
	outputList.drawList();
	cout << endl;
	return nullptr;
}


void LogicComponent::doDalculations() {
	Token* token = outputList.begin();
	while (token != nullptr) {
		if (token->symbols[0] != '\0' && isNumber(token->symbols)) {
			stack.push_back(token);
			token = token->next;
			outputList.deleteFirst();
		}
		else {
			switch (token->symbols[0]) {
			case '+': case '-':
			case '*': case '/':
			{
				Token* first = new Token(*stack.end());
				stack.pop_back();
				Token* second = new Token(*stack.end());
				stack.pop_back();
				doOperation(token->symbols[0], second, first); 
				token = token->next;
				outputList.deleteFirst();
				break;
			}
				// functions
			case '~': case '?':
			case '<': case '>':
			{
				doFunction(token);
				token = token->next;
				outputList.deleteFirst();
				break;
			}
			default:break;
			}
		}
	}
}

void LogicComponent::doOperation(const char& s, Token* first, Token* second) {
	if (first != nullptr && second != nullptr) {
		cout << "doOperation(): ";
		cout << s << " ";
		stack.drawList();
		cout << endl;
		int firstVal = atoi(first->symbols);
		int secondVal = atoi(second->symbols);
		Token* result = nullptr;
		int res;
		short int length;
		switch (s) {
		case '+': {
			res = firstVal + secondVal;
			break;
		}
		case '-': {
			res = firstVal - secondVal;
			break;
		}
		case '*': {
			res = firstVal * secondVal;
			break;
		}
		case '/': {
			if (secondVal == 0) {
				cout << "ERROR"; 
				stack.pop_back();
				break;
			}
			else {
				res = firstVal / secondVal;
			}
			break;
		}
		}

		length = countDigits(res) + 1;
		char* buff = new char[length];
		sprintf_s(buff, length, "%d", res);
		//getCharNumber(buff, length, res);
		
		result = new Token(buff, length);
		stack.push_back(result);

		if (buff != nullptr) delete[] buff;
		if (result != nullptr) delete result;
		if (first != nullptr) delete first;
		if (second != nullptr) delete second;
	}

}


void LogicComponent::doFunction(Token* token) {
	cout << "doFunction (): ";
	token->showToken();
	stack.drawList();
	cout << endl;

	switch (token->symbols[0]) {
	case '~': {
		char zero[] = "0";
		Token* tmp = new Token(zero, strlen(zero) + 1);
		Token* first = new Token(*stack.end());
		stack.pop_back();
		doOperation('-', tmp, first);
		break;
	}

	case '?': ifFunc(); break;
	case '<': minMaxFunc(token); break;
	case '>': minMaxFunc(token); break;
	default: break;
	}
}

void LogicComponent::ifFunc() {
	Token* c = new Token(*stack.end());
	stack.pop_back();
	Token* b = new Token(*stack.end());
	stack.pop_back();
	Token* a = new Token(*stack.end());
	stack.pop_back();
	
	int aVal = atoi(a->symbols);
	int bVal = atoi(b->symbols);
	int cVal = atoi(c->symbols);
	aVal > 0 ? stack.push_back(new Token(*b)) : stack.push_back(new Token(*c));
	
	delete a, b, c;

}

void LogicComponent::minMaxFunc(Token* token) {
	int* tokenValues = calcSortedArr(token);
	short int arguments = token->arguments;

	switch (token->symbols[0])
	{
	case '>':
	{
		//getCharNumber(buff, length, tokenValues[length - 1]);
		char* buff;
		short int len = countDigits(tokenValues[arguments - 1]) + 1;
		buff = new char[len];
		sprintf_s(buff, len, "%d", tokenValues[arguments - 1]);
		//deleteStackTokens(token);
		stack.push_back(new Token(buff, len));
		break;
	}
	case '<': {
		//getCharNumber(buff, length, tokenValues[0]);
		char* buff;
		short int len = countDigits(tokenValues[0]) + 1;
		buff = new char[len];
		sprintf_s(buff, len, "%d", tokenValues[0]);
		//deleteStackTokens(token);
		stack.push_back(new Token(buff, len));
		break;
	}
	default:
		break;
	}
	delete[] tokenValues;
}

void LogicComponent::deleteStackTokens(Token* token) {
	short int length = token->arguments;
	for (short int i = 0; i < length; i++) {
		stack.pop_back();
	}
}

int* LogicComponent::calcSortedArr(Token* token) {
	short int arguments = token->arguments;
	int* tokenValues = new int[arguments];
	for (short int i = 0; i < arguments; i++) {
		if (stack.end() != nullptr) {
			tokenValues[i] = atoi(stack.end()->symbols);
			stack.pop_back();
		}
	}
	insertionSort(tokenValues, arguments);
	for (int i = 0; i < arguments; i++)
		cout << tokenValues[i] << " ";
	cout << endl;
	return tokenValues;
}


//Token* LogicComponent::convertToONP(Token* token, bool callFromConvert,
//	bool isInsideFunction, short int* counter_operands = nullptr) {
//	short int function_count = 0;
//	Token* functionPointer = nullptr;
//	short int functionArgs = 0;
//
//	while (token != nullptr) {
//		if (token->symbols[0] != '\0' && isNumber(token->symbols)) {
//			outputList.push_back(token);
//		}
//		else {
//			switch (token->symbols[0]) {
//			case '+': case '-':
//			case '*': case '/':
//				replaceOperations(token); break;
//				// functions
//			case '?': case '~':
//			case '<': case '>':
//			{
//				functionPointer = new Token(*token);
//				functionArgs = 0;
//				break;
//			}
//			case '(':
//			{
//				token = convertToONP(token->next, true,
//					functionPointer != nullptr, &functionArgs);
//				if (functionPointer) {
//					functionPointer->arguments = functionArgs;
//					stack.push_back(functionPointer);
//					delete functionPointer;
//				}
//				functionPointer = nullptr;
//				break;
//			}
//			case ',':
//			{
//				if (isInsideFunction && counter_operands) *counter_operands += 1;
//				//Если стек закончился до того, как был встречен токен открывающая скобка, 
//				//то в выражении пропущен разделитель аргументов функции (запятая), либо пропущена открывающая скобка.
//				//Проверить это условие (написать код) !!!
//				auto* end = stack.end();
//				pullOutOperator(end);
//				break;
//			}
//			case ')': {
//
//				// Если стек закончился до того, как был встречен токен открывающая скобка, то в выражении пропущена скобка.
//				// Проверить условия (написать код) !!!
//				auto* end = stack.end();
//				pullOutOperator(end);
//				end = stack.end();
//				if (end != nullptr && end->symbols[0] == '(') {
//					stack.pop_back();
//					end = stack.end();
//				}
//				if (end != nullptr) {
//					int prior = findPriority(end->symbols[0]);
//					if (prior == 3) {
//						outputList.push_back(end);
//						stack.pop_back();
//						end = stack.end();
//					}
//				}
//				if (isInsideFunction && counter_operands) *counter_operands += 1;
//				if (callFromConvert) return token;
//				break;
//			}
//			default:
//				break;
//			}
//			cout << "stack: ";
//			stack.drawList(); cout << endl;
//			cout << "outputlist: ";
//			outputList.drawList(); cout << endl;
//		}
//		token = token->next;
//	}
//
//	cout << "After while stack: " << endl;
//	stack.drawList();
//
//	auto* end = stack.end();
//	pullOutOperator(end);
//	cout << endl;
//	cout << "After while ouputlist: " << endl;
//	outputList.drawList();
//	cout << endl;
//	return nullptr;
//}









//short int prior = findPriority(token->symbols[0]);
//if (token->symbols[0] != '\0' && isNumber(token->symbols)) {
//	outputList.push_back(token);
//}
//else if (prior == 1 || prior == 2) {
//	replaceOperations(token);
//}
//else if (prior == 3) {
//	functionPointer = new Token(*token);
//	functionArgs = 0;
//}
//else if (prior == 4 && token->symbols[0] == '(') {
//	token = convertToONP(token->next, true,
//		functionPointer != nullptr, &functionArgs);
//	if (functionPointer) {
//		functionPointer->arguments = functionArgs;
//		stack.push_back(functionPointer);
//		delete functionPointer;
//	}
//	functionPointer = nullptr;
//}
//else if (prior == 4 && token->symbols[0] == ')') {
//	auto* end = stack.end();
//	pullOutOperator(end);
//	end = stack.end();
//	if (end != nullptr && end->symbols[0] == '(') {
//		stack.pop_back();
//		end = stack.end();
//	}
//	if (end != nullptr) {
//		int prior = findPriority(end->symbols[0]);
//		if (prior == 3) {
//			outputList.push_back(end);
//			stack.pop_back();
//			end = stack.end();
//		}
//	}
//	if (isInsideFunction && counter_operands) *counter_operands += 1;
//	if (callFromConvert) return token;
//	break;
//}
//else if (token->symbols[0] == ',' && isInsideFunction && counter_operands) {
//	if (isInsideFunction && counter_operands) *counter_operands += 1;
//	//Если стек закончился до того, как был встречен токен открывающая скобка, 
//	//то в выражении пропущен разделитель аргументов функции (запятая), либо пропущена открывающая скобка.
//	//Проверить это условие (написать код) !!!
//	pullOutOperator(stack.end());
//}
//else {
//
//}
//cout << "stack: ";
//stack.drawList(); cout << endl;
//cout << "outputlist: ";
//outputList.drawList(); cout << endl;
//token = token->next;
