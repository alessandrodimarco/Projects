//Alessandro DiMarco
//Project 3 Hash Table
//CS 323-33
//10/7/15

import java.io.*;
import java.util.Scanner;

public Scanner inFile;

class BucketSort {

	public static void main(String[] args) throws Exception {
		if(args.length < 2) {
			System.out.println("Missing Arguments");
			System.exit(1);
		}

		File in_file  = new File(args[0]);
		File out_file = new File(args[1]);
		Scanner temp  = new Scanner(in_file);

		//search for largest number
		int maxNum = -1;
		while (temp.hasNext()) {
			int num = Integer.parseInt(temp.next());
			if (num > maxNum)
				maxNum = num;
		}
		temp.close();
		
		HashTable t = new HashTable(maxNum, in_file, out_file);
		t.buildTable();

		t.print();

		t.closeFiles();
	}
}

class HashTable {

	private int[] table;
	private int size;
	private Scanner in_file;
	private PrintWriter out_file;

	public HashTable(int s, File in, File out) throws Exception{
		size  = s+1;
		table = new int[size];

		in_file  = new Scanner(in);
		out_file = new PrintWriter(out);
	}

	public void buildTable() {
		while (in_file.hasNext()) {
			int index = hashForBucketSort(Integer.parseInt( in_file.next() ));
			table[index]++;
		}
	}

	public int hashForBucketSort (int data) {
		return data%size;
	}

	public void print() {
		for (int i = 0; i < size; i++)
			for (int j = 1; j <= table[i]; j++)
				out_file.print(i + " ");

		out_file.print("\n");
	}

	public int getMax() {
		return size;
	}

	public void closeFiles() {
		in_file.close();
		out_file.close();
	}
}