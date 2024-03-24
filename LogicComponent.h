#pragma once
#include "Token.h"
#include "List.h"

class LogicComponent {
private:
	List stack;
	List outputList;
	bool isERROR = false;
	static const short int CHAR_OP_LENGTH = 20; // 19 dlugosc int + 1


public:
	static bool isNumber(const char* str);
	Token* createToken(char* char_op, int& char_op_count);

	Token* convertToONP(bool callFromConvert,
		bool isInsideFunction, short int* counter_operands,
		char* input, char* char_op, int& char_op_count, int& c);
	void startConversion(char* input);

	static short int findPriority(const char& s);
	void replaceOperations(Token* token);
	void pullOutOperator(Token* end, bool isParenth);
	void doCalculations();
	void doOperation(const char& s, Token* first, Token* second);
	void doFunction(Token* token);
	void ifFunc();
	void minMaxFunc(Token* token);
	void deleteStackTokens(Token* token);
	int* calcSortedArr(Token* token);
};