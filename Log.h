#ifndef LOG_H
#define LOG_H
    #include "Settings.h"
    #include "LinkedList.h" 
    #include "GameTurn.h"
    #include <stdlib.h>
    #include <stdio.h>

    /*********************************************************************************
       Log(struct): record each step the players took in a game 
            m, n & k(int)- stores settings info
            gameNum(int)- stores the order of the game 
            gameTurnList(LinkedList*)- linked list of GameTurns(steps made in each game)
    *********************************************************************************/
    typedef struct 
    {
        /* don't have Settings stuct because I plan to have 1 Settings* for the entire program,
           changing the settings will effect previous settings */
        int m;
        int n;
        int k;
        int gameNum;
        LinkedList* gameTurnList;
    }Log;

    void freeLog(void*);

    void printLog(void*);

    Log* createLog(Settings* set, int gameNum);

    void fprintLog(void*, FILE*);
#endif