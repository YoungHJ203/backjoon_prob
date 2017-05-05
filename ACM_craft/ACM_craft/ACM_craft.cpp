#include<iostream>
#include<vector>
#include<list>
#include<map>

using namespace std;

int main() {
	// the number of cases
	int caseNum;

	cin >> caseNum;

	// implement all cases
	for (int i = 0; i < caseNum; i++) {
		int bN, rN;			// the number of bulidings and rules
		int maxTime = 0;	// max time to finish the work

		cin >> bN >> rN;

		// construction period for each building ,total time to finish the construction and next work of a work
		vector<int> conPeriod(bN);

		// prework list
		vector<vector<int>> preWork(bN);

		// all needed time to construct each building
		for (int i = 0; i < bN; i++) {
			cin >> conPeriod[i];
			preWork[i].reserve(bN);
			preWork[i][i] = conPeriod[i];
		}

		// get the rule between the prework and the postwork
		for (int i = 0; i < rN; i++) {
			int pre, post;

			cin >> pre >> post;

			// store the relationship betweem the prework and postwork
			preWork[pre - 1][post - 1] = conPeriod[pre - 1];
		}
		
		
		for (int i = 0; i < bN;i++) {
			for (int j = 0; j < bN; j++) {
				

			}		
		}

		int finish;		// building number
		
		// get building number to construct
		cin >> finish;

		toCheck[finish-1]=finish-1;
		history[finish]=finish;
		totalTime[finish - 1] = conPeriod[finish -1];
		next[finish-1] = 0;
		
		// check all possible routes
		while (!toCheck.empty()) {
			int current;

			// check if the current work should be considered
			current = toCheck.begin()->first;			
			toCheck.erase(current);

			//totalTime[current] = totalTime[current] + conPeriod[current];

			cout << current+1 << endl;

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
				if (history[*it+1]!=*it+1) {
					toCheck[*it] = *it;			// store the prework
					history[*it+1] = *it+1;
				}
				
				it++;
			}
		}

		cout << maxTime<<endl;
	}
}

//
//int main() {
//	// the number of cases
//	int caseNum;
//
//	cin >> caseNum;
//
//	// implement all cases
//	for (int i = 0; i < caseNum; i++) {
//		int bN, rN;			// the number of bulidings and rules
//		map<int, int> toCheck;		// list to check
//		map<int, int> history;		// list to store the previous visit ***** very very important
//
//		list<int>::iterator it;
//		int maxTime = 0;	// max time to finish the work
//
//		cin >> bN >> rN;
//
//		// construction period for each building ,total time to finish the construction and next work of a work
//		vector<int> conPeriod(bN), totalTime(bN), next(bN);
//
//		// prework list
//		vector<list<int>> preWork(bN);
//
//		// all needed time to construct each building
//		for (int i = 0; i < bN; i++) {
//			cin >> conPeriod[i];
//			totalTime[i] = 0;
//		}
//
//		// get the rule between the prework and the postwork
//		for (int i = 0; i < rN; i++) {
//			int pre, post;
//
//			cin >> pre >> post;
//
//			// store the relationship betweem the prework and postwork
//			preWork[post - 1].push_back(pre - 1);
//		}
//
//
//		int finish;		// building number
//
//						// get building number to construct
//		cin >> finish;
//
//		toCheck[finish - 1] = finish - 1;
//		history[finish] = finish;
//		totalTime[finish - 1] = conPeriod[finish - 1];
//		next[finish - 1] = 0;
//
//		// check all possible routes
//		while (!toCheck.empty()) {
//			int current;
//
//			// check if the current work should be considered
//			current = toCheck.begin()->first;
//			toCheck.erase(current);
//
//			//totalTime[current] = totalTime[current] + conPeriod[current];
//
//			cout << current + 1 << endl;
//
//			it = preWork[current].begin();
//
//			// store the prework of current work to check in list
//			while (it != preWork[current].end()) {
//
//				// check the prework to be considered for max time
//				if (totalTime[current] + conPeriod[*it] > totalTime[*it]) {
//					totalTime[*it] = totalTime[current] + conPeriod[*it];		// update the total time to finish the final work
//					next[*it] = current;										// update the next work of prework
//
//																				// update the max time
//					if (totalTime[*it] > maxTime) {
//						maxTime = totalTime[*it];
//					}
//				}
//
//				// case that we didn't check the prework before
//				if (history[*it + 1] != *it + 1) {
//					toCheck[*it] = *it;			// store the prework
//					history[*it + 1] = *it + 1;
//				}
//
//				it++;
//			}
//		}
//
//		cout << maxTime << endl;
//	}
//}
//
