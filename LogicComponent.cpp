#include "LogicComponent.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

short int countDigits(int number) {
	if (number == 0) return 1;
	// sprawdzenie czy liczba ujemna, jesli ujemna to dodaje 1 i traktuje to jako minus
	short int count = number > 0 ? 0 : 1;
	while (number != 0) {
		number /= 10;
		++count;
	}
	return count;
}

bool isNumber(const char* str) {
	for (int i = 0; str[i] != '\0'; ++i) {
		if (!isdigit(str[i])) {
			return false;
		}
	}
	return true;
}

short int LogicComponent::findPriority(const char& s) {
	switch (s) {
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	case '?': case '<': case 'N': case '>': return 3; // negacja right associative
	case'(': case ')': return 4;
	default: return -1;
	}
}

void LogicComponent::setNewTempToken(char*& tok) {
	if (tok != nullptr) {
		delete[] tok;
	}
	tok = new char[CHAR_OP_LENGTH];
	scanf_s("%19s", tok, CHAR_OP_LENGTH);
}

Token* LogicComponent::createToken(char* char_op) {
	short int size = 2;
	short int char_op_count = 0;
	char* symbols = new char[size];

	if (char_op[1] == 'I') {
		symbols[0] = '<';
		symbols[1] = '\0';
	}
	else if (char_op[1] == 'A') {
		symbols[0] = '>';
		symbols[1] = '\0';
	}
	else if (char_op[1] == 'F') {
		symbols[0] = '?';
		symbols[1] = '\0';
	}
	else if (char_op[0] == 'N') {
		symbols[0] = 'N';
		symbols[1] = '\0';
	}
	else {
		delete[] symbols;
		while (char_op[char_op_count] != '\0' && char_op[char_op_count] > 0) {
			char_op_count++;
		}
		size = char_op_count + 1;
		symbols = new char[size];

		for (int i = 0; i < size - 1; ++i) {
			symbols[i] = char_op[i];
		}
		symbols[size - 1] = '\0';
	}

	Token* temp = new Token(symbols, size);
	delete[] symbols;
	return temp;
}

void LogicComponent::startConversion() {
	isERROR = false;
	char* char_op = new char[CHAR_OP_LENGTH];
	// pobieranie pierwszego tokena
	scanf_s("%19s", char_op, CHAR_OP_LENGTH);
	printf("\n");
	convertToONP(false, false, nullptr, char_op);
	if (char_op != nullptr) {
		delete[] char_op;
	}
	stack.~List();
	outputList.~List();
}

Token* LogicComponent::convertToONP(bool callFromConvert, bool isInsideFunction,
	short int* counter_operands, char*& char_op) {
	Token* functionPointer = nullptr;
	short int functionArgs = 0;
	while (char_op[0] != '\0' && !isERROR) {
		if (char_op[0] == '.') {
			pullOutOperator(stack.end(), true);
			outputList.drawList();
			doCalculations();
			char_op[0] = '\0';
			if (!isERROR) {
				stack.drawReversedList();
			}
			else {
				return nullptr;
			}
		}
		else if (char_op[0] == '\n') {
		}
		else {
			Token* tm = createToken(char_op);
			setNewTempToken(char_op);
			if (tm->symbols[0] != '\0' && isNumber(tm->symbols)) {
				outputList.push_back(tm);
			}
			else {
				switch (tm->symbols[0]) {
				case '+': case '-':
				case '*': case '/':
				case 'N':
				{
					replaceOperations(tm);
					break;
				}

				// functions
				case '?': case '<':
				case '>': {
					functionPointer = new Token(*tm);
					functionArgs = 0;
					break;
				}
				case '(': {
					stack.push_back(tm);
					convertToONP(true, functionPointer != nullptr, &functionArgs, char_op);

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
				case ',': {
					if (isInsideFunction && counter_operands) {
						pullOutOperator(stack.end(), false);
						*counter_operands += 1;
					}
					break;
				}
				case ')': {
					if (isInsideFunction && counter_operands) {
						*counter_operands += 1;
					}
					pullOutOperator(stack.end(), true);
					if (callFromConvert) {
						return tm;
					}
					break;
				}

				default:break;
				}
			}
			if (tm != nullptr) {
				delete tm;
			}
		}
	}
	return nullptr;
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
			if (token->symbols[0] != 'N') {
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
		else break;
	}
	stack.push_back(token);
}

void LogicComponent::pullOutOperator(Token* end, bool isParenth) {
	while (end != nullptr && end->symbols[0] != '(') {
		outputList.push_back(end);
		stack.pop_back();
		end = stack.end();
	}
	if (isParenth) {
		if (end != nullptr && end->symbols[0] == '(') {
			stack.pop_back();
			end = stack.end();
		}
		if (end != nullptr) {
			int prior = findPriority(end->symbols[0]);
			if (prior == 3 && end->symbols[0] != 'N') {
				outputList.push_back(end);
				stack.pop_back();
				end = stack.end();
			}
		}
	}
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
			case 'N': case '?':
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
				printf("ERROR\n");
				stack.~List();
				outputList.~List();
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
	case 'N': {
		char zero[] = "0";
		Token* tmp = new Token(zero, strlen(zero) + 1);
		Token* first = new Token(*stack.end());
		stack.pop_back();
		doOperation('-', tmp, first);
		break;
	}
	case '?': {
		ifFunc();
		break;
	}
	case '<': {
		minMaxFunc(token);
		break;
	}
	case '>': {
		minMaxFunc(token);
		break;
	}
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
	}
	else {
		res = new Token(*c);
	}
	stack.push_back(res);
	delete res;
	delete a, b, c;
}

void LogicComponent::minMaxFunc(Token* token) {
	int* tokenValues = calcSortedArr(token);
	short int arguments = token->arguments;
	int max = tokenValues[0];
	int min = tokenValues[0];
	for (short int i = 0; i < arguments; ++i) {
		if (tokenValues[i] > max) {
			max = tokenValues[i];
		}
		if (tokenValues[i] < min) {
			min = tokenValues[i];
		}
	}
	switch (token->symbols[0]) {
	case '>': {
		char* buff;
		short int len = countDigits(max) + 1;
		buff = new char[len];
		// przepisuje maksymalna liczbe do buff
		sprintf_s(buff, len, "%d", max);
		stack.push_back(new Token(buff, len));
		break;
	}
	case '<': {
		short int len = countDigits(min) + 1;
		char* buff;
		buff = new char[len];
		// przepisuje minimalna liczbe do buff
		sprintf_s(buff, len, "%d", min);
		stack.push_back(new Token(buff, len));
		delete[] buff;
		break;
	}
	default: break;
	}
	delete[] tokenValues;
}

int* LogicComponent::calcSortedArr(Token* token) {
	short int arguments = token->arguments;
	int* tokenValues = new int[arguments];
	for (short int i = 0; i < arguments; ++i) {
		Token* end = stack.end();
		if (end != nullptr) {
			tokenValues[i] = atoi(end->symbols);
			stack.pop_back();
		}
	}
	return tokenValues;
}