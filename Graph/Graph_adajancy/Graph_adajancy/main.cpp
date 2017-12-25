//
//  main.cpp
//  Graph_adajancy
//
//  Created by Tommy on 2017/12/10.
//  Copyright © 2017年 Tommy. All rights reserved.
//

#include <iostream>
#include <queue>
struct vertex {
    vertex(int k):data(k),link(0){}
    vertex* link;
    int data;
};

typedef class graph* Graph;
class graph {
private:
    int n; //number of vertex
    int m; // number of edge
    struct successors {
        int count; // number for DFS
        int len; // number of the adjancy list
        int isSorted;
        vertex* link;
    } * alist;
    
public: 
    graph(int k) : n(k),m(0) {
        this->alist = new successors [n];
        for (int i = 0; i < n; ++i){
            this->alist[i].count = 0;
            this->alist[i].link = 0;
            this->alist[i].len = 0;
            this->alist[i].isSorted = 1;
        }
    }
    ~graph() {
        //std::cout << "Delete graph";      
        // Linked list deletion
        //TODO  
        
        delete [] this->alist;
    }
    graph(const graph& g) {
        this->alist = new successors[g.n];
        for (int i = 0; i < g.n; i++){
            this->alist[i].link->data = g.alist[i].link->data;
        }
        this->n = g.n;
        this->m = g.m;
    }
    void graphDestroy(Graph);
    void graphAddEdge(Graph,int source, int sink);   
    int graphVertexCount(Graph);
    int graphEdgeCount(Graph);   
    int graphOutDegree(Graph, int source);   
    int graphHasEdge(Graph, int source, int sink);
    void DFS(int);
    void DFS();
    void BFS(int);
    //void grpahForeach(Graph, int sou)
};


void graph::DFS() {
    std::cout << "DFS Start!" << std::endl;
    DFS(0);
}

void graph::DFS(int source) {
    std::cout << source ;
    this->alist[source].count = 1;
    
    /*  for (the vertex has neighbor not been)  */
    for(vertex* node = this->alist[source].link;node;node = node->link){
        if (node && this->alist[node->data].count != 1)  DFS(node->data);
    }
}

void graph::graphDestroy(Graph g) {
    //for (int i = 0; i < g->n; i++) delete g->alist; // I don't know whether it will destroy all the link
    delete g->alist;
    delete g;
}

void graph::BFS(int v) {
    std::queue<int> q;
    std::cout << "Start BFS !" << std::endl;
    //for(int i = 0; i < this->alist[i].len; i++){q.push(this->alist[i])}
    vertex w(0);
    this->alist[v].count = 1;
    q.push(v);
    while(! q.empty()) {
        v = q.front();
        q.pop();
        std::cout << v;
        for(vertex* node = this->alist[v].link;node;node = node ->link) {
            if(node && this->alist[node->data].count!=1) {
                this->alist[node->data].count = 1;
                q.push(node->data);
            }
        }
    }
}
void graph::graphAddEdge(Graph g, int u, int v) { // assign vertex
    g->m++;
    this->alist[u].len++;
    this->alist[v].len++;
   // g->alist[u]->list[g->alist[u]->d++] = v;
   // g->alist[u]->isSorted = 0;
    if (this->alist[u].link) {
        vertex* w = this->alist[u].link;
        for (;w->link;w = w->link){}
        w->link = new vertex(v);
    }
    else {
        this->alist[u].link  = new vertex(v);
    }
    
    
    if (this->alist[v].link) {
        vertex* k = this->alist[v].link;
        for (;k->link;k = k->link){}
        k->link = new vertex(u);
    }
    else {
        this->alist[v].link  = new vertex(u);
    }

}


int graph::graphHasEdge(Graph g, int source, int sink) {
    //Because I use simple Adjancy list (twice in the search), so I only search one
    for (vertex* node = this->alist[source].link;node;node = node ->link) {
        if (node->data == sink) {return 1;}
    }
    return 0;
}



int graph::graphEdgeCount(Graph g) {
    return g->m;
}
int graph::graphVertexCount(Graph g) {
    return g->n;
}

int graph::graphOutDegree(Graph g, int source) {
   return this->alist[source].len;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    graph g(5);
    g.graphAddEdge(&g,0,1);
    g.graphAddEdge(&g,0,2);
    g.graphAddEdge(&g,1,2);
    //g.DFS();
    g.BFS(0);
    //std::cout << "Hello, World!\n";
    return 0;
}
