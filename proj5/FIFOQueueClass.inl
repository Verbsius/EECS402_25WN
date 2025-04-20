// Name: Yiwei Gui
// Date: 4/6/2025
// Modified: 4/16/2025
// Purpose:
// This file contains the implementation of the FIFOQueueClass, which 
// represents a First-In-First-Out (FIFO) queue using a doubly linked list. 
// It provides methods to enqueue items, dequeue items, print the queue, 
// get the number of elements, and clear the queue. The class ensures 
// efficient insertion and removal of elements at the appropriate ends 
// of the queue.
# include "FIFOQueueClass.h"


template <class T>
FIFOQueueClass<T>::FIFOQueueClass() {
    head = NULL;
    tail = NULL;
}

template <class T>
FIFOQueueClass<T>::~FIFOQueueClass() {
    clear();
}

template <class T>
void FIFOQueueClass<T>::enqueue(const T &newItem) {
    // Empty linked list;
    if (head == NULL) {
        head = new LinkedNodeClass<T>(NULL, newItem, NULL);
        tail = head;
        return;
    }

    // If not empty, add new item to the tail;

    LinkedNodeClass<T>* nodePtr;
    nodePtr = new LinkedNodeClass<T>(tail, newItem, NULL);
    nodePtr -> setBeforeAndAfterPointers();
    tail = nodePtr;

}
template <class T>
bool FIFOQueueClass<T>::dequeue(T &outItem) {
    // Empty linked list return false;
    if (head == NULL) {
        return false;
    }


    // Remove the tail value because it is a queue;
    outItem = head -> getValue();
    LinkedNodeClass<T>* nodePtr = head;
    head = head -> getNext();
    if (head != NULL) {
        head -> setBeforeAndAfterPointers();
    } 
    else {
        tail = NULL;
    }

    delete nodePtr;
    return true;
}
template <class T>
void FIFOQueueClass<T>::print() const
{
    LinkedNodeClass<T>* nodePtr = head;

    if (head == NULL) {
        cout << endl;
    } 
    else {
        while (nodePtr != NULL) {
            cout << nodePtr->getValue();  
            nodePtr = nodePtr->getNext();
            if (nodePtr != NULL) {
                cout << " ";  
            }
        }
        cout << endl;  
    }
}

template <class T>
int FIFOQueueClass<T>::getNumElems() const {
    int numElems = 0;
    LinkedNodeClass<T>* nodePtr = head;

    while (nodePtr != NULL) {
        numElems++;
        nodePtr = nodePtr->getNext();
    }

    return numElems;
}

template <class T>
void FIFOQueueClass<T>::clear()
{
    if (head == NULL) {
        return;
    }

    LinkedNodeClass<T>* currentNode = head;
    LinkedNodeClass<T>* nextNode = NULL;

    while (currentNode != NULL)
    {
        nextNode = currentNode -> getNext();
        delete currentNode;
        currentNode = nextNode;
    }

    head = NULL;
    tail = NULL;
}