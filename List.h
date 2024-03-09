#pragma once
#include "Token.h"
class List {
	Token* first = nullptr;
	size_t size = 0;
public:
	List();
	void begin();
	void end();
	size_t GetSize();
	void push_back(Token* t);
	void pop_back();
	void drawList();
	~List();
};