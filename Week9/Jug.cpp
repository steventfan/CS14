#include "Jug.h"

Vertex::Vertex(int amountA, int amountB)
{
    previous = -1;
    distance = UINT_MAX;
    unvisited = false;
    this->amountA = amountA;
    this->amountB = amountB;
}

Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA)
{
    this->Ca = Ca;
    this->Cb = Cb;
    this->N = N;
    this->cfA = cfA;
    this->cfB = cfB;
    this->ceA = ceA;
    this->ceB = ceB;
    this->cpAB = cpAB;
    this->cpBA = cpBA;
}

Jug::~Jug()
{
    
}

int Jug::solve(std::string &solution)
{
    if(Ca < 1 || Cb < 1 || Cb > 1000 || Ca > Cb || N < 0 || N > Cb || cfA < 0 || cfB < 0 || ceA < 0 || ceB < 0 || cpAB < 0 || cpBA < 0)
    {
        solution = "";
        
        return -1;
    }
    
    Vertex empty(0, 0);
    
    vertices.push_back(empty);
    process.push(0);
    graph();
    
    std::string success;
    
    success = dijkstra();
    if(success.empty() )
    {
        return 0;
    }
    while(!traverse.empty() )
    {
        solution += (traverse.top() + '\n');
        traverse.pop();
    }
    solution += success;
    
    return 1;
}

void Jug::graph()
{
    while(!process.empty() )
    {
        bool found = false;
        unsigned int current = process.top();
        
        process.pop();
        for(unsigned int i = 0; i < visited.size(); i++)
        {
            if(current == visited.at(i) )
            {
                found = true;
                
                break;
            }
        }
        if(!found)
        {
            visited.push_back(current);
            process.push(fillA(current) );
            process.push(fillB(current) );
            process.push(emptyA(current) );
            process.push(emptyB(current) );
            process.push(pourAB(current) );
            process.push(pourBA(current) );
        }
    }
}

unsigned int Jug::fillA(unsigned int current)
{
    unsigned int index;
    bool found = false;
    Vertex neighbor(Ca, vertices.at(current).amountB);
    
    for(unsigned i = 0; i < vertices.size(); i++)
    {
        if(vertices.at(i).amountA == neighbor.amountA && vertices.at(i).amountB == neighbor.amountB)
        {
            index = i;
            found = true;
            
            break;
        }
    }
    
    std::pair<unsigned int, std::string> pairing;
    
    if(found)
    {
        pairing = std::make_pair(index, "fill A");
    }
    else
    {
        vertices.push_back(neighbor);
        pairing = std::make_pair(vertices.size() - 1, "fill A");
    }
    vertices.at(current).neighbors.push_back(pairing);
    
    return vertices.at(current).neighbors.back().first;
}

unsigned int Jug::fillB(unsigned int current)
{
    unsigned int index;
    bool found = false;
    Vertex neighbor(vertices.at(current).amountA, Cb);
    
    for(unsigned i = 0; i < vertices.size(); i++)
    {
        if(vertices.at(i).amountA == neighbor.amountA && vertices.at(i).amountB == neighbor.amountB)
        {
            index = i;
            found = true;
            
            break;
        }
    }
    
    std::pair<unsigned int, std::string> pairing;
    
    if(found)
    {
        pairing = std::make_pair(index, "fill B");
    }
    else
    {
        vertices.push_back(neighbor);
        pairing = std::make_pair(vertices.size() - 1, "fill B");
    }
    vertices.at(current).neighbors.push_back(pairing);
    
    return vertices.at(current).neighbors.back().first;
}

unsigned int Jug::emptyA(unsigned int current)
{
    unsigned int index;
    bool found = false;
    Vertex neighbor(0, vertices.at(current).amountB);
    
    for(unsigned i = 0; i < vertices.size(); i++)
    {
        if(vertices.at(i).amountA == 0 && vertices.at(i).amountB == neighbor.amountB)
        {
            index = i;
            found = true;
            
            break;
        }
    }
    
    std::pair<unsigned int, std::string> pairing;
    
    if(found)
    {
        pairing = std::make_pair(index, "empty A");
    }
    else
    {
        vertices.push_back(neighbor);
        pairing = std::make_pair(vertices.size() - 1, "empty A");
    }
    vertices.at(current).neighbors.push_back(pairing);
    
    return vertices.at(current).neighbors.back().first;
}

unsigned int Jug::emptyB(unsigned int current)
{
    unsigned int index;
    bool found = false;
    Vertex neighbor(vertices.at(current).amountA, 0);
    
    for(unsigned i = 0; i < vertices.size(); i++)
    {
        if(vertices.at(i).amountA == neighbor.amountA && vertices.at(i).amountB == 0)
        {
            index = i;
            found = true;
            
            break;
        }
    }
    
    std::pair<unsigned int, std::string> pairing;
    
    if(found)
    {
        pairing = std::make_pair(index, "empty B");
    }
    else
    {
        vertices.push_back(neighbor);
        pairing = std::make_pair(vertices.size() - 1, "empty B");
    }
    vertices.at(current).neighbors.push_back(pairing);
    
    return vertices.at(current).neighbors.back().first;
}

unsigned int Jug::pourAB(unsigned int current)
{
    unsigned int index;
    bool found = false;
    int neighborA = vertices.at(current).amountA;
    int neighborB = vertices.at(current).amountB;
    
    while(neighborA > 0 && neighborB < Cb)
    {
        neighborA--;
        neighborB++;
    }
    
    Vertex neighbor(neighborA, neighborB);
    
    for(unsigned i = 0; i < vertices.size(); i++)
    {
        if(vertices.at(i).amountA == neighbor.amountA && vertices.at(i).amountB == neighbor.amountB)
        {
            index = i;
            found = true;
            
            break;
        }
    }
    
    std::pair<unsigned int, std::string> pairing;
    
    if(found)
    {
        pairing = std::make_pair(index, "pour A B");
    }
    else
    {
        vertices.push_back(neighbor);
        pairing = std::make_pair(vertices.size() - 1, "pour A B");
    }
    vertices.at(current).neighbors.push_back(pairing);
    
    return vertices.at(current).neighbors.back().first;
}

unsigned int Jug::pourBA(unsigned int current)
{
    unsigned int index;
    bool found = false;
    int neighborA = vertices.at(current).amountA;
    int neighborB = vertices.at(current).amountB;
    
    while(neighborA < Ca && neighborB > 0)
    {
        neighborA++;
        neighborB--;
    }
    
    Vertex neighbor(neighborA, neighborB);
    
    for(unsigned i = 0; i < vertices.size(); i++)
    {
        if(vertices.at(i).amountA == neighbor.amountA && vertices.at(i).amountB == neighbor.amountB)
        {
            index = i;
            found = true;
            
            break;
        }
    }
    
    std::pair<unsigned int, std::string> pairing;
    
    if(found)
    {
        pairing = std::make_pair(index, "pour B A");
    }
    else
    {
        vertices.push_back(neighbor);
        pairing = std::make_pair(vertices.size() - 1, "pour B A");
    }
    vertices.at(current).neighbors.push_back(pairing);
    
    return vertices.at(current).neighbors.back().first;
}

std::string Jug::dijkstra()
{
    for(unsigned int i = 0; i < vertices.size(); i++)
    {
        if(vertices.at(i).amountA == 0 && vertices.at(i).amountB == N)
        {
            break;
        }
        else if(i == vertices.size() - 1)
        {
            return "";
        }
    }
    
    std::vector<Vertex *> unvisited;
    unsigned index;
    
    for(unsigned i = 0; i < vertices.size(); i++)
    {
        Vertex *pointer = &vertices.at(i);
        
        unvisited.push_back(pointer);
    }
    unvisited.at(0)->distance = 0;
    while(!unvisited.empty() )
    {
        unsigned int minimum = 0;
        
        for(unsigned int i = 0; i < unvisited.size(); i++)
        {
            if(unvisited.at(i)->distance < unvisited.at(minimum)->distance)
            {
                minimum = i;
            }
        }
        for(unsigned int i = 0; i < vertices.size(); i++)
        {
            if(vertices.at(i).amountA == unvisited.at(minimum)->amountA && vertices.at(i).amountB == unvisited.at(minimum)->amountB)
            {
                index = i;
            }
        }
        for(unsigned i = 0; i < unvisited.at(minimum)->neighbors.size(); i++)
        {
            unsigned int alternate = unvisited.at(minimum)->distance + getCost(unvisited.at(minimum)->neighbors.at(i).second);
            
            if(vertices.at(unvisited.at(minimum)->neighbors.at(i).first).distance > alternate)
            {
                vertices.at(unvisited.at(minimum)->neighbors.at(i).first).distance = alternate;
                vertices.at(unvisited.at(minimum)->neighbors.at(i).first).previous = index;
            }
        }
        unvisited.erase(unvisited.begin() + minimum);
    }
    for(unsigned int i = 0; i < vertices.size(); i++)
    {
        if(vertices.at(i).amountA == 0 && vertices.at(i).amountB == N)
        {
            index = i;
            
            break;
        }
    }
    unsigned int shortest = vertices.at(index).distance;
    
    while(vertices.at(index).previous != -1)
    {
        for(unsigned int i = 0; i < vertices.at(vertices.at(index).previous).neighbors.size(); i++)
        {
            if(vertices.at(vertices.at(index).previous).neighbors.at(i).first == index)
            {
                traverse.push(vertices.at(vertices.at(index).previous).neighbors.at(i).second);
                
                break;
            }
        }
        index = vertices.at(index).previous;
    }
    
    std::stringstream ss;
    ss << shortest;
    
    return "success " + ss.str();
}

int Jug::getCost(std::string value) const
{
    if(value == "fill A")
    {
        return cfA;
    }
    else if(value == "fill B")
    {
        return cfB;
    }
    else if(value == "empty A")
    {
        return ceA;
    }
    else if(value == "empty B")
    {
        return ceB;
    }
    else if(value == "pour A B")
    {
        return cpAB;
    }
    else
    {
        return cpBA;
    }
}