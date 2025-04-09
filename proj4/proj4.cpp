# include <iostream>
# include "SortedListClass.h"
# include "LIFOStackClass.h"
# include "FIFOQueueClass.h"
# include "LinkedNodeClass.h"

using namespace std;
//Do NOT remove any of the preprocessor directives in this file.
//They should not affect your ability to write test code in your
//main function below, and they must be in your submitted main
//file exactly as provided to you with the project.
#ifdef ANDREW_TEST
#include "andrewTest.h"
#else
int main()
{
//This is just a placeholder main function - it does exceptionally
//little actual testing, so you'll want to add your own tests here.
//Feel free to leave your tests in the version of this file you
//submit, but we will not be running your main function, so the
//output, etc., of your main doesn't need to match anything from
//a sample output, etc.

// ===================== FIFOQueueClass Tests =====================
cout << "===== FIFOQueueClass Tests =====" << endl;
FIFOQueueClass queue;

cout << "Enqueue 5 values: 10, 20, 30, 40, 50" << endl;
queue.enqueue(10);
queue.enqueue(20);
queue.enqueue(30);
queue.enqueue(40);
queue.enqueue(50);
queue.print(); // Expected: 10 20 30 40 50

cout << "Dequeuing 2 items..." << endl;
int val;
if (queue.dequeue(val)) cout << "Dequeued: " << val << endl;
if (queue.dequeue(val)) cout << "Dequeued: " << val << endl;
queue.print(); // Expected: 30 40 50

cout << "Queue size: " << queue.getNumElems() << endl; // Expected: 3

cout << "Clearing queue..." << endl;
queue.clear();
queue.print(); // Expected: List is empty!
cout << "Queue size: " << queue.getNumElems() << endl; // Expected: 0

cout << endl;

// ===================== LIFOStackClass Tests =====================
cout << "===== LIFOStackClass Tests =====" << endl;
LIFOStackClass stack;

cout << "Pushing 5 values: 10, 20, 30, 40, 50" << endl;
stack.push(10);
stack.push(20);
stack.push(30);
stack.push(40);
stack.push(50);
stack.print(); // Expected: 50 40 30 20 10

cout << "Popping 2 items..." << endl;
if (stack.pop(val)) cout << "Popped: " << val << endl;
if (stack.pop(val)) cout << "Popped: " << val << endl;
stack.print(); // Expected: 30 20 10

cout << "Stack size: " << stack.getNumElems() << endl; // Expected: 3

cout << "Clearing stack..." << endl;
stack.clear();
stack.print(); // Expected: List is empty!
cout << "Stack size: " << stack.getNumElems() << endl; // Expected: 0

cout << endl;

// ===================== SortedListClass Tests =====================
cout << "===== SortedListClass Tests =====" << endl;
SortedListClass sortedList;

cout << "Inserting: 40, 10, 50, 20, 30" << endl;
sortedList.insertValue(40);
sortedList.insertValue(10);
sortedList.insertValue(50);
sortedList.insertValue(20);
sortedList.insertValue(30);

cout << "Printing forward:" << endl;
sortedList.printForward(); // Expected: 10, 20, 30, 40, 50

cout << "Printing backward:" << endl;
sortedList.printBackward(); // Expected: 50, 40, 30, 20, 10

cout << "Removing front and last:" << endl;
if (sortedList.removeFront(val)) cout << "Removed front: " << val << endl;
if (sortedList.removeLast(val)) cout << "Removed last: " << val << endl;

cout << "Printing forward again:" << endl;
sortedList.printForward(); // Expected: 20, 30, 40

cout << "Testing getElemAtIndex:" << endl;
if (sortedList.getElemAtIndex(1, val)) cout << "Index 1: " << val << endl;
if (!sortedList.getElemAtIndex(10, val)) cout << "Index 10 is out of range." << endl;

cout << "List size: " << sortedList.getNumElems() << endl; // Expected: 3

cout << "Clearing list..." << endl;
sortedList.clear();
sortedList.printForward(); // Expected: empty
cout << "List size: " << sortedList.getNumElems() << endl; // Expected: 0

return 0;
}
#endif
