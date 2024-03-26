#include "List.h"
#include <iostream>
using namespace std;

List::List() {

}

void List::push_back(Token* t) {
	if (t == nullptr) {
		return;
	}

	if (first == nullptr) {
		first = new Token(*t);
		last = first;
		first->next = nullptr;
		first->prev = nullptr;
		++size;
		return;
	}

	last->next = new Token(*t);
	last->next->prev = last;
	last = last->next;
	++size;
}

void List::pop_back() {
	if (first == nullptr) {
		return;
	}

	--size;
	// usuwam pierwszy (on jest ostatnim) element z listy
	if (first->next == nullptr) {
		delete first;
		first = nullptr;
		last = nullptr;
		return;
	}

	Token* tmp = last->prev;
	delete last;
	last = tmp;
	if (last != nullptr) {
		last->next = nullptr;
	}
}

void List::drawList() const {
	if (first == nullptr) {
		return;
	}
	Token* tmp = first;
	tmp->showToken();
	printf(" ");
	while (tmp->next != nullptr) {
		tmp = tmp->next;
		tmp->showToken();
		printf(" ");
	}
	printf("\n");
}

void List::drawReversedList() {
	Token* tmp = end();
	if (tmp == nullptr) {
		return;
	}
	tmp->showToken();
	while (tmp->prev != nullptr) {
		tmp = tmp->prev;
		tmp->showToken();
	}
	printf("\n");
}

void List::deleteFirst() {
	if (first == nullptr) {
		return;
	}

	--size;

	Token* tmp = first;
	first = first->next;

	if (first != nullptr) {
		first->prev = nullptr;
	}
	else {
		// Jesli lista jest teraz pusta, ustawiam last na nullptr
		last = nullptr;
	}

	delete tmp;
}


Token* List::begin() {
	return first;
}

Token* List::end() {
	if (last == nullptr) {
		return nullptr;
	}
	else {
		return last;
	}
}

List::~List() {
	Token* cur = first;
	while (cur != nullptr) {
		Token* next = cur->next;
		delete cur;
		cur = next;
	}
	first = nullptr;
	last = nullptr;
	size = 0;
}