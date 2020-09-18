#include "UserInterface.h"

int main(int argc, char* argv[])
{
    int option, lower, upper, endCondition;
    char prompt[512] = "Please select the following options:\n\t1: Start a new game\n\t2: View the settings of the game\n\t3: View the current logs\n\t4: Save the logs to a file\n\t5: Exit the application\n";
    Settings* set = (Settings*) malloc(sizeof(Settings)); 
    LinkedList *list = createLinkedList();
    lower = 1;
    upper = 5;
    endCondition = 4;
    /* if EDITOR is defined, change my prompt and set the end condition of the do while loop to 5 */
    #ifdef EDITOR
        strncpy(prompt,"Please select the following options:\n\t1: Start a new game\n\t2: View the settings of the game\n\t3: View the current logs\n\t4: Save the logs to a file\n\t5: Edit existing board \n\t6: Exit the application\n", 512);
        endCondition = 5;
        upper++;
    #endif

    if(argc != 2)
    {
        printf("USAGE: ./tictactoe <settings file>\n\tM > 2\n\tN > 2\n\tK <= N OR M\n");
    }
    else
    {
        /* goes in the statement if the read is successful */
        if(settingReader(argv[1],fopen(argv[1], "r"), set))
        {
            do 
            {
                
                option = intput(prompt, lower, upper);

                switch (option)
                {
                    /* Play a new game */
                    case 1:
                        
                        newGame(set, list);
                        break;

                    /* View Settings */
                    case 2:
                        viewSettings(set);
                        break;

                    /* View Logs */
                    case 3:
                        viewLogs(list);
                        break;

                    /* Write the Logs to a file */
                    case 4:
                    /* if SECRET Is defined user can't write to a file */
                        #ifdef SECRET
                            printf("can't write to a file as SECRET is definedd\n\n");
                        #else 
                            logSaver(list, set);
                            printf("Saved!!\n");
                        #endif
                        break;

                    /* Edit Settings */
                    case 5:
                        /* if EDITOR is define only then we can edit our settings */
                        #ifdef EDITOR
                            editSettings(set);
                            
                        #endif
                        break;
                    default:
                        break;
                }
            }while(option >= 1 && option <= endCondition); /* endCondition changes if EDITOR is defined or not */
            
            printf("Thank you for using me program!! :DD\n");
        }
        else
        {
            /* printing the error message in red */
            printf("\033[1;31mFile IO Error: quitting \\TwT/\n\033[0m");
        }
        
    }

    free(set);
    freeLinkedList(&list, &freeLog);
    return 0;
}

/**************************************************************************************
    FUNCTION: editSettings
    IMPORTS: set(Settings*)
    EXPORT: none
    PURPOSE: edit set(Settings*) so that the board for the consequent games 
             will be of that settings 
****************************************************************************************/
void editSettings(Settings* set)
{
    int biggerDimension;
    set->m = intput("Enter new M value:\n\t", 3, 14);
    set->n = intput("Enter new N value:\n\t", 3, 14);
    
    /* getting the bigger dimension (length/width) to ensure that K doesn't pass that */
    if(set->m > set->n)
    {
        biggerDimension = set->m;
    }
    else
    {
            biggerDimension = set->n;
    }
    set->k = intput("Enter new K value:\n\t", 3, biggerDimension);
}
    
/**************************************************************************************
    FUNCTION: input
    IMPORTS: string(char*), lower(int), upper(int)
    EXPORT: num(int)
    PURPOSE: read the user input as a string and convert it into an int if valid 
****************************************************************************************/
int intput(char* string, int lower, int upper)
{
    char* prompt, inputString[20];
    int num;
    num = 0;
    prompt = (char*)malloc(512 * sizeof(char));
    strncpy(prompt, string, 512);
     
    do
    {
        /* reading the user input as a String */
        printf("%s", prompt);
        scanf("%s", inputString);

       
        if(!validateStringToInt(inputString))
        {
            sprintf(prompt ,"Please enter an integer\n");
            num =-1000;
        }
        else
        { 
            /* change the prompt message if it loops again it means that it is out of range */
            sprintf(prompt, "Please enter an integer in the range of %d and %d\n", lower, upper);
            num = atoi(inputString);
        }
       
    } while (num < lower || num > upper);
    
    free(prompt);
    prompt = NULL;

    return num;
}

/**************************************************************************************
    FUNCTION: validateStringToInt
    IMPORTS: string(char*)
    EXPORT: valid(int)
    PURPOSE: validate whether the string import can be converted into an integer 
****************************************************************************************/
int validateStringToInt(char* string)
{
    int ii, valid, numCount;
    valid = TRUE;
    numCount = 0;

    /* in the acsii table 48 is the char '0' and 57 is the char '9'
       compare each char in the string to those value(48 & 57) and 
       add up the ones that are numbers but in char format */
    for (ii = 0; ii < strlen(string); ii++)
    {
        if (string[ii] >= 48 && string[ii] <= 57)
        {
            numCount++;
        }
    }
  
    /* if the num of char formatted integers doesn't match 
       the length of the string then the string can't be converted into an int  */
    if(numCount != (int)strlen(string))
    {
        valid = FALSE;
    }
    return valid;
}

/**************************************************************************************
    FUNCTION: userInput
    IMPORTS: string(char*),x(int*), xLower(int), xupper(int), y(int*), yLower(int), yUpper(int)
    EXPORT: x(int*), y(int*) through parameter
    PURPOSE: read the user input in the form <x,y> and ensure it is valid
****************************************************************************************/
void userInput(char* string, int* x, int xLower,int xUpper,int* y, int yLower,int yUpper)
{
    char* prompt,  inputString[20], *xString, *yString;
    int errors, commaCount, ii;
    errors = TRUE;
    prompt = (char*)malloc(512 * sizeof(char));
    strncpy(prompt, string, 512);
     
    do
    {   
        /* read the user input as a String, at this point it can be in any form */
        printf("%s", prompt);
        scanf("%s", inputString);
        /* no comma means that it is already invalid */
        if(!strstr(inputString, ","))
        {
            printf("*Input must be in the form <x,y>!!*\n");
        }
        else
        {
            /* counts the number of comma that the user inputed have as there can only have 1 comma*/
            ii = 0;
            commaCount = 0;
            while(inputString[ii] != '\0')
            {
                if(inputString[ii] == ',')
                {
                    commaCount++;
                }
                ii++;
            }

            if(commaCount != 1)
            {
                printf("\nInput must be in the form <x,y> with only ONE comma!!!*\n");
            }
            else
            {
                /* spill up x and y with the comma */
                xString = strtok(inputString, ",");
                yString = strtok(NULL, ",");

                /* if before or after the comma strtok will return NULL */
                if(xString == NULL || yString == NULL)
                {
                    printf("*Input must be in the form <x,y>!!*");
                }
                else
                {
                    /* checking if x is in an integer using it's String form */
                    if(!validateStringToInt(xString))
                    {
                        printf("*Please enter an integer for x*\n");
                        *x =-1000;
                    }
                    else 
                    { 
                        *x = atoi(xString);
                        /* checking if it is in range */
                        if(*x < xLower || *x > xUpper)
                        {
                            printf("*Range of x is %d and %d*\n", xLower, xUpper);
                        }
                        else
                        {
                            errors = FALSE;
                        }
                        
                    }

                     /* checking if y is in an integer using it's String form */
                    if(!validateStringToInt(yString))
                    {
                        printf("*Please enter an integer for y*\n");
                        *y =-1000;
                    }
                    else 
                    { 
                        *y = atoi(yString);
                        /* checking if y is in range */
                        if(*y < yLower || *y > yUpper)
                        {
                            printf("*Range of y is %d and %d*\n", yLower, yUpper);
                            errors = TRUE;
                        }
                        else
                        {
                            /* if x is incorrect and y is correct still want it to loop loop*/
                            if(errors == FALSE)
                            {
                                errors = FALSE;
                            }
                        }
                    }
                }
            }
        }
        printf("\n\n");
    } while(errors); /* only stop looping if errors is false */
    
    free(prompt);
    prompt = NULL;
}

/**************************************************************************************
    FUNCTION: switchPlayer
    IMPORTS: player(char*), prompt(char*)
    EXPORT: player(char*), prompt(char*) throught the parameter
    PURPOSE: which the prompt for player X or O
****************************************************************************************/
static void switchPlayer(char* player, char* prompt)
{
    /* if the prompt includes the String "X" then switch to change the prompt for player O */
    if(strstr(prompt, "X"))
    {
        strncpy(prompt, "PLAYER O:\n", 50);
    }
    else
    {
        strncpy(prompt, "PLAYER X:\n", (sizeof(prompt)));
    }

    /* if the player is 'X' then change it to 'O' */
    if(*player == 'X')
    {
        *player = 'O';
    }
    else
    {
        *player = 'X';
    }
}

/**************************************************************************************
    FUNCTION: newGame
    IMPORTS: set(Settings*), list(LinkedList*)
    EXPORT: none
    PURPOSE: play a game tictactoe based on set(Settings*) and Log each 
             step into a list(LinkedList*)
****************************************************************************************/
void newGame(Settings *set, LinkedList* list)
{
    Board board;
    Log* log;
    GameTurn* gameTurn;
    char *prompt, *player; 
    int *x, *y, turnCount, occupied, foundWinner;
    static int gameNum = 1;
    log = createLog(set, gameNum);
    board = createBoard(set);
    prompt = (char*) malloc(50 * sizeof(char));
    player = (char*) malloc(sizeof(char));
    strncpy(prompt, "PLAYER X: \n", 50);
    x = (int*) malloc(sizeof(int));
    y = (int*) malloc(sizeof(int));
    *player = 'X';
    turnCount = 0;
    occupied = FALSE;
    foundWinner = FALSE;

    do
    {
        if(occupied)
        {
            printf("(spot has been taken please try again)\n");
        }
        else
        {
            printBoard(board, set);
            printf("%s", prompt);
        }

        /* read user input, x and y coordinate will be passed by reference */
        userInput("Please enter a <x,y> coordinate\n", x, 0, set->m-1, y, 0, set->n-1);

        /* inputPosition() returns TRUE, it means that the position is successfully inputed */
        if(inputPosition(*player, *x, *y, board))
        {
            /* check for winner */
            foundWinner = winner(*x,*y, *player,board,set);
            turnCount++;
            occupied = FALSE;

            /* Store the information of each turn into gameTurn(GameTurn*) and 
               put it in the log(Logs*)'s linked list */
            gameTurn = (GameTurn*)malloc(sizeof(GameTurn));
            gameTurn->player = *player;
            gameTurn->turn = turnCount;
            gameTurn->x = *x;
            gameTurn->y = *y;
            insertLast(log->gameTurnList, gameTurn);
            switchPlayer(player, prompt);
        }
        /* otherwise the position the user entered is occupied */
        else
        {
            occupied = TRUE;
        }
     /* if turnCount is equals to M * N it means and no one won it means it has come to a draw */
    }while(!foundWinner && turnCount < set->m * set->n);

    printBoard(board, set);

    if(foundWinner)
    {
        /* after each user input the player and prompt is switch thus if was the last person to make
           the winning move it 'X' the player(char*) is now = 'O' and has to be switched back to 'X*/
        switchPlayer(player, prompt);
        printf("\033[32;1m \n\nPLAYERR %c WON!!! *cheer noises*\n\033[0m\n", *player);
    }
    else
    {
        printf("\n\nIt is a draw!!!!\n");
    }

    /* insert the Logs for this game into a linked list */
    insertLast(list, log);
    gameNum++;
    freeBoard(board, set->m);
    free(prompt);
    free(player);
    free(x);
    free(y);
    
    player = NULL;
    prompt = NULL;
    x = NULL;
    y = NULL;
}

/**************************************************************************************
    FUNCTION: viewSettings
    IMPORTS: set(Settings*)
    EXPORT: none
    PURPOSE: display the settings 
****************************************************************************************/
void viewSettings(Settings *set)
{
    printf("\tM = %d\n\tN = %d\n\tK = %d\n\n", set->m, set->n, set->k);
}

/**************************************************************************************
    FUNCTION: viewLogs
    IMPORTS: list(LinkedList*)
    EXPORT: none
    PURPOSE: print the Lgos in the stored in the linked list
****************************************************************************************/
void viewLogs(LinkedList* list)
{
    printLinkedList(list, &printLog);
}



