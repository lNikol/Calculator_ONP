#include "List.h"
#include <iostream>
using namespace std;

List::List() {

}

void List::push_back(Token* t) {
	if (first == nullptr) {
		first = t;
		first->next = nullptr;
	}
	else if (t == nullptr) return;
	else {
		t->next = nullptr;
		if (first == nullptr) return;

		Token* tmp = first;
		while (tmp->next != nullptr) {
			tmp = tmp->next;
		}
		tmp->next = t;
	}
	size++;
}

void List::pop_back() {
	if (first == nullptr) return;
	Token* tmp = first;
	while (tmp->next->next != nullptr) {
		tmp = tmp->next;
	}
	delete tmp->next;
	tmp->next = nullptr;
}

void List::drawList() {
	Token* tmp = first;
	cout << first->symbols[0] << " ";
	while (tmp->next != nullptr) {
		tmp = tmp->next;
		cout << tmp->symbols[0] << " ";
	}
}

List::~List() {
	cout << endl;
	Token* cur = first;
	while (cur != nullptr) {
		cout << cur->symbols[0] << " ";
		Token* next = cur->next;
		delete cur;
		cur = next;
	}
	first = nullptr;
}