/* ------------------------------------------------------------------------- *
 *
 * Filename : Move.h
 * Version  : 1.0
 *
 * Author   : Michael Gubbels
 * Date     : March 3, 2007
 *
 * Purpose  : Contains informaiton for a specific Move through two-
 *          : dimensional maze.
 *
 * ------------------------------------------------------------------------- */

#ifndef H_move
#define H_move

#include <iostream>

using namespace std;


//-----------------------------------------------------------------------------
// "Support" structures (meaning, that they help make code pretty)
//-----------------------------------------------------------------------------

// Name: Position
// Purpose: Stores x and y coordinates of a position (generic use!)
struct Position
{
  /** x coordinate **/
  int x;

  /** y coordinate **/
  int y;
};


//-----------------------------------------------------------------------------
// Class declaration
//-----------------------------------------------------------------------------

class Move
{
 public:

  /** Constructors **/

  Move();
    /* Purpose : To create a "default" Move object
     * Postconditions : A Move object will exist
     */

  Move(const Move& otherMove);
    /* Purpose : To create a copy of a Move object
     * Arguments -
     *   const Move& otherMove : Move to copy
     *   Postconditions : A copy of a Move object will exist
     */

  Move(char initID, int initPosX, int initPosY, Move* initPrevious,
       bool initBacktrack);
    /* Purpose : To create a Move object with the specifed values
     * Arguments -
     *   char initID : Move ID (E, N, W, S)
     *   int initPosX : x-coordinate position
     *   int initPosY : y-coordinate position
     *   Move* initPrevious : Pointer to previous move
     *   bool initBacktrack : Is a backtrack?
     * Postconditions : A Move object will exist
     */


  /** Destructors **/

  ~Move();
    /* Purpose : To destroy the Move!  ...with the aid of a dolphin.
     * Postconditions : A Move object will no longer exist.
     */


  /** Overloaded operators **/

  const Move& operator=(const Move& otherMove);
    /* Purpose : Overloads assignment operator
     * Returns reference to new Move object that will be used in assignment
     */

  
  /** Accessors/mutators **/

  char getID();
    /* Purpose : Gets move ID
     * Returns : Move ID (indicates feasible move)
     */

  Position getPosition();
    /* Purpose : Returns position
     * Returns : Move position
     */

  Move* getPrevious();
    /* Purpose : Returns pointer to previous Move
     * Returns : Pointer to previous Move on stack
     */

  bool isBacktrack();
    /* Purpose : Indicates if a move is a backtrack
     * Returns : Boolean value indicating whether the Move is a backtrack
     */

  void setID(char newID);
    /* Purpose : Sets ID to specified ID
     * Arguments -
     *   char newID : The new ID
     */

  void setPosition(int newPosX, int newPosY);
    /* Purpose : Sets position coordinates to specified coordinates
     * Arguments -
     *   int newPosX : New x-coordinate
     *   int newPosY : New y-coordinate
     */

  void setBacktrack(bool didBacktrack);
    /* Purpose : Sets the backtrack flag to the specified truth value
     * Arguments -
     *   bool didBacktrack : Truth value specifying whether is a backtrack
     */

  void setPrevious(Move* newPrevious);
    /* Purpose: Sets the pointer to the specified Move pointer
     * Arguments -
     *   Move* newPrevious : The pointer Move pointer to set as previous
     */

 private:

  /** Character ID to Indicate Feasibility**/
  char ID; // E N W S

  /** Position (x,y) of Move **/
  Position position; // (row, col)

  /** Pointer to previous Move **/
  Move* previous; // Ptr to prev Move

  /** Flag indicating whether the Move is a backtrack **/
  bool backtrack; // Flag indicating if is a backtrack
};

#endif
