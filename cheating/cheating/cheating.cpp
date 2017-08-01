#include<iostream>
#include<vector>
#include<map>
#include<set>
using namespace std;

void makeSet(vector<vector<bool>>&, set<int>&, map<int, set<int>>&, map<int, int>&, int, int, int);
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
		for (int j = 0; j < 2; j++) {
			set<int> studentSet;
			
			makeSet(room, studentSet, present, presentDT,i, j, 0);
		}

		
		// update dynamic table
		if (i != 0) {
			map<int,set<int>>::iterator it= present.begin();
			while (it!=present.end()) {
				int studentNum = it->second.size();
				map<int, set<int>>::iterator pastIt = past.begin();

				while(pastIt!=past.end()){
					set<int>::iterator presentIt = it->second.begin();
					while (presentIt != it->second.end()) {
						if (pastIt->second.find(*presentIt - 1) != pastIt->second.end() || pastIt->second.find(*presentIt + 1) != pastIt->second.end()) {
							break;
						}

						presentIt++;
					}

					if (presentIt == it->second.end()) {
						presentDT[it->first] = max(studentNum+pastDT[pastIt->first],presentDT[it->first]);
						maxStudent = max(maxStudent, presentDT[it->first]);
					}

					pastIt++;
				}
				
				it++;
			}
		}
		else {
			map<int, int>::iterator it = presentDT.begin();

			while (it != presentDT.end()) {
				maxStudent = max(maxStudent, it->second);
				it++;
			}
		}
		past = present;
		pastDT = presentDT;
		present.clear();
		presentDT.clear();

	}

	return maxStudent;

}

int max(int a, int b) {
	if (a > b) {
		return a;
	}
	
	return b;
}

void makeSet(vector<vector<bool>> &room, set<int> &studentSet, map<int,set<int>> &present, map<int,int> &presentDT,int row,int current,int interval) {
	int flag = 0;

	current = current + interval;

	if (room[row][current] != false) {
		studentSet.insert(current);
		flag = 1;
	}

	if (current + 2 < room[0].size()) {
		makeSet(room,studentSet,present, presentDT,row,current, 2);

		if (current + 3 < room[0].size()) {
			makeSet(room, studentSet, present, presentDT,row, current, 3);
		}
	}
	else {
		int key = 0;

		set<int>::iterator setIt = studentSet.begin();
		while (setIt!=studentSet.end()) {
			key = key | (1 << *setIt);

			setIt++;
		}
		
		present[key] = studentSet;
		presentDT[key] = studentSet.size();
	}

	if (flag == 1 ) {
		studentSet.erase(current);
	}
}