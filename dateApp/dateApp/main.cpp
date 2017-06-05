#include<iostream>
#include<vector>
#include<list>
#include<iterator>

using namespace std;

// set of adjacent school index and distance
class Pair {
public:
	Pair() {
		index = 0;
		distance = 0;
	}

	Pair(int index,int distance) {
		this->index = index;
		this->distance = distance;
	}

	int index;
	int distance;
};

int main() {
	
	int N = 0;					// total number of school
	int M = 0;					// the number of roads

	cin >> N >> M;

	vector<char> school(N);							// type of school
	vector<list<Pair>> edgelist(N,list<Pair> (0));	// edge list
	vector<int>	dt(N,-1);							// dynamic table for minimum spanning tree
	vector<int> visited(N, 0);							// check if the school is visited
	int sum = 0;									// total sum of distances
	int pivot = 0;									// index of school which has shortest distance to spanning tree
	int min = -1;									// minimum distance to spanning tree

	// enter the type of schools
	for (int i = 0; i < N; i++) {
		cin >> school[i];
	}
	
	// enter the roads
	for (int i = 0; i < M; i++) {
		int index1 = 0;
		int index2 = 0;
		int dis = 0;

		cin >> index1 >> index2 >> dis;

		if (school[index1-1] != school[index2-1]) {
			Pair temp1(index1-1, dis);
			Pair temp2(index2-1, dis);

			edgelist[index1-1].push_back(temp2);
			edgelist[index2-1].push_back(temp1);
		}
	}

	// initialize dynamic table
	list<Pair>::iterator it = edgelist[0].begin();
	visited[0] = 1;

	while (it != edgelist[0].end()) {
		dt[(*it).index] = (*it).distance;
		if (min<0 || min>dt[(*it).index]) {
			min = dt[(*it).index];
			pivot = (*it).index;
		}
		it++;		
	}

	visited[pivot] = 1;
	sum += min;

	// find shortest school that is connected to spanning tree
	int count = N-1;
	int temp = 0;
	while (--count) {
		
		it = edgelist[pivot].begin();

		while (it != edgelist[pivot].end()) {
			if(dt[(*it).index]<0 || dt[(*it).index]>(*it).distance)
				dt[(*it).index] = (*it).distance;
			it++;
		}

		min = -1;
		for (int i = 0; i < N; i++) {
			if (!visited[i]) {
				if (min > dt[i] && dt[i]>0 || min<0) {
					min = dt[i];
					temp = i;
				}
			}
		}

		sum += min;
		if (pivot == temp) {
			cout << -1 << endl;
		}
		pivot = temp;
		visited[pivot] = 1;
	}

	cout << sum << endl;
}