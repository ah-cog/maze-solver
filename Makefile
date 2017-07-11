MazeApp : clean MazeApp.o MoveImp.o list
	g++ -o MazeApp MazeApp.o MoveImp.o

MazeApp.o : MazeApp.cpp MazeApp.h StackImp.cpp Stack.h
	g++ -c MazeApp.cpp

MoveImp.o : MoveImp.cpp Move.h
	g++ -c MoveImp.cpp

clean :
	rm -f *.o MazeApp

clean_temp :
	rm -f *~

clean_all : clean clean_temp

list :
	ls