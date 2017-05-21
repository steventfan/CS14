#include <iostream>
#include <string>
#include "Tree.h"

Tree::Tree( )
{
    root = 0;
}

Tree::~Tree( )
{
    //calls deconstructor helper function
    deletion(root);
}

void Tree::insert(const string &data)
{
    if(root == 0)
    {
        root = new Node(data);
        
        return;
    }
    Node *current = root;
    
    while(1)
    {
        //if current has no children
        if(current->left == 0 && current->middle == 0 && current->right == 0)
        {
            if(current->large.empty() )
            {
                if(data > current->small)
                {
                    current->large = data;
                }
                else
                {   
                    current->large = current->small;
                    current->small = data;
                }
            }
            else
            {
                split(current, data, 0, 0);
            }
            
            return;
        }
        //else current has children
        else
        {
            if(data < current->small)
            {
                current = current->left;
            }
            else if( !(current->large.empty() ) )
            {
                if(data < current->large)
                {
                    current = current->middle;
                }
                else if(data > current->large)
                {
                    current = current->right;
                }
            }
            else if(data > current->large)
            {
                current = current->right;
            }
        }
    }
}

void Tree::preOrder( ) const
{
    preOrder(root);
    std::cout << std::endl;
}

void Tree::inOrder( ) const
{
    inOrder(root);
    std::cout << std::endl;
}

void Tree::postOrder( ) const
{
    postOrder(root);
    std::cout << std::endl;
}

void Tree::remove(const string &data)
{
    if( !(search(data) ) )
    {
        return;
    }
    Node *current = search(root, data);
    Node *swap = current;
    
    //find successor or itself if none
    //initial movement from node
    if(current->middle != 0 && current->small == data)
    {
        swap = current->middle;
    }
    else if(current->right != 0)
    {
        swap = current->right;
    }
    //find inorder successor
    while(swap->left != 0 || swap->middle != 0 || swap->right != 0)
    {
        swap = swap->left;
    }
    if(current->small == data)
    {
        current->small = swap->small;
        //if node to delete is a 2-node, fix
        if(swap->large.empty() )
        {
            swap->small.clear();
            fix(swap, 0);
        }
        else
        {
            swap->small = swap->large;
            swap->large.clear();
        }
    }
    else
    {
        if(current != swap)
        {
            current->large = swap->small;
            //if node to delete is a 2-node, fix
            if(swap->large.empty() )
            {
                swap->small.clear();
                fix(swap, 0);
            }
            else
            {
                swap->small = swap->large;
                swap->large.clear();
            }
        }
        else
        {
            swap->large.clear();
        }
    }
}

bool Tree::search(const string &data) const
{
    //if search is true, returns Node*, else returns 0 (false)
    return search(root, data);
}

void Tree::split(Node *current, const string& data, Node *leftChild, Node *rightChild)
{
    std::string midValue;
    Node *leftNode;
    Node *rightNode;
    
    //find small, middle, and large value
    if(data > current->small && data < current->large)
    {
        midValue = data;
        leftNode = new Node(current->small);
        rightNode = new Node(current->large);
    }
    else if(current->small > data)
    {
        midValue = current->small;
        leftNode = new Node(data);
        rightNode = new Node(current->large);
    }
    else
    {
        midValue = current->large;
        leftNode = new Node(current->small);
        rightNode = new Node(data);
    }
    //append middle value to parent/create new parent
    if(current->parent == 0)
    {
        root = new Node(midValue);
        
        root->left = leftNode;
        leftNode->parent = root;
        root->right = rightNode;
        rightNode->parent = root;
    }
    else if(current->parent->large.empty() )
    {
        if(midValue > current->parent->small)
        {
            current->parent->large = midValue;
        }
        else
        {
            current->parent->large = current->parent->small;
            current->parent->small = midValue;
        }
        if(leftNode->small < current->parent->small)
        {
            current->parent->left = leftNode;
            current->parent->middle = rightNode;
        }
        else
        {
            current->parent->middle = leftNode;
            current->parent->right = rightNode;
        }
        leftNode->parent = current->parent;
        rightNode->parent = current->parent;
    }
    else
    {
        split(current->parent, midValue, leftNode, rightNode);
    }
    //if current is not a leaf, connect with previous values from recursion
    if(current->left != 0 || current->middle != 0 || current->right != 0)
    {
        if(leftChild->small < leftNode->small)
        {
            leftNode->left = leftChild;
            leftChild->parent = leftNode;
            leftNode->right = rightChild;
            rightChild->parent = leftNode;
            rightNode->left = current->middle;
            rightNode->left->parent = rightNode;
            rightNode->right = current->right;
            rightNode->right->parent = rightNode;
        }
        else if(rightChild->small > rightNode->small)
        {
            leftNode->left = current->left;
            leftNode->left->parent = leftNode;
            leftNode->right = current->middle;
            leftNode->right->parent = leftNode;
            rightNode->left = leftChild;
            leftChild->parent = rightNode;
            rightNode->right = rightChild;
            rightChild->parent = rightNode;
        }
        else
        {
            leftNode->left = current->left;
            leftNode->left->parent = leftNode;
            leftNode->right = leftChild;
            leftChild->parent = leftNode;
            rightNode->left = rightChild;
            rightChild->parent = rightNode;
            rightNode->right = current->right;
            rightNode->right->parent = rightNode;
        }
    }
    delete current;
}

void Tree::preOrder(Node *current) const
{
    if(current != 0)
    {
        if(current->large.empty() )
        {
            std::cout << current->small << ", ";
            preOrder(current->left);
            preOrder(current->right);
        }
        else
        {
            std::cout << current->small << ", ";
            preOrder(current->left);
            std::cout << current->large << ", ";
            preOrder(current->middle);
            preOrder(current->right);
        }
    }
}

void Tree::inOrder(Node *current) const
{
    if(current != 0)
    {
        if(current->large.empty() )
        {
            inOrder(current->left);
            std::cout << current->small << ", ";
            inOrder(current->right);
        }
        else
        {
            inOrder(current->left);
            std::cout << current->small << ", ";
            inOrder(current->middle);
            std::cout << current->large << ", ";
            inOrder(current->right);
        }
    }
}

void Tree::postOrder(Node *current) const
{
    if(current != 0)
    {
        if(current->large.empty() )
        {
            postOrder(current->left);
            postOrder(current->right);
            std::cout << current->small << ", ";
        }
        else
        {
            postOrder(current->left);
            postOrder(current->middle);
            std::cout << current->small << ", ";
            postOrder(current->right);
            std::cout << current->large << ", ";
        }
    }
}

Node * Tree::search(Node *current, const string &data) const
{
    if(current != 0)
    {
        if(data == current->small)
        {
            return current;
        }
        if(data < current->small)
        {
            return search(current->left, data);
        }
        else if(current->large.empty() )
        {
            return search(current->right, data);
        }
        else
        {
            if(data == current->large)
            {
                return current;
            }
            else if(data < current->large)
            {
                return search(current->middle, data);
            }
            else
            {
                return search(current->right, data);
            }
        }
    }
    
    return 0;
}

void Tree::fix(Node *current, Node *child)
{
    if(current == root)
    {
        if(current->left != 0 || current->right != 0)
        {
            root = child;
        }
        else
        {
            root = 0;
        }
        delete current;
        
        return;
    }
    //if node to delete has no 3-node siblings (merge)
    if(current->parent->left->large.empty() && current->parent->middle->large.empty() && current->parent->right->large.empty() )
    {
        //if node is parent's left child
        if(current->parent->left == current)
        {
            current = current->parent;
            current->left->small = current->small;
            if(current->large.empty() )
            {
                current->left->large = current->right->small;
                current->small.clear();
                if(child != 0)
                {
                    current->left->left = child;
                    child->parent = current->left;
                    current->left->middle = current->right->left;
                    current->left->middle->parent = current->left;
                    current->left->right = current->right->right;
                    current->left->right->parent = current->left;
                }
                delete current->right;
                current->right = 0;
                fix(current, current->left);
            }
            else
            {
                current->left->large = current->middle->small;
                current->small = current->large;
                current->large.clear();
                if(child != 0)
                {
                    current->left->left = child;
                    child->parent = current->left;
                    current->left->middle = current->middle->left;
                    current->left->middle->parent = current->left;
                    current->left->right = current->middle->right;
                    current->left->right->parent = current->left;
                }
                delete current->middle;
                current->middle = 0;
            }
        }
        //else if node is parent's right child
        else if(current->parent->right == current)
        {
            current = current->parent;
            if(current->large.empty() )
            {
                current->left->large = current->small;
                current->small.clear();
                delete current->right;
                current->right = 0;
                if(child != 0)
                {
                    current->left->middle = current->left->right;
                    current->left->middle->parent = current->left;
                    current->left->right = child;
                    child->parent = current->left;
                }
                fix(current, current->left);
            }
            else
            {
                current->right->large = current->large;
                current->large.clear();
                current->right->small = current->middle->small;
                if(child != 0)
                {
                    current->right->right = child;
                    child->parent = current->right;
                    current->right->middle = current->middle->right;
                    current->right->middle->parent = current->right;
                    current->right->left = current->middle->left;
                    current->right->left->parent = current->right;
                }
                delete current->middle;
                current->middle = 0;
            }
        }
        //else node is parent's middle child
        else
        {
            current = current->parent;
            current->left->large = current->small;
            current->small = current->large;
            current->large.clear();
            if(child != 0)
            {
                current->left->middle = current->left->right;
                current->left->middle->parent = current->left;
                current->left->right = child;
                child->parent = current->left;
            }
            delete current->middle;
            current->middle = 0;
        }
    }
    //else node to delete has 3-node siblings (redistribute)
    else
    {
        //if node is parent's left child
        if(current->parent->left == current)
        {
            current = current->parent;
            current->left->small = current->small;
            if(current->large.empty() )
            {
                current->small = current->right->small;
                current->right->small = current->right->large;
                current->right->large.clear();
                if(child != 0)
                {
                    current->left->left = child;
                    child->parent = current->left;
                    current->left->right = current->right->left;
                    current->left->right->parent = current->left;
                    current->right->left = current->right->middle;
                    current->right->left->parent = current->right;
                    current->right->middle = 0;
                }
            }
            else
            {
                current->small = current->middle->small;
                if(current->middle->large.empty() )
                {
                    current->middle->small = current->large;
                    current->large = current->right->small;
                    current->right->small = current->right->large;
                    current->right->large.clear();
                    if(child != 0)
                    {
                        current->left->left = child;
                        child->parent = current->left;
                        current->left->right = current->middle->left;
                        current->left->right->parent = current->left;
                        current->middle->left = current->middle->right;
                        current->middle->left->parent = current->middle;
                        current->middle->right = current->right->left;
                        current->middle->right->parent = current->middle;
                        current->right->left = current->right->middle;
                        current->right->left->parent = current->right;
                        current->right->middle = 0;
                    }
                }
                else
                {
                    current->middle->small = current->middle->large;
                    current->middle->large.clear();
                    if(child != 0)
                    {
                        current->left->left = child;
                        child->parent = current->left;
                        current->left->right = current->middle->left;
                        current->left->right->parent = current->left;
                        current->middle->left = current->middle->right;
                        current->middle->left->parent = current->middle;
                        current->middle->right = current->right->left;
                        current->middle->right->parent = current->middle;
                        current->right->left = current->right->middle;
                        current->right->left->parent = current->right;
                        current->right->middle = 0;
                    }
                }
            }
        }
        //else if node is parent's right child
        else if(current->parent->right == current)
        {
            current = current->parent;
            if(current->large.empty() )
            {
                current->right->small = current->small;
                current->small = current->left->large;
                current->left->large.clear();
                if(child != 0)
                {
                    current->right->right = child;
                    child->parent = current->right;
                    current->right->left = current->left->right;
                    current->right->left->parent = current->right;
                    current->left->right = current->left->middle;
                    current->left->right->parent = current->left;
                    current->left->middle = 0;
                }
            }
            else
            {
                current->right->small = current->large;
                if(current->middle->large.empty() )
                {
                    current->large = current->middle->small;
                    current->middle->small = current->small;
                    current->small = current->left->large;
                    current->left->large.clear();
                    if(child != 0)
                    {
                        current->right->right = child;
                        child->parent = current->right;
                        current->right->left = current->middle->right;
                        current->right->left->parent = current->right;
                        current->middle->right = current->middle->left;
                        current->middle->right->parent = current->middle;
                        current->middle->left = current->left->right;
                        current->middle->left->parent = current->middle;
                        current->left->right = current->left->middle;
                        current->left->right->parent = current->left;
                        current->left->middle = 0;
                    }
                }
                else
                {
                    current->large = current->middle->large;
                    current->middle->large.clear();
                    if(child != 0)
                    {
                        current->right->right = child;
                        child->parent = current->right;
                        current->right->left = current->middle->right;
                        current->right->left->parent = current->right;
                        current->middle->right = current->middle->middle;
                        current->middle->right->parent = current->middle;
                        current->middle->middle = 0;
                    }
                }
            }
        }
        //else node is parent's middle child
        else
        {
            current = current->parent;
            if(current->right->large.empty() )
            {
                current->middle->small = current->small;
                current->small = current->left->large;
                current->left->large.clear();
                if(child != 0)
                {
                    current->middle->right = child;
                    child->parent = current->middle;
                    current->middle->left = current->left->right;
                    current->middle->left->parent = current->middle;
                    current->left->right = current->left->middle;
                    current->left->right->parent = current->left;
                    current->left->middle = 0;
                }
            }
            else
            {
                current->middle->small = current->large;
                current->large = current->right->small;
                current->right->small = current->right->large;
                current->right->large.clear();
                if(child != 0)
                {
                    current->middle->left = child;
                    child->parent = current->middle;
                    current->middle->right = current->right->left;
                    current->middle->right->parent = current->middle;
                    current->right->left = current->right->middle;
                    current->right->left->parent = current->right;
                    current->right->middle = 0;
                }
            }
        }
    }
}

void Tree::deletion(Node *current)
{
    if(current != 0)
    {
        if(current->large.empty() )
        {
            deletion(current->left);
            deletion(current->right);
            delete current;
        }
        else
        {
            deletion(current->left);
            deletion(current->middle);
            deletion(current->right);
            delete current;
        }
    }
}