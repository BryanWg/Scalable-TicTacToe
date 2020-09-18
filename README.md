# Scalable Tic Tac Toe

Date created: 01/10/2019

Date last modified: 20/10/2019

### Compile:
         make 
         
### To run: 
         ./tictactoe a         // where a is the setting files, size of the board can be changed there
         
### Purpose: 
         make a resizable tictactoe game where is users are able to specify 
         the size of the board and how many consecutive X/O is needed to win,
         it is able to record the logs each game and print it to the terminal or a file.

### Files in project:
        Board.c         -Board.h
        Boolean.h       
        FileManager.c   -FileManger.h
        GameTurn.c      -GameTurn.h
        LinkedList.c    -LinkedList.h
        Log.c           -Log.h
        Makefile

### Functionality:
        -> Reads a settings file and validates it making sure it is 
           in format <dimension=value>, and the value is between 3 and 15
        -> Play a game of tic tac toe and save each new game and the turns 
           tooked by the players 
        -> View the current settings
        -> View the Logs(settings, games and turns took by the players in each game)
        -> Save the Logs into a file with a name format MNK_<M>-<N>-<K>_<HOUR>-<MIN>_<DAY>-<MONTH>.log
            - there is a conditional compilation where it will give an error message when trying to save the logs
        -> conditional compilation where the user is able to edit the current settings  

### To do:
        N/A

### Known bugs:
        - When prompted by the menu and "3a 2" is entered  it register "3a" and "2" as seperate inputs 
          hence "3a" will be invalid and an error message will appear and it will exucute "2" option 