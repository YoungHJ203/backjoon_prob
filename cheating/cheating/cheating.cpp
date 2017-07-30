#include<iostream>
#include<vector>
#include<map>
#include<set>
using namespace std;

int arrangeStudent(vector<vector<bool>>&);
int max(int, int );

int main() {

	int testCase=0;

	cin >> testCase;

	for (int i = 0; i < testCase; i++) {
		int N = 0,M = 0;

		// enter a row and column of class room
		cin >> N >> M;

		// status of room
		vector<vector<bool>> room(N, vector<bool>(M, false));

		// enter each state of the seat in the class room
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < M; k++) {
				char c = 0;
				cin >> c;

				if (c == '.') {
					room[j][k] = true;
				}
				else if (c == 'x') {
					room[j][k] = false;
				}
			}
		}
		
		
		// get the maximum number of students in a classroom who aren't able to cheat
		int students = arrangeStudent(room);

		cout << students << endl;
	}	
}

int arrangeStudent(vector<vector<bool>>& room) {
	int row = room.size();
	int col = room[0].size();
	int num = 0;
	map<int, set<int>> past;
	map<int, set<int>> present;
	map<int, int> pastDT;
	map<int, int> presentDT;
	int maxStudent = 0;

	for (int i = 0; i < row;i++) {
		int ref = 0;
		int num2 = 0;
		int key = 0;
		num = (col - 1) / 2;

		// find max independant sets
		while (num >= 0) {
			set<int> studentSet;
			int ini = 0;

			while (ini+2*num+3*num2<col) {
				ref = ini;

				for (int j = -1; j < num; j++) {
					if (room[i][ref] != false) {
						studentSet.insert(ref);

						if (ref != 0)
							key = key*ceil(ref) + ref;
					}
					ref += 2;
				}
				ref += 3;
				for (int k = 0; k < num2; k++) {
					if (room[i][ref] != false) {
						studentSet.insert(ref);

						if (ref != 0)
							key = key*ceil(ref) + ref;
						else
							key = key*ceil(ref + 1);
					}
					ref += 3;
				}

				if (present.find(key) == present.end()) {
					present[key] = studentSet;
					presentDT[key] = studentSet.size();
				}

				ini++;
			}
			

			num2++;
			while (1+num*2+3*num2>col) {
				num--;
			}
		}

		// update dynamic table
		if (i != 0) {
			map<int,set<int>>::iterator it= present.begin();
			while (it!=present.end()) {
				int compareNum = past.size();
				map<int, set<int>>::iterator pastIt = past.begin();

				while(pastIt!=past.end()){
					set<int> temp = it->second;

					set<int>::iterator tempIt = temp.begin();
					while (tempIt != temp.end()) {
						if (pastIt->second.find(*tempIt - 1) != pastIt->second.end() || pastIt->second.find(*tempIt + 1) != pastIt->second.end()) {
							break;
						}

						tempIt++;
					}

					if (tempIt == temp.end()) {
						presentDT[it->first] = max(presentDT[it->first]+pastDT[pastIt->first],presentDT[it->first]);
						maxStudent = max(maxStudent, presentDT[it->first]);
					}

					pastIt++;
				}
				
				it++;
			}
		}

		past = present;
	}

	return maxStudent;

}

int max(int a, int b) {
	if (a > b) {
		return a;
	}
	
	return b;
}