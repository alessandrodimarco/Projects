//Alessandro DiMarco
//Project 2 Heap Sort
//CS 323-33
//9/23/15

import java.io.*;
import java.util.Scanner;

class HeapSort {

	public static void main(String[] args) throws Exception {
		if(args.length < 2) {
			System.out.println("Missing Arguments");
			System.exit(1);
		}

        File in_file  = new File(args[0]);
        File out_file = new File(args[1]);

        //count the total number of entries
        Scanner file = new Scanner(in_file);
        int total = 0;
        while (file.hasNext()) {
        	file.next();
        	total++;
		}

		Heap a = new Heap(total+1, in_file, out_file);

		a.buildHeap();

		//print heap
		a.printText();
		a.print(a.getSize());
		a.endLine();

		a.deleteHeap();

		//print heap
		a.printText();
		a.print(a.getSize());

		a.closeFile();
	}
}


class Heap {
	private int pq[];
	private int size_of_queue;
	private int size_of_array;
	private Scanner file;
	private PrintWriter out_file;

	public Heap(int size, File inFile, File outFile) throws FileNotFoundException{
		file = new Scanner(inFile);
		out_file = new PrintWriter(outFile);
		size_of_queue = 0;
		size_of_array = size;
		pq = new int[size];
	}

	public void insertOneDataItem(int data) throws Exception{
		if (isFull())
			throw new Exception("heap is full\n");

		out_file.print("insert " + String.format("%2d", data) + "\t");

		pq[++size_of_queue] = data;
		bubbleUp();

		print(10);
		return;
	}

	public void buildHeap() throws Exception{
		while (file.hasNext()) {
			insertOneDataItem(Integer.parseInt(file.next()));
		}
	}

	public int deleteRoot() throws Exception{
		if (isEmpty())
			throw new Exception("heap is empty\n");

		int data = pq[1];
		pq[1]    = pq[size_of_queue--];

		if (size_of_queue > 0)
			bubbleDown();

		return data;
	}

	public void deleteHeap() throws Exception{
		while (!isEmpty()) {
			out_file.print("delete " + String.format("%2d", deleteRoot()) + "\t");
			print(10);
		}
	}

	public void print(int limit) {
		for (int i = 1; i <= size_of_queue && i <= limit; i++)
			out_file.print(String.format("%2d", pq[i]) + " ");

		out_file.print("\n");
	}

	public boolean isEmpty() {
		return size_of_queue == 0;
	}

	public boolean isFull() {
		return size_of_queue >= size_of_array-1;
	}

	public int peek() {
		return pq[1];
	}

	public int getSize() {
		return size_of_queue;
	}

	public void printText() {
		out_file.print("\nFinal Heap:\n");
	}

	public void closeFile() {
		out_file.close();
	}

	public void endLine() {
		out_file.print("\n");
	}

	//internal method for deleting the root adding a item
	private void bubbleUp() {

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
	private void bubbleDown() {
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
}
