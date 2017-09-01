#include<iostream>
#include<vector>
#include<map>
#include<set>
using namespace std;

void makeSet(vector<vector<bool>>&,map<int, set<int>>&, map<int, int> &,set<int>&,int,int,int);
int getKey(set<int>&);
int arrangeStudent(vector<vector<bool>>&);
int max(int, int );
bool checkIndependent(map<int, set<int>>&, set<int>&);
int checkIndependent(map<int, set<int>>&,int);

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
			makeSet(room, present, presentDT,studentSet, i, j, 0);
		}

		// update dynamic table
		if (i != 0) {
			map<int,set<int>>::iterator it= present.begin();
			while (it!=present.end()) {
				int compareNum = past.size();
				map<int, set<int>>::iterator pastIt = past.begin();
				int studentNum = presentDT[it->first];

				while(pastIt!=past.end()){
					set<int> temp = it->second;

					set<int>::iterator tempIt = temp.begin();
					while (tempIt != temp.end()) {
						if (pastIt->second.find((*tempIt) - 1) != pastIt->second.end() || pastIt->second.find((*tempIt) + 1) != pastIt->second.end()) {
							break;
						}
						tempIt++;
					}

					if (tempIt == temp.end()) {
						presentDT[it->first] = max(studentNum+pastDT[pastIt->first],presentDT[it->first]);
						maxStudent = max(maxStudent, presentDT[it->first]);
					}

					pastIt++;
				}
				
				it++;
			}
		}
		else {
			map<int, int>::iterator tempIt = presentDT.begin();
			while (tempIt != presentDT.end()) {
				maxStudent = max(maxStudent, tempIt->second);
				tempIt++;
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

void makeSet(vector<vector<bool>> &room,map<int, set<int>> &present, map<int,int> &presentDT,set<int> &studentSet, int row,int current, int interval) {
	int size = room[0].size();
	
	current = current + interval;

	if (room[row][current] != false) {
		studentSet.insert(current);
	}

	if (current + 2 < size) {
	
		makeSet(room, present, presentDT, studentSet, row, current, 2);

		if (current + 3 < size) {
			makeSet(room, present, presentDT, studentSet, row, current, 3);
		}
		
	}
	else {
		int key = getKey(studentSet);
		int flag = 0;
		
		flag=checkIndependent(present, key);

		switch (flag)
		{
			case 0: {present[key] = studentSet; 
				presentDT[key] = studentSet.size();
				break; }
			case -1: {	break; }
			default: {	present.erase(flag);
						presentDT.erase(flag);
						present[key] = studentSet;
						presentDT[key] = studentSet.size();
				break; }
		}
	}

	if (room[row][current] != false) {
		studentSet.erase(current);
	}

}

int getKey(set<int> &studentSet) {
	int key = 0;

	set<int>::iterator setIt = studentSet.begin();

	while (setIt != studentSet.end()) {
		key = key | (1 << (*setIt));
		
		setIt++;
	}

	return key;
}

int checkIndependent(map<int,set<int>> &present,int key) {
	int flag = 0;
	map<int, set<int>>::iterator it = present.begin();

	while (it != present.end()) {
		if ((key & it->first) == key) {
			flag = -1;
			break;
		}
		else if ((key & it->first) == it->first) {
			flag = it->first;
			break;
		}

		it++;
	}

	return flag;
}