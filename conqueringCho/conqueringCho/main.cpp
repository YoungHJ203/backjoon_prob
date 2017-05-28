#include<iostream>
#include<vector>

using namespace std;

bool check(int, int, int);
void skip(int*);
int countSet(vector<int>&, int, int, int*, int*);
int  cirSet(vector<int>&, int, int,int*,int*);

int main(){
	int testCase=0;	// the number of test cases

	// get the number of test cases
	cin >> testCase;

	for (int i = 0; i < testCase; i++) {
		int numSec=0;				// the half number of sections
		int numPlat=0;				// the number of platoon members
		int setNum=0;				// the number of sets
		int init[2] = { 0,0 };		// state of initial two sets
		int end[2] = { 0,0 };		// state of end two sets

		// get the number of sections and number of platoon members
		cin >> numSec >> numPlat;

		vector<int>	enemy(2*(numSec));	// the number of enemy in each section

		// get the number of enemy in an section
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < numSec; k++) {
				if (j == 0) {
					cin >> enemy[2 * k];
				}
				else {
					cin >> enemy[2 * k + 1];
				}
			}
		}

		// in the case of making set through 0 and numSec-1 Column
		setNum = countSet(enemy, numSec, numPlat,init,end) + cirSet(enemy, numSec, numPlat, init, end);		
		
		cout << 2 * numSec - setNum << endl;

	}
}

// check if conquering two section simultanously is possible
bool check(int enemy1, int enemy2, int plat) {
	if (enemy1 + enemy2 <= plat) {
		return true;
	}
	else {
		return false;
	}
}

// skip conquering two sections simultanously
void skip(int* state) {
	state[0] = state[1];
	state[1] = 0;
}

// get the max number of sets between startCol and endCol
int countSet(vector<int> &enemy, int numSec, int numPlat, int *init, int *end) {
	int state[2] = { 0,0 };		// shows previous two states         0 : no set,  -1 or 1 : set
	int setNum = 0;				// the number of sets
								// get the maximum number of possible sets
								// initial setting about first two sections

	if (check(enemy[0], enemy[1], numPlat)) {		// case that making set is possible
		setNum++;
		state[0] = 0;
		state[1] = 1;
		init[0] = init[1] = 1;
	}
	else {										// the other case that the making set isn't possible
		skip(state);
	}


	for (int j = 2; j < 2 * numSec; j++) {
		// first row
		if (j % 2 == 0) {
			if (check(enemy[j], enemy[j - 2], numPlat) && state[0] == 0) {	// making set is better
				if (state[1] != 1) { 
					setNum++; 
					if (j == 2) {
						init[0] = -1;
					}

					if (j == 2 * numSec - 2) {
						end[0] = -1;
					}
				}

				state[0] = state[1];
				state[1] = 1;
			}
			else {															// making set isn't possible
				skip(state);
			}
		}
		
		// second row
		else {
			int stateCase = 0;								// 0 ; making any set isn't possible
															// 1 ; making horizantle set is possible
															// 2 ; making vertical set is possible
															// 3 ; making every set is possible
			if (check(enemy[j], enemy[j - 2], numPlat))		stateCase++;
			if (check(enemy[j], enemy[j - 1], numPlat))		stateCase = stateCase + 2;

			switch (stateCase) {
			// making set isn't possible
			case 0: {
				if (state[0] == 1 && state[1] == 1) {
					state[0] = 0; state[1] = 0;
				}
				else {
					skip(state);
				}
				break;
			}
			
			// making horizontal set
			case 1: {
				if (state[0] == 0) {
					setNum++;
					state[0] = state[1];
					state[1] = -1;

					if (j == 2) {
						init[1] = -1;
					}

					if (j == 2 * numSec - 1) {
						end[1] = -1;
					}
				}
				else if(state[0]==1){
					if (state[1] == 1) {
						setNum++;
						state[0] = 1;
						state[1] = -1;
						if (j == 3) {
							init[0] = -1;
							init[1] = -1;
						}

						if (j == 2 * numSec - 1) {
							end[0] = -1;
							end[1] = -1;
						}
					}
					else {
						state[0] = 0;
						state[1] = 0;
					}
				}
				else {
					skip(state);
				}
				break;
			}

			// making vertical set
			case 2: {
				if (state[1] == 0) {
					setNum++;
					state[0] = state[1];
					state[1] = 1;

					if (j == 2 * numSec - 1) {
						end[0] = 1;
						end[1] = 1;
					}
				}
				else{
					if (state[0] == 1) {
						setNum++;
						state[0] = 0;
						state[1] = 1;

						if (j == 2 * numSec - 1) {
							end[0] = 1;
							end[1] = 1;
						}
					}
					else {
						skip(state);
					}
				}
				break;
			}

			// making every set is possible
			case 3: {
				if (state[0] == -1) {
					if (state[1] == 0) {
						setNum++;
						state[0] = state[1];
						state[1] = 1;

						if (j == 2 * numSec - 1) {
							end[0] = 1;
							end[1] = 1;
						}
					}
					else {
						skip(state);
					}
				}

				// making horizontal set is better
				else if (state[0] == 0) {
					if (j < 2 * numSec - 1) {
						if (check(enemy[j - 1], enemy[j + 1], numPlat)) {
							setNum++;
							state[0] = state[1];
							state[1] = -1;

							if (j == 3) {
								init[1] = -1;
							}

							if (j == 2 * numSec - 1) {
								end[1] = -1;
							}
						}
						else {
							setNum++;
							state[0] = state[1];
							state[1] = 1;

							if (j == 2 * numSec - 1) {
								end[1] = 1;
							}
						}
					}
					else {
						setNum++;
						state[0] = state[1];
						state[1] = 1;

						if (j == 3) {
							init[1] = 1;
						}

						if (j == 2 * numSec - 1) {
							end[1] = 1;
						}
					}
				}
				else {
					if (state[1] == 1) {
						setNum++;
						state[0] = state[1];
						state[1] = 1;							

						if (j == 2 * numSec - 1) {
							end[0] = 1;
							end[1] = 1;
						}
					}
					else {
						setNum++;
						state[0] = state[1];
						state[1] = 1;

						if (j == 2 * numSec - 1) {
							end[0] = 1;
							end[1] = 1;
						}
					}

					if (j == 2 * numSec - 1) {
						end[0] = 1;
						end[1] = 1;
					}
				}
				break;
			}
			}
		}
	}

	return setNum;
}

// get the number of sets between numSec-1 Col and 0 Col
int cirSet(vector<int> &enemy,int numSec,int numPlat,int *init,int *end) {
	int setNum = 0;

	if (numSec > 2) {
		if (init[0] == 0 && end[0] == 0 && check(enemy[0], enemy[2 * numSec - 2], numPlat)) setNum++;
		if (init[1] == 0 && end[1] == 0 && check(enemy[1], enemy[2 * numSec - 1], numPlat)) setNum++;
		if (init[0] == 1 && init[1] == 1 && end[0] == 0 && end[1] == 0 && check(enemy[0], enemy[2 * numSec - 2], numPlat) && check(enemy[1], enemy[2 * numSec - 1], numPlat))
			setNum++;
		if (init[0] == 0 && init[1] == 0 && end[0] == 1 && end[1] == 1 && check(enemy[0], enemy[2 * numSec - 2], numPlat) && check(enemy[1], enemy[2 * numSec - 1], numPlat))
			setNum++;
	}

	return setNum;
}


// change starting point of checking section
void change(vector<int> &enemy, int numSec) {
	int temp[2] = { enemy[0],enemy[1] };

	for (int i = 0; i < numSec-1; i++) {
		enemy[2 * i] = enemy[2 * i + 2];
		enemy[2 * i+1] = enemy[2 * i + 3];
	}
	enemy[2 * numSec - 2] = temp[0];
	enemy[2 * numSec - 1] = temp[1];
}