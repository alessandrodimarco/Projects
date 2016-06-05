//Alessandro DiMarco
//Project 3 Hash Table
//CS 323-33
//10/7/15


#include <iostream>
#include <fstream>
#include <iomanip> 
using namespace std;

class HashTable {
private:
	int* table;
	int size;

public:
	HashTable(int s) {
		size = s;
		table = new int(size);

		for (int i = 0; i < size; i++)
			table[i] = 0;
	}

	~HashTable() {
		delete[] table;
	}

	void buildTable(ifstream& in_file, ofstream& out_file) {
		int data;
		while (in_file >> data) {
			out_file << "insert " << setw(2) << setfill(' ') << data << "\t";
			add(data);
			print(out_file, 10);
		}
	}

	void add (int data) {
		table[data]++;
	}

	void print(ofstream& out_file, int lim) {
		int limit = lim;
		for (int i = 0; i < size; i++)
			for (int j = 1; j <= table[i]; j++) {
				out_file << setw(2) << setfill(' ') << i << " ";
				limit++;
				if (limit == 10)
					break;
			}

		out_file << endl;
	}

	int getSize() {
		return size;
	}
};


int main (int argc, char *argv[]) {
	if (argc < 3) {
		cout << "Missing arguments\n";
		return -1;
	}

	ifstream tmp (argv[1]);
	int num, maxNum = -1;
	while (tmp >> num)
		if (num > maxNum)
			maxNum = num;
	tmp.close();

	//open input and output file
	ifstream in_file (argv[1]);
	ofstream out_file (argv[2]);

	out_file << "Building Table:\n";
	HashTable t(maxNum+1);
	t.buildTable(in_file, out_file);

	out_file << "\nFinal Table:\n";
	t.print(out_file, t.getSize());

	in_file.close();
	out_file.close();


}