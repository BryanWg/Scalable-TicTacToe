#ifndef BOARD_HEADER
#define BOARD_HEADER
    #include <stdio.h>
    #include <stdlib.h>
    #include "Settings.h"
    #include "Boolean.h"

    /*********************************************************************************
        Position(struct): is used to represent spot/location on the board
            player(char)- used to identify player X or O
            occupied(int)- used as a boolean ti check if the position is empty or not
    *********************************************************************************/
    typedef struct
    {
        int occupied;
        char player;
    }Position;
    /*********************************************************************************
        Board(typedef): is a 2d array of position
    *********************************************************************************/
    typedef Position** Board; 

    Board createBoard(Settings *set);

    void freeBoard(Board board, int);

    void printBoard(Board board, Settings *set);

    int inputPosition(char player, int x, int y, Board board);

    int winner(int x, int y, char player, Board board, Settings* set);
#endif
