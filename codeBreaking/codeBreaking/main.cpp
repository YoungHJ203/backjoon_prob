#include<iostream>
#include<list>
#include<stack>
#include<iterator>
using namespace std;

int main() {
	int testCase = 0;

	cin >> testCase;

	// practice test cases
	for (int i = 0; i < testCase; i++) {
		list<char> keyLogger;
		stack<char>	front;
		stack<char>	back;
		char c = 0;

		// buffer initiation
		cin.ignore();
		
		// enter the code
		while (cin.peek()!='\n') {	
			cin >> c;
			keyLogger.push_back(c);
		}
		
		// break the code
		while (!keyLogger.empty()) {
			c = keyLogger.front();
			keyLogger.pop_front();
			
			switch (c)
			{
			case '<': {	if (!front.empty()) {
				back.push(front.top());
				front.pop();
			}	break; }
			case '>': {	if (!back.empty()) {
				front.push(back.top());
				back.pop();
			}	break; }
			case '-': {	if (!front.empty()) {
				front.pop();
			}break; }
			default: {	front.push(c); break; }
			}
		}

		// assemble the code
		while (!front.empty()) {
			back.push(front.top());
			front.pop();
		}

		// print the code
		while (!back.empty()) {
			cout << back.top();
			back.pop();
		}

		cout << endl;
	}
}