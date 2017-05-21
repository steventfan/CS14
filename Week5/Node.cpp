#include <string>
#include "Node.h"

Node::Node()
{
    small = "";
    large = "";
    left = 0;
    middle = 0;
    right = 0;
    parent = 0;
}

Node::Node(string data)
{
    small = data;
    large = "";
    left = 0;
    middle = 0;
    right = 0;
    parent = 0;
}