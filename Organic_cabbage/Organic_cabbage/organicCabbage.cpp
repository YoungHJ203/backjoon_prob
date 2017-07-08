#include<iostream>
#include<list>
#include<iterator>
#include<map>

using namespace std;

template<class T>
class treeNode {
public:
	treeNode(treeNode* parent= nullptr, T ele = 0) {
		this->parent = parent;
		this->child = new list<treeNode*>(0, 0);
		this->ele = ele;
	}

	~treeNode(){
		delete this->child;
	}

	void setEle(T ele) {
		this->ele = ele;
	}

	T getEle() {
		return ele;
	}

	void setParent(treeNode* parent) {
		this->parent = parent;
	}

	treeNode* getParent() {
		return this->parent;
	}

	void addChild(treeNode* child) {
		this->child.push_back(child);
	}

	void deleteChild(treeNode* child) {
		iterator<list<treeNode*>> childNode = this->child.begin();

		while (childNode != this->child.end()) {
			if (child == childNode) {
				this->child.erase(childNode);
			}
			childNode++;
		}
	}

	&list<treeNode*> getChild() {
		return this->child;
	}
	
	bool hasChild() {
		if (this->child.size() == 0) {
			return false;
		}
		else {
			return true;
		}
	}

	bool isLeaf() {
		if (hasChild()) {
			return false;
		}
		else {
			return true;
		}
	}

private:	
	T ele;					// element of tree
	treeNode* parent;
	list<treeNode*> child;
};

template<class T>
class tree {
public:
	tree(T ele = 0) {
		this->root->ele = ele;
	}

	void setRoot(treeNode* root) {
		this->root = root;
	}


	treeNode* getRoot(treeNode* ref) {
		while (ref->getParent()!=nullptr) {
			ref = ref->getParent();
		}

		return ref;
	}


private:
	treeNode root;
};

class point {
public:
	point() {
		this->x = 0;
		this->y = 0;
	}

	point(int x = 0, int y = 0) {
		this->x = x;
		this->y = y;
	}

	~point() {}

	int x;
	int y;
};

int main() {
	
	int testCase = 0;

	cin >> testCase;

	for (int i = 0; i < testCase; i++) {
		int h = 0, v=0;		// horizontal, vertical length of the farm
		int num = 0;		// number of cabbages in the farm
		int setNum = 0;		// numeber of set

		cin >> h >> v >> num;
		
		list<point*> cab(0);

		// enter all cabbage's position
		for (int j = 0; j < num; j++) {
			int x = 0, y = 0;
			
			cin >> x >> y;

			point* cabbage = new point(x, y);

			cab.push_back(cabbage);
		}

		map<double, treeNode<point>* > checked;

		// until there's no point that isn't in a set
		while (cab.size()) {
			// pop out the cabbage
			point* ref = *(cab.begin());
			cab.pop_front();

			list<treeNode<point>*> toCheck;	// points near an reference point

			
			// check the near point
			for (int k = 0; k < 4; k++) {
				double p = 0 ;
					
				switch (k)
				{
					case 0: {	p = (ref->x - 1) * 100 + ref->y;	break; }
					case 1: {	p = (ref->x + 1) * 100 + ref->y;	break; }
					case 2: {	p = ref->x * 100 + (ref->y-1);		break; }
					case 3: {	p = ref->x * 100 + (ref->y+1);		break; }
					default:	break;
				}

				if (checked[p]) {
					toCheck.push_back(checked[p]);
				}				
				
			}


			// check the set of those point near the reference point
			if (toCheck.empty()) {
				// make a new set
				tree* temp

			}
			else {
				// check if any two points are in one set

				// 
			}



			// update the previous set and set number
		}

		// print the number of set


	}

}