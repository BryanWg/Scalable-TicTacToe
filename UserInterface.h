#ifndef UI_H
#define UI_H
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include "FileManager.h"
    #include "Settings.h"
    #include "LinkedList.h"
    #include "Board.h"
    #include "GameTurn.h"
    #include "Log.h"
    
    void newGame(Settings *set, LinkedList* list);

    void viewSettings(Settings *set);

    void viewLogs(LinkedList* list);

    int validateStringToInt(char* string);

    void editSettings(Settings* set);

    void changeSettings(Settings *set);

    int intput(char* string, int lower, int upper);
#endif 
