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
		//cout << "\npush_back_: ";
		//for (int i = 0; i < t->size; i++) {
			//cout << t->symbols[i];
		//}
		//cout <<" push_back_end" << endl;
		t->next = nullptr;

		Token* tmp = first;
		while (tmp->next != nullptr) {
			tmp = tmp->next;
		}
		tmp->next = new Token(*t);
		//cout << "push_back " << tmp << "\n";
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