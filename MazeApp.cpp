/* ------------------------------------------------------------------------- *
 *
 * Filename : MazeApp.cpp
 * Version  : 1.0
 *
 * Author   : Michael Gubbels
 * Date     : March 3, 2007
 *
 * Purpose  : This program solves a two-dimensional maze specified in a
 *          : specific format--that is, with walls specified using the
 *          : asterisk '*', and a valid empty space that can be moved to
 *          : with a space character ' '.  The goal is indicated by the
 *          : 'd' character.  This indicates the location of a dragon.
 *          : The dragon must die, apparently (poor dragon).
 *
 * ------------------------------------------------------------------------- */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#include "MazeApp.h"

using namespace std;


//-----------------------------------------------------------------------------
// Globals
//-----------------------------------------------------------------------------

/** This indicates very obvious errors, as it states... **/
const int FLAGRANT_ERROR = -1;

/** These indicate directions, as they state! **/
const char EAST = 'E';
const char NORTH = 'N';
const char WEST = 'W';
const char SOUTH = 'S';


//-----------------------------------------------------------------------------
// Main function
//-----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
  if(argc != 2)
    {
      cerr << "Invalid argument form." << endl;
      cerr << "Use form: 'MazeApp inputFile'" << endl;
      exit(0);
    }

  /** READ IN COMMAND LINE ARGUMENTS **/
  
  /** The maze input file name **/
  string inputFileName = argv[1];
  
  /** The maze array **/
  MazeMap mazeMap;

  /** DISPLAY WELCOME AND READ IN MAZE MAP FROM FILE **/
  cout << "Welcome to Merlin's wizardry, your highness!" << endl;

  // Check to see if input file is valid.
  // Read maze map from file into 2D array.
  cout << "Reading secret map of \"" << inputFileName << "\" ..." << endl;
  if(readMazeMapFile(mazeMap, inputFileName) == FLAGRANT_ERROR)
    {
      cerr << "Input file cannot be read." << endl;
      cerr << "Use a valid input file with form: 'MazeApp inputFile'" << endl;
      exit(0);
    }

  cout << "Trying now to find a solution... Please be patient..." << endl;

  /** FIND SOLUTION **/
  Stack<Move*> feasibleMoveStack;
  Stack<Move*> moveStack;
  Stack<Move*> backtrackStack;

  MazeCursor mazeCursor;
  Move* prevMove;

  MazeMap mazeMapSolution;
  copyMazeMap(mazeMap, mazeMapSolution);

  Position entrancePos;
  bool solvable;
  bool foundDragon;

  // Add the follow to "cursor"?:
  if( !(findMazeMapEntrance(entrancePos, mazeMap)) )
    {
      cerr << "No entrances have been located on the map!" << endl;
      cerr << "Use a valid map (that is, one with an entrance!)." << endl;
      exit(0);
    }

  // Initialize route information
  mazeCursor.currPos.x = entrancePos.x;
  mazeCursor.currPos.y = entrancePos.y;
  mazeCursor.prevPos.x = -1;
  mazeCursor.prevPos.y = -1;
  solvable = 1;
  foundDragon = 0;

  // Look through moves!
  do
    {
      // If the dragon is here, we're done!
      if( dragonIsHere(mazeMap, mazeCursor)  )
	{
	  //cout << "Dragon found!" << endl;
	  foundDragon = 1;	  
	}
      // Dragon is not here!  We are not done!
      else
	{
	  if( canMove(mazeMap, mazeCursor, moveStack, feasibleMoveStack) )
	    {
	      makeMove(mazeCursor, feasibleMoveStack, moveStack);
	    }
	  else // otherwise, backtrack
	    {
	      // Make sure move stack isn't empty!
	      if( feasibleMoveStack.isEmptyStack() && !(moveStack.isEmptyStack()) )
		{
		  solvable = 0;
		}
	      else
		{
		  if( !(moveStack.isEmptyStack()) )
		    {
		      backtrack(feasibleMoveStack, moveStack, backtrackStack);
		      makeMove(mazeCursor, feasibleMoveStack, moveStack);
		    }
		}
	    }
	}
    } while( (foundDragon == 0) && (solvable == 1) );

  if( (foundDragon == 1) && (solvable == 1) )
    {
      /** DISPLAY SOLUTION **/
      cout << "Here is the solution: ";
      displaySolutionMoves(moveStack);

      cout << "The solution is maze form:" << endl;
      displayMazeMapSolution(mazeMap, moveStack, backtrackStack);
    }
  else
    {
      cout << "No solution can be found.  "
	   << "The dragon is too sneaky, and it will surely eat you." << endl;
    }

  cout << "Thank you for using merlin's MazeApp." << endl;

  return 0;
}


//-----------------------------------------------------------------------------
// Program functions
//-----------------------------------------------------------------------------

/*
 * Purpose : Displays a maze map in the form of a 2D array
 * Arguments -
 *   MazeMap& a_mazeMap : Reference to MazeMap
 */
void displayMazeMap(MazeMap& a_mazeMap)
{
  for(int i = 0; i < a_mazeMap.rows; i++)
    {
      for(int j = 0; j < a_mazeMap.cols; j++)
	{
	  cout << a_mazeMap.map[i][j];
	}
      cout << endl;
    }
}

/*
 * Purpose : Displays the maze map with the solution and backtrack information
 *         : indicated
 * Arguments -
 *   MazeMap& a_mazeMap : Reference to a MazeMap
 *   Stack<Move*>& a_moveStack : Reference to a Stack of Move pointers
 *   Stack<Move*>& a_backtrackStack : Reference to Stack of Move pointers
 */
void displayMazeMapSolution(MazeMap& a_mazeMap, Stack<Move*>& a_moveStack,
			    Stack<Move*>& a_backtrackStack)
{
  bool solutionFlag = 0;
  bool backtrackFlag = 0;

  for(int i = 0; i < a_mazeMap.rows; i++)
    {
      for(int j = 0; j < a_mazeMap.cols; j++)
	{
	  solutionFlag = 0;
	  backtrackFlag = 0;
	  
	  Move* pMove = NULL;

	  if( !(a_moveStack.isEmptyStack()) )
	    pMove = a_moveStack.top();

	  while(pMove != NULL)
	    {
	      if( (i == pMove->getPosition().x) &&
		  (j == pMove->getPosition().y) )
		{
		  solutionFlag = 1;
		}
	      pMove = pMove->getPrevious();
	    }

	  if( !(a_backtrackStack.isEmptyStack()) )
	    pMove = a_backtrackStack.top();

	  while(pMove != NULL)
	    {
	      if( (i == pMove->getPosition().x) &&
		  (j == pMove->getPosition().y) )
		{
		  backtrackFlag = 1;
		}
	      pMove = pMove->getPrevious();
	    }

	  if( a_mazeMap.map[i][j] == 'd' )
	    cout << "x";
	  else if( solutionFlag == 1 )
	    cout << "s";
	  else if( backtrackFlag == 1 )
	    cout << "b";
	  else
	    cout << a_mazeMap.map[i][j];
	}
      cout << endl;
    }
}

/*
 * Purpose : Displays solution as a sequence of Move ID symbols
 * Arguments -
 *   Stack<Move*>& a_moveStack : Reference to a Stack of Move pointers
 */
void displaySolutionMoves(Stack<Move*>& a_moveStack)
{
  Stack<char> tmpMoveSeqStack;

  Move* pMove = NULL;
  if( !(a_moveStack.isEmptyStack()) )
    {
      Move* pMove = a_moveStack.top();

      // Get remaining moves
      while(pMove != NULL)
	{
	  tmpMoveSeqStack.push(pMove->getID());
	  pMove = pMove->getPrevious();
	}

      while( !(tmpMoveSeqStack.isEmptyStack()) )
	{
	  cout << tmpMoveSeqStack.top();
	  tmpMoveSeqStack.pop();

	  if( !(tmpMoveSeqStack.isEmptyStack()) )
	    cout << "-";
	}
      cout << endl;
    }
}

/*
 * Purpose : Locates a single maze entrance indicated by the 'e' symbol
 * Arguments -
 *   Position& a_entrancePos : Reference to Position indicator
 *                           : that will hold the entrance position
 *   MazeMap& a_mazeMap : Reference to a MazeMap
 * Returns : Truth value indicating whether an entrance was found
 */
bool findMazeMapEntrance(Position& a_entrancePos, MazeMap& a_mazeMap)
{
  int count = 0;

  for(int row = 0; row < a_mazeMap.rows; row++)
    {
      for(int col = 0; col < a_mazeMap.cols; col++)
	{
	  if(a_mazeMap.map[row][col] == 'e')
	    {
	      a_entrancePos.x = row;
	      a_entrancePos.y = col;
	      
	      return true;
	    }
	}
    }

  return false;
}

/*
 * Purpose : Determines whether a move can be made
 * Arguments -
 *   MazeMap& a_mazeMap : Reference to a MazeMap
 *   MazeCursor&a_mazeCursor : Reference to a MazeCursor
 *   Stack<Move*>& a_feasibleMoveStack : Stack of Move pointers
 * Returns : Truth value indicating whether a move can be made
 */
bool canMove(MazeMap& a_mazeMap, MazeCursor& a_mazeCursor,
	     Stack<Move*>& a_moveStack,
	     Stack<Move*>& a_feasibleMoveStack)
{
  bool tmp_areFeasibleMoves = 0;

  // Look South
  if( canMoveSouth(a_mazeMap, a_mazeCursor, a_moveStack) )
    {
      addMoveSouth(a_mazeCursor, a_feasibleMoveStack);
      tmp_areFeasibleMoves = 1;
    }
  // Look West
  if( canMoveWest(a_mazeMap, a_mazeCursor, a_moveStack) )
    {
      addMoveWest(a_mazeCursor, a_feasibleMoveStack);
      tmp_areFeasibleMoves = 1;
    }
  // Look North
  if( canMoveNorth(a_mazeMap, a_mazeCursor, a_moveStack) )
    {
      addMoveNorth(a_mazeCursor, a_feasibleMoveStack);
      tmp_areFeasibleMoves = 1;
    }
  // Look East
  if( canMoveEast(a_mazeMap, a_mazeCursor, a_moveStack) )
    {
      addMoveEast(a_mazeCursor, a_feasibleMoveStack);
      tmp_areFeasibleMoves = 1;
    }
  
  return tmp_areFeasibleMoves;
}

/*
 * Purpose : Returns true if dragon is located here!
 * Arguments -
 *   MazeMap& a_mazeMap : Reference to MazeMap
 *   MazeCursor& a_mazeCursor : Reference to MazeCursor
 * Returns : Truth value indicating whether dragon is here
 */
bool dragonIsHere(MazeMap& a_mazeMap, MazeCursor& a_mazeCursor)
{
  if( tolower(a_mazeMap.map[a_mazeCursor.currPos.x][a_mazeCursor.currPos.y] )
      == 'd' )
    return true;
  else
    return false;
}

// ** CHECKS FOR EAST ** //

/*
 * Purpose : Adds a move east to the stack of feasible moves
 * Arguments -
 *   MazeCursor& a_mazeCursor : Reference ot MazeCursor
 *   Stack<Move*>& a_feasibleMoveStack : Reference to Stack of Move pointers
 */
void addMoveEast(MazeCursor& a_mazeCursor, Stack<Move*>& a_feasibleMoveStack)
{
  Move* pPrevMove = NULL;
  if( !(a_feasibleMoveStack.isEmptyStack()) )
    pPrevMove = a_feasibleMoveStack.top();

  Move* pNewMove =
    new Move(EAST, a_mazeCursor.currPos.x, a_mazeCursor.currPos.y,
	     pPrevMove, 0);

  a_feasibleMoveStack.push(pNewMove);
}

/*
 * Purpose : Returns true if moving east is feasible!
 * Arguments -
 *   MazeMap& a_mazeMap : Reference to a MazeMap
 *   MazeCursor& a_mazeCursor : Reference to MazeCursor
 * Returns : Truth value indicating whether move is feasible
 */
bool canMoveEast(MazeMap& a_mazeMap, MazeCursor& a_mazeCursor,
		 Stack<Move*>& a_moveStack)
{
  // Are we still in bounds of the maze?
  if( a_mazeCursor.currPos.y+1 < a_mazeMap.cols )
    {
      if( a_mazeCursor.currPos.y+1 != a_mazeCursor.prevPos.y )
	{
	  // Check to see if there is a wall to the east
	  if(((a_mazeMap.map[a_mazeCursor.currPos.x][a_mazeCursor.currPos.y+1]
	       == ' ') ||
	      (a_mazeMap.map[a_mazeCursor.currPos.x][a_mazeCursor.currPos.y+1]
	       == 'd') ) &&
	     (!(moveAlreadyMade(a_mazeCursor.currPos.x,
				a_mazeCursor.currPos.y+1,
				a_moveStack))))
	    {
	      // Moving east is feasible, so return true!
	      return true;
	    }
	}
    }
  return false;
}

// ** CHECKS FOR NORTH **//

/*
 * Purpose : Adds a move north to the stack of feasible moves
 * Arguments -
 *   MazeCursor& a_mazeCursor : Reference ot MazeCursor
 *   Stack<Move*>& a_feasibleMoveStack : Reference to Stack of Move pointers
 */
void addMoveNorth(MazeCursor& a_mazeCursor, Stack<Move*>& a_feasibleMoveStack)
{
  Move* pPrevMove = NULL;
  if( !(a_feasibleMoveStack.isEmptyStack()) )
    pPrevMove = a_feasibleMoveStack.top();

  Move* pNewMove =
    new Move(NORTH, a_mazeCursor.currPos.x, a_mazeCursor.currPos.y,
	     pPrevMove, 0);
  a_feasibleMoveStack.push(pNewMove);
}

/*
 * Purpose : Returns true if moving north is feasible!
 * Arguments -
 *   MazeMap& a_mazeMap : Reference to a MazeMap
 *   MazeCursor& a_mazeCursor : Reference to MazeCursor
 * Returns : Truth value indicating whether move is feasible
 */
bool canMoveNorth(MazeMap& a_mazeMap, MazeCursor& a_mazeCursor,
		  Stack<Move*>& a_moveStack)
{
  // Are we still in bounds of the maze?
  if( a_mazeCursor.currPos.x-1 >= 0 )
    {
      if( a_mazeCursor.currPos.x-1 != a_mazeCursor.prevPos.x )
        {
          // Check to see if there is a wall to the north
	  if(((a_mazeMap.map[a_mazeCursor.currPos.x-1][a_mazeCursor.currPos.y]
	       == ' ') ||
	      (a_mazeMap.map[a_mazeCursor.currPos.x-1][a_mazeCursor.currPos.y]
	       == 'd') ) &&
	     (!(moveAlreadyMade(a_mazeCursor.currPos.x-1,
				a_mazeCursor.currPos.y,
				a_moveStack))))

            {
              // Moving north is feasible, so return true!
              return true;
            }
        }
    }
  return false;
}

// ** CHECKS FOR WEST **//

/*
 * Purpose : Adds a move west to the stack of feasible moves
 * Arguments -
 *   MazeCursor& a_mazeCursor : Reference ot MazeCursor
 *   Stack<Move*>& a_feasibleMoveStack : Reference to Stack of Move pointers
 */
void addMoveWest(MazeCursor& a_mazeCursor, Stack<Move*>& a_feasibleMoveStack)
{
  Move* pPrevMove = NULL;
  if( !(a_feasibleMoveStack.isEmptyStack()) )
    pPrevMove = a_feasibleMoveStack.top();

  Move* pNewMove =
    new Move(WEST, a_mazeCursor.currPos.x, a_mazeCursor.currPos.y,
	     pPrevMove, 0);
  a_feasibleMoveStack.push(pNewMove);
}

/*
 * Purpose : Returns true if moving west is feasible!
 * Arguments -
 *   MazeMap& a_mazeMap : Reference to a MazeMap
 *   MazeCursor& a_mazeCursor : Reference to MazeCursor
 * Returns : Truth value indicating whether move is feasible
 */
bool canMoveWest(MazeMap& a_mazeMap, MazeCursor& a_mazeCursor,
		 Stack<Move*>& a_moveStack)
{
  // Are we still in bounds of the maze?
  if( a_mazeCursor.currPos.y-1 >= 0 )
    {
      if( a_mazeCursor.currPos.y-1 != a_mazeCursor.prevPos.y )
        {
          // Check to see if there is a wall to the west
	  if(((a_mazeMap.map[a_mazeCursor.currPos.x][a_mazeCursor.currPos.y-1]
               == ' ') ||
              (a_mazeMap.map[a_mazeCursor.currPos.x][a_mazeCursor.currPos.y-1]
               == 'd') ) &&
             (!(moveAlreadyMade(a_mazeCursor.currPos.x,
                                a_mazeCursor.currPos.y-1,
				a_moveStack))))

            {
              // Moving west is feasible, so return true!
              return true;
            }
        }
    }
  return false;
}

// ** CHECKS FOR SOUTH **//

/*
 * Purpose : Adds a move south to the stack of feasible moves
 * Arguments -
 *   MazeCursor& a_mazeCursor : Reference ot MazeCursor
 *   Stack<Move*>& a_feasibleMoveStack : Reference to Stack of Move pointers
 */
void addMoveSouth(MazeCursor& a_mazeCursor, Stack<Move*>& a_feasibleMoveStack)
{
  Move* pPrevMove = NULL;
  if( !(a_feasibleMoveStack.isEmptyStack()) )
    pPrevMove = a_feasibleMoveStack.top();

  Move* pNewMove =
    new Move(SOUTH, a_mazeCursor.currPos.x, a_mazeCursor.currPos.y,
	     pPrevMove, 0);
  a_feasibleMoveStack.push(pNewMove);
}

/*
 * Purpose : Returns true if moving south is feasible!
 * Arguments -
 *   MazeMap& a_mazeMap : Reference to a MazeMap
 *   MazeCursor& a_mazeCursor : Reference to MazeCursor
 * Returns : Truth value indicating whether move is feasible
 */
bool canMoveSouth(MazeMap& a_mazeMap, MazeCursor& a_mazeCursor,
		  Stack<Move*>& a_moveStack)
{
  // Are we still in bounds of the maze?
  if( a_mazeCursor.currPos.x+1 < a_mazeMap.rows )
    {
      if( a_mazeCursor.currPos.x+1 != a_mazeCursor.prevPos.x )
        {
          // Check to see if there is a wall to the south
	  if(((a_mazeMap.map[a_mazeCursor.currPos.x+1][a_mazeCursor.currPos.y]
               == ' ') ||
              (a_mazeMap.map[a_mazeCursor.currPos.x+1][a_mazeCursor.currPos.y]
               == 'd') ) &&
             (!(moveAlreadyMade(a_mazeCursor.currPos.x+1,
                                a_mazeCursor.currPos.y,
				a_moveStack))))
            {
              // Moving south is feasible, so return true!
              return true;
            }
        }
    }
  return false;
}

/*
 * Purpose : Indicates whether a move was already made
 * Arguments -
 *   int a_xPos : x-coordinate
 *   int a_yPos : y-coordinate
 *   Stack<Move*>& a_moveStack : Reference to stack of moves
 * Returns : Truth value indicating whether move was made
 */
bool moveAlreadyMade(int a_xPos, int a_yPos, Stack<Move*>& a_moveStack)
{
  bool tmpMoveAlreadyMade = 0;

  Move* pTmpMovePtr = NULL;
  if( !(a_moveStack.isEmptyStack()) )
    pTmpMovePtr = a_moveStack.top();

  while( (pTmpMovePtr != NULL) && (tmpMoveAlreadyMade == 0) )
    {
      if( (a_xPos == pTmpMovePtr->getPosition().x) &&
	  (a_yPos == pTmpMovePtr->getPosition().y) )
	{
	  tmpMoveAlreadyMade = 1;
	}
      pTmpMovePtr = pTmpMovePtr->getPrevious();
    }

  return tmpMoveAlreadyMade;
}

/*
 * Purpose : Makes a move
 * Arguments -
 *   MazeCursor& a_mazeCursor : Reference to MazeCursor
 *   Stack<Move*>& a_feasibleMoveStack : Stack of Move pointers
 *   Stack<Move*>& a_moveStack : Stack of Move pointers
 * Returns : Truth value indicating whether move is feasible
 */
bool makeMove(MazeCursor& a_mazeCursor, Stack<Move*>& a_feasibleMoveStack,
	      Stack<Move*>& a_moveStack)
{
  bool madeMove = false;

  Move* pPrevMove = NULL;
  if( !(a_moveStack.isEmptyStack()) )
    pPrevMove = a_moveStack.top();

  Move* pTmpMove = new Move(*a_feasibleMoveStack.top());
  pTmpMove->setPrevious( pPrevMove );
  a_moveStack.push( pTmpMove );
  a_feasibleMoveStack.pop();

  a_mazeCursor.prevPos.x = a_mazeCursor.currPos.x;
  a_mazeCursor.prevPos.y = a_mazeCursor.currPos.y;

  if( a_moveStack.top()->getID() == EAST )
    {
      a_mazeCursor.currPos.x = a_moveStack.top()->getPosition().x;
      a_mazeCursor.currPos.y = a_moveStack.top()->getPosition().y+1;
      madeMove = 1;
    }
  else if( a_moveStack.top()->getID() == NORTH )
    {
      a_mazeCursor.currPos.x = a_moveStack.top()->getPosition().x-1;
      a_mazeCursor.currPos.y = a_moveStack.top()->getPosition().y;
      madeMove = 1;
    }
  else if( a_moveStack.top()->getID() == WEST )
    {
      a_mazeCursor.currPos.x = a_moveStack.top()->getPosition().x;
      a_mazeCursor.currPos.y = a_moveStack.top()->getPosition().y-1;
      madeMove = 1;
    }
  else if( a_moveStack.top()->getID() == SOUTH )
    {
      a_mazeCursor.currPos.x = a_moveStack.top()->getPosition().x+1;
      a_mazeCursor.currPos.y = a_moveStack.top()->getPosition().y;
      madeMove = 1;
    }
  
  a_moveStack.top()->setPosition( a_mazeCursor.currPos.x,
				  a_mazeCursor.currPos.y );
  
  return madeMove;
}

/*
 * Purpose : Performs backtracking
 * Returns : Truth value indicating whether backtracking was performed
 */
bool backtrack(Stack<Move*>& a_feasibleMoveStack, Stack<Move*>& a_moveStack,
	       Stack<Move*>& a_backtrackStack)
{
  bool backtracked = false;

  do
    {
       // Place moves onto backtrackStack
      Move* pPrevMove = NULL;

      if( !(a_backtrackStack.isEmptyStack()) )
	pPrevMove = a_backtrackStack.top();

      a_moveStack.top()->setPrevious( pPrevMove );

      a_backtrackStack.push( a_moveStack.top() ); // Add Move to backtrackStack
      a_backtrackStack.top()->setBacktrack( 1 ); // Flag Move as a backtrack
      a_moveStack.pop(); // Remove Move from moveStack

      if( backtracked == false )
	backtracked = true;
    }
  while( (a_moveStack.top()->getPosition().x !=
	  a_feasibleMoveStack.top()->getPosition().x) ||
	 (a_moveStack.top()->getPosition().y !=
	  a_feasibleMoveStack.top()->getPosition().y) );

  return backtracked;
}

/*
 * Purpose : Reads maze map from file into 2D array
 * Arguments -
 *   MazeMap& a_mazeMap : Reference to MazeMap
 *   string a_inputFileName : String of input file name
 * Returns : Integer indicating whether maze map was read successfully
 */
int readMazeMapFile(MazeMap& a_mazeMap, string a_inputFileName)
{
  bool valid = 1; // Indicates whether input file is stil valid!

  ifstream inputFile(a_inputFileName.c_str());

  if( inputFile.good() )
    {
      string rowStr = "";
      
      /** READ IN FIRST LINE OF FILE (ROWS/COLS) **/
      
      getline(inputFile, rowStr); // Read in the first line (with rows/cols)
      istringstream strBuff; // String stream (used as input buffer)
      strBuff.str(rowStr); // Load first input file line into input buffer
      
      // Extract rows and colums from input buffer
      strBuff >> a_mazeMap.rows >> a_mazeMap.cols;

      /** ALLOCATE MEMORY FOR MAZE **/

      // Allocate rows
      a_mazeMap.map = new char*[a_mazeMap.rows];

      // Allocate columns
      int row=0, col=0;
      for(row=0; row < a_mazeMap.rows; row++)
	{
	  a_mazeMap.map[row] = new char[a_mazeMap.cols];
	}

      // Zero out map
      for(row = 0; row < a_mazeMap.rows; row++)
	{
	  for(col = 0; col < a_mazeMap.cols; col++)
	    {
	      a_mazeMap.map[row][col] = ' ';
	    }
	}

      row=0, col=0;
      for(int i = 0; (i < a_mazeMap.rows) && (!inputFile.eof()); i++)
	{
	  // Get row string!
	  getline(inputFile, rowStr);

	  if(rowStr.length() > a_mazeMap.cols)
	    valid = 0;

	  if(valid == 1)
	    {
	      // Go through row and extract tiles!
	      for(col = 0; col < a_mazeMap.cols; col++)
		{
		  a_mazeMap.map[row][col] = rowStr[col];
		  // a_mazeMap.moveMap[row][col].setPosition(row,col);
		}
      
	      // Increment so we use next row! (Go one row down)
	      row++;
	    }
	  else
	    {
	      // Set counter to max, so loop breaks
	      i = a_mazeMap.rows;
	    }
	}
  
      inputFile.close();
    }
  else
    {
      valid = 0;;
    }

  if(valid == 1)
    return 0;
  else
    return -1;
}

/*
 * Purpose : Copies a MazeMap
 * Arguments -
 *   MazeMap& a_mazeMapSource : Copy source
 *   MazeMap& a_mazeMapSource : Copy destination
 */
void copyMazeMap(MazeMap& a_mazeMapSource, MazeMap& a_mazeMapDestination)
{
  a_mazeMapDestination.rows = a_mazeMapSource.rows;
  a_mazeMapDestination.cols = a_mazeMapSource.cols;

  /** ALLOCATE MEMORY FOR MAZE **/

  // Allocate rows
  a_mazeMapDestination.map = new char*[a_mazeMapDestination.rows];

  // Allocate columns
  int row=0, col=0;
  for(row=0; row < a_mazeMapDestination.rows; row++)
    {
      a_mazeMapDestination.map[row] = new char[a_mazeMapDestination.cols];
    }

  // Zero out map
  for(row = 0; row < a_mazeMapDestination.rows; row++)
    {
      for(col = 0; col < a_mazeMapDestination.cols; col++)
	{
	  a_mazeMapDestination.map[row][col] = a_mazeMapSource.map[row][col];
	}
    }
}
