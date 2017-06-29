#ifndef JUG_H
#define JUG_H

//using vector, stack libraries (Source: www.cplusplus.com)

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <climits>

class Vertex
{
    friend class Jug;
    public:
        Vertex(int, int);
    private:
        int amountA;
        int amountB;
        int previous;
        unsigned int distance;
        bool unvisited;
        std::vector<std::pair<unsigned int, std::string> > neighbors;
};

class Jug
{
    public:
        Jug(int, int, int, int, int, int, int, int, int);
        ~Jug();
        //solve is used to check input and find the solution if one exists
        //returns -1 invalid inputs. solution set to empty string.
        //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
        //returns 1 if solution is found and stores solution steps in solution string.
        int solve(std::string &);
    private:
        //anything else you need
        int Ca;
        int Cb;
        int N;
        int cfA;
        int cfB;
        int ceA;
        int ceB;
        int cpAB;
        int cpBA;
        std::stack<unsigned int> process;
        std::vector<unsigned int> visited;
        std::vector<Vertex> vertices;
        std::stack<std::string> traverse;
        void graph();
        unsigned int fillA(unsigned int);
        unsigned int fillB(unsigned int);
        unsigned int emptyA(unsigned int);
        unsigned int emptyB(unsigned int);
        unsigned int pourAB(unsigned int);
        unsigned int pourBA(unsigned int);
        std::string dijkstra();
        int getCost(std::string) const;
};

#endif