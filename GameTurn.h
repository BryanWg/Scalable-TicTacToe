#ifndef GAMETURN_H
#define GAMETURN_H
    #include <stdlib.h>
    #include <stdio.h>
    
    /*********************************************************************************
        GameTurn(struct): used to store each turn made by the players(X & O)
            turn(int)- turn number while the game is still going 
            player(char)- player whose turn it is 
            x(int)- x coordinate
            y(int)- y coordinate 
    *********************************************************************************/
    typedef struct 
    {
        int turn;
        char player;
        int x;
        int y;
    }GameTurn;
    
    void freeGameTurn(void*);

    void printGameTurn(void*);

    void fprintGameTurn(void*, FILE*);
#endif