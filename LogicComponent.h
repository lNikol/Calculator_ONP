#pragma once
#include "Token.h"
#include "List.h"

class LogicComponent {
private:
	List stack;
	List outputList;
	List inputList;
	Token* firstToken;

public:
	bool isNumber(const char* str);
	Token* createToken(char* char_op, int& char_op_count);

	void readInput(const char* input);
	void convertToONP(Token* token, short int* counter_operands);
	void startConversion();

	short int findPriority(const char& s);
	void replaceOperations(Token* token);
	void pullOutOperator(Token* end);
};