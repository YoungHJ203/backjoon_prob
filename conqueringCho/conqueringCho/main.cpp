#include<iostream>
#include<vector>

using namespace std;

class setOfSection {	// set of conquering sections
public:
	int first;			// first section in a set
	int second;			// second section in a set
	int overlapNum;		// the number of sections overlapped

	// checking if those sections are overlapped
	bool isOverlapped(setOfSection a) {
		if (this->first == a.first || this->first == a.second || this->second == a.first || this->second == a.second) {
			return true;
		}
		return false;
	}
};


int main(){
	int testCase;	// the number of test cases

	// get the number of test cases
	cin >> testCase;

	for (int i = 0; i < testCase; i++) {
		int numSec;					// the half number of sections
		int numPlat;				// the number of platoon members
		
		// get the number of sections and number of platoon members
		cin >> numSec >> numPlat;

		vector<vector<int>>	enemy(2,vector<int> (numSec));	// the number of enemy

		// get the number of enemy in an section
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < numSec; k++) {
				cin >> enemy[j][k];

				// check if continuous sections can be simultanously conquered
				if (k > 0 && enemy[j][k-1]+ enemy[j][k]<=numPlat) {
					
				}
			}

			if (enemy[j][numSec-1] + enemy[j][0] <= numPlat) {
				
			}
		}
	}
}