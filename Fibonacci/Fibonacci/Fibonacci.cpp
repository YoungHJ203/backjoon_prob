#include<iostream>
#include<vector>
using namespace std;

int fibonacci(int);

int countZer0;				// the number of zero called
int countOne;				// the number of one called

int main() {
	int caseNum;			// the number of test cases 
	
	// get the number of test cases
	cin >> caseNum;

	
	vector<int> index (caseNum);				// indices of fibonacci sequence

	for (int i = 0; i < caseNum; i++) {
		cin >> index[i];				// get an index of fibonacci sequence
	}

	for (int i = 0; i < caseNum; i++) {
		countOne = 0;
		countZer0 = 0;

		fibonacci(index[i]);
		cout << countZer0 << " " << countOne << endl;
	}
	

}

int fibonacci(int n) {
	if (n == 0) {
		countZer0++;
		return 0;
	}
	else if (n == 1) {
		countOne++;
		return 1;
	}
	else {
		return fibonacci(n - 1) + fibonacci(n - 2);
	}

}