#pragma once
#include "Token.h"
class List {
	Token* first = nullptr;
	size_t size = 0;
	short int counter = 0; // mozna usunac, bo size robi w operationList to samo
public:
	List();
	Token* begin();
	Token* end();
	size_t GetSize();
	void increaseByIndex(short int& index);
	short int getCounter();
	void setCounter(const short int& s);
	void push_back(Token* t);
	void pop_back();
	void drawList();
	~List();
};