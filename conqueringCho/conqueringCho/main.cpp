#include<iostream>
#include<vector>

using namespace std;

int min(int,int,int);
int min(int, int);

int main(){
	int testCase;	// the number of test cases

	// get the number of test cases
	cin >> testCase;

	for (int i = 0; i < testCase; i++) {
		int numSec;					// the half number of sections
		int numPlat;				// the number of platoon members
		int minPlat[4];				// minimum of platoon in each state ; 0: no section in (i-1) column, 1:lower section in (i-1) column, 2:upper section in (i-1) column, 3:full section in (i-1) column
		int temp[4];				// temporarily store the minimum of platoon in i column

		// get the number of sections and number of platoon members
		cin >> numSec >> numPlat;

		vector<vector<int>>	enemy(2,vector<int> (numSec));	// the number of enemy

		// get the number of enemy in an section
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < numSec; k++) {
				cin >> enemy[j][k];
			}
		}

		// initialization of minimun of platoon
		minPlat[0] = 0;
		minPlat[1] = 1;
		minPlat[2] = 1;
		minPlat[3] = (enemy[0][0] + enemy[1][0] <= numPlat ? 1 : 2);

		// 
		for (int j = 0; j < numSec; j++) {
			// update 0 state in i column
			if (enemy[0][j]+enemy[1][j]<=numPlat) {
				temp[0] = min();
			}
			else {
			
			}

			if () {

			}
		}
	}
}

int min(int a, int b, int c) {
	int min = a;
	if (min > b) {
		min = b;
	}
	if (min > c) {
		min = c;
	}

	return min;
}

int min(int a, int b) {
	return (a > b ? b : a);
}