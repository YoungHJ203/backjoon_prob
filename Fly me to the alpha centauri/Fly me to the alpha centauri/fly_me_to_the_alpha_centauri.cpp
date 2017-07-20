 #include<iostream>
#include<cmath>
using namespace std;

int main() {
	
	int testCase=0;

	cin >> testCase;


	for (int i = 0; i < testCase; i++) {
		int start = 0, end = 0;
		int N=0;
		double n1 = 0;
		int n2 = 0;

		cin >> start >> end;

		N = end - start;
		n1 = sqrt(N);
		n2 = (int) sqrt(N);

		if (n1 == n2) {
			N = 2 * sqrt(N) - 1;
		}
		else {
			double a = 0, b = 0;

			a = floor(sqrt(N));
			b = ceil(sqrt(N));

			a = a*a;
			b = b*b;

			double check = (a + b) / 2;
			double flag = N;

			if (flag < check) {
				N = 2 * (floor(sqrt(N)));
			}
			else {
				N = 2 * (ceil(sqrt(N))) - 1;
			}
		}

		cout << N << endl;
	}

}