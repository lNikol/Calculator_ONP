#include "Token.h"
#include <iostream>

using namespace std;

Token::Token(const Token& t) {
	size = t.size;
	arguments = t.arguments;
	index = t.index;
	symbols = new char[size];
	for (size_t i = 0; i < size; i++) {
		symbols[i] = t.symbols[i];
	}
	next = nullptr;
	prev = nullptr;
}

Token::Token(char* symbs, const int& s) {
	next = nullptr;
	prev = nullptr;
	symbols = new char[s];
	for (int i = 0; i < s; i++) {
		symbols[i] = symbs[i];
		size++;
	}
}

void Token::showToken() {
	for (size_t i = 0; i < size; i++) {
		switch (symbols[0]) {
		case '?': {
			cout << "IF";
			++i;
			break;
		}
		case '>': {
			cout << "MAX" << arguments;
			++i;
			break;
		}
		case '<': {
			cout << "MIN" << arguments;
			++i;
			break;
		}
		case '~': {
			cout << "N";
			i++;
			break;
		}
		default: cout << symbols[i]; break;
		}
	}
}

Token::~Token() {
	//cout << "~Token(size:"<<size<<"): ";
	if (symbols != nullptr) {
		//cout << symbols[0] << "_" << arguments;
		delete[] symbols;
	}
	size = 0;
	//cout << endl;
}
