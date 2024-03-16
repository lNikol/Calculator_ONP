#pragma once
struct Token {
	char* symbols;
	short int counter = 0;
	short int index = -1;
	size_t size = 0;
	Token* next;

	Token(const Token& t);
	Token(char* symbols, const int& s);
	void showToken();
	~Token();
};