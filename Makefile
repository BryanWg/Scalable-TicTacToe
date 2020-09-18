CFLAGS = -Wall -Werror -g -ansi -pedantic
OBJ = UserInterface.o FileManager.o Board.o LinkedList.o Log.o GameTurn.o 
EXEC = tictactoe
ifdef SECRET
CFLAGS += -D SECRET
endif
ifdef EDITOR
CFLAGS += -D EDITOR
endif

$(EXEC) : $(OBJ)
	gcc $(OBJ) -o $(EXEC)

UserInterface.o : UserInterface.c UserInterface.h FileManager.h Board.h LinkedList.h Log.h GameTurn.h
	gcc $(CFLAGS) -c UserInterface.c 

FileManager.o : Boolean.h Settings.h FileManager.h FileManager.c LinkedList.h
	gcc $(CFLAGS) -c FileManager.c 

Board.o :  Board.c Board.h Boolean.h Settings.h
	gcc $(CFLAGS) -c Board.c

LinkedList.o : LinkedList.c LinkedList.h
	gcc $(CFLAGS) -c LinkedList.c

Log.o : Log.c Log.h
	gcc $(CFLAGS) -c Log.c

GameTurn.o : GameTurn.c GameTurn.h
	gcc $(CFLAGS) -c GameTurn.c


clean : 
	rm -rf $(OBJ) $(EXEC)
