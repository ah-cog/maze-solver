#ifndef H_MazeApp
#define H_MazeApp

#include "Move.h"
#include "Stack.h"


//-----------------------------------------------------------------------------
// "Support" structures (meaning, that they help make code pretty)
//-----------------------------------------------------------------------------

struct MazeCursor
{
  Position currPos;
  Position prevPos;
};

struct MazeMap
{
  char** map;

  int rows;
  int cols;
};


//-----------------------------------------------------------------------------
// Function signatures
//-----------------------------------------------------------------------------

void displayMazeMap(MazeMap& a_mazeMap);
void displayMazeMapSolution(MazeMap& a_mazeMap, Stack<Move*>& a_moveStack,
			    Stack<Move*>& a_backtrackStack);

void displaySolutionMoves(Stack<Move*>& a_moveStack);
bool findMazeMapEntrance(Position& a_entrancePos, MazeMap& a_mazeMap);
int readMazeMapFile(MazeMap& a_mazeMap, string a_inputFileName);
void copyMazeMap(MazeMap& a_mazeMapSource, MazeMap& a_mazeMapDestination);

bool dragonIsHere(MazeMap& a_mazeMap, MazeCursor& a_mazeCursor);

bool canMove(MazeMap& a_mazeMap, MazeCursor& a_mazeCursor,
	     Stack<Move*>& a_moveStack,
	     Stack<Move*>& a_feasibleMoveStack);

void addMoveEast(MazeCursor& a_mazeCursor, Stack<Move*>& a_feasibleMoveStack);
bool canMoveEast(MazeMap& a_mazeMap, MazeCursor& a_mazeCursor,
		 Stack<Move*>& a_moveStack);
bool dragonIsEast(MazeMap& a_mazeMap, MazeCursor& a_mazeCursor);

void addMoveNorth(MazeCursor& a_mazeCursor, Stack<Move*>& a_feasibleMoveStack);
bool canMoveNorth(MazeMap& a_mazeMap, MazeCursor& a_mazeCursor,
		  Stack<Move*>& a_moveStack);
bool dragonIsNorth(MazeMap& a_mazeMap, MazeCursor& a_mazeCursor);

void addMoveWest(MazeCursor& a_mazeCursor, Stack<Move*>& a_feasibleMoveStack);
bool canMoveWest(MazeMap& a_mazeMap, MazeCursor& a_mazeCursor,
		 Stack<Move*>& a_moveStack);
bool dragonIsWest(MazeMap& a_mazeMap, MazeCursor& a_mazeCursor);

void addMoveSouth(MazeCursor& a_mazeCursor, Stack<Move*>& a_feasibleMoveStack);
bool canMoveSouth(MazeMap& a_mazeMap, MazeCursor& a_mazeCursor,
		  Stack<Move*>& a_moveStack);
bool dragonIsSouth(MazeMap& a_mazeMap, MazeCursor& a_mazeCursor);

bool moveAlreadyMade(int a_xPos, int a_yPos, Stack<Move*>& a_moveStack);
bool makeMove(MazeCursor& a_mazeCursor, Stack<Move*>& a_feasibleMoveStack,
	      Stack<Move*>& a_moveStack);

bool backtrack(Stack<Move*>& a_feasibleMoveStack, Stack<Move*>& a_moveStack,
	       Stack<Move*>& a_backtrackStack);

#endif
