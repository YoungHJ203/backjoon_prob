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

	node<T>* getTrailer() {
		return this->trailer;
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

	// add a new node after the reference node
	node<T>* addAfter(node<T>* reference, T ele) {
		node<T>* newNode = new node<T>(ele);
		
		newNode->pre = reference;
		newNode->next = reference->next;
		reference->next->pre = newNode;
		reference->next = newNode;

		this->size++;
		
		return newNode;
	}

	// delete the reference node
	node<T>* del(node<T>* reference) {
		node<T>* temp;

		if (reference != this->head) {
			temp = reference->pre;
			reference->pre->next = reference->next;
			reference->next->pre = reference->pre;

			delete reference;

			this->size--;

			return temp;
		}
		else {
			return reference;
		}
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
	node<char>* refer;
	list<char> editor;
	
	// enter characters
	while (cin.peek() != '\n') {
		cin >> c;
		editor.addLast(c);
	}

	// move the cursor at the end of editor
	cursor = editor.getSize();
	refer = editor.getTrailer()->pre;

	// enter the number of commands
	cin >> commandNum;

	// enter commands
	for (int i = 0; i<commandNum; i++) {
		cin >> c;
		
		switch (c) {
		case 'P': {	
					cin >> c; 
					refer=editor.addAfter(refer, c); 
					cursor++; 
					break; }
		case 'B': {	
					refer = editor.del(refer);
					if (cursor > 0) {	
						cursor--; 
					}	break; }
		case 'L': {
					if (cursor > 0) {
						refer = refer->pre;
						cursor--;
					}	break; }
		case 'D': {
					if (cursor < editor.getSize()){
						refer = refer->next;
						cursor++;
					}	 break; }
		default: {break;}
		}		
	}	

	// print all editor
	editor.printAll();
}