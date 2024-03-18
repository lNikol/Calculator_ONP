#pragma once
#include "Token.h"
#include "List.h"

class LogicComponent {
private:
	List stack;
	List outputList;
	List inputList;
	bool isERROR = false;

public:
	bool isNumber(const char* str);
	Token* createToken(char* char_op, int& char_op_count);

	void readInput(const char* input);
	Token* convertToONP(Token* token, bool callFromConvert, bool isInsideFunction, short int* counter_operands);
	void startConversion();

	short int findPriority(const char& s);
	void replaceOperations(Token* token);
	void pullOutOperator(Token* end);
	void doDalculations();
	void doOperation(const char& s, Token* first, Token* second);
	void doFunction(Token* token);
	void ifFunc();
	void minMaxFunc(Token* token);
	void deleteStackTokens(Token* token);
	int* calcSortedArr(Token* token);
};