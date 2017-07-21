#include<iostream>
#include<vector>
#include<map>
using namespace std;

int arrangeStudent(vector<vector<bool>>&);

int main() {

	int testCase=0;

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
	int num = (col - 1) / 2;

	for (int i = 0; i < row;i++) {
		int ref = 0;
		int num2 = 0;

		// find max independant sets
		while (num >= 0) {
			for (int j = 0; j < num; j++) {
				if (room[i][ref] != false) {
				
				}
					ref += 2;
			}
			ref += 3;
			for (int k = 0; k < num2-1; k++) {
				if (room[i][ref]!=false) {
					
				}
					ref += 3;
			}

			num2++;
			while (1+num*2+3*num2>col) {
				num--;
			}
		}

		// update dynamic table
		if (i != 0) {
			
		}

	}
}