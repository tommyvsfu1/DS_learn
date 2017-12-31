#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

ifstream infile;
ofstream outfile;


class BST;

class TreeNode
{
private:
    TreeNode *leftchild;
    TreeNode *rightchild;
    TreeNode *parent;
    int key;
    string element;
    int Z;
    int counter; //the number of passing node
    
public:
    TreeNode():leftchild(0),rightchild(0),parent(0),key(0),element(""),Z(0),counter(0){};
    TreeNode(int a, string b, int c):leftchild(0),rightchild(0),parent(0),key(a),element(b),Z(c),counter(0){};
    
    int Getkey(){return key;}  //check node
    string GetElement(){return element;} //check node
    
    friend class BST;
    
};

class BST
{
private:
    TreeNode *root;
    TreeNode* Leftmost(TreeNode *current);
    TreeNode* Successor(TreeNode *current);
    TreeNode* Rightmost(TreeNode *current);
    TreeNode* Predecessor(TreeNode *current);
public:
    BST():root(0){};
    
    TreeNode* Search(int key);
    void InsertBST(int key, string element, int x);
    void InorderPrint();   //check BST success
    void Levelorder();    // check BST success
    void Drop(int N);
    void DeleteR(int key);
    void DeleteL(int key);
};

TreeNode* BST::Search(int KEY)
{
    TreeNode *current = root;   //point current to root as the beginning
    
    while(current != NULL && KEY != current->key)
    {
        if(KEY < current->key)
        {
            current = current->leftchild;
        }
        else
        {
            current = current->rightchild;
        }
    }
    return current;
}

void BST::InsertBST(int key, string element, int Z)
{
    TreeNode *y = 0;  //parent to be
    TreeNode *x = 0;
    TreeNode *insert_node = new TreeNode(key, element, Z);
    
    x = root;
    while (x != NULL)
    {
        y = x;
        if (insert_node->key < x->key)
        {
            x = x->leftchild;
        }
        else
        {
            x = x->rightchild;
        }
    }
    //x = NULL; y = parent of insert_node
    
    insert_node->parent = y;
    
    //the following if-else: attach insert_node to BST
    
    if (y == NULL)
    {
        this->root = insert_node;
    }
    else if (insert_node->key == y->key)
    {
        y->element = insert_node->element;
        y->Z = insert_node->Z;
        y->counter = 0;
    }
    else if (insert_node->key < y->key)
    {
        y->leftchild = insert_node;
    }
    else
    {
        y->rightchild = insert_node;
    }
    
    
}

TreeNode* BST::Rightmost(TreeNode *current)
{
    while(current->rightchild != NULL)
    {
        current = current->rightchild;
    }
    return current;
}

TreeNode* BST::Predecessor(TreeNode *current)
{
    if(current->leftchild != NULL)
    {
        return Rightmost(current->leftchild);
    }
}


TreeNode* BST::Leftmost(TreeNode *current)
{
    while (current->leftchild != NULL)
    {
        current = current->leftchild;
    }
    return current;
}

TreeNode* BST::Successor(TreeNode *current)
{
    if(current->rightchild != NULL)
    {
        return Leftmost(current->rightchild);
    }
}

void BST::InorderPrint()
{
    TreeNode *current = new TreeNode;
    current = Leftmost(root);
    while(current)
    {
        cout<<"id: "<<current->key<<" Dir: "<<current->element<<" X: "<<current->Z<<endl;
        current = Successor(current);
    }
}

void BST::Levelorder()
{
    queue<TreeNode*> q;
    q.push(this->root);
    
    while(!q.empty())
    {
        TreeNode *current = q.front();
        q.pop();
        cout<<"id: "<<current->key<<" Dir: "<<current->element<<" X: "<<current->Z<<endl;
        
        if(current->leftchild != NULL)
        {
            q.push(current->leftchild);
        }
        if(current->rightchild != NULL)
        {
            q.push(current->rightchild);
        }
    }
}

void BST::Drop(int N)
{
    for (int i = 1; i < N; i++)
    {
        queue<TreeNode*> q;
        q.push(this->root);
        if (this->root == NULL)
        {
            outfile<<"Tree is empty."<<endl;
            return;
        }
        
        while(!q.empty())
        {
            TreeNode *current = q.front();
            q.pop();
            //cout<<current->key<<" ";
            
            if(current->element == "L" && current->leftchild != NULL)
            {
                q.push(current->leftchild);
            }
            else if(current->element == "R" && current->rightchild != NULL)
            {
                q.push(current->rightchild);
            }
            
            current->counter = current->counter + 1;
            if(current->counter == current->Z && current->Z != 0)
            {
                current->counter = 0;
                if(current->element == "L")
                {
                    current->element = "R";
                }
                else
                {
                    current->element = "L";
                }
            }
            
            
        }
        
        
    }
    queue<TreeNode*> q;
    q.push(this->root);
    
    while(!q.empty())
    {
        TreeNode *current = q.front();
        q.pop();
        outfile<<current->key<<" ";
        
        if(current->element == "L" && current->leftchild != NULL)
        {
            q.push(current->leftchild);
        }
        else if(current->element == "R" && current->rightchild != NULL)
        {
            q.push(current->rightchild);
        }
        
        current->counter = current->counter + 1;
        if(current->counter == current->Z && current->Z != 0)
        {
            current->counter = 0;
            if(current->element == "L")
            {
                current->element = "R";
            }
            else
            {
                current->element = "L";
            }
        }
        
        
    }
}

void BST::DeleteR(int KEY)
{
    TreeNode *delete_node = Search(KEY);
    if (delete_node == NULL)
    {
        outfile<<"Deletion failed.\n";
        return;
    }
    
    TreeNode *y = 0;  //deleted node
    TreeNode *x = 0;  //child of deleted node
    
    //case1 case2
    if (delete_node->leftchild == NULL || delete_node->rightchild == NULL)
    {
        y = delete_node;
    }
    else
    {
        y = Successor(delete_node);
    }
    
    if (y->leftchild != NULL)
    {
        x = y->leftchild;
    }
    else
    {
        x = y->rightchild;
    }
    
    if (x != NULL)
    {
        x->parent = y->parent;
    }
    
    if (y->parent == NULL)
    {
        this->root = x;
    }
    else if (y == y->parent->leftchild)
    {
        y->parent->leftchild = x;
    }
    else
    {
        y->parent->rightchild = x;
    }
    
    //case 3
    if (y != delete_node)
    {
        delete_node->key = y->key;
        delete_node->element = y->element;
        delete_node->Z = y->Z;
        delete_node->counter = y->counter;
    }
    
    delete y;
    y = 0;
    
}

void BST::DeleteL(int KEY)
{
    TreeNode *delete_node = Search(KEY);
    if (delete_node == NULL)
    {
        outfile<<"Deletion failed.\n";
        return;
    }
    
    TreeNode *y = 0;  //deleted node
    TreeNode *x = 0;  //child of deleted node
    
    //case1 case2
    if (delete_node->leftchild == NULL || delete_node->rightchild == NULL)
    {
        y = delete_node;
    }
    else
    {
        y = Predecessor(delete_node);
    }
    
    if (y->leftchild != NULL)
    {
        x = y->leftchild;
    }
    else
    {
        x = y->rightchild;
    }
    
    if (x != NULL)
    {
        x->parent = y->parent;
    }
    
    if (y->parent == NULL)
    {
        this->root = x;
    }
    else if (y == y->parent->leftchild)
    {
        y->parent->leftchild = x;
    }
    else
    {
        y->parent->rightchild = x;
    }
    
    //case 3
    if (y != delete_node)
    {
        delete_node->key = y->key;
        delete_node->element = y->element;
        delete_node->Z = y->Z;
        delete_node->counter = y->counter;
    }
    
    delete y;
    y = 0;
    
}


int main(int argc, char* argv[])
{
    infile.open (argv[1]);
    outfile.open(argv[2]);
    BST T;
    string s;
    int id;
    int X;
    int n;
    
    
    // infile.open("case.txt");
    if(!infile)
    {
        cerr<<"Unable to open file case.txt"<<endl;
        exit(1);
    }
    
    // outfile.open("test.txt");
    if(!outfile)
    {
        cerr<<"Unable to open the file test.txt"<<endl;
        exit(1);
    }
    
    while(infile>>s)
    {
        if(s == "add")
        {
            infile>>id;
            infile>>s;
            infile>>X;
            T.InsertBST(id,s,X);
        }
        else if (s == "drop")
        {
            infile>>n;
            T.Drop(n);
            outfile<<endl;
        }
        else if (s == "deleteR")
        {
            infile>>id;
            T.DeleteR(id);
        }
        else if (s == "deleteL")
        {
            infile>>id;
            T.DeleteL(id);
        }
    }
    
    /*
     cout<<"Inorder Traversal:\n";
     T.InorderPrint();
     cout<<endl;
     
     
     cout<<"Levelorder Traversal:\n";
     T.Levelorder();
     cout<<endl;
     
     */
    
    
    
    
    return 0;
}

