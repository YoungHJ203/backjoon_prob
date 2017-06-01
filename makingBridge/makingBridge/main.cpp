#include<iostream>
#include<list>
#include<iterator>

using namespace std;

int combination(int, int);

int main() {
	int testCase=0;

	cin >> testCase;

	for (int i = 0; i < testCase; i++) {
		int a = 0, b = 0;

		cin >> a >> b;
		
		cout << combination(b, a) << endl;
	}
}

// calculate the number of possible cases where bridge can be constructed
int combination(int b, int a) {
	int sub = b - a;
	int com = 1;
	list<int> div;

	if (sub > a) {
		sub = a;
	}

	a = sub;

	if (sub == 0) {
		return 1;
	}

	for (int i = 0; i < sub-1; i++) {
		div.push_back(a--);
	}

	// to multiply smaller numbers
	b = b - sub + 1;

	for (int i = 0; i < sub; i++) {
		com *= b;
		
		if (div.size() > 0) {
			list<int>::iterator it = div.begin();

			while (com % (*it) != 0) {
				it++;

				if (it == div.end())
					break;
			}

			if (it != div.end()) {
				com /= (*it);

				div.erase(it);
			}
		}
				
		b++;
	}
	
	list<int>::iterator it = div.begin();

	while (it != div.end()) {
		com /= (*it);

		it++;
	}

	return com;
}