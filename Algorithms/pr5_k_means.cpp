//Alessandro DiMarco
//Project 5 K Means Clustering
//CS 323-33
//11/22/15


#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;

ifstream in_file;
ofstream out_file1;
ofstream out_file2;

struct xycoord 
{
    int sumX, sumY;      //sum of x's and y's
    int numOfPoints;     //total number of points
    double centX, centY; //centX, CentY = sumX, sumY divided by the numOfPoints
};

class PointNode 
{
	int x;
    int y;
    int label;         //cluster label
    double distance;   //useless attribute
	PointNode* next;

public:
	PointNode (int xCord, int yCord) 
	{
		x = xCord;
        y = yCord;
        label = -1;
        distance = -1.0;
		next = nullptr;
	}

    string printNode() 
    {
        //pad x and y to two digits
        stringstream sx, sy;
        sx << std::setw (2) << to_string(x);
        sy << std::setw (2) << to_string(y); 

        //return string that has x value, y value and cluster label
        return sx.str() + " " + sy.str() + " " + to_string(label);
    }

    string printNodeDeluxe() 
    {
        return printNode() + " " + to_string(distance);
    }

    //get methods
	int getX() { return x; }
    int getY() { return y; }
    int getLabel() { return label; }
    double getDistance()  { return distance; }
    PointNode* getNext()  { return next;     }

    //set methods
	void setX(int xCord) { x = xCord; }
    void setY(int yCord) { y = yCord; }
    void setLabel(int c) { label = c; }
    void setDistance(double d) { distance = d; }
    void setNext(PointNode* n) { next = n;     }
};

class List 
{
    PointNode* root;
    PointNode* itr;  //iterator for linked list

public:
    List() 
    {
        root = new PointNode(-9999, -9999);
        itr  = nullptr;
    }

    ~List() 
    {
        PointNode* ptr = root;
        PointNode* temp;
        while (ptr != nullptr)
        {
            temp = ptr;
            ptr  = ptr -> getNext();
            delete temp;
        }
        root = nullptr;
        itr  = nullptr;
    }

    void add(PointNode* new_node) 
    {
        PointNode* current = root;

        while (current -> getNext() != nullptr)
            current = current -> getNext();

        new_node -> setNext(current -> getNext());
        current  -> setNext(new_node);
    }

    bool isEmpty() 
    {
        return root -> getNext() == nullptr;
    }

    //set iterator to beginning of linked list
    void reset() 
    {
        itr = root -> getNext();
    }

    //check to make sure next item is not null
    bool checkNext () 
    {
        return !(itr -> getNext() == nullptr);
    }

    //set iterator to the next item
    PointNode* nextItem() 
    {
        PointNode* temp = itr;
        itr = itr -> getNext();
        return temp;
    }

    //prints x, y, and label of pointNode
    void printList() 
    {
        PointNode* ptr = root;
        while (ptr != nullptr) 
        {
            out_file1 << ptr -> printNode() << endl;
            ptr = ptr -> getNext();
        }
        out_file1 << "\n" << string(25, '-') << "\n\n";
    }

    //prints x, y, label and distance of pointNode
    void printListDeluxe() 
    {
        PointNode* ptr = root;
        while (ptr != nullptr) 
        {
            out_file2 << ptr -> printNodeDeluxe() << endl;
            ptr = ptr -> getNext();
        }
        out_file2 << "\n" << string(25, '-') << "\n\n";
    }

};

class Kmeans 
{
    int k, rows, cols;
    bool reassignment;   //boolen to determine whether a point was reassigned a new label
    
    int **imageArray;    //array of points with labels
    xycoord *centroids;
    List listHead; 

public:
    Kmeans(int incomingK, int r, int c) 
    {
        k = incomingK;
        rows = r;
        cols = c;
        centroids = new xycoord[k+1];
        reassignment = true;

        //initalize imageArray to 0
        imageArray = new int*[rows];
        for (int i = 0; i < rows; i++)
            imageArray[i] = new int[cols] ();

        //set centroids to 0
        resetCentroids();
    }

    ~Kmeans() 
    {
        for (int i = 0; i < rows; i++) 
        {
            delete[] imageArray[i];
        }

        delete[] imageArray;
        delete[] centroids;
    }

    void randomLabel() 
    {
        int x, y, counter = 0;
        PointNode* t;

        //read file and set labels randomly
        while(in_file >> x >> y) 
        {
            int label = counter++ % k + 1;  //set label from 1 to k
            t =  new PointNode(x,y);        //create new PointNode t from data
            t -> setLabel(label);           //set PointNode t label
            listHead.add(t);                //add PointNode t to list
        }
    }

    void printImage() 
    {
        for (int i = 0; i < rows; i++) 
        {
            for (int j = 0; j < cols; j++) 
            {
                if (imageArray[i][j] == 0)
                    out_file2 << ' ';
                else
                    out_file2 << imageArray[i][j];
            }
            out_file2 << endl;
        }
        out_file2 << "\n" << string(rows, '-') << "\n";
    }

    //reset the centroids back to zero to recalculate the centroid
    void resetCentroids() 
    {
        //set number of points to 0 
        for(int i = 1; i < 5; i++) 
        {
            centroids[i].numOfPoints = 0;
            centroids[i].sumX  = 0;
            centroids[i].sumY  = 0;
            centroids[i].centX = 0;
            centroids[i].centY = 0;
        }
    }

    //calculate the centroid for each of the k groups
    //and for each point add its label to the image array
    void calcCentroidsAndLabelImageArray() 
    {
        resetCentroids();
        listHead.reset();
        PointNode* t;

        while (listHead.checkNext()) 
        {
            t = listHead.nextItem();

            //save x, y and label of t
            int lb = t -> getLabel();
            int x  = t -> getX();
            int y  = t -> getY();

            //set the image label
            imageArray[x][y] = lb;

            //add x, y and number of points
            centroids[lb].sumX += x;
            centroids[lb].sumY += y;
            centroids[lb].numOfPoints++;            
        }

        for (int i = 1; i < 5; i++) 
        {
            centroids[i].centX = (double)centroids[i].sumX / centroids[i].numOfPoints;
            centroids[i].centY = (double)centroids[i].sumY / centroids[i].numOfPoints;
        }
    }

    //calculate label with the smallest distance to the pointNode
    void calcLabel(PointNode* t) 
    {
        int oldLabel = t -> getLabel();
        int newLabel = -1;
        double min   = numeric_limits<double>::infinity();  //set min to infinity

        for (int i = 1; i < 5; i++) 
        {
            double dist = sqrt(pow(t->getX() - centroids[i].centX, 2) + pow(t->getY() - centroids[i].centY, 2));

            if (min > dist) 
            {
                min = dist;
                newLabel = i;
                t -> setDistance(dist);
            }
        }

        //if newLabel is different than oldLabel
        //then set PointNode t label to the newLabel
        if (newLabel != oldLabel) 
        {
            t -> setLabel(newLabel);

            //since t was reassigned we must make this true
            reassignment = true;
        }

    }

    void cluster() 
    {
        //print k, row and column number
        out_file1 << k << "\n" << rows << " " << cols << "\n\n";

        //read file and set labels randomly
        randomLabel();

        //calculate centroid and add labels to the image array
        calcCentroidsAndLabelImageArray(); 

        //print list and image
        listHead.printList();
        printImage();

        //cycle through linked list until there are no more reassignments (swaps)
        while (reassignment) 
        {
            //reset the pointer to the head of the list
            listHead.reset();
            PointNode* t;

            //reassignment is false unless theres a label change
            reassignment = false;

            //traverse linked list and calculate new label for each point
            while (listHead.checkNext()) 
            {
                t = listHead.nextItem();
                calcLabel(t);
            }

            //calculate centroid and add labels to the image array
            calcCentroidsAndLabelImageArray();

            //print list and image
            listHead.printList();
            printImage();
        }

        //print list with distance in out_file2
        listHead.printListDeluxe();
    }
};

int main(int argc, char *argv[]) 
{
    // if (argc < 4) 
    // {
    //     cout << "Missing arguments\n";
    //     return -1;
    // }

    // in_file.open(argv[1]);
    // out_file1.open(argv[2]);
    // out_file2.open(argv[3]);

    //debugging
    in_file.open("5_Kmean_data.txt");
    out_file1.open("output1.txt");
    out_file2.open("output2.txt");

    int k, r, c;
    in_file >> k >> r >> c;
    Kmeans kme(k, r, c);
    kme.cluster();
}