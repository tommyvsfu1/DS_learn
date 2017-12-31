//
//  main.cpp
//  Graph_adajancy
//
//  Created by Tommy on 2017/12/10.
//  Copyright © 2017年 Tommy. All rights reserved.
//
class ShortestPath;
#include <iostream>
#include <queue>
#include <list>
#include <algorithm>
#include <functional>
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
    int** length;
    int** minDist;
public: 
    //friend class ShortestPath;
    graph(int k) : n(k),m(0) {
        this->length = new int* [n];
        this->minDist = new int* [n];
        for (int i = 0; i < n; ++i) {
            this->length[i] = new int [n];
            this->minDist[i] = new int[n];
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                this->length[i][j] = std::numeric_limits<int>::max();
                this->minDist[i][j] = std::numeric_limits<int>::max();
                }
                else {
                this->length[i][j] = 0;
                this->minDist[i][j] = 0;  
                }
            }
        }
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

    // Graph Basic

    void graphDestroy(Graph);
    void graphAddEdge(Graph,int source, int sink,int);   
    int graphVertexCount(Graph);
    int graphEdgeCount(Graph);   
    int graphOutDegree(Graph, int source);   
    int graphHasEdge(Graph, int source, int sink);
    bool* boundaryset(int source, int bound);
    std::vector<std::pair<int,int> > MultisourceBoundarySet(int*set, int size);


    // Debug
    void debugWeight();
    

    // Search 
    void DFS(int);
    void DFS();
    void BFS(int);

    // mindistance
    void Dijkstra(int v);
    void BellmanFord(int v);
};

bool compare (const std::pair<int,int>& p1,const std::pair<int,int>& p2) {
            return p1.first > p2.first;

} 
std::vector<std::pair<int,int> >  graph::MultisourceBoundarySet(int*set, int size) {
    //std::list<std::pair<int,int>> L ;
    //for (int i = 0; i < this->m; ++i){
    //}
    static std::vector<std::pair<int ,int > >  L;
    for (int i = 0; i < size; ++i) {
            for (vertex* node = this->alist[set[i]].link;node;node = node ->link){
                std::pair<int,int> p(set[i],node->data);
                if (node->data <= set[i]) {
                    p.first = node->data;
                    p.second = set[i];
                }
                L.push_back(p);
            }
    }

    /*For Debug 
    for (std::list<std::pair<int,int> >::iterator it = L.begin();it != L.end(); it++){
        std::cout << (*it).first << " " << (*it).second << std::endl;
    }
    */
   //for (std::list<std::pair<int,int> >::iterator it = L.begin();it != L.end(); it++) {
    

    std::sort(L.begin(),L.end());
    for (std::vector<std::pair<int,int> >::iterator it = L.begin(); it != L.end(); ){      
        if ((it+1) != L.end()) {
            if ((*it) == *(it+1)){it = L.erase(it); it = L.erase(it);}
            else {std::cout << (*it).first << " " << (*it).second << std::endl; ++it;}
        }
        else {std::cout << (*it).first << " " << (*it).second << std::endl; ++it;}
        
    }
    for (std::vector<std::pair<int,int> >::iterator it = L.begin(); it != L.end(); it++){   

        std::cout << (*it).first << " " << (*it).second << std::endl;
    }

    //std::pair<int,int>* s = new std::pair<int,int>[L.size()];
    //for (int i = 0; i < L.size(); ++i){
     //   s[i].first = L[i].first;
      //  s[i].second = L[i].second;
    //}
    return L;
}


bool* graph::boundaryset(int source, int bound){
    bool s[this->n];
    for (int i = 0; i < this->n; ++i) {
        if(this->length[source][i] < bound) {
            s[i] = 1;
        }
        else s[i] = 0;
    }
}


void graph::debugWeight(){
    for (int i = 0; i < this->n; ++i) {
        for (int j = 0; j < this->n; ++j) {
            std::cout << length[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

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
void graph::graphAddEdge(Graph g, int u, int v, int weight) { // assign vertex
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
    // setting weight
    this->length[u][v] = weight;
    this->length[v][u] = weight;
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


void graph::BellmanFord(int v) {
    //bool boundary = this->boundaryset(v,)
    bool s[this->n];
    int mindistance[this->n];
    for (int i = 0; i < this->n; ++i){
        s[i] = 0;
        mindistance[i] = this->length[v][i];
    }
    // source to source , source already left, and distance to itself = 0
    s[v] = 1;
    mindistance[v] = 0;   

    for (int i = 0; i < n-1; ++i){ //n-1 edge iteration, every iteration update the boundary
        for (int u = 0;u < n-1; ++u){   // check whether the vertex is left side (this actually is the roll of the Dijska's choose(n))
            for (int k = 0; k < n; ++k){ //check all the out-degree from the vertex
                if (!s[u] && (mindistance[u]+length[u][k]) < mindistance[k]) {
                    s[u] = 1;
                    mindistance[k] = mindistance[u]+length[u][k];
                }
            }
        }
    }
    std::cout << "Shortest path" << std::endl;
    for (int i = 0; i < this->n; i++)
        std::cout << mindistance[i] << " ";
}

void graph::Dijkstra(int v){
    /* Initialization */
    bool s[this->n];
    int mindistance[this->n];
    for (int i = 0; i < this->n; ++i){
        s[i] = 0;
        mindistance[i] = this->length[v][i];
    }
    // source to source , source already left, and distance to itself = 0
    s[v] = true;
    mindistance[v] = 0;


    // iteration start
    for (int i = 0; i < n-1; i++) {

        /* choose shortest path from boundary set*/
        bool* bound = this->boundaryset(v,std::numeric_limits<int>::max());
        int min = std::numeric_limits<int>::max();
        int u;
        for (int j = 0; j < n; ++j) {
            if(bound[j] == 1) {
                if (this->length[v][j] < min) {
                    min = this->length[v][j];
                    u = j;
                }
            }
        }

        s[u] = true;
        mindistance[u] = this->length[v][u];

        //update the shortest path from this new member
        for (int k = 0; k < this->n; ++k) {
            if (!s[k] && (mindistance[u]+this->length[u][k]) < this->length[v][k]) mindistance[k] = mindistance[u] + this->length[u][k];
        }        

    }

}

int main(int argc, const char * argv[]) {
    // insert code here...
    graph g(6);
    g.graphAddEdge(&g,0,1,13);
    g.graphAddEdge(&g,0,2,20);
    g.graphAddEdge(&g,1,3,50);
    g.graphAddEdge(&g,3,2,70);
    g.graphAddEdge(&g,2,4,60);
    g.graphAddEdge(&g,3,4,20);    
    g.graphAddEdge(&g,4,5,30);
    int set[3] = {0,1,2};
    //g.DFS();
    //g.debugWeight();
    //std::cout << g.graphHasEdge(&g,2,3);
    std::vector<std::pair<int,int> > s;
    s= g.MultisourceBoundarySet(set,3);
    std::cout << s.size();
    //std::cout << sizeof(*s)/sizeof(s);
   // g.BellmanFord(0);
    //std::cout << "Hello, World!\n";
    return 0;
}
