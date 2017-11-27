//
//  main.cpp
//  BST
//
//  Created by Tommy on 2017/11/27.
//  Copyright © 2017 Tommy. All rights reserved.
//
#include <iostream>

class BST;
class TreeNode {
public:
    
    TreeNode(int k) : leftchild(0), rightchild(0),current(0), key(k),dir('N'),x(-1){}
    TreeNode(int k, char s, int u):leftchild(0), rightchild(0),current(0), key(k),dir(s),x(u){}
    ~TreeNode(){std::cout << "destructor" << std::endl;}
    TreeNode():leftchild(0),rightchild(0),current(0),key(-1),dir('N'),x(-1){}
    TreeNode(const TreeNode& p) {
        std::cout << "copy constructor!" << std::endl;
        this->current = p.current;
        this->key = p.key;
        this->leftchild = p.leftchild;
        this->rightchild = p.rightchild;
    }
    
    char Update();
    friend class BST;
private:
    TreeNode* leftchild;
    TreeNode* rightchild;
    TreeNode* current;
    int key;
    char dir;
    int x;
};

char TreeNode::Update(){
    //==============
    // prevent error
    if (x < 0){ std::cout << "data is wrong!"; return 'D';}
    //==============
    
    static char cb;
    if (x == 0 ) return this->dir;
    --x;
    cb = this->dir;
    if (x == 0) {
        if (this->dir == 'R') this->dir = 'L';
        else if(this->dir == 'L') this->dir = 'R';
    }
    
    //std::cout << this->key << " " << std::endl; //homework need to print
    
    return cb;
}


class BST {
public:
    BST(TreeNode* n):root(n){}
    void Insert(TreeNode*);
    TreeNode* Inorder(TreeNode* node) {
        if (node) {
            Inorder(node->leftchild);
            std::cout << node->key << " " << node->dir << " " << node->x << std::endl;
            Inorder(node->rightchild);
        }
        return 0;
    }
    void Delete(int key);
    void Drop(int number);
    TreeNode* GetRoot() {return root;}
    
private:
    TreeNode* root;
};

void BST::Insert(TreeNode* t) {
    if (!root) return ;
    //TreeNode* p = new TreeNode;
    TreeNode* q = new TreeNode;
    for (TreeNode* p = root; p;) {
        q = p;
        if (t->key == p->key){ // if id exists, replace
            p->dir = t->dir;
            p->x = t->x;
            return;
        }
        if (t->key < p->key) p = p->leftchild;
        else if (t->key > p->key) p = p->rightchild;
        //else if watch out , don't if if, because the p is change after p = p->leftchild
    }
    
    // link to the right parent
    TreeNode* p = new TreeNode;
    //p->key = t->key;
    if (q->key > t->key) q->leftchild = p;
    else q->rightchild = p;
    
    // assign the data
    p->key = t->key;
    p->dir = t->dir;
    p->x = t->x;
    
}

void BST::Delete(int k) {
    //start searching first, check root
    if (!root) {std::cout<< "empty tree"; return ;}
    
    TreeNode* q = new TreeNode;
    TreeNode* p  = new TreeNode;
    //delete p;
    for (p = root; p;) {
        q = p;
        if (p->key == k) break;
        if (p->key < k) p = p->rightchild;
        else p = p -> leftchild;
    }
    
    if (!p){ std::cout << "key doesn't exist"; return ;}
    else {
        
        // p is TreeNode
        if (!p->leftchild && !p->rightchild) {
            delete p;
            std::cout << "fucking I delete it"<< std::endl;
            std::cout << p->key;
            return ;}
        
        //no child //don't know why can't delete
        else if(p->leftchild && p->rightchild) { // two child or say two subtree
            
        }
        else {
            if (p->leftchild) {
                if (p->key < q->key) {q->leftchild = p->leftchild;}
                else {q->rightchild = p->leftchild;}
            }
            else {
                if (p->key < q->key) {q->leftchild = p->rightchild;}
                else {q->rightchild = p->rightchild;}
            }
        }
    }
}



void BST::Drop(int number) {
    //==============
    // prevent error
    if (!root) {std::cout <<"Tree is empty." << std::endl; return ;}
    //==============
        
        
    
    for (int i = 0; i < number; i++) {
        for (TreeNode* n = root; n;) {
            char k = n->Update();
            if (k == 'R') n = n->rightchild;
            else if(k == 'L') n = n->leftchild;
            //else {std::cout << "data is wrong!!!"; return;}
        }
    }
}


int main(int argc, const char * argv[]) {
    
    TreeNode* k = new TreeNode(3,'R',3);
    TreeNode* p1 = new TreeNode(4,'L',1);
    TreeNode* p2 = new TreeNode(13,'R',5);
    TreeNode* p3 = new TreeNode(1,'R',2);
    TreeNode* p4 = new TreeNode(15,'R',1);
    TreeNode* p5 = new TreeNode(5,'L',5);
    TreeNode* p6 = new TreeNode(7,'L',2);
    BST T(k);
    T.Insert(p1);
    T.Insert(p2);
    T.Insert(p3);
    T.Insert(p4);
    T.Insert(p5);
    T.Insert(p6);
    T.Inorder(T.GetRoot());
    T.Delete(15);
    T.Inorder(T.GetRoot());
    //int* qq = new int;
    //delete qq;
/*
    std::cout << "start droping !!!, GAME START!" << std::endl;
    std::cout << "drop 1" << std::endl;
    T.Drop(1);
    T.Inorder(T.GetRoot());
    std::cout << "drop 2" << std::endl;
    T.Drop(1);
    T.Inorder(T.GetRoot());
    //T.Delete(15);
    //std::cout << "-----\n";
    //T.Inorder(T.GetRoot());
 */
    return 0;
}

