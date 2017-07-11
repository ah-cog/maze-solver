===============================================================================
 MAZEAPP README
===============================================================================

-------------------------------------------------------------------------------
 0. CONTENTS
-------------------------------------------------------------------------------

0. You're looking at it!
1. Files
   a. Heirchy
   b. Description
2. Compiling and Running
   a. Compiling
   b. Running
3. Testing


-------------------------------------------------------------------------------
1. FILES
   a. HEIRCHY
-------------------------------------------------------------------------------

The following is a file heirchy that represents the file/folder structure
for the Record Reader program:

/ (pwd)
MazeApp.cpp
MazeApp.h
MoveImp.cpp
Move.h
StackImp.cpp
Stack.h
testMazeExample.txt
testMazeEmpty1.txt
testMazeNoSolution.txt
Makefile
README
TEST

Details about these files are in 1b.


-------------------------------------------------------------------------------
1. FILES
   b. DESCRIPTION
-------------------------------------------------------------------------------

FILENAME            TYPE/DESCRIPTION

MazeApp.cpp         Source file.  Main program source file.

MazeApp.h           Header file.  Contains function headers, etc. used
                    throughout the program.

MoveImp.cpp         Source file.  Contains implementation of the Move class.

Move.h              Header file.  Contains the declaration of the Move class.

StackImp.cpp        Source file.  Contains the implementation of the Stack
                    template class.

Stack.h             Header file.  Contains the declaration of the Stack
                    template class.

testMaze
  Example.txt       Text file.  Contains the maze test example from the
                    homework handout.

testMaze
  Empty1.txt        Text file.  Contains an empty maze test example.

testMaze
  NoSolution.txt    Text file.  Contains the maze test example from the
                    homework handout, but with no solution!

Makefile            Makefile.  Used to build program from source files.

README              Text file.  You're reading it!  Contains information
                    about program and program files.

TEST                Text file.  Contains testing information and results.
                    Demonstrates program functionality for a variety of test
                    cases.


-------------------------------------------------------------------------------
2. COMPILING AND RUNNING
   a. COMPILING
-------------------------------------------------------------------------------

To compile the program the following files are required:

MazeApp.cpp
MazeApp.h
MoveImp.cpp
Move.h
StackImp.cpp
Stack.h

The following file is optional:

Makefile

The included makefile may be used to compile the program with a
single command.  To use the makefile, the present work directory
must contain the files listed above as well as the makefile (named either
'Makefile' or 'makefile').  To compile using the makefile, simply type the
'make' command using the Linux or Unix terminal:

terminal> make

This will automatically compile and link the source files and create an
executable binary file named 'MazeApp'.

Alternatively, the program can be compiled and linked manually.  To do this
from the Linux or Unix terminal, enter the following:

terminal> g++ -c MazeApp.cpp MoveImp.cpp
terminal> g++ -o MazeApp MazeApp.o MoveImp.o

These steps will produce an executable binary file named 'MoveApp'.

These steps are done assuming that no object files exist (if the object files
exist from a previous compilation, errors may occur).


-------------------------------------------------------------------------------
2. COMPILING AND RUNNING
   b. COMPILING
-------------------------------------------------------------------------------

Provided that the program was successfully compiled (using one of the two
methods described in 2a), it can be run by typing the following command:

terminal> ./MazeApp


-------------------------------------------------------------------------------
3. TESTING
-------------------------------------------------------------------------------

For testing results, refer to TEST file (located in the same directory as this
README file).


Michael Gubbels
March 4, 2007