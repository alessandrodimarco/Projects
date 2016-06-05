//Alessandro DiMarco
//Project 4 Radix Sort
//CS 323-33
//10/24/15

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

ifstream in_file;
ofstream out_file;

class Node
{
  string data;
  Node* next;

public:
  Node (string d)
  {
    data = d;
    next = nullptr;
  }

  string getData() { return data; }

  Node* getNext()  { return next; }

  void setData(string s) { data = s; }

  void setNext(Node* n)  { next = n; }
};

class Stack
{
  Node* top;

public:
  Stack()
  {
    top = nullptr;
  }

  ~Stack()
  {
    Node* ptr = top;
    Node* temp;
    while (ptr != nullptr)
    {
      temp = ptr;
      ptr  = ptr->getNext();
      delete temp;
    }
  }

  void push(string d)
  {
    Node* n = new Node(d);
    n->setNext(top);
    top = n;
  }

  string pop()
  {
    if (top == nullptr)
    {
      cout << "Stack is empty";
      return "";
    }

    string t = top->getData();
    top = top->getNext();
    return t;
  }

  bool isEmpty()
  {
    return top == nullptr;
  }

  void printStack()
  {
    Node* current = top;
    while (current != nullptr)
    {
      out_file << current->getData() << " ";
      current   = current->getNext();
    }
    out_file << endl;
  }
};

class Queue
{
  Node* head;
  Node* tail;

public:
  Queue()
  {
    head = new Node("-999");
    tail = head;
  }

  void enqueue(string d)
  {
    Node* n = new Node(d);

    tail->setNext(n);
    tail = n;
  }

  string dequeue()
  {
    if (isEmpty())
    {
      out_file << "Queue is empty" << endl;
      return "";
    }

    string temp = head->getNext()->getData();
    if (head->getNext()->getNext() == nullptr)
    {
      tail = head;
      head->setNext(nullptr);
    }
    else
    {
      head->setNext(head->getNext()->getNext());
    }

    return temp;
  }


  bool isEmpty()
  {
    return head->getNext() == nullptr;
  }

  ~Queue()
  {
    Node* ptr = head;
    Node* temp;
    while (ptr != nullptr)
    {
      temp = ptr;
      ptr  = ptr->getNext();
      delete temp;
    }
  }

  void printQueue()
  {
    if (isEmpty())
    {
      out_file << "Queue is empty" << endl;
      return;
    }

    Node* current = head;
    while (current != nullptr)
    {
      out_file << current->getData() << " ";
      current = current->getNext();
    }

    out_file << endl;
  }
};

class HashTable
{
public:
  Queue table[10];

  HashTable() {}

  void setVal(int index, string value)
  {
    table[index].enqueue(value);
  }

  void printHashTable (string tableNumber)
  {
    out_file << tableNumber << endl;
    out_file << "----------------------------------------------------\n";

    for (int i = 0; i < 10; ++i)
    {
      out_file << i << " ";
      table[i].printQueue();
      out_file << endl;
    }
  }
};

//global stack
Stack stk;

class RadixSort
{
  HashTable tableOne;		//currentTable = true
  HashTable tableTwo;		//currentTable = false
  bool currentTable;		//boolean to switch tables
  int  currentDigit;		//track digit place value
  int  totalDigits;

public:
  RadixSort(int max)
  {
    totalDigits     = max;
    currentDigit = max-1;
    currentTable = true;

  }

  int hash(string d)
  {
    int num = (d[currentDigit]-'0');	//convert string d into number
    return num%10;
  }

  void move(HashTable& A, HashTable& B)
  {
    string str;
    for (int i = 0; i < 10; ++i)
    {
      while (!A.table[i].isEmpty())
      {
        //move string from table A to table B
        str = A.table[i].dequeue();
        B.setVal(hash(str), str);
      }
    }
  }

  void sort()
  {
    //move items from stack to tableOne
    while (!stk.isEmpty())
    {
      string str = stk.pop();
      int length = str.size();

      if (length < totalDigits)
      {
        //pad numbers with leading zeros
        stringstream ss;
        ss << std::setw (totalDigits) << setfill('0') << str;
        str = ss.str();
      }

      tableOne.setVal(hash(str), str);
    }
    tableOne.printHashTable("TableOne");
    --currentDigit;

    for (; currentDigit >= 0; --currentDigit)
    {
      if (currentTable)
      {
        //Move number from tableOne to tableTwo
        move(tableOne, tableTwo);
        tableTwo.printHashTable("TableTwo");
      }
      else
      {
        //Move number from tabletwo to tableOne
        move(tableTwo, tableOne);
        tableOne.printHashTable("TableOne");
      }

      currentTable ^= true; //switch currentTable
    }
  }
};

int main (int argc, char** argv)
{
  if (argc < 3) {
    cout << "Missing arguments\n";
    return -1;
  }

  in_file.open(argv[1]);
  out_file.open(argv[2]);

  // debugging
  // in_file.open("4_radix_sort_data.txt");
  // out_file.open("output1.txt");

  //find largest integer
  string incoming;
  int maxDigits = -1;
  while (in_file >> incoming)
  {
    stk.push(incoming);
    if ((int)incoming.size() > maxDigits)
    maxDigits = incoming.size();
  }

  //print stack
  out_file << "Stack:\n";
  stk.printStack();
  out_file << "\n";

  //sort numbers
  RadixSort rdx(maxDigits);
  rdx.sort();

  in_file.close();
  out_file.close();
}
