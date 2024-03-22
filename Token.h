#pragma once
struct Token {
	char* symbols;
	short int arguments = 0; // amount of operands
	short int index = 0;
	size_t size = 0;
	Token* next;
	Token* prev;

	Token(const Token& t);
	Token(char* symbs, const int& s);
	void showToken();
	~Token();
};