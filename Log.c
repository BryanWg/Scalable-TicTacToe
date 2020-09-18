/************************************************************************************************  
FILE: Log.c
AUTHOR: Bryan Wong
LAST MODIFIED: 20/10/19
PURPOSE: Print and free Log that holds each step (GameTurn) that the player takes in a linked list
*************************************************************************************************/
#include "Log.h"
/**************************************************************************************
    FUNCTION: createLog
    IMPORTS: inSet(Settings*), inGameNum(int)
    EXPORT: log(Log*)
    PURPOSE: malloc and initialise a Log 
****************************************************************************************/
Log* createLog(Settings* inSet, int inGameNum)
{
    Log* log = (Log*)malloc(sizeof(Log));
    log->m = inSet->m;
    log->n = inSet->n;
    log->k = inSet->k;
    log->gameTurnList = createLinkedList();
    log->gameNum = inGameNum;
    return log;
}

/**************************************************************************************
    FUNCTION: printLog
    IMPORTS: data(void*)
    EXPORT: none
    PURPOSE: print Log in a proper manner
****************************************************************************************/
void printLog(void* data)
{
    Log* log  = (Log*) data;
    printf("Settings:\n\tM: %d\n\tK: %d\n\tK: %d\n\nGAME %d:\n", log->m, log->n, log->k, log->gameNum);
    printLinkedList(log->gameTurnList, &printGameTurn);
}

/**************************************************************************************
    FUNCTION: freeLog
    IMPORTS: data(void*)
    EXPORT: none
    PURPOSE: free Log 
****************************************************************************************/
void freeLog(void* data)
{
    Log* log = (Log*) data;
    freeLinkedList(&(log->gameTurnList), &freeGameTurn);
    free(log);
}

/**************************************************************************************
    FUNCTION: fprintLog
    IMPORTS: data(void*), f(FILE*)
    EXPORT: none
    PURPOSE: print Log to a file based off the f(FILE*)
****************************************************************************************/
void fprintLog(void* data, FILE* f)
{
    Log* log  = (Log*) data;
    fprintf(f, "Settings:\n\tM: %d\n\tK: %d\n\tK: %d\n\nGAME %d:\n", log->m, log->n, log->k, log->gameNum);
    fprintLinkedList(f, log->gameTurnList, &fprintGameTurn);
}