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
					if (prior == 1 || prior == 2) tm->arguments = 2;
					if (tm->symbols[0] == '~') tm->arguments = 1;
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

void LogicComponent::startConversion() {
	convertToONP(inputList.begin(), false, false, nullptr);
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
