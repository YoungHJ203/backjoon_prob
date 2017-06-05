#include<iostream>
#include<vector>
#include<list>
#include<iterator>
<<<<<<< HEAD

using namespace std;

// set of adjacent school index and distance
class Pair {
public:
	Pair() {
		index = 0;
		distance = 0;
	}

	Pair(int index,int distance) {
=======
using namespace std;

class adjacentSchool{
public:
	adjacentSchool(int index = 0, int distance = 0) {
>>>>>>> refs/remotes/origin/master
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
	
<<<<<<< HEAD
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
=======
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
>>>>>>> refs/remotes/origin/master
				dt[(*it).index] = (*it).distance;
			it++;
		}

<<<<<<< HEAD
		min = -1;
		for (int i = 0; i < N; i++) {
			if (!visited[i]) {
				if (min > dt[i] && dt[i]>0 || min<0) {
					min = dt[i];
					temp = i;
=======
		mindis = -1;
		// find next school to visit
		for (int i = 0; i < N; i++) {
			if (!visited[i]) {
				if ((mindis<0 || mindis>dt[i]) && dt[i]>0) {
					minIndex = i;
					mindis = dt[i];
>>>>>>> refs/remotes/origin/master
				}
			}
		}

<<<<<<< HEAD
		sum += min;
		if (pivot == temp) {
			cout << -1 << endl;
		}
		pivot = temp;
		visited[pivot] = 1;
	}
=======
		// a case where all schools can't be connected
		if (pivot == minIndex) {
			sum = -1;
			break;
		}

		pivot = minIndex;
		sum += mindis;
	}

	cout << sum << endl;
>>>>>>> refs/remotes/origin/master

	cout << sum << endl;
}