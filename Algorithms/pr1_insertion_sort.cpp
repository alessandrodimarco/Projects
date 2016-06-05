//Alessandro DiMarco
//Project 1 Insertion Sort
//CS 323-33
//9/10/15


#include <iostream>
#include <fstream>
using namespace std;

//flag for duplicate entries
bool flag = true;

class List {
protected:
    struct node {
        int data;
        node* next;
    };

private:
    node* root;

public:
    List() {
        root = new node();
        root->data = -9999;
        root->next = NULL;
    }

    ~List() {
        node* ptr = root;
        node* temp;
        while (ptr != NULL){
            temp = ptr;
            ptr = ptr->next;
            delete temp;
        }
        root = NULL;
    }

    void add(int adata) {
        node* current = root;

        //create new node to be inserted
        node* new_node = new node();
        new_node -> data = adata;
        new_node -> next = NULL;

        while (current->next != NULL && current->next->data < new_node->data) {
            current = current->next;
        }

        //check if entry is already in the list
        if (new_node->data == current->data) {
            cout << new_node->data << " is a duplicate" << endl;
            flag = false;
            return;
        }

        new_node->next = current->next;
        current->next = new_node;
    }

    bool isEmpty() {
        return (root->next == NULL);
    }

    void print(ofstream& ofile) {
        node* ptr = root;
        ofile << "listhead --> ";

        //counter
        int i = 0;
        while (ptr != NULL) {
            //if 10 nodes have been printed then break out of loop
            if (i == 10) break;

            //print different statements depending on whether you are in the middle
            //of the list, at then end of the list or if the next node is NULL
            if (ptr->next != NULL) {
                if (i != 9)
                    ofile << "(" << ptr->data << ", " << ptr->next->data << ") --> ";
                else
                    ofile << "(" << ptr->data << ", " << ptr->next->data << ") ";
            } else
                ofile << "(" << ptr->data << ", -1)";

            //increment i and move pointer to the next node
            i++;
            ptr = ptr->next;
        }
        ofile << endl;
    }
};

int main(int argc, char *argv[]) {
    if (argc < 3) {
		cout << "Missing arguments\n";
		return -1;
	}

    ifstream in_file (argv[1]);
    ofstream out_file (argv[2]);

    // debugging
    // ifstream in_file ("1_insertion_sort_data.txt");
    // ofstream out_file ("output1.txt");

    List myList;
    int num;

    //read file and add numbers to linked lists
    while (in_file >> num) {
        myList.add(num);
        
        //prints only if number was added to the list 
        if (flag)
            myList.print(out_file);
        else 
            flag = true;
    }

    in_file.close();
    out_file.close();
    return 0;
}
