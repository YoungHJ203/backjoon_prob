#include<iostream>
#include<list>
#include<iterator>
#include<map>

using namespace std;

template<class T>
class treeNode {
public:
	treeNode(treeNode* parent= nullptr, treeNode* root=nullptr) {
		this->root = root;
		this->parent = parent;
		this->child = new list<treeNode*>(0, 0);
	}

	~treeNode(){
		delete this->child;
	}

	void setRoot(treeNode* root) {
		this->root = root;
	}

	treeNode* getRoot() {
		return this->root;
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
	treeNode* root;			// back link to root node
	treeNode* parent;
	list<treeNode*> child;
};

template<class T>
class tree {
public:
	tree(treeNode* root = nullptr) {
		this->root = root;
	}

	bool hasRoot() {
		if (this->root != nullptr) {
			return false;
		}
		else {
			return ture;
		}
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
	treeNode* root;
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

		cin >> h >> v >> num;
		
		list<point*> cab(0);

		// enter all cabbage's position
		for (int j = 0; j < num; j++) {
			int x = 0, y = 0;
			
			cin >> x >> y;

			point* cabbage = new point(x, y);

			cab.push_back(cabbage);
		}

		map<int, treeNode<point>> checked;

		// until there's no point in the list
		while (cab.size()) {
			// pop out the cabbage
			point* ref = *(cab.begin());
			cab.pop_front();

			list<treeNode<point>*> toCheck;

			// check the near point
			for (int k = 0; k < 2; k++) {
				for (int k2 = 0; k2 < 2;  k2++) {
				
				}
			}


			// check the set of those point near the reference point



			// update the previous set and set number
		}

		// print the number of set


	}

}