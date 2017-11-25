#include<iostream>
using namespace std;


// listnode 盡量不要寫destructor 因為通常會手動幫忙delete, this is very important!!!!
class listnode {
private:
    listnode* link;
    int value;
public:
    friend class Stack;
    listnode(int x) {
        link = NULL;
        value = x;
    }
    listnode() {
        link = NULL;
        value = 0;
    }
    //~listnode(){
    //   cout << "destrcutor of listnode\n";
    //    delete link;
    //}
    listnode(const listnode& l) {
        this->link = l.link;
        this->value = l.value;
        cout << "copy constructor!\n";
    }
};



class Stack {
private:
    listnode* first;
public:
    Stack(int x) {
        first = new listnode(x); // this definitely will use copy constructor
    }
    ~Stack() {
        cout << "destructor of List\n";
        for (listnode* i = first; i != NULL; i = i->link) {
            listnode* tmp = i;
            delete tmp;
        }
    }
    Stack (const Stack& l) {
        cout << "copy constructor of List\n";
        this->first = l.first;
    }
    void traverse();
    void PUSH(int x) {
        listnode* tmp = first;
        first = new listnode(x);
        first->link = tmp;
    }
    void length() {
        int count = 0;
        for (listnode* i = first; i != NULL; i = i->link) {count++;}
        cout << "lengh is " << count << endl;
    }
    void inverse();
    int Delete();
    void PUSH() {
        listnode* tmp = first;
        first = new listnode(3);
        first->link = tmp;
    }
};

void Stack::traverse() {
    for (listnode* i = first; i != NULL; i = i->link) {
        cout << i->value << " ";
    }

    
}


int Stack::Delete() {
    
        listnode* tmp = first;
        static int ss = tmp->value;
        if (first ->link == NULL)
            first->link = new listnode(5);
        first = first->link;
        delete tmp;
        return ss;
    
}

void Stack::inverse() {
    
    listnode* previous = this->first;
    listnode* current;
    listnode* future;
    // initialization
    current = previous;
    future = current->link;
    while(1) {
        if (previous == first) { // B.C base case
            previous = new listnode(first->value);
        }
        else previous = current;
        current = future;
        future = current->link;
        current->link = previous;
        if (future == NULL) break; // B.C boundary condition
    }
    first = current;
}




int main() {
    
    Stack l(5);
    l.PUSH(4);
    l.PUSH(6);
    l.length();
    l.traverse();
    
    l.inverse();
    l.length();
    l.traverse();
    l.length();
    
  //  l.Delete(1);
    cout << "yes" << endl;
    
    l.length();
    l.PUSH();
    l.length();
    l.traverse();
    l.PUSH();
    l.traverse();
    l.length();
    cout << "delete is " << l.Delete() << endl;
    l.traverse();
     l.length();
    l.PUSH(10);
    l.length();
    
    return 0;
    
}

