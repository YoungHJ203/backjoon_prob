#include<iostream>
#include<cstdlib>
#include<vector>
#include<iterator>
#include<string>
#include<map>

using namespace std;

// Node in line
class lineNode {
public:
	lineNode() {
		this->positionValue = 0;
		this->prev = nullptr;
		this->next = nullptr;
		this->x = 0;
		this->y = 0;
		this->otherLine = nullptr;
	}

	lineNode(int positionValue, int x, int y, lineNode* prev = nullptr, lineNode* next = nullptr,lineNode* p=nullptr) {
		this->positionValue = positionValue;
		this->prev = prev;
		this->next = next;
		this->x = x;
		this->y = y;
		this->otherLine = p;
	}

	~lineNode() {}

	int x;
	int y;
	lineNode* otherLine;
	lineNode* prev;
	lineNode* next;
	int positionValue;
};

// Node list in line
class Llist {
public:
	Llist(int positionValue = 0, int x = 0, int y = 0, lineNode* otherLine=nullptr) {
		this->header = new lineNode(positionValue, x, y, nullptr, nullptr,otherLine);
		this->trailer = new lineNode(positionValue, x, y, nullptr, nullptr, otherLine);

		this->header->next = this->trailer;
		this->trailer->prev = this->header;
		this->size = 0;
	}

	// push a new point in the last of list
	void push_back(lineNode& p) {
		p.prev = this->trailer->prev;
		p.next = this->trailer;

		p.prev->next = &p;
		p.next->prev = &p;
		this->size++;
	}

	// extract the specific node, not delete
	void extract(lineNode& ref) {
		ref.prev->next = ref.next;
		ref.next->prev = ref.prev;

		this->size--;
	}

	// delete the node from the list
	void delNode(lineNode& ref) {
		ref.prev->next = ref.next;
		ref.next->prev = ref.prev;

		ref.otherLine->prev->next = ref.otherLine->next;
		ref.otherLine->next->prev = ref.otherLine->prev;

		ref.~lineNode();

		this->size--;
	}

	lineNode* header;
	lineNode* trailer;
	int size;
};

void sorting(Llist&);
void mergeSort(vector<lineNode*>&, int, int);

int main() {
	int N = 0, K = 0;
	string str;
	map<int, Llist> minusPoint;		// points in 'x-y=k' line
	map<int, Llist> plusPoint;		// points in 'x+y=k' line
	lineNode* current = nullptr;	// current point in that frog princess is
	int flag = 0;					// indicates that the current node is in minus line ;0  or plus line ;1

	cin >> N >> K;

	// get the command
	for (int i = 0; i < K; i++) {
		char c;

		cin >> c;

		str.push_back(c);
	}

	// get the coordinate of points
	for (int i = 0; i < N; i++) {
		int x = 0, y = 0;

		cin >> x >> y;

		lineNode* minus = new lineNode(x - y,x,y);
		lineNode* plus = new lineNode(x + y, x, y);
		
		// starting point
		if (i == 0) {
			current = minus;
		}

		minus->otherLine = plus;
		plus->otherLine = minus;

		// put the node in each node list
		map<int, Llist>::iterator it = minusPoint.find(x - y);
		// in the case that (x-y) is already in the list
		if (it != minusPoint.end()) {
			(*it).second.push_back(*minus);
		}
		// the other case
		else {
			Llist* pointLine = new Llist(x - y,x,y);
			minusPoint[x - y] = *pointLine;
			minusPoint[x - y].push_back(*minus);
		}

		it = plusPoint.find(x + y);
		// in the case that (x+y) is already in the list
		if (it != plusPoint.end()) {
			(*it).second.push_back(*plus);
		}
		// the other case
		else {
			Llist* pointLine = new Llist(x + y,x, y);
			plusPoint[x + y] = *pointLine;
			plusPoint[x + y].push_back(*plus);
		}
	}

	// sorting
	map<int, Llist>::iterator it = minusPoint.begin();
	while(it!=minusPoint.end()){
		if((*it).second.size > 1)
			sorting((*it).second);
		it++;
	}
	it = plusPoint.begin();
	while (it != plusPoint.end()) {
		if ((*it).second.size != 1)
			sorting((*it).second);
		it++;
	}

	string::iterator command = str.begin();
	// move until there's no command
	while(command!=str.end()){
		switch (*command) {
		case 'A': {		
						// if current node is in minus line
						if (flag == 0) {
							// in the case that movement of 'A' is possible	
							if (current->next->next != nullptr) {
								lineNode* temp = current;
								current = current->next;
								minusPoint[temp->x - temp->y].delNode(*temp);
							}
						}
						else {
							// in the case that movement of 'A' is possible	
							if (current->otherLine->next->next != nullptr) {
								// change the current node position
								current = current->otherLine;
								flag = 0;

								lineNode* temp = current;
								current = current->next;
								minusPoint[temp->x - temp->y].delNode(*temp);
							}
						}
					break; }
		case 'B': { 
						// if current node is in plus line
						if (flag == 1) {
							// in the case that movement of 'B' is possible	
							if (current->next->next != nullptr) {
								lineNode* temp = current;
								current = current->next;
								minusPoint[temp->x - temp->y].delNode(*temp);
							}
						}
						else {
							// in the case that movement of 'B' is possible	
							if (current->otherLine->next->next != nullptr) {
								// change the current node position
								current = current->otherLine;
								flag = 1;

								lineNode* temp = current;
								current = current->next;
								minusPoint[temp->x - temp->y].delNode(*temp);
							}
						}
					break; }
		case 'C': { 
						// if current node is in plus line
						if (flag == 1) {
							// in the case that movement of 'C' is possible	
							if (current->prev->prev != nullptr) {
								lineNode* temp = current;
								current = current->prev;
								minusPoint[temp->x - temp->y].delNode(*temp);
							}
						}
						else {
							// in the case that movement of 'C' is possible	
							if (current->otherLine->prev->prev!= nullptr) {
								// change the current node position
								current = current->otherLine;
								flag = 1;

								lineNode* temp = current;
								current = current->prev;
								minusPoint[temp->x - temp->y].delNode(*temp);
							}
						}
					break; }
		case 'D': { 
						// if current node is in minus line
						if (flag == 0) {
							// in the case that movement of 'C' is possible	
							if (current->prev->prev != nullptr) {
								lineNode* temp = current;
								current = current->prev;
								minusPoint[temp->x - temp->y].delNode(*temp);
							}
						}
						else {
							// in the case that movement of 'C' is possible	
							if (current->otherLine->prev->prev != nullptr) {
								// change the current node position
								current = current->otherLine;
								flag = 0;

								lineNode* temp = current;
								current = current->prev;
								minusPoint[temp->x - temp->y].delNode(*temp);
							}
						}
					break; }
		default: {break; }
		}

		command++;
	}

	cout << current->x << " " << current->y << endl;

}

void sorting(Llist& nodeInLine) {
	int size = nodeInLine.size;
	vector<lineNode*> temp(size);
	lineNode* ref = nodeInLine.header->next;
	int i = 0;

	// copy node in list to array
	while(ref!=nodeInLine.trailer){
		temp[i++] = ref;
		lineNode* secondref = ref;

		ref = ref->next;
		
		nodeInLine.extract(*secondref);
	}

	// mergesort
	mergeSort(temp,0,size-1);

	// recopy array to list
	for (int i = 0; i < size; i++) {
		nodeInLine.push_back(*temp[i]);
	}
}


void mergeSort(vector<lineNode*> &arr, int first, int last) {
	int mid = (first + last) / 2;

	if (first < last) {
		// divide
		mergeSort(arr, first, mid);
		mergeSort(arr, mid+1,last);

		vector<lineNode*> temp(last - first + 1);
		
		int i = first, j = mid + 1, k = 0;
		// merge sort
		while (k != last - first + 1 && i<=mid && j<=last) {
			if (arr[i]->x < arr[j]->x) {
				temp[k++] = arr[i++];
			}
			else {
				temp[k++] = arr[j++];
			}
		}

		if (i > mid) {
			while (j <= last) {
				temp[k++] = arr[j++];
			}
		}
		else if( j > last ){
			while (i <= mid) {
				temp[k++] = arr[i++];
			}
		}

		// recopy
		int index = first;
		for (int i = 0; i < temp.size();i++) {
			arr[index++] = temp[i];
		}
	}
}