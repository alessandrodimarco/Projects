//Alessandro DiMarco
//Project 2 Heap Sort
//CS 323-33
//9/17/15


#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Heap {
private:
	int* pq;
	int  size_of_queue;
	int  size_of_array;

public:
	Heap(int size) {
		size_of_queue = 0;
		size_of_array = size;
		pq = new int[size];
	}

	~Heap() {
		delete[] pq;
	}

	void insertOneDataItem(int data) {
		if (isFull())
			throw "heap is full\n";

		pq[++size_of_queue] = data;
		bubbleUp();
		return;
	}

	void buildHeap(ifstream& in_file, ofstream& out_file) {
		int data;
		while (in_file >> data) {
			out_file << "insert " << setw(2) << setfill(' ') << data << "\t";
			insertOneDataItem(data);
			print(out_file, 10);
		}
	}

	int deleteRoot() {
		if (isEmpty())
			throw "heap is empty\n";

		int data = pq[1];
		pq[1]    = pq[size_of_queue--];

		if (size_of_queue > 0)
			bubbleDown();

		return data;
	}

	void deleteHeap(ofstream& out_file) {
		while (!isEmpty()) {
			out_file << "delete " << setw(2) << setfill(' ') << deleteRoot() << "\t";
			print(out_file, 10);
		}

		out_file << endl;
	}

	void print(ofstream& out_file, int limit) {
		for (int i = 1; i <= size_of_queue && i <= limit; i++)
			out_file << setw(2) << setfill(' ') << pq[i] << " ";

		out_file << endl;
	}

	bool isEmpty() {
		return size_of_queue == 0;
	}

	bool isFull() {
		return size_of_queue >= size_of_array-1;
	}

	int peek() {
		return pq[1];
	}

	int getSize() {
		return size_of_queue;
	}

private:
	//internal method for deleting the root adding a item
	void bubbleUp() {

		int child_index  = size_of_queue;
		int parent_index = child_index/2;
		int temp;

		while (pq[parent_index] > pq[child_index] && child_index != 1) {
			//swap child and parent
			temp = pq[child_index];
			pq[child_index]  = pq[parent_index];
			pq[parent_index] = temp;

			//move parent and child index along the array
			child_index  = parent_index;
			parent_index = child_index/2;
		}
	}

	//internal function for deleting the root
	void bubbleDown() {
		int min_index, temp;
		int parent_index      = 1;
		int left_child_index  = 2;
		int right_child_index = 3;

		while (left_child_index <= size_of_queue || right_child_index <= size_of_queue) {

			//check if the right child index is greater than the size of the queue
			if (right_child_index > size_of_queue) {
				//then check the left child index
				if (left_child_index > size_of_queue) {
					//if they are both out of bounds then the parent has no children
					return;
				}
				//else set the min_index to the left child index
				else min_index = left_child_index;
			}
			//if the right child is not larger than the index, then there
			//must be two children and we must check which child is larger
			else if (pq[left_child_index] < pq[right_child_index])
                  min_index = left_child_index;
            else
                  min_index = right_child_index;

            //check whether the parent is greater than the minimum
            //of the two children
     		if (pq[parent_index] > pq[min_index]) {
     			//swap the two numbers
            	temp = pq[min_index];
            	pq[min_index]    = pq[parent_index];
            	pq[parent_index] = temp;

            	//set the index
            	parent_index = min_index;

            	//compute the children
            	left_child_index  = 2*parent_index;
				right_child_index = 2*parent_index+1;
      		}
      		else
      			return;
		}
	}
};

int main(int argc, char *argv[]) {
	if (argc < 3) {
		cout << "Missing arguments\n";
		return -1;
	}

	//count the number of data items in the file
	ifstream tmp (argv[1]);
	int num, count = 0;
	while (tmp >> num)
		count++;
	tmp.close();

	//open input and output file
	ifstream in_file (argv[1]);
	ofstream out_file (argv[2]);

	out_file << "Building heap:\n";
	Heap aheap(count+1);
	aheap.buildHeap(in_file, out_file);

	out_file << "\nFinal heap:\n";
	aheap.print(out_file, aheap.getSize());

	out_file <<"\nDeleting heap:\n";
	aheap.deleteHeap(out_file);

	out_file << "Final heap:\n";
	aheap.print(out_file, aheap.getSize());

	in_file.close();
	out_file.close();
	return 0;
}
