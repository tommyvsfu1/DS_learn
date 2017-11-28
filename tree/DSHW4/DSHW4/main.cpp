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
    
    TreeNode(int k) : leftchild(0), rightchild(0),current(0), key(k),dir('N'),x(-1),frequency(-1){}
    TreeNode(int k, char s, int u):leftchild(0), rightchild(0),current(0), key(k),dir(s),x(u),frequency(u){}
    ~TreeNode(){std::cout << "destructor" << std::endl;}
    TreeNode():leftchild(0),rightchild(0),current(0),key(-1),dir('N'),x(-1),frequency(-1){}
    TreeNode(const TreeNode& p) {
        std::cout << "copy constructor!" << std::endl;
        this->current = p.current;
        this->key = p.key;
        this->leftchild = p.leftchild;
        this->rightchild = p.rightchild;
        this->frequency = p.frequency;
        this->x = p.x;
        this->dir = p.dir;
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
    int frequency;
};

char TreeNode::Update(){
    //==============
    // prevent error
    if (x < 0){ std::cout << "data is wrong!"; return 'D';}
    //==============
    
    static char cb;
    if (x == 0 && frequency == 0) return this->dir;
    --x;
    cb = this->dir;
    if (x == 0) {
        if (this->dir == 'R') this->dir = 'L';
        else if(this->dir == 'L') this->dir = 'R';
        x = frequency;
    }
    
    //std::cout << this->key << " " << std::endl; //homework need to print
    
    return cb;
}


class BST {
public:
    BST(TreeNode* n):root(n){}
    void Insert(TreeNode*);
    void Inorder(TreeNode* node) {
        if (node) {
            Inorder(node->leftchild);
            std::cout << node->key << " " << node->dir << " " << node->x << std::endl;
            Inorder(node->rightchild);
        }
        return;
    }
    void Delete(int key);
    void Drop(int number);
    TreeNode* maxchild(TreeNode*);
    TreeNode* minchild(TreeNode*);
    TreeNode* GetRoot() {return root;}
    
private:
    TreeNode* root;
};


TreeNode* BST::maxchild(TreeNode* n) {
    // this node should not be a null pointer, because this case is the two child case
    TreeNode* q;
    for(static TreeNode* k = n;;k = k->rightchild) {
        if (k->rightchild == 0) {
            q->rightchild = 0;
            return k;
        }
        q = k;
    }
}

TreeNode* BST::minchild(TreeNode* n) {
    // this node should not be a null pointer, because this case is the two child case
    TreeNode* q;
    for(static TreeNode* k = n;;k = k->leftchild) {
        if (k->leftchild == 0) {
            q->leftchild = 0;
            return k;
        }
        q = k;
    }
    
}

void BST::Insert(TreeNode* t) {
    if (!root) return ;
    //TreeNode* p = new TreeNode;
    TreeNode* q;
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
    // assign the data
    TreeNode* p = new TreeNode(*t); //copy constructor
    //p->key = t->key;
    if (q->key > t->key) q->leftchild = p;
    else q->rightchild = p;
    


    
}

void BST::Delete(int k) {
    //start searching first, check root
    if (!root) {std::cout<< "empty tree"; return ;}
    
    TreeNode* q = 0;
    TreeNode* p = 0;
    //delete p;
    for (p = root; p;) {
      
        if (p->key == k) break;
        //=====this line I think is putting below
        q = p;
        if (p->key < k) p = p->rightchild;
        else p = p -> leftchild;
    }
    
    if (!p){ std::cout << "Deletion failed."; return ;}
    else {
        
        // p is TreeNode need to be deleted
        if (!p->leftchild && !p->rightchild) {
            if (q->key < k) q->rightchild = 0;
            else q->leftchild = 0;
            delete p;
            //std::cout << p->key;
            return ;
        }
        
        else if(p->leftchild && p->rightchild) { // two child or say two subtree
            if (q->key < k) {
                q->rightchild = maxchild(p);
                q->rightchild->leftchild = p->leftchild;
                q->rightchild->rightchild = p->rightchild;
                delete p;
            }
            else {
                q->leftchild = maxchild(p);
                q->leftchild->leftchild = p->leftchild;
                q->leftchild->rightchild = p->rightchild;
                delete p;
            }
        }
        else {
            if (p->leftchild) {
                if (p->key < q->key) {q->leftchild = p->leftchild;}
                else {q->rightchild = p->leftchild;}
                delete p;
            }
            else {
                if (p->key < q->key) {q->leftchild = p->rightchild;}
                else {q->rightchild = p->rightchild;}
                delete p;
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
    
    TreeNode k(3,'R',2);
    TreeNode p1(4,'L',1);
    TreeNode p2(13,'R',5);
    TreeNode p3(1,'R',2);
    TreeNode p4(15,'R',1);
    TreeNode p5(5,'L',5);
    TreeNode p6(7,'L',2);
    BST T(&k);
    T.Insert(&p1);
    T.Insert(&p2);
    T.Insert(&p3);
    T.Insert(&p4);
    T.Insert(&p5);
    T.Insert(&p6);
    T.Inorder(T.GetRoot());
    //T.Delete(13);
    //T.Inorder(T.GetRoot());
    
    T.Drop(2);
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

