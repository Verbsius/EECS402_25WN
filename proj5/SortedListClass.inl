// Name: Yiwei Gui
// Date: 4/6/2025
// Purpose:
// This file contains the implementation of the SortedListClass.


#include "SortedListClass.h"

template <class T>
SortedListClass<T>::SortedListClass() {
    head = NULL;
    tail = NULL;
}

template <class T> 
SortedListClass<T>::SortedListClass(const SortedListClass<T> &rhs) {
    head = NULL;
    tail = NULL;
    if (rhs.head == NULL){
        return;
    }

    LinkedNodeClass<T>* currentNode = rhs.head;
    // From the head pointer, iterating the linked list;
    while (currentNode != NULL){
        insertValue(currentNode -> getValue());
        currentNode = currentNode -> getNext();
    }
}

template <class T>
SortedListClass<T>::~SortedListClass() {
    clear();
}

template <class T>
SortedListClass<T>& SortedListClass<T>::operator=(const SortedListClass<T> &rhs) 
{

    if (rhs.head == NULL){
        return* this;
    }
    // clear the current list
    clear();

    if (this == &rhs){
        return* this;
    }

    // clear the current list
    clear();

    LinkedNodeClass<T>* currentNode = rhs.head;
    while (currentNode != NULL){
        insertValue(currentNode -> getValue());
        currentNode = currentNode -> getNext();
    }
    return* this;
}

template <class T>
void SortedListClass<T>::clear() {
    if (head == NULL){
        return;
    }

    LinkedNodeClass<T>* currentNode = head;
    LinkedNodeClass<T>* nextNode = NULL;

    while (currentNode != NULL){
        nextNode = currentNode -> getNext();
        delete currentNode;
        currentNode = nextNode;
    }

    head = NULL;
    tail = NULL;
}

template <class T>
void SortedListClass<T>::insertValue(const T &valToInsert) {
    LinkedNodeClass<T> *newNode;
    
    // Case 1: Empty list
    if (head == NULL) {
        newNode = new LinkedNodeClass<T>(NULL, valToInsert, NULL);
        head = newNode;
        tail = newNode;
        return;
    }
    
    // Case 2: Insert at the beginning (new value is less than head value)
    if (valToInsert < head->getValue()) {
        newNode = new LinkedNodeClass<T>(NULL, valToInsert, head);
        head = newNode;
        newNode->setBeforeAndAfterPointers();
        return;
    }
    
    // Case 3: Insert in the middle or end
    LinkedNodeClass<T> *currNode = head;
    
    // Find the position to insert
    // We insert after nodes with equal value 
    while (currNode->getNext() != NULL && 
           currNode->getNext()->getValue() <= valToInsert) {
        currNode = currNode->getNext();
    }
    
    // Case 3a: Insert at the end
    if (currNode->getNext() == NULL) {
        newNode = new LinkedNodeClass<T>(currNode, valToInsert, NULL);
        tail = newNode;
        newNode->setBeforeAndAfterPointers();
    }
    // Case 3b: Insert in the middle
    else {
        newNode = new LinkedNodeClass<T>(currNode, valToInsert, 
            currNode->getNext());
        newNode->setBeforeAndAfterPointers();
    }
}

template <class T>
void SortedListClass<T>::printForward() const {
    cout << "Forward List Contents Follow:"
         << endl;
    
    LinkedNodeClass<T>* currentNode = head;
    while(currentNode != NULL) {
        // Indent two spaces
        cout << "  "
             << currentNode -> getValue()
             << endl;
        currentNode = currentNode -> getNext();
    }
    cout << "End Of List Contents"
         << endl;
}

template <class T>
void SortedListClass<T>::printBackward() const {
    cout << "Backward List Contents Follow:"
         << endl;

    LinkedNodeClass<T>* currentNode = tail;
    while(currentNode != NULL) {
        // Indent two spaces
        cout << "  "
             << currentNode -> getValue()
             << endl;
        currentNode = currentNode -> getPrev();
    }
    cout << "End Of List Contents"
         << endl;
}

template <class T>
bool SortedListClass<T>::removeFront(T &theVal) {

    if (head == NULL) {
        return false;
    }
    else {

        theVal = head -> getValue();

        // Save the head pointer for deletion later
        LinkedNodeClass<T>* nodePtr = head;

        // The new head pointer points to the next node;
        head = head -> getNext();
        delete nodePtr;

        if (head == NULL) {
            tail = NULL;
        }
        else {
            head -> setPreviousPointerToNull();
        }
    }
    return true;
}

template <class T>
bool SortedListClass<T>::removeLast(T &theVal) {
    if (tail == NULL) {
        return false;
    } else {
       
        theVal = tail->getValue();

  
        LinkedNodeClass<T>* nodePtr = tail;

        tail = tail->getPrev();

        if (tail != NULL) {
            tail->setNextPointerToNull();
        } else {
            // List is now empty
            head = NULL;
        }

        delete nodePtr;
        return true;
    }
}

template <class T>
int SortedListClass<T>::getNumElems() const {
    int count = 0;
    LinkedNodeClass<T>* currNode = head;
    
    while (currNode != NULL) {
        count++;
        currNode = currNode->getNext();
    }
    
    return count;
}

template <class T>
bool SortedListClass<T>::getElemAtIndex(const int index, T &outVal) const {
    // Check if index is out of range
    if (index < 0) {
        return false;
    }
    
    int currIndex = 0;
    LinkedNodeClass<T>* currNode = head;
    
    // Traverse to the specified index
    while (currNode != NULL && currIndex < index) {
        currNode = currNode->getNext();
        currIndex++;
    }
    
    // If we reached the end of the list before reaching the index
    // or if the list is empty, return false
    if (currNode == NULL) {
        return false;
    }
    
    // We found the node at the specified index
    outVal = currNode->getValue();
    return true;
}