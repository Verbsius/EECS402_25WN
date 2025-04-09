// Name: Yiwei Gui
// Date: 4/6/2025
// Purpose:
// This file contains the implementation of the LinkedNodeClass.

# include "LinkedNodeClass.h"


LinkedNodeClass::LinkedNodeClass(LinkedNodeClass* inPrev, const int &inVal,
     LinkedNodeClass* inNext) {
    prevNode = inPrev;
    nodeVal = inVal;
    nextNode = inNext;
}

int LinkedNodeClass::getValue() const {
    return nodeVal;
}

LinkedNodeClass* LinkedNodeClass::getNext() const {
    return nextNode;
}

LinkedNodeClass* LinkedNodeClass::getPrev() const {
    return prevNode;
}

void LinkedNodeClass::setNextPointerToNull() {
    nextNode = NULL;
}

void LinkedNodeClass::setPreviousPointerToNull() {
    prevNode = NULL;
}

void LinkedNodeClass::setBeforeAndAfterPointers() {
    if (prevNode != NULL) {
        prevNode -> nextNode = this;
    }
    
    if (nextNode != NULL) {
        nextNode -> prevNode = this;
    }
}