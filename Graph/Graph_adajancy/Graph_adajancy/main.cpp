//
//  main.cpp
//  Graph_adajancy
//
//  Created by Tommy on 2017/12/10.
//  Copyright © 2017年 Tommy. All rights reserved.
//

#include <iostream>

typedef class graph* Graph;

class graph {
private:
    int n;
    int m;
    struct successors {
        int d;
        int len;
        int isSorted;
        int list[];
    } ** alist;
    
public:
    graph(int k): n(k),m(0) {
        this->alist = new successors* [n];
        for (int i = 0; i < n; ++i){
            this->alist[i] = new successors;
            this->alist[i]->d = 0;
            this->alist[i]->len = 0;
            this->alist[i]->isSorted = 1;
        }
    }
    ~graph() {
        std::cout << "Delete graph";
        for (int i = 0; i < n; i++){
            delete [] this->alist[i];
        }
        delete [] this->alist;
    }
    void graphAddEdge(Graph g, int u, int v) {
        
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
