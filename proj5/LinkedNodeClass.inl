// Name: Yiwei Gui
// Date: 4/16/2025
// Purpose:
// This file contains the implementation of the LinkedNodeClass.

#include "LinkedNodeClass.h"

template <class T>
LinkedNodeClass<T>::LinkedNodeClass(LinkedNodeClass<T>* inPrev, const T &inVal,
     LinkedNodeClass<T>* inNext) {
    prevNode = inPrev;
    nodeVal = inVal;
    nextNode = inNext;
}

template <class T>
T LinkedNodeClass<T>::getValue() const {
    return nodeVal;
}

template <class T>
LinkedNodeClass<T>* LinkedNodeClass<T>::getNext() const {
    return nextNode;
}

template <class T>
LinkedNodeClass<T>* LinkedNodeClass<T>::getPrev() const {
    return prevNode;
}

template <class T>
void LinkedNodeClass<T>::setNextPointerToNull() {
    nextNode = NULL;
}

template <class T>
void LinkedNodeClass<T>::setPreviousPointerToNull() {
    prevNode = NULL;
}

template <class T>
void LinkedNodeClass<T>::setBeforeAndAfterPointers() {
    if (prevNode != NULL) {
        prevNode -> nextNode = this;
    }
    
    if (nextNode != NULL) {
        nextNode -> prevNode = this;
    }
}