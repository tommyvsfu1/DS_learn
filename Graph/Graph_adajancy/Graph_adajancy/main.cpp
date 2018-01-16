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
#include <fstream>
#include <stack>
std::ifstream fin;
std::ofstream fout;
struct vertex {
    vertex(int k):data(k),link(0){}
    vertex* link;
    int data;
    //vertex* shortestPathlink;
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
        vertex** path;
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
            this->alist[i].path = new vertex*;
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
    //bool* boundaryset(int source, int bound);
    std::vector<std::pair<int,int> > MultisourceBoundarySet(int*set, int size,std::vector<std::pair<int, int> >&);
    std::vector<std::pair<int,int> > MultisourceBoundaryVertex(int*set, int size, std::vector<std::pair<int, int> > &);


    // Debug
    void debugWeight();
    bool NegativeCycle(int );

    // Search 
    void DFS(int);
    void DFS();
    void BFS(int);

    // mindistance
    void Dijkstra(int v);
    void BellmanFord(int v, int output);
    void BellmanFord(int v, int* mindistance);
    void AllPairs(int n);
};

bool compare (const std::pair<int,int>& p1,const std::pair<int,int>& p2) {
            return p1.first > p2.first;

}

std::vector<std::pair<int,int> >  graph::MultisourceBoundarySet(int*set, int size, std::vector<std::pair<int, int> >& L) { // size = set size
    std::cout << "into the Multisource " << std::endl;
    //static std::vector<std::pair<int ,int > >  L;

    for (int i = 0; i < size; ++i) {
            for (vertex* node = this->alist[set[i]].link;node;node = node ->link){
                // Searching
                bool flag = true;
                for (int k = 0; k < size; k++) { //sequential search
                    if (set[k] == node->data){flag = false;}
                }
                if (flag) {
                    //std::cout << "the flag has ";
                    std::cout << set[i] << " " << node->data << std::endl;
                    std::pair<int,int> p(set[i],node->data);
                    L.push_back(p);
                }
            }
    }


    
    
    /*For Debug 
    for (std::list<std::pair<int,int> >::iterator it = L.begin();it != L.end(); it++){
        std::cout << (*it).first << " " << (*it).second << std::endl;
    }
    */
   //for (std::list<std::pair<int,int> >::iterator it = L.begin();it != L.end(); it++) {
    

    /*  output edge filter, if we use the pair match way
    std::sort(L.begin(),L.end());
    for (std::vector<std::pair<int,int> >::iterator it = L.begin(); it != L.end(); ){      
        if ((it+1) != L.end()) {
            if ((*it) == *(it+1)){it = L.erase(it); it = L.erase(it);}
            else {++it;}
            //else {std::cout << (*it).first << " " << (*it).second << std::endl; ++it;}
        }
        else {++it;}
       // else {std::cout << (*it).first << " " << (*it).second << std::endl; ++it;}
    }
    */
    
    
    /*For Debug
    for (std::vector<std::pair<int,int> >::iterator it = L.begin(); it != L.end(); it++){   

        std::cout << (*it).first << " " << (*it).second << std::endl;
    }
     */
    

    return L;
}
std::vector<std::pair<int,int> > graph::MultisourceBoundaryVertex(int*set, int size, std::vector<std::pair<int, int> > & L)
{
    //std::cout << "into the MultisourceVertex " << std::endl;
    //static std::vector<std::pair<int ,int > >  L;
    
    for (int i = 0; i < size; ++i) {
        //std::cout << set[i] << std::endl;
        for (vertex* node = this->alist[set[i]].link;node;node = node ->link){
            // Searching
                //std::cout << "the flag has ";
                //std::cout << set[i] << " " << node->data << std::endl;
                std::pair<int,int> p(set[i],node->data);
                L.push_back(p);
            
        }
    }
    
    
    
    
    /*For Debug
     for (std::list<std::pair<int,int> >::iterator it = L.begin();it != L.end(); it++){
     std::cout << (*it).first << " " << (*it).second << std::endl;
     }
     */
    //for (std::list<std::pair<int,int> >::iterator it = L.begin();it != L.end(); it++) {
    
    
    /*  output edge filter, if we use the pair match way
     std::sort(L.begin(),L.end());
     for (std::vector<std::pair<int,int> >::iterator it = L.begin(); it != L.end(); ){
     if ((it+1) != L.end()) {
     if ((*it) == *(it+1)){it = L.erase(it); it = L.erase(it);}
     else {++it;}
     //else {std::cout << (*it).first << " " << (*it).second << std::endl; ++it;}
     }
     else {++it;}
     // else {std::cout << (*it).first << " " << (*it).second << std::endl; ++it;}
     }
     */
    
    
    /*For Debug
     for (std::vector<std::pair<int,int> >::iterator it = L.begin(); it != L.end(); it++){
     
     std::cout << (*it).first << " " << (*it).second << std::endl;
     }
     */
    
    
    return L;
    
}
/*
bool* graph::boundaryset(int source, int bound){
    bool s[this->n];
    for (int i = 0; i < this->n; ++i) {
        if(this->length[source][i] < bound) {
            s[i] = 1;
        }
        else s[i] = 0;
    }
    return true;
}
*/

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
    //this->alist[v].len++;
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
    
 /*
    if (this->alist[v].link) {
        vertex* k = this->alist[v].link;
        for (;k->link;k = k->link){}
        k->link = new vertex(u);
    }
    else {
        this->alist[v].link  = new vertex(u);
    }
  */
    
    // setting weight
    this->length[u][v] = weight;
    //this->length[v][u] = weight;
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


void graph::BellmanFord(int v, int output) { // v is single source
    //bool boundary = this->boundaryset(v,)
    std::vector< int >  linked(this->n+1);
   
    for (int i = 0; i < n; i++)
        linked[i] = -1;
    
    bool s[this->n];
    //std::list<int> LeftSide;
      std::queue<int> Side;
    int mindistance[this->n];
    for (int i = 0; i < this->n; ++i){
        s[i] = 0;
        mindistance[i] = this->length[v][i];
    }
    // source to source , source already left, and distance to itself = 0
    s[v] = 1;
    mindistance[v] = 0;
    Side.push(v);
    //LeftSide.push_back(v);
    //std::cout << LeftSide.size();
    //std::cout << "yes , it ok";
    for (int i = 1; i <= n; ++i){ //n-1 edge iteration, every iteration update the boundary
      
        int set[Side.size()];
      //  std::cout << "the list has ";
        const int queueSize = int(Side.size());
        for (int k = 0; k < queueSize; ++k){
            //std::cout << Side.front() << " ";
            set[k] = Side.front();
            Side.pop();
        }
       // std::cout << std::endl;
        std::vector<std::pair<int , int> > vv;
        MultisourceBoundaryVertex(set, queueSize,vv);
        //std::cout << "into update " << std::endl;
        for (int k = 0; k < vv.size(); k++){//vv contains all the outputedge
            //std::cout << vv[k].first << " " << vv[k].second << std::endl;
            //Side.push_back(vv[k].second);
            Side.push(vv[k].second);
            if (mindistance[vv[k].first] + this->length[vv[k].first][vv[k].second] <= mindistance[vv[k].second]) {
                mindistance[vv[k].second] = mindistance[vv[k].first] + this->length[vv[k].first][vv[k].second];
                //std::cout << "error" << std::endl;
                //std::cout << vv[k].first << " " << vv[k].second << std::endl;
                linked[vv[k].second] = vv[k].first;
            
            }
        }
        
        
    }
    /*
    std::cout << "mindistance" << std::endl;
    for (int i = 1; i < this->n; i++) {
        std::cout << mindistance[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "the recursive path is " << std::endl;
    for (int i = 1; i< n; i++) {
        std::cout <<  linked[i] << " ";
    }
     */
    //std::cout << std::endl;

    if (mindistance[output] == std::numeric_limits<int>::max()) {fout << "No path\n";return;}
    int kk = linked[output];
    std::stack<int> out;
    out.push(output);
    while(1) {
        if (kk == v) { out.push(kk);break;}
        out.push(kk);
        kk = linked[kk];
    }
    
    /* the out path is */
    //std::cout << "shortest path distance is " << mindistance[output] << std::endl;

    fout << mindistance[output] << " ";
    const int size = out.size();
    for (int i = 0; i < size; i++) {
        //std::cout << out.top() << " ";
        fout << out.top() << " ";
        out.pop();
    }
    fout << std::endl;
    //std::cout << std::endl;
}




void graph::BellmanFord(int v, int* mindistance) { // v is single source
    bool s[this->n];
    std::queue<int> Side;

    
    // source to source , source already left, and distance to itself = 0
    s[v] = 1;
    //mindistance[v] = 0;
    Side.push(v);

    for (int i = 1; i <= n; ++i){ //n-1 edge iteration, every iteration update the boundary
        //std::cout << "the" << i << "time" << std::endl;
        // push all the destination I have
        /* Check the leftsize node, and the edge*/
        // std::cout << "Shortest path" << std::endl;
        //for (int i = 0; i < this->n; i++)
        //     std::cout << mindistance[i] << " ";
        // std::cout << std::endl;
        
        
        int set[Side.size()];
        //std::cout << "the list has ";
        const int queueSize = int(Side.size());
        for (int k = 0; k < queueSize; ++k){
            //std::cout << Side.front() << " ";
            set[k] = Side.front();
            Side.pop();
        }
        //std::cout << std::endl;
        std::vector<std::pair<int , int> > vv;
        MultisourceBoundaryVertex(set, queueSize,vv);
        //std::cout << "into update " << std::endl;
        for (int k = 0; k < vv.size(); k++){//vv contains all the outputedge
            //std::cout << vv[k].first << " " << vv[k].second << std::endl;
            //Side.push_back(vv[k].second);
            Side.push(vv[k].second);
            if (mindistance[vv[k].first] + this->length[vv[k].first][vv[k].second] < mindistance[vv[k].second]) {
                mindistance[vv[k].second] = mindistance[vv[k].first] + this->length[vv[k].first][vv[k].second];
            }
        }
        
        
    }

    
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
    for (int i = 0; i < n-1+n-1+n-1; i++) {

        /* choose shortest path from boundary set*/
       // bool* bound = this->boundaryset(v,std::numeric_limits<int>::max());
        int min = std::numeric_limits<int>::max();
        int u;
        for (int j = 0; j < n; ++j) {
           // if(bound[j] == 1) {
                if (this->length[v][j] < min) {
                    min = this->length[v][j];
                    u = j;
                }
           // }
        }

        s[u] = true;
        mindistance[u] = this->length[v][u];

        //update the shortest path from this new member
        for (int k = 0; k < this->n; ++k) {
            if (!s[k] && (mindistance[u]+this->length[u][k]) < this->length[v][k]) mindistance[k] = mindistance[u] + this->length[u][k];
        }        

    }

}


bool graph::NegativeCycle(int v) {
    int mindistance[this->n];
    for (int i = 0; i < this->n; ++i) {
        mindistance[i] = this->length[v][i];
    }
    mindistance[v] = 0;
    int copy[this->n];
    
    
    BellmanFord(v, mindistance);
    for (int i = 0; i < this->n; i++){
        copy[i] = mindistance[i];
    }

    BellmanFord(v, mindistance);
    /* Debug
    for (int i = 0; i < this->n; i++){
        std::cout << mindistance[i] << " ";
    
    }
     */
    for (int i = 0; i < this->n; ++i) {
        if (mindistance[i] != copy[i]) {
            return 1;
        }
    }

 
    return 0;
    
}

/*
 All-pairs
           source         destination
            (i)   - - - - - -(j)
              \              /
               \            /
                \          /
                 \        /
                  \      /
                   \    /
                    (k)
*/
void graph::AllPairs(int n) {
    int a[n][n];
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = this->length[i][j];
        }
    }
    
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (a[i][j] > a[i][k] + a[k][j]) {
                    a[i][j] = a[i][k] + a[k][j];
                }
            }
        }
    }
    
}
int main(int argc, const char * argv[]) {
    // insert code here...
    fin.open(argv[1],std::ios::in);
    fout.open(argv[2],std::ios::out);
    
    // graph number
    std::string str;
    getline(fin, str);
    int nodenumber =std::atoi(str.c_str());
    graph g(nodenumber+1);
    // load to #
    
    
    int checkNode;
    while(getline(fin, str)) {
        if(str == "#") break;
        //std::cout << str << std::endl;
        int n1 = int(str.find_first_of(" ",0));
        int nn1 = std::atoi(str.substr(0,n1).c_str());
        int n2 = int(str.find_first_of(" ",n1+1));
        int nn2 = std::atoi(str.substr(n1+1,n2).c_str());
        int nn3 = std::atoi(str.substr(n2+1).c_str());
        checkNode = nn1;
        std::cout << nn1 << " " << nn2 << " " <<  nn3 << std::endl;
        g.graphAddEdge(&g, nn1, nn2, nn3);
    }
    //std::cout << "#" << std::endl;
   // g.graphAddEdge(&g, 100000000, 2, 3);
    for (int k = 1; k < nodenumber+1; ++k) {
        if (g.NegativeCycle(k)) {
            fout << "Negative cycle\n";
            exit(1);
        }
    }
    while(getline(fin, str)) {
        int n = int(str.find_first_of(" ",0));
        int nn1 = std::atoi(str.substr(0,n).c_str());
        int nn2 = std::atoi(str.substr(n+1).c_str());
        //std::cout << nn1 << " " << nn2 << std::endl;
        g.BellmanFord(nn1, nn2);
    }
    return 0;
}
