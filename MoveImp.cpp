#include "Move.h"

//-----------------------------------------------------------------------------
// Class constructors
//-----------------------------------------------------------------------------

/*
 * Purpose : To create a "default" Move object
 * Postconditions : A Move object will exist
 */
Move::Move()
{
  this->ID = 'X';
  this->position.x = 0;
  this->position.y = 0;
  this->previous = NULL;
  this->backtrack = 0;
}

/* 
 * Purpose : To create a copy of a Move object
 * Arguments -
 *   const Move& otherMove : Move to copy
 *   Postconditions : A copy of a Move object will exist
 */
Move::Move(const Move& otherMove)
{
  this->ID = otherMove.ID;
  this->position.x = otherMove.position.x;
  this->position.y = otherMove.position.y;
  this->previous = otherMove.previous;
  this->backtrack = otherMove.backtrack;
}

/* 
 * Purpose : To create a Move object with the specifed values
 * Arguments -
 *   char initID : Move ID (E, N, W, S)
 *   int initPosX : x-coordinate position
 *   int initPosY : y-coordinate position
 *   Move* initPrevious : Pointer to previous move
 *   bool initBacktrack : Is a backtrack?
 * Postconditions : A Move object will exist
 */
Move::Move(char initID, int initPosX, int initPosY, Move* initPrevious,
	   bool initBacktrack)
{
  this->ID = initID;
  this->position.x = initPosX;
  this->position.y = initPosY;
  this->previous = initPrevious;
  this->backtrack = initBacktrack;
}


//-----------------------------------------------------------------------------
// Class destructors
//-----------------------------------------------------------------------------

/* 
 * Purpose : To destroy the Move!  ...with the aid of a dolphin.
 * Postconditions : A Move object will no longer exist.
 */
Move::~Move()
{
  // Take care when deleting moves!  Other moves might point to
  // this memory space as well!  They'll point to a "junk" space
  // if this is deleted!
  delete this->previous;
}


//-----------------------------------------------------------------------------
// Overloaded operators
//-----------------------------------------------------------------------------

/* 
 * Purpose : Overloads assignment operator
 * Returns reference to new Move object that will be used in assignment
 */
const Move& Move::operator=(const Move& otherMove)
{
  if( this != &otherMove )
    {
      this->ID = otherMove.ID;
      this->position.x = otherMove.position.x;
      this->position.y = otherMove.position.y;
      this->previous = otherMove.previous;
      this->backtrack = otherMove.backtrack;
    }

  return *this;
}


//-----------------------------------------------------------------------------
// Accessors/mutators
//-----------------------------------------------------------------------------

/*
 * Purpose : Returns position
 * Returns : Move position
 */
Position Move::getPosition()
{
  return this->position;
}

/*
 * Purpose : Returns pointer to previous Move
 * Returns : Pointer to previous Move on stack
 */
Move* Move::getPrevious()
{
  return this->previous;
}

/*
 * Purpose : Indicates if a move is a backtrack
 * Returns : Boolean value indicating whether the Move is a backtrack
 */
bool Move::isBacktrack()
{
  return this->backtrack;
}

/*
 * Purpose : Gets move ID
 * Returns : Move ID (indicates feasible move)
 */
char Move::getID()
{
  return this->ID;
}

/*
 * Purpose : Sets ID to specified ID
 * Arguments -
 *   char newID : The new ID
 */
void Move::setID(char newID)
{
  this->ID = newID;
}

/*
 * Purpose : Sets position coordinates to specified coordinates
 * Arguments -
 *   int newPosX : New x-coordinate
 *   int newPosY : New y-coordinate
 */
void Move::setPosition(int x, int y)
{
  this->position.x = x;
  this->position.y = y;
}

/*
 * Purpose : Sets the backtrack flag to the specified truth value
 * Arguments -
 *   bool didBacktrack : Truth value specifying whether is a backtrack
 */
void Move::setBacktrack(bool didBacktrack)
{
  this->backtrack = didBacktrack;
}

/*
 * Purpose: Sets the pointer to the specified Move pointer
 * Arguments -
 *   Move* newPrevious : The pointer Move pointer to set as previous
 */
void Move::setPrevious(Move* newPrevious)
{
  this->previous = newPrevious;
}
