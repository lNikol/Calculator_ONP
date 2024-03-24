#pragma once
struct Token {
	char* symbols;
	int arguments = 0; // amount of operands
	int index = 0;
	size_t size = 0;
	Token* next = nullptr;
	Token* prev = nullptr;
	Token& operator=(Token&& t);
	Token(const Token& t);
	Token(char* symbs, const int& s);
	void showToken();
	~Token();
};