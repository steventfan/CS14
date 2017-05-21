#include <iostream>
#include <string>
#include "BSTree.h"
#include "Node.h"

BSTree::BSTree()
{
    root = 0;
}

Node& Node::operator=(const Node& data)
{
    if(this != &data)
    {
        this->dataString = data.dataString;
        this->count = data.count;
    }
    
    return *this;
}

Node * BSTree::search(const std::string &data, Node *current) const
{
    if(current != 0)
    {
        if(data == current->dataString)
        {
            return current;
        }
        else
        {
            if(data < current->dataString)
            {
                return search(data, current->left);
            }
            else
            {
                return search(data, current->right);
            }
        }
    }
    else
    {
        return 0;
    }
}

void BSTree::inOrder(Node *current) const
{
    if(current != 0)
    {
        inOrder(current->left);
        std::cout << current->dataString << '(' << current->count << "), ";
        inOrder(current->right);
    }
}

void BSTree::postOrder(Node *current) const
{
    if(current != 0)
    {
        postOrder(current->left);
        postOrder(current->right);
        std::cout << current->dataString << '(' << current->count << "), ";
    }
}

void BSTree::preOrder(Node *current) const
{
    if(current != 0)
    {
        std::cout << current->dataString << '(' << current->count << "), ";
        preOrder(current->left);
        preOrder(current->right);
    }
}

void BSTree::remove(Node *data)
{
    Node *current = data;
    Node *successor = 0;
    
    if(current->left == 0 && current->right == 0)
    {
        if(current->parent != 0)
        {
            if(current->parent->left == current)
            {
                current->parent->left = 0;
            }
            else
            {
                current->parent->right = 0;
            }
        }
        else
        {
            root = 0;
        }
        delete current;
    }
    else if(current->left != 0)
    {
        successor = current->left;
        while(successor->right != 0)
        {
            successor = successor->right;
        }
        *current = *successor;
        remove(successor);
    }
    else
    {
        successor = current->right;
        while(successor->left != 0)
        {
            successor = successor->left;
        }
        *current = *successor;
        remove(successor);
    }
}

void BSTree::insert(const std::string &data)
{
    Node *current = root;
    
    if(search(data) )
    {
        current = search(data, root);
        current->count = current->count + 1;
    }
    else
    {
        Node *newNode = new Node(data);
        
        if(root == 0)
        {
            root = newNode;
        }
        else
        {
            while(1)
            {
                if(data < current->dataString)
                {
                    if(current->left == 0)
                    {
                        current->left = newNode;
                        newNode->parent = current;
                        
                        return;
                    }
                    else
                    {
                        current = current->left;
                    }
                }
                else
                {
                    if(current->right == 0)
                    {
                        current->right = newNode;
                        newNode->parent = current;
                        
                        return;
                    }
                    else
                    {
                        current = current->right;
                    }
                }
            }
        }
    }
}

bool BSTree::search(const std::string &data) const
{
    return search(data, root);
}

void BSTree::inOrder() const
{
    inOrder(root);
    std::cout << std::endl;
}

void BSTree::postOrder() const
{
    postOrder(root);
    std::cout << std::endl;
}

void BSTree::preOrder() const
{
    preOrder(root);
    std::cout << std::endl;
}

std::string BSTree::largest() const
{
    Node *current = root;
    
    if(current == 0)
    {
        return "";
    }
    else
    {
        while(1)
        {
            if(current->right == 0)
            {
                return current->dataString;
            }
            else
            {
                current = current->right;
            }
        }
    }
}

std::string BSTree::smallest() const
{
    Node *current = root;
    
    if(current == 0)
    {
        return "";
    }
    else
    {
        while(1)
        {
            if(current->left == 0)
            {
                return current->dataString;
            }
            else
            {
                current = current->left;
            }
        }
    }
}

int BSTree::height(const std::string &data) const
{
    if(!search(data) )
    {
        return -1;
    }
    Node *current = search(data, root);
    Node *currentLeft = current;
    Node *currentRight = current;
    int leftCount = 0;
    int rightCount = 0;
    
    if(current->left != 0)
    {
        currentLeft = currentLeft->left;
        leftCount++;
        leftCount = leftCount + height(currentLeft->dataString);
    }
    if(current->right != 0)
    {
        currentRight = currentRight->right;
        rightCount++;
        rightCount = rightCount + height(currentRight->dataString);
    }
    if(leftCount >= rightCount)
    {
        return leftCount;
    }
    else
    {
        return rightCount;
    }
}

void BSTree::remove(const std::string &data)
{
    if(search(data) )
    {
        Node *current = search(data, root);
        
        if(current->count > 1)
        {
            current->count = current->count - 1;
        }
        else
        {
            remove(current);
        }
    }
}