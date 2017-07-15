#include<iostream>
#include<cstdbool>
#include<list>
#include<iterator>
#include<map>

using namespace std;

class point {
public:
	point(int x = 0, int y = 0) {
		this->x = x;
		this->y = y;
	}

	~point() {}

	int x;
	int y;
};

template<class T>
class treeNode {
public:
	treeNode(treeNode<T>* parent = nullptr, T& ele = NULL) {
		this->parent = parent;
		this->ele.x = ele.x;
		this->ele.y = ele.y;
	}

	~treeNode(){
		delete this->child;
	}

	void setEle(T& ele) {
		this->ele = ele;
	}

	T& getEle() {
		return ele;
	}

	void setParent(treeNode<T>* parent) {
		this->parent = parent;
	}

	treeNode<T>* getParent() {
		return this->parent;
	}

	void addChild(treeNode<T>* child) {
		this->child.push_back(child);
	}

	void deleteChild(treeNode<T>* child) {
		iterator<list<treeNode<T>*>> childNode = this->child.begin();

		while (childNode != this->child.end()) {
			if (child == childNode) {
				this->child.erase(childNode);
			}
			childNode++;
		}
	}

	list<treeNode<T>*>& getChild() {
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
	treeNode<T>* parent;
	list<treeNode<T>*> child;
};

template<class T>
class tree {
public:
	static treeNode<T>* getRoot(treeNode<T>* ref) {
		while (ref->getParent()!=nullptr) {
			ref = ref->getParent();
		}

		return ref;
	}
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

		// until there's no point that isn't included in a set
		while (cab.size()) {
			// pop out the cabbage
			point* ref = *(cab.begin());
			cab.pop_front();
			double key = ref->x * 100 + ref->y;

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
					list<treeNode<point>*>::iterator it = toCheck.begin();

					while (it!= toCheck.end()) {
						if (tree<point>::getRoot(*it) == tree<point>::getRoot(checked[p])) {
							break;
						}
							it++;
					}

					if (it == toCheck.end()) {
						toCheck.push_back(checked[p]);
					}
				}				
				
			}
			

			if (!toCheck.empty()) {
				treeNode<point>* standard = *(toCheck.begin());
				list<treeNode<point>*>::iterator it = toCheck.begin();

				it++;

				standard = tree<point>::getRoot(standard);

				while (it!=toCheck.end()) {
					tree<point>::getRoot(*it)->setParent(standard);

					it++;
				}

				treeNode<point>* newNode = new treeNode<point>(standard,*ref);

				checked[key]= newNode;

				setNum = setNum + 1 - (int)toCheck.size();
			}
			else {
				treeNode<point>* newNode = new treeNode<point>(nullptr, *ref);

				checked[key] = newNode;

				setNum++;
			}

		}

		// print the number of set
		cout << setNum<<endl;
	}

}