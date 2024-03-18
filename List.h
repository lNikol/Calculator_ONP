#pragma once
#include "Token.h"
class List {
	Token* first = nullptr;
	size_t size = 0;
public:
	List();
	Token* begin();
	Token* end();
	size_t GetSize();
	void push_back(Token* t);
	void deleteFirst();
	void pop_back();
	void drawList();
	~List();
};