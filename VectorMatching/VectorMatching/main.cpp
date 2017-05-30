#include<iostream>
#include<vector>
#include<iterator>
#include<math.h>

using namespace std;

void recurSearch(vector<vector<double>>&, vector<int>&, int, int, const int&, double&);
void check(vector<vector<double>>&, vector<int>&, double&);

int main(){ 
	int testNum=0;

	// enter the number of test cases
	cin >> testNum;

	for (int i = 0; i < testNum;i++) {
		int pointNum=0;
		double min = -1;

		// enter the number of points
		cin >> pointNum;

		// points
		vector<vector<double>> point(2, vector<double> (pointNum));

		// half set of points
		vector<int> index(pointNum / 2, 0);

		for (int j = 0; j < pointNum; j++) {
			cin >> point[0][j] >> point[1][j];
		}

		// making half sets of points recursively
		recurSearch(point,index,-1,pointNum/2,pointNum,min);
		
		cout << min << endl;
	}

}

// making half sets of points recursively
void recurSearch(vector<vector<double>> &point, vector<int> &index, int now,int count, const int &pointNum, double &min) {
	
	for (int i = now + 1; i < pointNum- count + 1; i++) {

		index[count-1]=i;

		// compare the new set with old set for checking which sets are better
		if (count == 1) {
			check(point, index, min);
		}
		else {
			recurSearch(point, index, i, count--, pointNum,min);
		}
	}
}

// checking which sets are better
void check(vector<vector<double>> &point,vector<int> &index, double &min) {
	double x1 = 0;
	double x2 = 0;
	double y1 = 0;
	double y2 = 0;
	double sum = 0;

	vector<int>::iterator it = index.begin();

	for (int i = 0; i < point.size(); i++) {
		if (it != index.end())
			if (i == *it) {
				x1 += point[0][i];
				y1 += point[1][i];
				it++;
			}
			else {
				x2 += point[0][i];
				y2 += point[1][i];
			}
		else {
			x2 += point[0][i];
			y2 += point[1][i];
		}
	}

	sum = sqrt((x1-x2)*(x1 - x2)+(y1-y2)*(y1 - y2));

	if (min > sum || min < 0) {
		min = sum;
	}
}