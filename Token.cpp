#include "Token.h"
#include <iostream>
using namespace std;

Token::Token(const Token& t) {
	size = t.size;
	counter = t.counter;
	symbols = new char[size];
	symbols = t.symbols;
	next = nullptr;
}
Token::Token(char* symbs, const int& s) {
	symbols = new char[1];
	size++;
	if (strcmp(symbs, "MIN") == 0) symbols[0] = '<';
	else if (strcmp(symbs, "MAX") == 0) symbols[0] = '>';
	else if (strcmp(symbs, "IF") == 0) symbols[0] = '?';
	else if (strcmp(symbs, "N") == 0) symbols[0] = '~';
	else {
		if (symbols != nullptr) { delete[] symbols; size--;	}
		symbols = new char[s];
		for (int i = 0; i < s; i++) {
			symbols[i] = symbs[i];
			size++;
		}
	}

}
void Token::showToken() {
	for (size_t i = 0; i < size; i++) {
		cout << symbols[i];
	}
}

Token::~Token() {
	
	if (symbols != nullptr) {
		cout << symbols[0];
		delete[] symbols;
	}
}
