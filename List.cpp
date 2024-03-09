#include "List.h"
#include <iostream>
using namespace std;

List::List() {

}

void List::push_back(Token* t) {
	//cout << endl <<" push_back symbol("<<t->symbols[0]<<"): " << t << endl;
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
		tmp->next = new Token(*t);

		//		Token* tmp2 = t;
		//tmp->next = t;
	}
	size++;
}

void List::pop_back() {
	if (first == nullptr) {
		 return;
	}
	Token* tmp = first;
	while (tmp->next->next != nullptr) {
		tmp = tmp->next;
	}
	//cout << "pop_back: " << tmp << " next: " << tmp->next << endl;
	delete tmp->next; // nie dziala poprawnie, kiedy usuwam jakis element ze stosu, to w output nie chce sie pojawiac
	tmp->next = nullptr;
	size--;
}

void List::drawList() {
	if (first == nullptr) return;
	Token* tmp = first;
	cout << first->symbols[0] << " ";
	while (tmp->next != nullptr) {
		tmp = tmp->next;
		cout << tmp->symbols[0] << " ";
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