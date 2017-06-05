#include<iostream>
#include<vector>
#include<list>
#include<iterator>

using namespace std;

void dfs(int, vector<list<int>>&, vector<int>&, int&);

int main() {
	int N = 0, M = 0;	

	// enter the number of students and squences
	cin >> N >> M;

	vector<list<int>> inEdgeList(N, list<int>(0));		// ingoing edge list
	vector<list<int>> outEdgeList(N, list<int>(0));		// outgoing edge list
	int count = 0;										// number of people who knows order of heights

	// enter the number of sequences
	for (int i = 0; i < M; i++) {
		int first = 0;
		int second = 0;

		cin >> first >> second;

		inEdgeList[second - 1].push_back(first - 1);
		outEdgeList[first - 1].push_back(second - 1);
	}

	// count the number of people who knows order
	for (int i = 0; i < N; i++) {
		int num = 0;				// number of people who is exactly positioned about i th person
		vector<int>	visited(N,0);		// vector of visited vector

		dfs(i, inEdgeList, visited, num);
		dfs(i, outEdgeList, visited, num);

		if (num == N - 1) {
			count++;
		}
	}

	cout << count << endl;
}

// depth first search
void dfs(int index,vector<list<int>> &edgeList,vector<int>& visited,int &num) {
	if (edgeList[index].size() != 0) {

		list<int>::iterator it = edgeList[index].begin();
		while (it!=edgeList[index].end()) {			
			if (!visited[*it]) {
				dfs(*it, edgeList, visited, num);
				num++;
				visited[*it] = 1;
			}

			it++;
		}
	}
}