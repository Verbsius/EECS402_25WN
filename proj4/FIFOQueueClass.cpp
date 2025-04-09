// Name: Yiwei Gui
// Date: 4/6/2025
// Purpose:
// This file contains the implementation of the FIFOQueueClass, which 
// represents a First-In-First-Out (FIFO) queue using a doubly linked list. 
// It provides methods to enqueue items, dequeue items, print the queue, 
// get the number of elements, and clear the queue. The class ensures 
// efficient insertion and removal of elements at the appropriate ends 
// of the queue.
# include "FIFOQueueClass.h"



FIFOQueueClass::FIFOQueueClass() {
    head = NULL;
    tail = NULL;
}

FIFOQueueClass::~FIFOQueueClass() {
    clear();
}

void FIFOQueueClass::enqueue(const int &newItem) {
    // Empty linked list;
    if (head == NULL) {
        head = new LinkedNodeClass(NULL, newItem, NULL);
        tail = head;
        return;
    }

    // If not empty, add new item to the tail;

    LinkedNodeClass* nodePtr;
    nodePtr = new LinkedNodeClass(tail, newItem, NULL);
    nodePtr -> setBeforeAndAfterPointers();
    tail = nodePtr;

}

bool FIFOQueueClass::dequeue(int &outItem) {
    // Empty linked list return false;
    if (head == NULL) {
        return false;
    }


    // Remove the tail value because it is a queue;
    outItem = head -> getValue();
    LinkedNodeClass* nodePtr = head;
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

void FIFOQueueClass::print() const
{
    LinkedNodeClass* nodePtr = head;

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


int FIFOQueueClass::getNumElems() const {
    int numElems = 0;
    LinkedNodeClass* nodePtr = head;

    while (nodePtr != NULL) {
        numElems++;
        nodePtr = nodePtr->getNext();
    }

    return numElems;
}


void FIFOQueueClass::clear()
{
    if (head == NULL) {
        return;
    }

    LinkedNodeClass* currentNode = head;
    LinkedNodeClass* nextNode = NULL;

    while (currentNode != NULL)
    {
        nextNode = currentNode -> getNext();
        delete currentNode;
        currentNode = nextNode;
    }

    head = NULL;
    tail = NULL;
}