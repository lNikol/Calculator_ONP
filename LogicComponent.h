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
	static bool isNumber(const char* str);
	Token* createToken(char* char_op, int& char_op_count);

	Token* convertToONP(Token* token, bool callFromConvert,
		bool isInsideFunction, short int* counter_operands,
		char* input, char* char_op, int& char_op_count, int& c);
	void startConversion(char* input, const int& EQUATION_LENGTH);

	static short int findPriority(const char& s);
	void replaceOperations(Token* token);
	void pullOutOperator(Token* end);
	void doCalculations();
	void doOperation(const char& s, Token* first, Token* second);
	void doFunction(Token* token);
	void ifFunc();
	void minMaxFunc(Token* token);
	void deleteStackTokens(Token* token);
	int* calcSortedArr(Token* token);
};