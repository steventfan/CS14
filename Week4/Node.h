#ifndef NODE_H
#define NODE_H

#include <string>

class Node
{
    friend class BSTree;
    private:
        std::string dataString;
        int count;
        Node *left;
        Node *right;
        Node *parent;
    public:
        Node(std::string);
        Node& operator=(const Node& data);
};

#endif