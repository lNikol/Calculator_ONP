#include "LogicComponent.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;


short int countDigits(int number) {
	if (number == 0) return 1;
	short int count = number > 0 ? 0 : 1;
	while (number != 0) {
		number /= 10;
		count++;
	}
	return count;
}

void insertionSort(int arr[], const short int& n)
{
	int i, key, j;
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
		char_op[i] = -51; // default undefined value for char
	}
	char_op_count = 0;
	delete[] symbols;
	return temp;
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
	short int tokenPrior = findPriority(token->symbols[0]);
	short int stackPrior = -1;
	if (tmp != nullptr) {
		stackPrior = findPriority(tmp->symbols[0]);
	}

	while (tmp != nullptr && stackPrior != -1 && stackPrior <= 3 && stackPrior >= tokenPrior) {
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
		outputList.push_back(end);
		stack.pop_back();
		end = stack.end();
	}
	if (end != nullptr && end->symbols[0] == '(') {
		stack.pop_back();
		end = stack.end();
	}
	if (end != nullptr) {
		int prior = findPriority(end->symbols[0]);
		if (prior == 3 && end->symbols[0] != '~') {
			outputList.push_back(end);
			stack.pop_back();
			end = stack.end();
		}
	}
}

void LogicComponent::startConversion(char* input, const int& EQUATION_LENGTH) {
	isERROR = false;
	const short int CHAR_OP_LENGTH = 20; // 19 dlugosc int + 1
	char char_op[CHAR_OP_LENGTH];
	int char_op_count = 0;
	int c = 0;
	convertToONP(nullptr, false, false, nullptr, input, char_op, char_op_count, c);
	//delete[] input;
	stack.~List();
	outputList.~List();
}


Token* LogicComponent::convertToONP(Token* token, bool callFromConvert,
	bool isInsideFunction, short int* counter_operands,
	char* input, char* char_op, int& char_op_count, int& c) {
	Token* functionPointer = nullptr;
	short int functionArgs = 0;
	while (input[c] != '\0' && !isERROR) {
		if (input[c] != ' ') {
			if (input[c] == '.') {
				pullOutOperator(stack.end());
				outputList.drawList();
				doCalculations();
				if (!isERROR) stack.drawReversedList();
				else return nullptr;
			}
			else {
				char_op[char_op_count++] = input[c];
			}

		}

		else if (input[c] == '\n') {
		}
		else {
			char_op[char_op_count++] = '\0';
			Token* tm = (token == nullptr) ? createToken(char_op, char_op_count) : new Token(*token);

			if (tm->symbols[0] != '\0' && isNumber(tm->symbols)) {
				outputList.push_back(tm);
				char_op_count = 0;
			}
			else {
				char_op_count = 0;
				switch (tm->symbols[0]) {
				case '+': case '-':
				case '*': case '/':
				case '~':
					replaceOperations(tm);
					break;
					// functions
				case '?': case '<':
				case '>':
					functionPointer = new Token(*tm);
					functionArgs = 0;
					break;
				case '(':
				{
					stack.push_back(tm);
					tm = convertToONP(nullptr, true,
						functionPointer != nullptr, &functionArgs, input,
						char_op, char_op_count, ++c);

					if (!isERROR) {
						if (functionPointer) {
							functionPointer->arguments = functionArgs;
							stack.push_back(functionPointer);
							delete functionPointer;
						}
						functionPointer = nullptr;
					}
					else return nullptr;
					break;
				}
				case ',':
				{
					if (isInsideFunction && counter_operands) {
						auto* end = stack.end();
						while (end != nullptr && end->symbols[0] != '(') {
							outputList.push_back(end);
							stack.pop_back();
							end = stack.end();
						}
						*counter_operands += 1;
					}
					break;
				}
				case ')': {
					pullOutOperator(stack.end());
					if (isInsideFunction && counter_operands) *counter_operands += 1;
					if (callFromConvert) return tm;
					break;
				}


				default:break;
				}
			}
			if (tm != nullptr) delete tm;
			// sprawdzic memory leak i jak dziala bez warunku na zamkniety nawias
		}
		c++;
	}
	return nullptr;
}

void LogicComponent::doCalculations() {
	Token* token = outputList.begin();
	while (token != nullptr && !isERROR) {
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
				token->showToken();
				stack.drawReversedList();
				Token* first = new Token(*stack.end());
				stack.pop_back();
				Token* second = new Token(*stack.end());
				stack.pop_back();
				doOperation(token->symbols[0], second, first);
				if (!isERROR) {
					token = token->next;
					outputList.deleteFirst();
				}
				else return;

				break;
			}
			// functions
			case '~': case '?':
			case '<': case '>':
			{
				token->showToken();
				stack.drawReversedList();
				doFunction(token);
				if (!isERROR) {
					token = token->next;
					outputList.deleteFirst();
				}
				else return;
				break;
			}
			default:break;
			}
		}
	}
}

void LogicComponent::doOperation(const char& s, Token* first, Token* second) {
	if (first != nullptr && second != nullptr) {
		int firstVal = atoi(first->symbols);
		int secondVal = atoi(second->symbols);
		int res = 0;
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
				cout << "ERROR\n";
				stack.~List();
				outputList.~List();
				inputList.~List();
				isERROR = true;
				return;
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

		stack.push_back(new Token(buff, length));

		if (buff != nullptr) delete[] buff;
		if (first != nullptr) delete first;
		if (second != nullptr) delete second;
	}

}

void LogicComponent::doFunction(Token* token) {
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
	Token* res;
	if (atoi(a->symbols) > 0) {
		res = new Token(*b);
		stack.push_back(res);
		delete res;
	}  
	else {
		res = new Token(*c);
		stack.push_back(res);
		delete res;
	}

	delete a, b, c;

}

void LogicComponent::minMaxFunc(Token* token) {
	int* tokenValues = calcSortedArr(token);
	short int arguments = token->arguments;

	switch (token->symbols[0])
	{
	case '>':
	{
		char* buff;
		short int len = countDigits(tokenValues[arguments - 1]) + 1;
		buff = new char[len];
		sprintf_s(buff, len, "%d", tokenValues[arguments - 1]);
		stack.push_back(new Token(buff, len));
		delete[] buff;
		break;
	}
	case '<': {
		char* buff;
		short int len = countDigits(tokenValues[0]) + 1;
		buff = new char[len];
		sprintf_s(buff, len, "%d", tokenValues[0]);
		stack.push_back(new Token(buff, len));
		delete[] buff;
		break;
	}
	default:
		break;
	}
	delete[] tokenValues;
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
	return tokenValues;
}