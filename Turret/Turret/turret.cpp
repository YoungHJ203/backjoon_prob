#include<iostream>
#include<list>
#include<iterator>
#include<math.h>
using namespace std;

double distance(int, int,int,int);

int main() {

	int caseNum;					// the number of cases to test
	int x1, x2, y1, y2, r1, r2;		// positions of observers and distances between a observer and a opposite
	list<int> result;				// results of each case

	// input the initial data
	cin >> caseNum;
	for (int i = 0; i < caseNum; i++) {
		cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
		

		// the only right case satisfying below conditions
		if (x1 >= -10000 && x2 >= -10000 && x1 <= 10000 && x2 <= 10000 && r1 >= 0 && r2 >= 0 && r1 <= 10000 && r2 <= 10000) {
			double d;		// distance between the observers

			d = distance(x1, y1, x2, y2);
			double r = (double)(r1 + r2);

			// nowhere case
			if (r < d) {
				result.push_back(0);
			}
			// only one place possible (circumscribe)
			else if (r == d) {
				result.push_back(1);
			}
			// other cases
			else {
				double rd = (double) abs(r1 - r2);

				if (rd < d) {			// two places possible case
					result.push_back(2);
				}
				else if (rd == d) {		// inscribe
					if(rd == 0) {
						result.push_back(-1);
					}
					else {
						result.push_back(1);
					}
					
				}
				else {					// so many places possible
					result.push_back(0);
				}
			}
		}
	}
	
	list<int>::iterator it = result.begin();
	while (it != result.end()) {
		cout << *it << endl;
		it++;
	}
}

double distance(int x1, int y1, int x2, int y2) {
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}