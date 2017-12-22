//
//  main.cpp
//  BST
//
//  Created by Tommy on 2017/11/27.
//  Copyright © 2017 Tommy. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <cstdlib>
std::ifstream fin;
std::ofstream fout;
static char cb;
class BST;
class TreeNode {
public:
    
    TreeNode(unsigned long long int k) : leftchild(0), rightchild(0), key(k),dir('N'),x(-1),frequency(-1){}
    TreeNode(unsigned long long int k, char s, unsigned long long int u):leftchild(0), rightchild(0), key(k),dir(s),x(u),frequency(u){}
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
    
    unsigned long long int key;
    char dir;
    unsigned long long int x;
    unsigned long long int frequency;
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
    void Delete(unsigned long long int key,char token);
    void Drop(unsigned long long int number);
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
}

void BST::maxchild(TreeNode*n) {
    // this node should not be a null pointer, because this case is the two child case
    TreeNode* q;
    //the xcode will note that q may be uninitalized because I assume the k 's leftchild is not nullat first
    // so q will be assigned after the first branch
    q = n->leftchild;
    TreeNode* k = n->leftchild;
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
    for(;;k = k->rightchild) {
        // so k == q when initial
            if (k->rightchild == 0) {
                this->Replace(n,k);
                q->rightchild = 0;
                k = 0;
                return ;
            }
            q = k;
    }
}

void BST::minchild(TreeNode*n) {
    // this node should not be a null pointer, because this case is the two child case
    TreeNode* q;
    //the xcode will note that q may be uninitalized because I assume the k 's leftchild is not nullat first
    // so q will be assigned after the first branch
    q = n->rightchild;
    for(TreeNode* k = n->rightchild;;k = k->leftchild) {
        // so k == q when initial
        if (k->leftchild == 0 && k->rightchild == 0) {
            this->Replace(n,k);
            n->rightchild = 0;
            k = 0;
            break;
        }
        else if (!k->leftchild) {
            this->Replace(n,k);
            n->rightchild = k->rightchild;
            k = 0;
            break;
        }
        else {
            if (k->leftchild == 0) {
                this->Replace(n,k);
                q->leftchild = 0;
                k = 0;
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

void BST::Delete(unsigned long long int k,char token) {
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
            if (p == root) {p = 0; return ;}
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



void BST::Drop(unsigned long long int number) {
    //==============
    // prevent error
    if (!root) {fout <<"Tree is empty." << std::endl; return ;}
    //==============
    
    
    for (unsigned long long int i = 0; i < number; i++) {
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
 
    fin.open(argv[1],std::ios::in);
    fout.open(argv[2],std::ios::out);

    std::string str;
    while (getline(fin,str,' ')) {
    if (str == "add") {
        //std::cout << "add";
        getline(fin,str,' ');
        unsigned long long int key = std::atoi(str.c_str());
        getline(fin,str,' ');
        char token = *str.c_str();
        getline(fin,str,'\n');
        unsigned long long int frequency = std::atoi(str.c_str());
        //std::cout << key << " " << token << " " << frequency;
        TreeNode* k = new TreeNode(key,token,frequency);
        T.Insert(k);
    }
    else if (str == "deleteR") {
       // std::cout << "deleteR ";
        getline(fin,str,'\n');
        unsigned long long int key = std::atoi(str.c_str());
        //std::cout << key;
        T.Delete(key,'R');
    }
    else if (str == "deleteL") {
       // std::cout << "deleteL ";
        getline(fin,str,'\n');
        unsigned long long int key = std::atoi(str.c_str());
        //std::cout << key;
        T.Delete(key,'L');
    }
    else {
       // std::cout << "drop ";
        getline(fin,str,'\n');
        unsigned long long int time = std::atoi(str.c_str());
        //std::cout << time;
        T.Drop(time);
    }
    //std::cout << std::endl;
    }
    fin.close();
    fout.close();
    return 0;

}

