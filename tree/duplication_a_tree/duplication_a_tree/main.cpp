//
//  main.cpp
//  duplication_a_tree
//
//  Created by Tommy on 2017/11/26.
//  Copyright © 2017年 Tommy. All rights reserved.
//
#include <iostream>
class BinaryTree;

class TreeNode {
public:
    TreeNode* leftchild;
    TreeNode* rightchild;
    TreeNode* current;
    std::string str;

    TreeNode(std::string s) : leftchild(0), rightchild(0),current(0),str(s){}
        TreeNode(TreeNode* t) : leftchild(0), rightchild(0),current(t),str(" "){}
    TreeNode() : leftchild(0), rightchild(0),current(0){}
    friend class BinaryTree;
};

class BinaryTree {

public:
     TreeNode* root;
    BinaryTree(TreeNode* t): root(t){}
    TreeNode* copy(TreeNode* orig) {
        if (orig) {
            TreeNode* tmp = new TreeNode;
            tmp->str = orig->str;
            tmp->leftchild = copy(tmp->leftchild);
            tmp->rightchild = copy(tmp->rightchild);
            return tmp;
        }
        return 0;
    }
};



int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
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
    
    
    return 0;
}
