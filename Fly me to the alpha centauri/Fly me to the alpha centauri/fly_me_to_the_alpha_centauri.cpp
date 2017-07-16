 #include<iostream>
#include<cmath>
using namespace std;

int main() {
	
	int testCase=0;

	cin >> testCase;


	for (int i = 0; i < testCase; i++) {
		int start = 0, end = 0;
		int N=0;
		double temp = 0;

		cin >> start >> end;

		temp = ceil(sqrt(end - start));

		if (end - start > 2)
			N = temp + 1;
		else
			N = temp;
		cout << N << endl;
	}

}