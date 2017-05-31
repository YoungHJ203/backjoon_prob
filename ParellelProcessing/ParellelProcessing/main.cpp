#include<iostream>

using namespace std;

void cal(int, int, int&);

int main() {
	int testCase=0;

	cin >> testCase;

	for (int i = 0; i < testCase; i++) {
		int a = 0;
		int b = 0;
		int num = 1;
		int result = 1;

		cin >> a >> b;

		a = a % 10;

		cal(a, b, num);
		
		if (num == 1) {
			b = 1;
		}

		while (b>num) {
			b -= num;
		}

		for (int i = 0; i < b; i++) {
			result *= a;
		}

		cout << result % 10 << endl;		
	}
}

// calculate a^b and the number of cycles needed for conditions where units digit of a^b equals to a
void cal(int a, int b, int &num) {
	int result = a*a;
	int remain = result % 10;

	while (remain!=a) {
		result *= a;
		remain = result % 10;
	
		
		num++;
	}
}