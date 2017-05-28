#include<iostream>
#include<vector>

using namespace std;

int min(int,int,int);
int min(int, int);
int dp(int, int, vector<vector<int>>&, int);
void substitution(vector<vector<int>> &);

int main(){
	int testCase;	// the number of test cases

	// get the number of test cases
	cin >> testCase;

	for (int i = 0; i < testCase; i++) {
		int numSec;					// the half number of sections
		int numPlat;				// the number of platoon members
		int minPlat=0;				// minimum number of platoons
		int count=0;				// checking how many cases are possible

		// get the number of sections and number of platoon members
		cin >> numSec >> numPlat;

		vector<vector<int>>	enemy(2,vector<int> (numSec));	// the number of enemy

		// get the number of enemy in an section
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < numSec; k++) {
				cin >> enemy[j][k];
			}
		}

		minPlat=dp(numSec,numPlat,enemy,0);

		if(enemy[0][0]+enemy[0][N-1]<=W){
			minPlat=min(dp(numSec,numPlat,enemy,1),minPlat);
			count++;
		}

		if(enemy[1][0]+enemy[1][N-1]<=W){
			minPlat=min(dp(numSec,numPlat,enemy,2),minPlat);
			count++;
		}

		if(count==2)
			minPlat=min(dp(numSec,numPlat,enemy,3),minPlat);

		cout << minPlat<<endl;
	}
}

int min(int a, int b, int c) {
	int min = a;
	if (min > b) {
		min = b;
	}
	if (min > c) {
		min = c;
	}

	return min;
}

int min(int a, int b) {
	return (a > b ? b : a);
}

// dynamic programming for counting minimum number of platoons
int dp(int N, int W, vector<vector<int>> &enemy, int checking){
		vector<vector<int>> dt(2,vector<int>(4))={0};				// dynamic table
		int i=0;

		
		// initialization of dynamic table
		switch(checking){
			case 0:{	dt[0][0]=0;	dt[0][1]=1;	dt[0][2]=1;	dt[0][3]=(enemy[0][i]+enemy[1][i]<=W?1:2);
						break;}
			default:{	dt[0][0]=0;	dt[0][1]=1;	dt[0][2]=1;	dt[0][3]=2;
						break;}

		}

		// counting the number of platoons through second column until column before last one
		for(i=1;i<N-1;i++){
				dt[1][0]=dt[0][3];

				if(i!=1 || (checking!=1 && checking!=3))
					dt[1][1]=min(dt[0][2]+(enemy[0][i-1]+enemy[0][i]<=W?1:2),dt[1][0]+1);
				else
					dt[1][1]=dt[1][0]+1;

				if(i!=1 || (checking!=2 && checking!=3))
					dt[1][2]=min(dt[0][1]+(enemy[1][i-1]+enemy[1][i]<=W?1:2),dt[1][0]+1);
				else
					dt[1][2]=dt[1][0]+1;


				dt[1][3]=min(dt[1][0]+(enemy[0][i]+enemy[1][i]<=W?1:2),dt[1][1]+1,dt[1][2]+1);

				if(i!=1 || (checking!=1 && checking!=2 && checking!=3))
					dt[1][3]=min(dt[1][3],dt[1][1]+(enemy[1][i-1]+enemy[1][i]<=W?1:2));

				// rearrange dynamic table
				substitution(dt);
		}

		if(i==N-1){
			// counting the number of platoons in last column
			switch(checking){
				case 0:{	dt[1][0]=dt[0][3];
							dt[1][1]=min(dt[0][2]+(enemy[0][i-1]+enemy[0][i]<=W?1:2),dt[1][0]+1);
							dt[1][2]=min(dt[0][1]+(enemy[1][i-1]+enemy[1][i]<=W?1:2),dt[1][0]+1);
							dt[1][3]=min(dt[1][0]+(enemy[0][i]+enemy[1][i]<=W?1:2),dt[1][1]+(enemy[1][i-1]+enemy[1][i]<=W?1:2),dt[1][2]+1);
							return dt[1][3];}
				case 1:{	return min(dt[0][1]+(enemy[1][i-1]+enemy[1][i]<=W?1:2),dt[0][3]+1);}
				case 2:{	return min(dt[0][2]+(enemy[0][i-1]+enemy[0][i]<=W?1:2),dt[0][3]+1);}
				case 3:{	return dt[0][3];}

			}
		}			
}

// rearrange dynamic table
void substitution(vector<vector<int> &v){
	for(int i =0;i<v[0].size();i++){
		v[0][i]=v[1][i];
	}
}