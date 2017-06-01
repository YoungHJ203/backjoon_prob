#include<iostream>
#include<stdbool.h>

using namespace std;

// node class
template <typename T>
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
template <typename T>
class list {
public:
	list() {
		this->head = new node<T>();
		this->trailer = new node<T>();

		head->next = this->getTrailer();
		trailer->pre = this->getHead();
		this->size = 0;
	}

	// return the size of list
	int getSize() {
		return size;
	}

	// check if this list is empty
	bool empty() {
		if (this->getSize() == 0)
			return true;
		return false;
	}

	// get the head
	node<T>* getHead() {
		return this->head;
	}

	// get the trailer
	node<T>* getTrailer() {
		return this->trailer;
	}

	// add a new element in ths last of list
	void addLast(T ele) {
		node<T>* newNode = new node<T>(ele);

		newNode->pre = this->trailer->pre;
		newNode->next = this->getTrailer();
		this->trailer->pre->next = newNode;
		this->trailer->pre = newNode;

		this->size++;
	}

	// delete the node of index
	T del(int index) {
		int temp = 0;

		if (index > this->getSize()) {
			cout << "The index is wrong" << endl;
			return -1;
		}

		node<T>* reference = this->getHead();

		for (int i = 0; i < index; i++) {
			reference = reference->next;
		}

		reference->pre->next = reference->next;
		reference->next->pre = reference->pre;
		temp = reference->ele;

		delete reference;

		this->size--;

		return temp;
	}

private:
	node<T> *head;
	node<T> *trailer;
	int size;
};

int hashFunction(int, int, int);

int main() {
	int n = 0, m = 0;
	int current = 1;

	cin >> n >> m;

	list<int> people;

	// fill the each person's number in the list
	for (int i = 0; i < n; i++) {
		people.addLast(i + 1);
	}

	cout << "<";
	while (!people.empty()) {
		current = hashFunction(current, m, people.getSize());

		cout << people.del(current);

		if (people.getSize() != 0) {
			cout << ", ";
		}		
	}

	cout << ">";

}

// hash function for the index of people
int hashFunction(int current, int m, int size) {
	current = (current + (m - 1)) % size;

	return (current == 0 ? size: current);
}