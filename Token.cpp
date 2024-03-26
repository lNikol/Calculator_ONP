#include "Token.h"
#include <iostream>

using namespace std;

Token::Token(const Token& t) {
	size = t.size;
	arguments = t.arguments;
	index = t.index;
	symbols = new char[size];
	for (size_t i = 0; i < size; ++i) {
		symbols[i] = t.symbols[i];
	}
	next = nullptr;
	prev = nullptr;
}


Token::Token(char* symbs, const int& s) {
	symbols = new char[s];
	for (int i = 0; i < s; ++i) {
		symbols[i] = symbs[i];
		++size;
	}
	next = nullptr;
	prev = nullptr;
}

void Token::showToken() {
	for (size_t i = 0; i < size - 1; ++i) {
		switch (symbols[0]) {
		case '?': {
			printf("IF");
			++i;
			break;
		}
		case '>': {
			printf("MAX%d", arguments);
			++i;
			break;
		}
		case '<': {
			printf("MIN%d", arguments);
			++i;
			break;
		}
		case 'N': {
			printf("N");
			++i;
			break;
		}
		default: {
			printf("%c", symbols[i]);
			break;
		}
		}
	}
	printf(" ");
}

Token::~Token() {
	if (symbols != nullptr) {
		delete[] symbols;
	}
	size = 0;
	arguments = 0;
	index = 0;
}
Token& Token::operator=(Token&& t) {
	size = t.size;
	arguments = t.arguments;
	index = t.index;
	symbols = new char[size];
	for (size_t i = 0; i < size; ++i) {
		symbols[i] = t.symbols[i];
	}
	next = nullptr;
	prev = nullptr;
	t.~Token();
	return *this;
}