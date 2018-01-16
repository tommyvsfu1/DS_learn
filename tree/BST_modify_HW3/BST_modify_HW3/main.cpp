//
//  main.cpp
//  BST
//
//  Created by Tommy on 2017/11/27.
//  Copyright © 2017 Tommy. All rights reserved.
//


/*
 BST 我當時犯的錯誤, 就是 delete 2 child node
 我們不是會去找2 child 的maxchild or minchild?
 當找到之後要把 maxchild , minchild 的parent 指向
 各自的leftchild , rightchild
 不是直接賦予0 ,小心R
 
 */
#include <iostream>
#include <fstream>
#include <cstdlib>
std::ifstream fin;
std::ofstream fout;
static char cb;
class BST;
class TreeNode {
public:
    
    
    
    TreeNode(long long int k) : leftchild(0), rightchild(0), key(k),dir('N'),x(-1),frequency(-1){}
    TreeNode(long long int k, char s, long long int u):leftchild(0), rightchild(0), key(k),dir(s),x(u),frequency(u){}
    ~TreeNode(){}//std::cout << "destructor" << std::endl;}
    TreeNode():leftchild(0),rightchild(0),key(-1),dir('N'),x(-1),frequency(-1){}
    TreeNode(const TreeNode& p) {
        //std::cout << "copy constructor!" << std::endl;
        
        this->key = p.key;
        this->leftchild = p.leftchild;
        this->rightchild = p.rightchild;
        this->frequency = p.frequency;
        this->x = p.x;
        this->dir = p.dir;
    }
    
    char Update(bool);
    friend class BST;
    
private:
    TreeNode* leftchild;
    TreeNode* rightchild;
    
    long long int key;
    char dir;
    long long int x;
    long long int frequency;
};

char TreeNode::Update(bool last){
    //==============
    // prevent error
    //if (x < 0){ std::cout << "data is wrong!"; return 'D';}
    //==============
    if (last) {
        fout << this->key;
        //std::cout << this->key << " ";//homework need to print
    }
    
    if (frequency == 0) return this->dir;
    --x;
    //cb = this->dir;
    cb = this->dir;
    if (x == 0) {
        if (this->dir == 'R') this->dir = 'L';
        else if(this->dir == 'L') this->dir = 'R';
        this->x = this->frequency;
    }
    
    return cb;
}


class BST {
public:
    BST(TreeNode* n):root(n){}
    BST():root(0){}
    void Insert(TreeNode*);
    void Inorder(TreeNode* node) {
        if (node == root) {
            std::cout << node->key << std::endl;
        }
        if (node) {
            Inorder(node->leftchild);
            std::cout << node->key << " " << node->dir << " " << node->x << std::endl;
            Inorder(node->rightchild);
        }
        return;
    }
    void Delete(long long int key,char token);
    void Drop(long long int number);
    void Replace(TreeNode*,TreeNode*);
    void maxchild(TreeNode*);
    void minchild(TreeNode*);
    TreeNode* GetRoot() {return root;}
    
private:
    TreeNode* root;
};


void BST::Replace(TreeNode* p1, TreeNode* p2) {
    p1->dir = p2->dir;
    p1->frequency = p2->frequency;
    p1->key = p2->key;
    p1->x = p2->x;
}

void BST::maxchild(TreeNode*n) {
    // this node should not be a null pointer, because this case is the two child case
    TreeNode* q;
    //the xcode will note that q may be uninitalized because I assume the k 's leftchild is not null at first
    // so q will be assigned after the first branch
    q = n->leftchild;
    TreeNode* k = n->leftchild;
    // q = k at first
    //-------------------->
    if (k->leftchild == 0 && k->rightchild == 0) {
        this->Replace(n,k);
        n->leftchild = 0;
        k = 0;
        return;
    }
    else if (!k->rightchild) {
        this->Replace(n,k);
        n->leftchild = k->leftchild;
        k = 0;
        return;
    }
    else {
        for(;;k = k->rightchild) {
            // so k == q when initial
            if (k->rightchild == 0) {
                this->Replace(n,k);
                q->rightchild = k->leftchild;
                k = 0;
                return ;
            }
            q = k;
        }
    }
}

void BST::minchild(TreeNode*n) {
    // this node should not be a null pointer, because this case is the two child case
    TreeNode* q;
    //the xcode will note that q may be uninitalized because I assume the k 's leftchild is not nullat first
    // so q will be assigned after the first branch
    q = n->rightchild;
    TreeNode* k = n->rightchild;
    // so k == q when initial
    if (k->leftchild == 0 && k->rightchild == 0) {
        this->Replace(n,k);
        n->rightchild = 0;
        k = 0;
        return;
    }
    else if (!k->leftchild) {
        this->Replace(n,k);
        n->rightchild = k->rightchild;
        k = 0;
        return;
    }
    else {
        for(;;k = k->leftchild) {
            if (k->leftchild == 0) {
                this->Replace(n,k);
                q->leftchild = k->rightchild;
                k = 0;
                return ;
            }
            q = k;
        }
    }
}

void BST::Insert(TreeNode* t) {
    if (!root)  {root = t; return;}
    //TreeNode* p = new TreeNode;
    TreeNode* q;
    for (TreeNode* p = root; p;) {
        q = p;
        if (t->key == p->key){ // if id exists, replace
            p->dir = t->dir;
            p->x = t->x;
            p->frequency = t->frequency;
            p->key = t->key;
            return;
        }
        if (t->key < p->key) p = p->leftchild;
        else if (t->key > p->key) p = p->rightchild;
        //else if watch out , don't if if, because the p is change after p = p->leftchild
    }
    
    // link to the right parent
    // assign the data
    TreeNode* p = new TreeNode(*t); //copy constructor
    //p->key = t->key;
    if (q->key > t->key) q->leftchild = p;
    else q->rightchild = p;
    
    
    
    
}

void BST::Delete(long long int k,char token) {
    //start searching first, check root
    //if (!root) {std::cout<< "empty tree"<< std::endl; return ;}
    //if (!root) {std::cout<< "Tree is empty."<< std::endl; return ;}
    
    TreeNode* q = 0;
    TreeNode* p = 0;
    
    //search first======================
    for (p = root; p;) {
        
        if (p->key == k) break;
        //=====this line I think is putting below
        q = p;
        if (p->key < k) p = p->rightchild;
        else p = p -> leftchild;
    }
    //==================================
    if (!p){ fout << "Deletion failed." << std::endl; return ;}
    //if (!p){ std::cout << "Deletion failed." << std::endl; return ;}
    
    // three case=======================
    else {
        if (!p->leftchild && !p->rightchild) {
            if (p == root) {root = 0; return ;}
            //linked-list deletion
            if (q->key < k) q->rightchild = 0;
            else q->leftchild = 0;
            //====================
            p = 0;
        }
        
        else if(p->leftchild && p->rightchild) { // two child or say two subtree
            if (token == 'R')
                this->minchild(p);
            else this->maxchild(p);
        }
        else {
            if (p->leftchild) {
                if (p == root) {
                    root = p->leftchild;
                    p = 0;
                    return ;
                }
                if (p->key < q->key) {q->leftchild = p->leftchild;}
                else {q->rightchild = p->leftchild;}
                p = 0;
            }
            else {
                if (p == root) {
                    root = p->rightchild;
                    p = 0;
                    return ;
                }
                if (p->key < q->key) {q->leftchild = p->rightchild;}
                else {q->rightchild = p->rightchild;}
                p = 0;
            }
        }
    }
}



void BST::Drop(long long int number) {
    //==============
    // prevent error
    if (!root) {fout <<"Tree is empty." << std::endl; return ;}
    //==============
    
    
    for (long long int i = 0; i < number; i++) {
        for (TreeNode* n = root; n;) {
            char k;
            if (i == number - 1)  {
                if (n != root) { fout << " ";}
                k = n->Update(true);
                
            }
            else k= n->Update(false);
            if (k == 'R') n = n->rightchild;
            else if(k == 'L') n = n->leftchild;
            //else {std::cout << "data is wrong!!!"; return;}
        }
        if (i == number - 1) {
            fout << std::endl;
            //std::cout << std::endl;
        }
    }
}


int main(int argc, const char * argv[]) {
    BST T;
    //std::cout << "hi";
    fin.open(argv[1],std::ios::in);
    fout.open(argv[2],std::ios::out);
    int count = 0;
    std::string str;
    while (getline(fin,str,' ')) {
        //std::cout << count++ << std::endl;
        if (str == "add") {
            //std::cout << "add";
            getline(fin,str,' ');
            long long int key = std::atoi(str.c_str());
            getline(fin,str,' ');
            char token = *str.c_str();
            getline(fin,str,'\n');
            long long int frequency = std::atoi(str.c_str());
            //std::cout << key << " " << token << " " << frequency;
            TreeNode* k = new TreeNode(key,token,frequency);
            T.Insert(k);
        }
        else if (str == "deleteR") {
            // std::cout << "deleteR ";
            getline(fin,str,'\n');
            long long int key = std::atoi(str.c_str());
            //std::cout << key;
            T.Delete(key,'R');
        }
        else if (str == "deleteL") {
            // std::cout << "deleteL ";
            getline(fin,str,'\n');
            long long int key = std::atoi(str.c_str());
            //std::cout << key;
            T.Delete(key,'L');
        }
        else {
            // std::cout << "drop ";
            getline(fin,str,'\n');
            long long int time = std::atoi(str.c_str());
            //std::cout << time;
            T.Drop(time);
        }
        //std::cout << std::endl;
    }
    fin.close();
    fout.close();
    return 0;
    
}



