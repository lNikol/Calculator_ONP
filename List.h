#pragma once
#include "Token.h"
class List {
	Token* first = nullptr;
	size_t size = 0;
public:
	List();
	Token* begin();
	Token* end();
	void push_back(Token* t);
	void deleteFirst();
	void pop_back();
	void drawList() const;
	void drawReversedList();
	~List();
};