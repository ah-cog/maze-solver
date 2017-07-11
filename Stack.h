/* ------------------------------------------------------------------------- *
 *
 * Filename : Stack.h
 * Version  : 1.0
 *
 * Author   : Michael Gubbels
 * Date     : March 3, 2007
 *
 * Purpose  : Implements a FILO stack (based on the Stack implementation in
 *          : 'Data Structures Using C++' by Merlin (used in class).
 *
 * ------------------------------------------------------------------------- */

#ifndef H_stack
#define H_stack

#include <iostream>
#include <cassert>

using namespace std;


//-----------------------------------------------------------------------------
// Support structures
//-----------------------------------------------------------------------------

// Basic node implementation
template<class Type>
struct Node
{
  Type info;
  Node<Type> *link;
};


//-----------------------------------------------------------------------------
// Class template declaration
//-----------------------------------------------------------------------------

template<class Type>
class Stack
{
 public:
  const Stack<Type>& operator=(const Stack<Type>&);
    // Overload the assignment operator.
  void initializeStack();
    // Function to initialize the stack to an empty state.
    // Postcondition: The stack elements are removed;
    //                stackTop = NULL.
  bool isEmptyStack();
    // Function to determine whether the stack is empty.
    // Postcondition: Retruns true if the stack is empty;
    //                otherwise, returns false.
  bool isFullStack();
    // Function to determine whether the stack is full;
    // Postcondition: Returns false
  void destroyStack();
    // Function to remove all the elements of the stack,
    // leaving the stack in an empty state.
    // Postcondition: stackTop = NULL
  void push(const Type& newItem);
    // Function to add newItem to the stack.
    // Precondition: The stack exists and is not full.
    // Postcondition: The Stack is changed and newItem
    //                is added to the top of the stack.
  Type top();
    // Function to return the top element of the stack.
    // Precondition: The stack exists and is not empty.
    // Postcondition: If the stack is empty, the program
    //                terminates; otherwise, the top element
    //                of the stack is returned.
  void pop();
    // Function to remove the stack top element of the stack.
    // Precondition: The stack exists and is not empty.
    // Postcondition: The stack is changed and the top element
    //                is removed from the stack.
  Stack();
    // Default constructor
    // Postcondition: stackTop = NULL
  Stack(const Stack<Type>& otherStack);
    // Copy constructor
  ~Stack();
    // Destructor
    // Postcondition: All the elements of the stack are removed

 private:
  Node<Type> *stackTop; // pointer to the stack
  void copyStack(const Stack<Type>& otherStack);
    // Function to make a copy of otherStack.
    // Postcondition: A copy of otherStack is created and
    //                assigned to this stack.
};

#include "StackImp.cpp"

#endif
