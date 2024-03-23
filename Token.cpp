﻿#include "Token.h"
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
		case '~': {
			printf("N");
			i++;
			break;
		}
		default: printf("%c", symbols[i]); break;
		}
	}
	printf(" ");

}

Token::~Token() {
	//cout << "~Token(size:"<<size<<"): ";
	if (symbols != nullptr) {
		//cout << symbols[0] << "_" << arguments;
		delete[] symbols;
	}
	size = 0;
}