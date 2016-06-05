#include <iostream>
#include <string>
#include "Edge.h"
#include "Vertex.h"
#include "Node.h"
#include "List.h"
#include "PrimMST.h"

//  compile program with:
//  g++ -std=c++11 main.cpp
//  ./a.out 1prims_data.txt output1.txt output2.txt

int main(int argc, char *argv[]) {
    if (argc < 4) 
    {
        std::cout << "Missing arguments\n";
        return -1;
    }

    PrimMST m(argv[1], argv[2], argv[3]);
    m.run();
}