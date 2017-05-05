#include<iostream>
#include<iterator>
#include<list>
#include<math.h>

using namespace std;

double checkIO(int x1, int y1, int x2, int y2, int cx, int cy, int r);

int main() {

	int testNum;
	list<int> results;

	// get the number of test cases
	cin >> testNum;
	
	// implement tests
	for (int i = 0; i < testNum; i++) {
		int x1, y1, x2, y2, planet, ioNum;

		// get an start and end points
		cin >> x1 >> y1 >> x2 >> y2;

		// get the number of planets
		cin >> planet;

		// before checking, initialize the number of planets through which the prince passes
		ioNum = 0;

		// check for each planet
		for (int j = 0; j < planet;j++) {
			int cx, cy, r;

			// get a coordinate of planet and radius
			cin >> cx >> cy >> r;
		
			if (checkIO(x1, y1, x2, y2, cx, cy, r)>0) {
				ioNum++;
			}
		}
		
		results.push_back(ioNum);
	}

	// print the results
	list<int>::iterator it = results.begin();
	while (it != results.end()) {
		cout << *it << endl;
		it++;
	}
}

// check if the prince passes through the planet
double checkIO(int x1, int y1, int x2, int y2, int cx, int cy, int r) {
	return (double)-((x1 - cx)*(x1 - cx) + (y1 - cy)*(y1 - cy) - r*r)*((x2 - cx)*(x2 - cx) + (y2 - cy)*(y2 - cy) - r*r);   // if the value is negative, it means that the prince pass through the planet and if not, it doesn't
}