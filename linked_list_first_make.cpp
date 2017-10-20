#include <iostream>
using namespace std;

class Chain;

class ChainNode{
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
	Chain() { first = new ChainNode; first->link = NULL;  }
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
	ChainNode* t = this->first;
	for (; t->link != NULL;) {
		cout << "kk";
		ChainNode* temp = new ChainNode;
		cout << "t" << t << endl;
		temp = t;
		cout << "temp" << temp << endl;
		t = t->link;
		cout << "t" << t << endl;
		
		cout << "yan\n";  
	}
	delete t;
	cout << "fdsfsfsfd";
	//else { cout << "You CAN'T DELETE THE HEADER NODE"; }

}

int Chain::length() {
	int count = 1;
	for (ChainNode* pointer = first->link; pointer != NULL; count++) { pointer = pointer->link; };
	cout <<  count;
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