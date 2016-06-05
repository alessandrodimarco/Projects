#ifndef Vertex_H
#define Vertex_H
#include <string>

class Vertex 
{
    int nodeID;

public:
    Vertex();
    Vertex(int ID);
    
    std::string printData();
    int getD();
    void setNodeID(int d);
};

//default constructor
Vertex::Vertex() : nodeID(-999) { }

//one param constructor
Vertex::Vertex(int ID) : nodeID(ID) { }

//return string of data to be printed
std::string Vertex::printData() { return std::to_string(nodeID); }

//get method
int Vertex::getD() { return nodeID; }

//set method
void Vertex::setNodeID(int d) { nodeID = d; }

#endif