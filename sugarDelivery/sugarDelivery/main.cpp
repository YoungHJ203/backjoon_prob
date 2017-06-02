#include<iostream>

using namespace std;

int main() {
	int N=0;
	int remain = 0;
	int bagNum = 0;

	// enter the total capacity of a bag
	cin >> N;

	// get the remaining sugar after the sugar is filled in the 5kg bags
	remain = N % 5;

	switch (remain) {
		case 0: {	
					bagNum = N / 5; break; }
		case 1: {	
					bagNum = N / 5 +1;
					break; }
		case 2: {	
					if (N / 5 < 2 && N % 3 == 0) {
						bagNum = N / 3;
					}
					else if (N / 5 >= 2) {
						bagNum = N / 5 +2;
					}
					else {
						bagNum = -1;
					}
					break; }
		case 3: {	
					bagNum = N / 5 + 1;
					break; }
		case 4: {	
					if (N / 5 >= 1) {
						bagNum = N / 5 +2;
					}
					else {
						bagNum = -1;
					}
					break; }
		default: {	
					break; }
	}

	cout << bagNum<<endl;
}

//#include<stdio.h>
//#pragma warning(disable:4996)
//int main(int N) { 
//	int temp, a;
//	scanf("%d", &N); 
//	temp = N - 4 ? 0 : -1;
//	a = N-- -7;
//	if (temp == 0) {
//		temp = N-- - 7 ? 1 + N / 5 + N % 5 % 2 : -1;
//	}
//	printf("%d", temp); }