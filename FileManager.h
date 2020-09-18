#ifndef FILE_MANAGER_HEADER
#define FILE_MANAGER_HEADER
    #include <stdio.h>
    #include <strings.h>
    #include <string.h>
    #include <stdlib.h>
    #include <time.h>
    #include "Settings.h"
    #include "Boolean.h"
    #include "LinkedList.h"
    #include "Log.h"
    #include "UserInterface.h"

    int settingReader(char* fileName, FILE* fIn, Settings *settings);

    int logreader(char* fileName, FILE* fIn, Settings *settings);

    void logSaver(LinkedList* list, Settings* set);
#endif

