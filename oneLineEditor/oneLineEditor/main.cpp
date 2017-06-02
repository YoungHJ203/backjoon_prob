#include<iostream>
#include<stdbool.h>
using namespace std;

// node class
template <class T>
class node {
public:
	node() {
		pre = nullptr;
		next = nullptr;
	}

	node(T ele) {
		pre = nullptr;
		next = nullptr;
		this->ele = ele;
	}

	node<T>* pre;
	node<T>* next;
	T ele;
};

// list class
template <class T>
class list {
public:
	// constructor
	list() {
		this->head = new node<T>();
		this->trailer = new node<T>();

		head->next = this->trailer;
		trailer->pre = this->head;
		size = 0;
	}

	// check if this list is empty
	bool empty() {
		if (this->size == 0)
			return true;
		return false;
	}

	// get ths number of node in this list
	int getSize() {
		return size;
	}

	// print all elements
	void printAll() {
		node<T>* reference = this->head->next;

		while (reference != this->trailer) {
			cout << reference->ele;
			reference = reference->next;
		}

		cout << endl;
	}

	// add a new node in the end of a list
	void addLast(T ele) {
		node<T>* newNode = new node<T>(ele);

		newNode->pre = this->trailer->pre;
		newNode->next = this->trailer;
		this->trailer->pre->next = newNode;
		this->trailer->pre = newNode;

		this->size++;
	}

	// add a new node before 'index'th node
	void addBefore(int index, T ele) {
		node<T>* newNode = new node<T>(ele);
		node<T>* reference = this->head;

		if (index > this->size + 1) {
			cout << "Wrong index (addBefore)" << endl;
			exit(0);
		}

		for (int i = 0; i < index; i++) {
			reference = reference->next;
		}
		
		newNode->pre = reference->pre;
		newNode->next = reference;
		reference->pre->next = newNode;
		reference->pre = newNode;

		this->size++;
	}

	// delete a node before 'index'th node
	void delBefore(int index) {
		node<T>* reference = this->head;

		if (index > this->size +1 ) {
			cout << "Wrong index (delBefore)" << endl;
			exit(0);
		}

		for (int i = 0; i < index-1; i++) {
			reference = reference->next;
		}

		reference->pre->next = reference->next;
		reference->next->pre = reference->pre;

		delete reference;

		this->size--;
	}

private:
	node<T>* head;
	node<T>* trailer;
	int size;
};

int main() {
	char c=0;
	int cursor = 0;
	int commandNum = 0;
	list<char> editor;
	
	// enter characters
	while (cin.peek() != '\n') {
		cin >> c;
		editor.addLast(c);
	}

	// move the cursor at the end of editor
	cursor = editor.getSize();

	// enter the number of commands
	cin >> commandNum;

	// enter commands
	for (int i = 0; i<commandNum; i++) {
		cin >> c;
		
		switch (c) {
		case 'P': {cin >> c; editor.addBefore(cursor + 1, c); cursor++; break; }
		case 'B': {if (cursor > 0) { editor.delBefore(cursor + 1); cursor--; } break; }
		case 'L': {if(cursor>0) cursor--; break; }
		case 'D': {if (cursor < editor.getSize()) cursor++; break; }
		default: {break;}
		}		
	}	

	// print all editor
	editor.printAll();
}