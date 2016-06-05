#ifndef List_H
#define List_H
#include <fstream>

template<class T>
class List 
{
    Node<T>* head;
    Node<T>* iterator;  //iterator for linked list

public:
    //dummy node is passed in
    List(T d);
    ~List();

    void insert(T data);
    void deleteVertex(T data);
    void deleteEdge(T data);
    void printList(std::ofstream&, int);
    bool isEmpty();
    void reset();
    bool checkNext();
    void nextItem();
    T getItem();
};

template <class T>
List<T>::List(T d) 
{ 
    head = new Node<T>(d); 
    iterator = nullptr; 
}

template <class T>
List<T>::~List() 
{
    Node<T>* ptr = head;
    Node<T>* temp;
    while (ptr != nullptr)
    {
        temp = ptr;
        ptr  = ptr -> getNext();
        delete temp;
    }
    head = nullptr;
    iterator = nullptr; 
}

template <class T>
void List<T>::insert(T data) 
{
    Node<T>* new_node = new Node<T>(data);
    Node<T>* current = head;

    while(current -> getNext() != nullptr && current->getNext() -> getData().getD() < new_node -> getData().getD())
        current = current -> getNext();

    new_node -> setNext(current -> getNext());
    current  -> setNext(new_node);
}

template <class T>
void List<T>::deleteVertex(T data) 
{
    Node<T>* current = head;

    //cycle through list until the current->next is the data to be deleted
    while(current -> getNext() != nullptr && current -> getNext() -> getData().getD() != data.getD()) 
        current = current -> getNext();

    //if item was not in list return
    if (current -> getNext() == nullptr) {
        return;
    }
    //if item is at the end of the list set prev->next to nullptr and delete current
    else if (current->getNext()->getNext() == nullptr) {
        Node<T>* temp = current->getNext();
        current->setNext(nullptr);
        delete temp;
        return;
    }
    //if item is at the middle of the list set prev->next to current->next and delete current
    else {
        Node<T>* temp = current->getNext();
        current->setNext(current->getNext()->getNext());
        delete temp;
    }
}

template <class T>
void List<T>::deleteEdge(T data) 
{
    Node<T>* prev = head;
    Node<T>* current = head -> getNext();
    
    while(current != nullptr) {
        T temp = current -> getData();

        if (temp.getNi() == data.getNi() && temp.getNj() == data.getNj()) {
            break;
        }

        prev = current;
        current = current -> getNext();
    }

    //if item is not in the list return
    if (current == nullptr) {
        return;
    }
    //if item is at the end of the list set prev->next to nullptr and delete current
    else if (current->getNext() == nullptr) {
        prev->setNext(nullptr);
        delete current;
        return;
    }
    //if item is at the middle of the list set prev->next to current->next and delete current
    else {
        prev->setNext(current->getNext());
        delete current;
    }
}

//print the list
template <class T>
void List<T>::printList(std::ofstream& out_file, int limit) 
{
    int i = 1;
    Node<T>* ptr = head;
    while (ptr != nullptr) 
    {
        out_file << ptr -> getData().printData() << "\n";
        ptr = ptr -> getNext();


        if (i == limit)
            break;

        i++;
    }
    
    out_file << "\n";
}

//isEmpty() function
template <class T>
bool List<T>::isEmpty() { return head -> getNext() == nullptr; }

//set iterator to beginning of linked list
template <class T>
void List<T>::reset() { iterator = head -> getNext(); }

//check to make sure next item is not null
template <class T>
bool List<T>::checkNext () { return !(iterator == nullptr); }

//get data in iterator
template <class T>
T List<T>::getItem() { return iterator -> getData(); }

//set iterator to the next item
template <class T>
void List<T>::nextItem() { iterator = iterator -> getNext(); }

#endif