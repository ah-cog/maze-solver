/* ------------------------------------------------------------------------- *
 *
 * Filename : StackImp.cpp
 * Version  : 1.0
 *
 * Author   : Michael Gubbels
 * Date     : March 3, 2007
 *
 * Purpose  : Implementation of the Stack template class
 *
 * ------------------------------------------------------------------------- */


//-----------------------------------------------------------------------------
// Class constructors
//-----------------------------------------------------------------------------

// Default constructor
// Postcondition: stackTop = NULL
template<class Type> // default constructor
Stack<Type>::Stack()
{
  stackTop = NULL;
}

// Copy constructor
template<class Type>
Stack<Type>::Stack(const Stack<Type>& otherStack)
{
  this->copyStack( otherStack );
  
  return *this;
}

//-----------------------------------------------------------------------------
// Class destructors
//-----------------------------------------------------------------------------

// Destructor
// Postcondition: All the elements of the stack are removed
template<class Type> // default destructor
Stack<Type>::~Stack()
{
  destroyStack();
}


//-----------------------------------------------------------------------------
// Overloaded operators
//-----------------------------------------------------------------------------

template<class Type>
const Stack<Type>& Stack<Type>::operator=(const Stack<Type>& otherStack)
{
  this->copyStack( otherStack );

  return *this;
}


//-----------------------------------------------------------------------------
// "Work" functions (Non-accessor/mutators)
//-----------------------------------------------------------------------------

// Function to remove all the elements of the stack,
// leaving the stack in an empty state.
// Postcondition: stackTop = NULL
template<class Type>
void Stack<Type>::destroyStack()
{
  Node<Type> *temp; // pointer to delete the node

  while(stackTop != NULL) // while there are elements
                          // in the stack
    {
      temp = stackTop; // Set temp to point to
                       // the current node
      stackTop = stackTop->link; // advance stackTop
                                 // to the next node
      delete temp; // deallocate the memory
                   // occupied by temp
    }
} // end destroyStack

// Function to initialize the stack to an empty state.
// Postcondition: The stack elements are removed;
//                stackTop = NULL.
template<class Type>
void Stack<Type>::initializeStack()
{
  destroyStack();
}

// Function to determine whether the stack is empty.
// Postcondition: Retruns true if the stack is empty;
//                otherwise, returns false.
template<class Type>
bool Stack<Type>::isEmptyStack()
{
  return(stackTop == NULL);
}

// Function to determine whether the stack is full;
// Postcondition: Returns false
template<class Type>
bool Stack<Type>::isFullStack()
{
  return false;
}

// Function to add newItem to the stack.
// Precondition: The stack exists and is not full.
// Postcondition: The Stack is changed and newItem
//                is added to the top of the stack.
template<class Type>
void Stack<Type>::push(const Type& newElement)
{
  Node<Type> *newNode; // pointer to create the new node

  newNode = new Node<Type>; // create the node
  assert(newNode != NULL);

  newNode->info = newElement; // store newElement in the node
  newNode->link = stackTop; // insert newNode before stackTop
  stackTop = newNode; // set stackTop to point to the
                      // top node
} // end push

// Function to return the top element of the stack.
// Precondition: The stack exists and is not empty.
// Postcondition: If the stack is empty, the program
//                terminates; otherwise, the top element
//                of the stack is returned.
template<class Type>
Type Stack<Type>::top()
{
  assert(stackTop != NULL); // if the stack is empty,
                            // terminate the program
  return stackTop->info; // return the top element
} // end top

// Function to remove the stack top element of the stack.
// Precondition: The stack exists and is not empty.
// Postcondition: The stack is changed and the top element
//                is removed from the stack.
template<class Type>
void Stack<Type>::pop()
{
  Node<Type> *temp; // pointer to deallocate the memory

  if(stackTop != NULL)
    {
      temp = stackTop; // set temp to point to the top node
      stackTop = stackTop->link; // advance stackTop to the next node
      delete temp; // delete teh top node
    }
  else
    cerr << "Cannot remove from an empty stack." << endl;
} // end pop

// Function to make a copy of otherStack.
// Postcondition: A copy of otherStack is created and
//                assigned to this stack.
template<class Type>
void Stack<Type>::copyStack(const Stack<Type>& otherStack)
{
  if( this != &otherStack )
    {
      Stack<Type> tmpBuffStack;
      
      Type* pTypePtr = NULL;
      if( !(otherStack.isEmptyStack()) )
	pTypePtr = &otherStack.top();

      // Store stack, backwards!
      while( pTypePtr != NULL )
	{
	  tmpBuffStack.push( otherStack.top() );
	  pTypePtr = pTypePtr->getPrevious();
	}

      // Read backwards stack into this stack
      while( !(tmpBuffStack.isEmptyList()) )
	{
	  this->push( tmpBuffStack.top() );
	  tmpBuffStack.pop();
	}
    }
}
