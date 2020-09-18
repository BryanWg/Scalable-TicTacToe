/************************************************************************************************  
FILE: GameTurn.c
AUTHOR: Bryan Wong  
LAST MODIFIED: 20/10/19
PURPOSE: To print and free each GameTurn struct that is stored in the linked list in Log struct
*************************************************************************************************/
#include "GameTurn.h"
/**************************************************************************************
    FUNCTION: printGameTurn
    IMPORTS: data(void*)
    EXPORT: none
    PURPOSE: to print GameTurn in a proper manner
****************************************************************************************/
void printGameTurn(void* data)
{
    GameTurn* gt = (GameTurn*) data;
    printf("\tTurn: %d\n\tPlayer: %c\n\tLocation: %d,%d\n\n", gt->turn, gt->player, gt->x, gt->y);
}

/**************************************************************************************
    FUNCTION: freeGameTurn
    IMPORTS: data(void*)
    EXPORT: none
    PURPOSE: free GameTurn 
****************************************************************************************/
void freeGameTurn(void* data)
{
    free(data);
}

/**************************************************************************************
    FUNCTION: fprintGameTurn
    IMPORTS: data(void*), f(FILE*)
    EXPORT: none
    PURPOSE: print GameTurn to a file based off the f(FILE*)
****************************************************************************************/
void fprintGameTurn(void* data, FILE* f)
{
    GameTurn* gt = (GameTurn*) data;
    fprintf(f, "\tTurn: %d\n\tPlayer: %c\n\tLocation: %d,%d\n\n", gt->turn, gt->player, gt->x, gt->y);
}
