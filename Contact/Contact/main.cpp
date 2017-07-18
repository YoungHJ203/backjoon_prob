#include<iostream>
#include<string>
#include<cstdbool>

using namespace std;

bool codeBreaking(string&);

int main() {

	int testCase=0;

	cin.clear();
	cin >> testCase;

	for (int i = 0; i < testCase; i++) {
		char c = 0;
		string code;

		if(i==0)
			cin.ignore(1,'\n');
		getline(cin, code);

		if (codeBreaking(code))
			cout << "YES" << endl;
		else
			cout << "NO" << endl;

		code.clear();
	}
}

bool codeBreaking(string& code) {
	int i = 0;
	int codeSize = code.size();

	while(i < codeSize){
		if (code[i] == '0' && code[i+1]=='1') {
			i = i + 2;
		}
		else if(code[i]=='1' && code[i+1]=='0'){
			i = i + 2;

			int count = 0;

			while (code[i]=='0') {
				i++;
				count++;
			}

			if (count == 0) {
				return false;
			}

			count = 0;

			while (code[i]=='1') {
				i++;
				count++;
			}

			if (i + 1 < codeSize) {
				if (code[i + 1] == '0') {
					i--;
					count--;
				}
			}

			if (count == 0) {
				return false;
			}
		}
		else {
			return false;
		}
	}

	if (i > 0)
		return true;
	else
		return false;
}