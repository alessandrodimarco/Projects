//Alessandro DiMarco
//Project 4 Radix Sort
//CS 323-33
//10/30/15

import java.io.*;
import java.util.Scanner;

class Node {
	private String data;
	private Node next;

	public Node (String d) {
		data = d;
		next = null;
	}

	public String getData() { return data; }

	public Node getNext()  { return next; }

	public void setData(String s) { data = s; }

	public void setNext(Node n)  { next = n; }
}

class Stack {
	private Node top;

	public Stack() {
		top = null;
	}

	public void push(String d) {
		Node n = new Node(d);
		n.setNext(top);
		top = n;
	}

	public String peek() {
		if (top == null) {
			System.out.println("Stack is empty");
			return "";
		}

		return top.getData();
	}

	public String pop() {
		if (top == null) {
			System.out.println("Stack is empty");
			return "";
		}

		String t = top.getData();
		top = top.getNext();
		return t;
	}

	public boolean isEmpty() {
		return top == null;
	}

	public void printStack(PrintWriter writer) {
		Node current = top;
		while (current != null) {
			writer.print(current.getData() + " ");
			current = current.getNext();
		}
		writer.print("\n\n");
	}
}

class Queue {
	private Node head;
	private Node tail;

	public Queue() {
		head = new Node("-999");
		tail = head;
	}

	public void enqueue(String d) {
		Node n = new Node(d);

		tail.setNext(n);
		tail = n;
	}

	public String dequeue() { 
		if (isEmpty()) {
			System.out.println("Queue is empty");
			return "";
		}

		String temp = head.getNext().getData();
		if (head.getNext().getNext() == null) {
			tail = head;
			head.setNext(null);
		}
		else {
			head.setNext(head.getNext().getNext());
		}

		return temp;
	}


	public boolean isEmpty() {
		return head.getNext() == null;
	}

	public void printQueue(PrintWriter writer) {
		if (isEmpty()) {
			System.out.println("Queue is empty");
			return;
		}

		Node current = head;
		while (current != null) {
			writer.print(current.getData() + " ");
			current = current.getNext();
		}

		writer.print("\n");
	}
}

class HashTable {
	public Queue table[];

	public HashTable() {
		table = new Queue[10];
		for (int i = 0; i < 10; ++i)
			table[i] = new Queue();
	}

	public
		void setVal(int index, String value) {
		table[index].enqueue(value);
	}

	public void printHashTable (String tableNumber, PrintWriter writer) {
		writer.print(tableNumber);
		writer.print("\n----------------------------------------------------\n");

		for (int i = 0; i < 10; ++i) {
			writer.print(i + " ");
			table[i].printQueue(writer);
			writer.print("\n");
		}
	}
}

class RadixSort {
	private HashTable tableOne;		//currentTable = true
	private HashTable tableTwo;		//currentTable = false
	private boolean currentTable;	//boolean to switch tables
	private int  currentDigit;		//track digit place value
	private int  totalDigits;

	public RadixSort(int max) {
		tableOne = new HashTable();
		tableTwo = new HashTable();
		totalDigits  = max;
		currentDigit = max-1;
		currentTable = true;

	}

	public int hash(String d) {
		int num = Character.getNumericValue(d.charAt(currentDigit)); //convert string d into number
		return (num%10);
	}

	void sort(Stack stk, PrintWriter writer) {
		stk.printStack(writer);
		
		//move items from stack to tableOne
		while (!stk.isEmpty()) {
			String str = stk.pop();
			int length = str.length();

			if (length < totalDigits) {
				//pad numbers with leading zeros
				str = String.format("%" + totalDigits + "s", str).replace(' ', '0');
			}

		 	tableOne.setVal(hash(str), str);
		}

		tableOne.printHashTable("TableOne", writer);
		--currentDigit;

		//cycle through digits and move tables
		for (; currentDigit >= 0; --currentDigit) {
			if (currentTable) {

				//Move number from tableOne to tableTwo
				for (int i = 0; i < 10; ++i) {
					while (!tableOne.table[i].isEmpty()) {
						String str = tableOne.table[i].dequeue();
						tableTwo.setVal(hash(str), str);
					}
				}
				tableTwo.printHashTable("TableTwo", writer);
			}
			else {
				//Move number from tabletwo to tableOne
				for (int i = 0; i < 10; ++i) {
	 					while (!tableTwo.table[i].isEmpty()) {
	 						String str = tableTwo.table[i].dequeue();
	 						tableOne.setVal(hash(str), str);
	 					}
	 			}

				tableOne.printHashTable("TableOne", writer);
			}

			currentTable ^= true; //switch currentTable
		}
	}
}


class main {
	public static void main(String[] args) throws Exception {
		if (args.length < 2) {
			System.out.println("Missing Arguments");
			System.exit(1);
		}

		File in_file  = new File(args[0]);
		File out_file = new File(args[1]);
		Scanner readFile   = new Scanner(in_file);
		PrintWriter writer = new PrintWriter(out_file);

		//search for largest number and add numbers to stack
		int num, maxNum = -1;
		Stack stk  = new Stack();
		while (readFile.hasNext()) {
			stk.push(readFile.next());	//push number into stack
			num = stk.peek().length();	//find the length of the number
			if (num > maxNum)
				maxNum = num;
		}
		readFile.close();

		//sort numbers
		RadixSort rdx = new RadixSort(maxNum);
		rdx.sort(stk, writer);

		writer.close();
	}
}