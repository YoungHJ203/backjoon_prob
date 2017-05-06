#include<iostream>
#include<list>
#include<queue>
#include<map>
#include<vector>

using namespace std;

int main() {
	// the number of cases
	int caseNum;

	cin >> caseNum;

	// implement all cases
	for (int i = 0; i < caseNum; i++) {
		int bN, rN;					// the number of bulidings and rules
		map<int, int> checkMap;		// list to check
		priority_queue<int> pq;		// to store and quickly get the building number to construct


		
		list<int>::iterator it;
		int maxTime = 0;	// max time to finish the work

		cin >> bN >> rN;

		// construction period for each building ,total time to finish the construction and next work of a work
		vector<int> conPeriod(bN), totalTime(bN), next(bN);

		// prework list
		vector<list<int>> preWork(bN);

		// all needed time to construct each building
		for (int i = 0; i < bN; i++) {
			cin >> conPeriod[i];
			totalTime[i] = 0;
		}

		// get the rule between the prework and the postwork
		for (int i = 0; i < rN; i++) {
			int pre, post;

			cin >> pre >> post;

			// store the relationship betweem the prework and postwork
			preWork[post - 1].push_back(pre - 1);
		}


		int finish;		// building number

						// get building number to construct
		cin >> finish;

		toCheck[finish - 1] = finish - 1;
		history[finish] = finish;
		totalTime[finish - 1] = conPeriod[finish - 1];
		next[finish - 1] = 0;

		// check all possible routes
		while (!toCheck.empty()) {
			int current;

			// check if the current work should be considered
			current = toCheck.begin()->first;
			toCheck.erase(current);

			//totalTime[current] = totalTime[current] + conPeriod[current];

			cout << current + 1 << endl;

			it = preWork[current].begin();

			// store the prework of current work to check in list
			while (it != preWork[current].end()) {

				// check the prework to be considered for max time
				if (totalTime[current] + conPeriod[*it] > totalTime[*it]) {
					totalTime[*it] = totalTime[current] + conPeriod[*it];		// update the total time to finish the final work
					next[*it] = current;										// update the next work of prework

																				// update the max time
					if (totalTime[*it] > maxTime) {
						maxTime = totalTime[*it];
					}
				}

				// case that we didn't check the prework before
				if (history[*it + 1] != *it + 1) {
					toCheck[*it] = *it;			// store the prework
					history[*it + 1] = *it + 1;
				}

				it++;
			}
		}

		cout << maxTime << endl;
	}
}

// modified djikstra algorithm with entry number 
/*
// entry of priority queue
class entryP{
public:
	int work;		// building number to construct
	int time;		// total time to construct the building

	// constructor
	entryP(int a, int b) {
		this->work = a;
		this->time = b;
	}

};

// overloading operator for priority queue
bool operator<(entryP a,entryP b) {
	return a.time < b.time;
}


// initialize
void ini(vector<int> &entryNum, priority_queue<entryP, vector<entryP>, less<entryP>> &checkList) {
	int size = entryNum.size();
	
	for (int i = 0; i < size; i++) {
		if (entryNum[i] == 0) {
			checkList.push(entryP(i, entryNum[i]));
		}
	}

}

int main() {
	// the number of cases
	int caseNum;

	cin >> caseNum;

	// implement each test case
	for (int i = 0; i < caseNum; i++) {
		int bN, rN;			// the number of bulidings and rules
		int maxTime = 0;	// max time to finish the specified work
		int finish;			// final building's number to construct
		cin >> bN >> rN;

		// construction period for each building, total time to finish the construction of specified building and the number of previous work for each building
		vector<int> constructP(bN,0), totalTime(bN,0), entryNum(bN,0);	

		// prework list
		vector<list<int>> preWork(bN);

		// work list to check
		priority_queue<entryP, vector<entryP>, less<entryP>> checkList;

		// needed for searching preWork
		list<int>::iterator it;

		// enter ala constuction periods for each building 
		for (int i = 0; i < bN; i++) {
			cin >> constructP[i];

			totalTime[i] = constructP[i];
		}

		// enter all rules between the prework and the postwork
		for (int i = 0; i < rN; i++) {
			int pre, post;

			cin >> pre >> post;

			// store the relationship betweem the prework and postwork
			preWork[pre - 1].push_back(post - 1);

			// increase the number of preworks
			entryNum[post - 1]++;
		}
		
		// initialize checklist
		ini(entryNum, checkList);
	
		// get building number to construct
		cin >> finish;

		// get the needed time to finish work
		while (!checkList.empty()) {
			int current;		// current node ( = current building number to construct)
			int currentTime;	// total constuction period for current work to finish

			// check if the current work should be considered
			current = checkList.top().work;
			currentTime = checkList.top().time;
			checkList.pop();

			it = preWork[current].begin();

			// store the prework of current work to check in list
			while (it != preWork[current].end()) {
				
				// check the prework to be considered for max time
				if (totalTime[current] + constructP[*it] > totalTime[*it]) {
					totalTime[*it] = totalTime[current] + constructP[*it];		// update the total time to finish the final work
					
					// trace the needed time to finish work
					if (totalTime[*it] > maxTime && (*it) == (finish-1)) {
						maxTime = totalTime[*it];
					}
				}
				
				// the case that needed time for post work(*it) is definitely set
				if (--entryNum[*it] == 0) {
					checkList.push(entryP(*it,totalTime[*it]));

				}
				
				it++;
			}
		}

		cout << maxTime<<endl;
	}
}
*/