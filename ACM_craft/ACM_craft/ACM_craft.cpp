#include<iostream>
#include<functional>
#include<list>
#include<vector>
#include<queue>
#include<map>

using namespace std;

void topoSort(vector<list<int>> &adjacentList, vector<int> &topoArray, vector<int> &entryNum) {
	priority_queue<int,vector<int>, greater<int> > pq;		// to store and quickly get the building number to construct
	int size = adjacentList.size();

	// sequential search
	for (int i = 0; i < size; i++) {
		if (entryNum[i] == 0) {		// the case that 'i' is final point
			pq.push(i);
		}
	}

	// topological sort
	for(int i=0;i<size;i++){
		int current = pq.top();
		pq.pop();	
		
		// add the current work to totoArray
		topoArray.insert(topoArray.begin(),current);

		// update entry number array
		list<int>::iterator lit = adjacentList[current].begin();
		while (lit!=adjacentList[current].end()) {
			if (--entryNum[*lit]==0) {
				pq.push(*lit);
			}
			lit++;
		}
	}
}

int main() {
	// the number of cases
	int caseNum;

	cin >> caseNum;

	// implement all cases
	for (int i = 0; i < caseNum; i++) {
		int bN, rN;						// the number of bulidings and rules
		vector<int> topoArray;			// topological sorted array for construction work
		map<int, int> checkMap;			// list to check
		int finish, first;				// final and first building numbers
		vector<int>::iterator it;		// to search the prework list
		int maxTime = 0;				// max time to finish the work

		cin >> bN >> rN;		
		
		// construction period for each building ,total time to finish the construction and next work of a work
		vector<int> constructP(bN,0), totalTime(bN,0), entryNum(bN,0), next(bN,0);
		
		// prework list
		vector<list<int>> preWork(bN);
		
		// enter needed time to construct each building
		for (int i = 0; i < bN; i++) {
			cin >> constructP[i];
			totalTime[i] = constructP[i];
		}

		// get the rule between the prework and the postwork
		for (int i = 0; i < rN; i++) {
			int pre, post;

			cin >> pre >> post;

			// store the relationship betweem the prework and postwork
			preWork[post - 1].push_back(pre - 1);

			// increase the number of going out path to next node
			entryNum[pre - 1]++;
		}

		// topological sort
		topoSort(preWork, topoArray, entryNum);

		// get building number to construct
		cin >> finish;

		// search the location in the topological array
		it = topoArray.begin();
		while (*it!=finish-1) {
			it++;
		}
		
		// add final work to check list
		checkMap[finish-1] = finish-1;

		// initialize max time and next work array
		maxTime = constructP[finish - 1];
		next[finish - 1] = finish - 1;

		// get the max time 
		while (it != topoArray.begin()) {
			int current=*it;

			// in the case that '*it' work is needed to be checked
			if (checkMap.count(current)) {
				list<int>::iterator pre = preWork[current].begin();

				while (pre != preWork[current].end()) {
					// check if new time is larger than the previous one
					if (totalTime[*pre] < totalTime[current] + constructP[*pre]) {
						totalTime[*pre] = totalTime[current] + constructP[*pre];

						next[*pre] = current;
						checkMap[*pre] = *pre;

						// check if these total time is max value
						if (maxTime < totalTime[*pre]) {
							maxTime = totalTime[*pre];
							first = *pre;
							next[first] = current;
						}
					}

					pre++;
				}
			}

			checkMap.erase(current);
			
			it--;
			
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