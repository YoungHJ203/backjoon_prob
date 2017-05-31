#include<iostream>

using namespace std;

int main() {
	int testCase=0;

	cin >> testCase;

	for (int i = 0; i < testCase; i++) {
		int a = 0;
		int b = 0;
		int num = 1;
		int result = 1;

		cin >> a >> b;

		for (int i = 0; i < b; i++) {
			result *= a;
			result = result % 10;
		}

		
		if (result != 0) {
			cout << result % 10 << endl;
		}
		else {
			cout << 10 << endl;
		}
		
	}
}
