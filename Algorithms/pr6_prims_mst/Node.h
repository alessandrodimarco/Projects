#ifndef NODE_H
#define NODE_H

template<class T>
class Node 
{
    T data;
    Node<T>* next;

public:
    Node (T d);
    
    T getData();
    Node<T>* getNext();
    void setData(T d);
    void setNext(Node<T>* n);
};

template<class T>
Node<T>::Node (T d) 
{
    data = d;
    next = nullptr;
}

//get methods
template<class T>
T Node<T>::getData() { return data; }

template<class T>
Node<T>* Node<T>::getNext() { return next; }

//set methods
template<class T>
void Node<T>::setData(T d)  { data = d; }

template<class T>
void Node<T>::setNext(Node<T>* n) { next = n; }

#endif