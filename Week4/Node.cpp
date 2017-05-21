#include "Node.h"

Node::Node(std::string data)
{
    dataString = data;
    count = 1;
    left = 0;
    right = 0;
    parent = 0;
}