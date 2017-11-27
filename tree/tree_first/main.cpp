//
//  main.cpp
//  tree_first
//
//  Created by Tommy on 2017/11/25.
//  Copyright © 2017年 Tommy. All rights reserved.
//

#include <iostream>
#include <string>
#include <queue>
#include <stack>

class BinaryTree;
class TreeNode {
public:
    TreeNode* leftchild;
    TreeNode* rightchild;
    TreeNode* parent;
    std::string str;
    
    TreeNode(): leftchild(0),rightchild(0),parent(0),str(""){};
    TreeNode(std::string s):leftchild(0),rightchild(0),parent(0),str(s){};
    TreeNode(const TreeNode& t) {
        this->leftchild = t.leftchild;
        this->rightchild = t.rightchild;
        this->parent = t.parent;
        this->str = t.str;
    }
    friend class BinaryTree;
};

class BinaryTree {
public:
    TreeNode* root;
    BinaryTree(): root(0){};
    BinaryTree(TreeNode* node): root(node){};
    
    void Preorder(TreeNode* current);
    void Inorder(TreeNode* current);
    void Postorder(TreeNode* current);
    void Levelorder();
};

class InorderIterator {
private:
    const BinaryTree& t;
    std::stack<TreeNode* > s;
    TreeNode* current;
public:
    std::string* Next();
    InorderIterator operator++(int) {
        while(current) {
            this->s.push(current);
            current = current -> leftchild;
        }
        if (!s.empty()) {
            current = s.top();
            s.pop();
            static InorderIterator* tmp;

            current = current->rightchild;
            return *tmp;
        }
    
        return *this;
    }
    
    InorderIterator(const BinaryTree& tree): t(tree), current(tree.root){};
    //InorderIterator() {}
    InorderIterator(const InorderIterator& p): t(p.t), current(p.current), s(p.s){}
    void Get() {std::cout << this->current->str;}
    
};

/*
TreeNode* InorderIterator::operator++(){
    while(current) {
        this->s.push(current);
        current = current -> leftchild;
    }
    if (!s.empty()) {
        current = s.top();
        s.pop();
        return current;
    }
    return 0;
}
*/
std::string* InorderIterator::Next() {
    while(current) {
        s.push(current);
        current = current -> leftchild;
    }
    if (! s.empty()) {
        current = s.top();
        s.pop();
        std::string& tmp = current->str;
        current = current->rightchild;
        return &tmp;
    }
    else return 0;
}

void BinaryTree::Preorder(TreeNode* current) {
    if (current) {
        std::cout << current->str << std::endl;
        Preorder(current->leftchild);
        Preorder(current->rightchild);
    }
}

void BinaryTree::Inorder(TreeNode* current) {
    if (current) {
        Inorder(current->leftchild);
        std::cout << current->str << std::endl;
        Inorder(current->rightchild);
    }
}

void BinaryTree::Postorder(TreeNode* current) {
    if (current) {
        Postorder(current->leftchild);
        Postorder(current->rightchild);
        std::cout << current->str << std::endl;
    }
}

void BinaryTree::Levelorder() {
    std::queue< TreeNode* > q;
    TreeNode* current = root;
    while (current) {
        std::cout << current->str;
        if (current->leftchild) q.push(current->leftchild);
        if (current->rightchild) q.push(current->rightchild);
        //=======================
        if (q.empty()) return ;
        current = q.front();
        q.pop();
        
    }
}

int main(int argc, const char * argv[]) {
    
    TreeNode* nodeA = new TreeNode("A");
    TreeNode* nodeB = new TreeNode("B");
    TreeNode* nodeC = new TreeNode("C");
    TreeNode* nodeD = new TreeNode("D");
    TreeNode* nodeE = new TreeNode("E");
    TreeNode* nodeF = new TreeNode("F");
    TreeNode* nodeG = new TreeNode("G");
    TreeNode* nodeH = new TreeNode("H");
    TreeNode* nodeI = new TreeNode("I");
    
    
    nodeA->leftchild = nodeB; nodeA->rightchild = nodeC;
    nodeB->leftchild = nodeD; nodeB->rightchild = nodeE;
    nodeE->leftchild = nodeG; nodeE->rightchild = nodeH;
    nodeC->leftchild = nodeF;
    nodeF->rightchild = nodeI;
    
    BinaryTree T(nodeA);
    InorderIterator i(T);
    //std::cout << *(i.Next());
    i++;
    i.Get();
    //i++;
    //i.Get();
    //std::cout << *(i.Next());
      //  std::cout << *(i.Next());
        //std::cout << *(i.Next());
    //T.Preorder(T.root);
    //T.Inorder(T.root);
    //T.Postorder(T.root);
    //T.Levelorder();
    return 0;
}
