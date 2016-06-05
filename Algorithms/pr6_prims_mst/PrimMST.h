#ifndef PRIMMST_H
#define PRIMMST_H
#include <fstream>

class PrimMST {
    int  N;
    int  totalCost;
    int* graphNode1Darray;
    const int LIMIT; //number of items to print limit

    List<Edge>   MSTofG;
    List<Edge>   edgeList;
    List<Vertex> setA;
    List<Vertex> setB;

    std::ifstream in_file;
    std::ofstream out_file1;
    std::ofstream out_file2;

public:
    PrimMST (char in[], char out1[], char out2[]);
    ~PrimMST();

    void run();
    void readInput();
    void createTwoSets();
    void printArray();
    void printList();
    void moveFromSetB(int vertex, Edge& edgeTemp);
};

//constructor that takes in 1 input file and 2 output files
PrimMST::PrimMST (char in[], char out1[], char out2[]) 
    : MSTofG(Edge()), edgeList(Edge()), setA(Vertex()), setB(Vertex()), 
      totalCost(0), LIMIT(100)
{
    in_file.open(in);
    out_file1.open(out1);
    out_file2.open(out2);

    //dynamically allocate 1D array with first number in input file
    in_file >> N;
    graphNode1Darray = new int[N += 1] ();
}

void PrimMST::run() 
{
    //read input file and then close it
    readInput();
    in_file.close();

    //Sets A and B are established
    createTwoSets();

    //print arrary and lists
    printArray();  
    printList();

    //reset iterator to beginning of edgeList
    edgeList.reset();

    //booleans to keep track of edge nodes Ni and Nj
    //and are true if the nodes are in setA
    bool verNi = false;
    bool verNj = false;

    // while setB is not empty, go through list of edges and 
    // pick the min edge from setB to setA
    //
    // 1) if vertices Ni and Nj are already in setA then delete the edge
    //    (the loweset edge must have been found already connecting the two vertices)
    // 2) if vertices Ni and Nj are not in setA then move the iterator to the next item
    //    and start at the top of the loop
    // 3) if only one vertex Ni or Nj are in setA then take the other vertex from setB and 
    //    move it into setA and delete the edge from the list
    while(!setB.isEmpty()) {
        Edge edgeTemp = edgeList.getItem();

        //reset iterator to beginning of list setA and setB
        setA.reset();
        setB.reset();

        //check if the edge vertices Ni or Nj is inside of setA
        while (setA.checkNext()) {
            Vertex verA = setA.getItem();

            if (edgeTemp.getNi() == verA.getD())
                verNi = true;

            if (edgeTemp.getNj() == verA.getD())
                verNj = true;

            setA.nextItem();
        }

        //if vertex Ni and Nj are not in setA, move to the next item
        //and go to the top of the loop
        if (!verNi && !verNj) {
            if (edgeList.checkNext())
                edgeList.nextItem();

            continue;
        }

        //if verNi and verNj are in setA then delete
        //their edge since we already have the minEdge
        if (verNi && verNj)
            edgeList.deleteEdge(edgeTemp);

        //if verNi is true then move vertex Nj from 
        //setB into setA 
        else if (verNi)
            moveFromSetB(edgeTemp.getNj(), edgeTemp);

        //if verNj is true then move vertex Ni from 
        //setB into setA 
        else if (verNj)
            moveFromSetB(edgeTemp.getNi(), edgeTemp);

        verNi = false;
        verNj = false;

        //reset edgeList iterator to the beginning
        edgeList.reset();

        printList();
    }

    out_file1 << N-1 << "\n\n";
    out_file1 << "MSTofG:\n";
    MSTofG.printList(out_file1, LIMIT);
    out_file1 << "Total Cost: " << totalCost << "\n";

    out_file1.close();
    out_file2.close();
}

//read input and and add to edgeList
void PrimMST::readInput() 
{
    int x, y, cost;
    while (in_file >> x >> y >> cost) {
        graphNode1Darray[x]++;
        graphNode1Darray[y]++;

        //create a new Edge and place into edgeList  EdgeData temp(x, y, cost);
        edgeList.insert(Edge(x, y, cost));
    }
}

void PrimMST::createTwoSets() {
    int i;
    for(i = 1; i < N; i++)
        if (graphNode1Darray[i] > 0) {
            setA.insert(Vertex(i++));
            break;
        }

    for (; i < N; i++)
        if (graphNode1Darray[i] > 0)
            setB.insert(Vertex(i));
}

void PrimMST::moveFromSetB(int vertex, Edge& edgeTemp) {

    //check in setB for vertex
    while (setB.checkNext()) {

        //verB holds current vertex in setB
        Vertex verB = setB.getItem();

        //if the vertex is equal to vertex in setB,  
        if (vertex == verB.getD()) {

            // 1) insert vertex into setA 
            setA.insert(verB);

            // 2) delete vertex from setB.
            setB.deleteVertex(verB);

            // 3) add cost of edge to total cost
            totalCost += edgeTemp.getD();

            // 4) insert edge into MSTofG
            MSTofG.insert(edgeTemp);

            // 5) deleteEdge from the edge list
            edgeList.deleteEdge(edgeTemp);

            break;
        }

        //if vertex didn't match the item in setB, move to the next item
        setB.nextItem();
    }
}

void PrimMST::printList() 
{
    out_file2 << "edgeList\n";
    edgeList.printList(out_file2, LIMIT);

    out_file2 << "setA\n";
    setA.printList(out_file2, LIMIT);

    out_file2 << "setB\n";
    setB.printList(out_file2, LIMIT);

    out_file2 << "MSTofG\n";
    MSTofG.printList(out_file2, LIMIT);

    out_file2 << std::string(50, '-') << "\n\n";
} 

void PrimMST::printArray() 
{
    out_file2 << "graphNode1Darray -- ";
    for (int i = 1; i < N; i++)
        out_file2 << graphNode1Darray[i] << " ";

    out_file2 << "\n\n";
}

PrimMST::~PrimMST() 
{
    delete[] graphNode1Darray; 
}

#endif