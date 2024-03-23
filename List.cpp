#include "List.h"
#include <iostream>
using namespace std;

List::List() {

}

void List::push_back(Token* t) {
	if (first == nullptr) {
		first = new Token(*t);
		first->next = nullptr;
		first->prev = nullptr;
	}
	else if (t == nullptr) return;
	else {
		Token* tmp = first;
		while (tmp->next != nullptr) {
			tmp->next->prev = tmp;
			tmp = tmp->next;
		}
		tmp->next = new Token(*t);
		tmp->next->prev = tmp;
	}
	size++;
}

void List::pop_back() {
	if (first == nullptr) {
		return;
	}
	Token* tmp = first;
	while (tmp->next != nullptr && tmp->next->next != nullptr) {
		tmp = tmp->next;
	}
	//cout << "pop_back: " << tmp << " next: " << tmp->next << endl;
	if (tmp->next != nullptr)
	{
		delete tmp->next;
		tmp->next = nullptr;
	}
	else if (tmp == first) {
		delete first;
		first = nullptr;
	}
	size--;
}

void List::drawList() {
	if (first == nullptr) return;
	Token* tmp = first;
	tmp->showToken();
	while (tmp->next != nullptr) {
		tmp = tmp->next;
		tmp->showToken();
	}
	cout << endl;
}

void List::drawReversedList() {
	Token* tmp = end();
	if (tmp == nullptr) return;
	if (tmp == first) {
		tmp->showToken();
	}
	//tmp->showToken();
	while (tmp->prev != nullptr) {
		//printf(" ");
		tmp->showToken();
		tmp = tmp->prev;
	}
	cout << endl;
}

void List::deleteFirst() {
	Token* tmp = first;
	if (tmp == nullptr) return;
	if (first->next != nullptr) first = first->next;
	else if (tmp == first) {
		first = nullptr;
		tmp->prev = nullptr;
		delete tmp;
	}
	else delete tmp;
}


Token* List::begin() {
	return first;
}

Token* List::end() {
	if (first == nullptr) return nullptr;
	Token* tmp = first;
	while (tmp->next != nullptr) {
		tmp = tmp->next;
	}
	return tmp;
}

List::~List() {
	Token* cur = first;
	while (cur != nullptr) {
		Token* next = cur->next;
		delete cur;
		cur = next;
	}
	first = nullptr;
	size = 0;
}