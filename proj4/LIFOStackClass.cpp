// File: LIFOStackClass.cpp
// Purpose: Implementation file for LIFOStackClass
// Author: Yiwei Gui
// Date: 4/7/2025

# include "LIFOStackClass.h"



LIFOStackClass::LIFOStackClass() {
    head = NULL;
    tail = NULL;
}

LIFOStackClass::~LIFOStackClass() {
    clear();
}

void LIFOStackClass::push(const int &newItem) {
    // Empty linked list;
    if (head == NULL) {
        head = new LinkedNodeClass(NULL, newItem, NULL);
        tail = head;;
        return;
    }
    // If not empty, add new item to the head because it is a stack;

    LinkedNodeClass* nodePtr;
    nodePtr = new LinkedNodeClass(NULL, newItem, head);
    nodePtr -> setBeforeAndAfterPointers();
    head = nodePtr;

}

bool LIFOStackClass::pop(int &outItem) {
    // Empty linked list
    if (head == NULL) {
        return false;
    }
    // If not empty, remove the head because it is a stack

    outItem = head -> getValue();
    LinkedNodeClass* nodePtr = head;
    head = head -> getNext();

    delete nodePtr;

    if (head == NULL) {
        tail = NULL;
    } 
    else {
        head -> setPreviousPointerToNull();
    }

    return true;
}

void LIFOStackClass::print() const {
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

int LIFOStackClass::getNumElems() const {
    int numElems = 0;
    LinkedNodeClass* nodePtr = head;

    while (nodePtr != NULL) {
        numElems++;
        nodePtr = nodePtr->getNext();
    }

    return numElems;
}


void LIFOStackClass::clear() {
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