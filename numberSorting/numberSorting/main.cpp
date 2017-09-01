#include<iostream>
#include<vector>

using namespace std;


template<class T, class S>
class Pair {
public:
	T order;
	S num;

	Pair() {}
};

void mergeSort(vector<Pair<int, Pair<int, int>>>&, int, int, int);

int main() {
	int size = 0;

	cin >> size;

	vector<Pair<int, Pair<int, int>>> numArray(size);

	for (int i = 0; i < size; i++) {
		int temp = 0;
		Pair<int, int> temp2;
		temp2.order = i;
		temp2.num = 0;

		cin >> temp;

		temp2.num = temp;

		numArray[i].order = 0;
		numArray[i].num = temp2;
	}

	// sorting according to the number entered
	mergeSort(numArray, 0, size - 1, 0);

	for (int i = 0; i < size; i++) {
		numArray[i].order = i;
	}

	mergeSort(numArray, 0, size - 1, 1);

	for (int i = 0; i < size; i++) { 
		cout << numArray[i].order << " ";
	}

	cout << endl;
}

void mergeSort(vector<Pair<int,Pair<int,int>>> &tempArray, int first, int last, int typeOfCase) {
	if (first < last) {
		int size = last - first + 1;
		int mid = (first + last) / 2;
		int index = first;

		if (first < mid) 
			mergeSort(tempArray, first, mid, typeOfCase);
		if (mid + 1 < last)
			mergeSort(tempArray, mid+1, last, typeOfCase);

		int leftSize = mid - first+1;
		int rightSize = last - mid;

		vector<Pair<int, Pair<int, int>>> left(leftSize);
		vector<Pair<int, Pair<int, int>>> right(rightSize);

		for (int i = 0; i < leftSize; i++) {
			left[i] = tempArray[index + i];
		}

		for (int i = 0; i < rightSize; i++) {
			right[i] = tempArray[index + leftSize + i];
		}

		int leftIndex = 0;
		int rightIndex = 0;

		while(leftIndex!=leftSize && rightIndex!=rightSize){
			if (typeOfCase == 0) {
				if (left[leftIndex].num.num <= right[rightIndex].num.num) {
					tempArray[index] = left[leftIndex];
					leftIndex++;
				}
				else {
					tempArray[index] = right[rightIndex];
					rightIndex++;
				}

				index++;
			}
			else {
				if (left[leftIndex].num.order <= right[rightIndex].num.order) {
					tempArray[index] = left[leftIndex];
					leftIndex++;
				}
				else {
					tempArray[index] = right[rightIndex];
					rightIndex++;
				}

				index++;
			}
		}

		if (leftIndex == leftSize) {
			while (rightIndex != rightSize) {
				tempArray[index] = right[rightIndex];
				rightIndex++;
				index++;
			}
		}
		else {
			while (leftIndex != leftSize) {
				tempArray[index] = left[leftIndex];
				leftIndex++;
				index++;
			}
		}
	}
}