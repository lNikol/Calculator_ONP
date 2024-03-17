#include "Token.h"
#include <iostream>
using namespace std;

Token::Token(const Token& t) {
	size = t.size;
	counter = t.counter;
	index = t.index;
	symbols = new char[size];
	for (size_t i = 0; i < size; i++) {
		symbols[i] = t.symbols[i];
	}
	next = nullptr;
}

Token::Token(char* symbs, const int& s) {
	next = nullptr;
	symbols = new char[s];
	for (int i = 0; i < s; i++) {
		symbols[i] = symbs[i];
		size++;
	}

}
void Token::showToken() {
	cout << "showToken(): ";
	for (size_t i = 0; i < size; i++) {
		cout << symbols[i];
	}
	cout << endl;
}

Token::~Token() {
	cout << "~Token(size:"<<size<<"): ";
	if (symbols != nullptr) {
		cout << symbols[0] << "_" << counter;
		delete[] symbols;
	}
	size = 0;
	cout << endl;
}
