/*

This is an implementation of an AVL tree using: 

note: insertNode and deleteNode always take in the root node and return the root node. 


*/

// AVL tree implementation in C++

#include <iostream>
using namespace std;

class Node
{
    public:
        int key;
        Node *left;
        Node *right;
        int height;
};

int max(int a, int b);

int height(Node* N)
{
    if(N == NULL)
    {
        return 0;
    }
    return N->height;

}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

Node* newNode(int key)
{
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return(node);
}

Node* rightRotate(Node *y)
{
    Node* x = y->left;
    Node* T2 = x->right;
    
    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right) + 1);
    x->height = max(height(x->left), height(x->right) + 1);

    return x;

}

Node* leftRotate(Node *x)
{
    Node *y = x->right; //whatever it is pointing to
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right) + 1 );
    y->height = max(height(y->left), height(y->right) + 1 );

    return y;

}

int getBalanceFactor(Node *N)
{
    if(N == NULL)
    {
        return 0;
    }
    else
    {
        return height(N->left) - height(N->right);
    }
}

Node *insertNode(Node *node, int key)
{
    if(node == NULL)
    {
        return newNode(key); //if node can be placed there, just place it there
                            //newNode allocates the memory
    }
    if(key < node->key)
    {
        node->left = insertNode(node->left, key); //if you find the space of node is occupied by an actual node, run a comparison to that node's keys to see if it should go to the left or right of node
                                                            //recursively call insertNode
    }
    else if(key > node->key)
    {
        node->right = insertNode(node->right, key);
    }
    else
    {
        return node;
    }

    //here only if the case 2 and 3 of the if, then series gets called:
    node->height = 1 + max(height(node->left), height(node->right)); //all other calls would have happened so height of left and right node are updated.
    int balanceFactor = getBalanceFactor(node);
    if(balanceFactor > 1)
    {
        if(key < node->left->key)
        {
            return rightRotate(node);
        }
        else if(key > node->left->key)
        {
            node->left = leftRotate(node->left); //left-right
            return rightRotate(node);
        }
    }
    if(balanceFactor < -1)
    {
        if(key > node->right->key)
        {
            return leftRotate(node);
        }
        else if(key < node->right->key )
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    return node;
}

Node* nodeWithMinimumValue(Node *node)
{
    Node *current = node;
    while(current->left != NULL)
    {
        current = current->left;
    }
    return current;
}


Node* deleteNode(Node *root, int key)
{
    //fine the node and delete it
    if(root == NULL)
    {
        return root;
    }
    if(key < root->key)
    {
        root->left = deleteNode(root->left, key);
    }
    else if(key > root->key)
    {
        root->right = deleteNode(root->right, key);
    }
    else //if(key == root->key)
    {
        if((root->left == NULL) || root->right == NULL)
        {
            Node *temp = root->left ? root->left : root->right;
            if(temp == NULL)
            {
                temp = root;
                root = NULL; //this can also be free(root);
                                            //  root = NULL;
            }
            else
            {
                *root = *temp;
            }
            free(temp); //freeing temp, that is why we do temp = rooot before (so we can delete the leafnode)
                        // single pointer A pointing to single pointer B means single pointer A points to the same address that B is pointing to, so deleting(A) means deleting the memory address also pointed to by B
                            //in case A, this means that root is now deleted
                            //in case B, this means that the child is now deleted 
        }
        else
        {
            Node *temp = nodeWithMinimumValue(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }

    }

    if(root == NULL)
    {
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right)); //adding the 1 is not because 1 was added or deleted, that is automatically corrected by the recursive nature of this code, the +1 is because
                                                                        //there is still a 'bridge' between the left node and right not from the root node of that subtree.
    int balanceFactor = getBalanceFactor(root);

    if(balanceFactor>1)
    {
        if(getBalanceFactor(root->left) >= 0)
        {
            return rightRotate(root);
        }
        else
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if(balanceFactor < -1)
    {
        if(getBalanceFactor(root->right) <= 0)
        {
            return leftRotate(root);
        }
        else
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }

    return root;
}

void printTree(Node *root, string indent, bool last)
{
    if(root != nullptr)
    {
        cout << indent;
        if(last)
        {
            cout << "R----";
            indent += "   ";
        }
        else
        {
            cout << "L----";
            indent += "|  ";
        }
        cout << root->key << endl;
        printTree(root->left, indent, false);
        printTree(root->right, indent, true);
    }
}

int main() {
  Node *root = NULL;
  root = insertNode(root, 33);
  root = insertNode(root, 13);
  root = insertNode(root, 53);
  root = insertNode(root, 9);
  root = insertNode(root, 21);
  root = insertNode(root, 61);
  root = insertNode(root, 8);
  root = insertNode(root, 11);
  printTree(root, "", true);
  root = deleteNode(root, 13);
  cout << "After deleting " << endl;
  printTree(root, "", true);
}
