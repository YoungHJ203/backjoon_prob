#include<iostream>
#include<vector>
#include<list>
#include<iterator>
using namespace std;

class adjacentSchool{
public:
	adjacentSchool(int index = 0, int distance = 0) {
		this->index = index;
		this->distance = distance;
	}

	int index;
	int distance;
};

int main() {
	int N = 0, M = 0;

	cin >> N >> M;

	vector<char> school(N);							// type of school
	vector<list<adjacentSchool>> edgeList(N, list<adjacentSchool>(0));	// edge list (road from school to school)
	vector<int>	visited(N, 0);						// 1: visited, 0: not yet
	vector<int>	dt(N, -1);							// dynamic table for connecting new school
	int pivot = 0;									// pivot school to update dynamic table
	int minIndex = 0;								// next candidate pivot school index
	int mindis = 0;									// min value in dynamic table
	int sum = 0;									// total distance in minimum spanning tree

	// enter the type of school
	for (int i = 0; i < N; i++) {
		cin >> school[i];	
	}
	
	// enter the road between schools
	for (int i = 0; i < M; i++) {
		int school1 = 0;
		int school2 = 0;
		int distance = 0;

		cin >> school1 >> school2 >> distance;

		// unable to connect same type of schools
		if (school[school1 - 1] != school[school2 - 1]) {
			adjacentSchool s1(school2-1, distance);
			adjacentSchool s2(school1-1, distance);

			edgeList[school1 - 1].push_back(s1);
			edgeList[school2 - 1].push_back(s2);
		}
	}

	// get the minimum spanning tree
	int temp = N-1;
	while(temp--){
		// update visited school
		visited[pivot] = 1;

		// update dynamic table
		list<adjacentSchool>::iterator it = edgeList[pivot].begin();
		while (it!=edgeList[pivot].end()) {
			if (dt[(*it).index] > (*it).distance || dt[(*it).index] < 0)
				dt[(*it).index] = (*it).distance;
			it++;
		}

		mindis = -1;
		// find next school to visit
		for (int i = 0; i < N; i++) {
			if (!visited[i]) {
				if ((mindis<0 || mindis>dt[i]) && dt[i]>0) {
					minIndex = i;
					mindis = dt[i];
				}
			}
		}

		// a case where all schools can't be connected
		if (pivot == minIndex) {
			sum = -1;
			break;
		}

		pivot = minIndex;
		sum += mindis;
	}

	cout << sum << endl;

}