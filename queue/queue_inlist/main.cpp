#include<iostream>
using namespace std;


// listnode 盡量不要寫destructor 因為通常會手動幫忙delete, this is very important!!!!
class listnode {
private:
    listnode* link;
    int value;
public:
    friend class Queue;
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



class Queue {
private:
    listnode* first;
    int rear;
    int front;
    int MaxSize;
public:
    Queue(int x) {
        first = new listnode(x); // this definitely will use copy constructor
        rear = front = 0;
        MaxSize = x;
    }
    ~Queue() {
        cout << "destructor of List\n";
        for (listnode* i = first; i != NULL; i = i->link) {
            listnode* tmp = i;
            delete tmp;
        }
    }
    Queue (const Queue& l) {
        cout << "copy constructor of List\n";
        this->first = l.first;
    }
    void traverse();

    int length() {
        static int count = 0;
        for (listnode* i = first; i != NULL; i = i->link) {count++;}
        cout << "lengh is " << count << endl;
        return count;
    }
    void inverse();
    int Delete();
    void PUSH() {
        if (IsFull()) {cout << "Queue is FUll!" << endl; return ;}
        listnode* i = first;
        for (; i->link != NULL; i = i->link){}
        rear = (rear + 1) % MaxSize;
        i->link = new listnode(rear);
    }
    void GetFrontAndRear() {
        cout << "front is " << front << endl;
        cout << "rear is " << rear << endl;
    }
    bool IsFull() {
        int new_rear = (rear + 1) % MaxSize;
        return new_rear == front;
    }

};

void Queue::traverse() {
    for (listnode* i = first; i != NULL; i = i->link) {
        cout << i->value << " ";
    }
}


int Queue::Delete() {
    if (rear == front) {
        cout << "the queue is empty\n";
        return -1;
    }

    listnode* tmp = first;
    static int ss = tmp->value;
    first = first->link;
    front = (front+1) % MaxSize;
    delete tmp;
    return ss;
    
}

void Queue::inverse() {
    
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
    
    Queue l(3);
    l.traverse();
    l.PUSH();
    l.GetFrontAndRear();
    l.Delete();
    l.GetFrontAndRear();
    l.PUSH();
    l.GetFrontAndRear();
    l.PUSH();
    l.GetFrontAndRear();
    ㄋ
    return 0;
    
}


