#ifndef EDGE_H
#define EDGE_H
#include <string>

class Edge 
{
    int Ni;
    int Nj;
    int edgeCost;

public:
    Edge();
    Edge(int i, int j, int cost);
    
    std::string printData();
    int getNi();
    int getNj();
    int getD();

    // piece of shit code
    // overload < symbol for insertion sort
    // bool operator< (EdgeData& r) 
    // { 
    //     return getD() < r.getD(); 
    // }
};

Edge::Edge() 
  : Ni(-999), Nj(-999), edgeCost(-999) 
{ }

//3 param constructor
Edge::Edge(int i, int j, int cost) 
  : Ni(i), Nj(j), edgeCost(cost) 
{ }

//get methods
int Edge::getNi() { return Ni;       }
int Edge::getNj() { return Nj;       }
int Edge::getD()  { return edgeCost; }

//print method
std::string Edge::printData() 
{
    return "<" + std::to_string(Ni) + ", " + std::to_string(Nj) + ", " + std::to_string(edgeCost) + "> ";
}

#endif