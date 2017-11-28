// DO NOT DELETE THE HEADER NODE, let DESTRUCTOR do that, or you may DELETE TWICE !!!!!

#include<iostream>
using namespace std;

class Chain;

class ChainNode {
private:
	int data;
	ChainNode *link;
public:
	friend class Chain;
	ChainNode() {
		data = 0;
		link = NULL;
	}
	~ChainNode() { delete link; }
	ChainNode(const ChainNode& p) {
		this->data = p.data;
		this->link = new ChainNode(*(p.link));
	}
};

class Chain {
private:
	ChainNode* first;
public:
	Chain() { first = new ChainNode; first->link = NULL; }
	//~Chain() { cout << "destructor of Chain"; delete first; }
	int length();
	void Delete(int x) {
		ChainNode* pointer = first;
		if (x > this->length()) cout << "it's not so long\n";
		else {
			for (int i = 0; i < x; i++) {
				pointer = pointer->link;
			}
			if (pointer == first) { first = new ChainNode; delete pointer; }
			else { delete pointer; }
		}

	}
	void Insert(int x) {
		ChainNode* pointer = first;
		if (x > this->length()) cout << "it's not so long\n";
		// Normal wirte
		else {
			if (pointer->link == NULL) { pointer->link = new ChainNode; }
			else {
				for (int i = 0; i < x; i++) {
					pointer = pointer->link;
				}
				pointer->link = new ChainNode;
				pointer->link->link = NULL;
			}
		}
	}

	void DelteAll();

};

void Chain::DelteAll() {
	ChainNode* t = this->first->link;
	if (t == NULL) { cout << "DO NOT DELETE HEADER NODE"; }
	else {
		for (; t->link != NULL;) {
			ChainNode* temp = new ChainNode;
			temp = t;
			t = t->link;
			delete temp;
		}
	}
	delete t;
}

int Chain::length() {
	int count = 1;
	for (ChainNode* pointer = first->link; pointer != NULL; count++) { pointer = pointer->link; };
	cout << count;
	return count;
}


int main() {
	Chain c;
	ChainNode* p = new ChainNode;
	c.length();
	c.Insert(1);
	cout << "length" << c.length();
	c.DelteAll();
	return 0;
}
