/************************************************************************************************  
FILE: Board.c
AUTHOR: Bryan Wong
LAST MODIFIED: 20/10/19
PURPOSE: malloc and initialise a Board and handle tic tac toe board manipulation 
*************************************************************************************************/
#include "Board.h"
/************************************************************************************************  
    FUNCTION: createBoard 
    IMPORTS: set (Settings*)
    EXPORT: board (Board)
    PURPOSE: malloc and initialise the 2d array of Position with ' ' (spaces) for player
             and FALSE (0) for occupied
*************************************************************************************************/
Board createBoard(Settings *set)
{
    Board board;
    int ii, jj;
    int x = set->m;
    int y = set->n;

    /* mallocing */
    board = (Board) malloc(x * sizeof(Position*));
    for (ii = 0; ii < x; ii++)
    {
        board[ii] = (Position*)malloc(y * sizeof(Position));
    }

    /* initialising */
    for (ii = 0; ii < x; ii++)
    {
        for( jj = 0 ; jj < y; jj++)
        {
           board[ii][jj].occupied = FALSE;
           board[ii][jj].player = ' ';
        }
    }
    return board;
}

/************************************************************************************************  
    FUNCTION: freeBoard
    IMPORTS: board (Board), x (int)
    EXPORT: none 
    PURPOSE: freeing the malloced Board(2d array of Position) 
*************************************************************************************************/
void freeBoard(Board board, int x)
{
    int ii;
    if (board == NULL)
    {
        printf("board does not exist or is not pointing at a malloced board");
    }
    else
    {
        for (ii = 0; ii < x; ii++)
        {
            free(board[ii]);
            board[ii] = NULL;
        }
        free(board);
        board = NULL;
    }
}

/*************************************************************************************************
    FUNCTION: recursiveLeftDiagonal (static)
    IMPORTS: ii(int), jj(int), player(char), xLength(int), yLength(int), 
             rowsTowin(int), curStreak(int), board(Board)
    EXPORT: streaks(int) 
    PURPOSE: recursive method that returns the number of times X or O has occured diagonally
             from the top right to bottom left
*************************************************************************************************/
static int recursiveLeftDiagonal(int ii, int jj, char player, int xLength, int yLength, int rowsToWin, int curStreak, Board board)
{
    int streaks;
    streaks = 0;
    
    /*
        base case: when it reach the end of the row or col OR when the current/next spot 
                   is not a the player(char) variable OR when the curStreak(int) equal
                   numbers in a row required to win.
    */
    if(ii > 0 && jj < yLength-1 && board[ii][jj].player == player && board[ii -1][jj+1].player == player && curStreak < rowsToWin)
    {
        curStreak++;
        streaks += recursiveLeftDiagonal( ii - 1, jj + 1, player, xLength, yLength, rowsToWin, curStreak, board) + 1;   
    }

    return streaks; 
}

/*************************************************************************************************
    FUNCTION: recursiveRightDiagonal (static)
    IMPORTS: ii(int), jj(int), player(char), xLength(int), yLength(int), 
             rowsTowin(int), curStreak(int), board(Board)
    EXPORT: streaks(int) 
    PURPOSE: recursive method that returns the number of times X or O has occured diagonally
             from the top left to bottom right
*************************************************************************************************/
static int recursiveRightDiagonal(int ii, int jj, char player, int xLength, int yLength, int rowsToWin, int curStreak, Board board)
{
    int streaks;
    streaks = 0;
    
    /*
        base case: when it reach the end of the row or col OR when the current/next spot 
                   is not a the player(char) variable OR when the curStreak(int) equal
                   numbers in a row required to win.
    */
    if(ii < xLength-1 && jj < yLength-1 && board[ii][jj].player == player && board[ii +1][jj+1].player == player && curStreak < rowsToWin)
    {
        curStreak++;
        streaks += recursiveRightDiagonal( ii + 1, jj + 1, player, xLength, yLength, rowsToWin, curStreak, board) + 1; 
    }

    return streaks; 
}

/*************************************************************************************************
    FUNCTION: recursiveRow (static)
    IMPORTS: ii(int), jj(int), y(int), player(char), xLength(int)
             rowsTowin(int), curStreak(int), board(Board)
    EXPORT: streaks(int) 
    PURPOSE: recursive method that returns the number of times X or O has occured in a row
             from the start of the row (board[0][column])
*************************************************************************************************/
static int recursiveRow(int ii, int jj, int y, char player, int xLength, int rowsToWin, int curStreak, Board board)
{
    int streaks;
    streaks = 0;
    
    /*
        base case: when it reach the end of the row OR when the current/next spot 
                   is not a the player(char) variable OR when the cuStreak equal
                   to the rows required to win.
    */
    if(jj < xLength && board[ii][y].player == player && board[jj][y].player == player && curStreak < rowsToWin)
    {
        curStreak++;
        streaks += recursiveRow( ii, jj + 1, y, player, xLength, rowsToWin, curStreak, board) + 1;
    }
    
    return streaks;
}

/*************************************************************************************************
    FUNCTION: recursiveCol (static)
    IMPORTS: ii(int), jj(int), x(int), player(char), yLength(int)
             colsTowin(int), curStreak(int), board(Board)
    EXPORT: streaks(int) 
    PURPOSE: recursive method that returns the number of times X or O has occured in a column 
             from the start of the column (board[row][0])
*************************************************************************************************/
static int recursiveCol(int ii, int jj, int x, char player, int yLength, int colsToWin, int curStreak, Board board)
{
    int streaks;
    streaks = 0;
    
    /*
        base case: when it reach the end of the column OR when the current/next spot 
                   is not a the player(char) variable OR when the curStreak equal
                   to the col required to win.
    */
    if(jj < yLength && board[x][ii].player == player && board[x][jj].player == player && curStreak < colsToWin)
    {
        curStreak++;
        streaks += recursiveCol( ii, jj + 1, x, player, yLength, colsToWin, curStreak, board) + 1;
    }

    return streaks;
}

/************************************************************************************************  
    FUNCTION: winner
    IMPORTS: x(int), y(int), player(char), board(Board), set(Settings*)
    EXPORT: foundWinner(int) 
    PURPOSE: returns TRUE(!0) if the player gets set->k amount consecutively in a row, col or diagonaly
             returns FALSE(0) if the player gets doesn't 
*************************************************************************************************/
int winner(int x, int y, char player, Board board, Settings* set)
{
    int foundWinner, ii, rowStreak, colStreak, jj, rightDiagonalStreak, leftDiagonalStreak; 
    foundWinner = FALSE;
    ii = 0;


    /* 
        ROW:
        Stop/won't looping if winner is found OR 
        when ii reached a point where it is impossible to get k in a row (remaining unchecked ii is smaller than k) OR
        when the required num of in a row to win is bigger than with the width of the board
    */
    while((ii < set->m-1) && !foundWinner && (set->k <= set->m) && (set->m - ii >= set->k))
    {
        rowStreak = 1;
        rowStreak += recursiveRow(ii, ii+1,y, player, set->m, set->k,1, board) ;
        ii++;

        if(rowStreak >= set->k)
        {
            foundWinner = TRUE;
        }
    }
    ii = 0;
    /* 
        COLUMN:
        Stop/won't looping if winner is found OR 
        when ii reached a point where it is impossible to get k consecutively (remaining unchecked ii is smaller than k) OR
        when the required num consecutively(k) to win is bigger than with the width of the board
     */
    while((ii < set->n-1) && !foundWinner && (set->k <= set->n) && (set->n - ii >= set->k))
    {
        colStreak = 1;
        colStreak += recursiveCol(ii, ii+1,x, player, set->n, set->k,1, board) ;
        ii++;

        if(colStreak >= set->k)
        {
            foundWinner = TRUE;
        }
    }

    /* Find the top left start position */
    ii = x;
    jj = y;
    while(ii >0 && jj >0)
    {
        ii--;
        jj--;
    }
    
    /* 
        RIGHT DIAGONAL: 
        Stop/won't looping if winner is found OR 
        when ii or jj reached a point where it is impossible to get k consecutively (remaining unchecked ii or jj is smaller than k) OR
        when the required num consecutively to win(k) is bigger than with the width or length of the board
    */
    while((ii < set->m-1) && (jj < set->n-1) && !foundWinner && (set->k <= set->m) && (set->m - ii >= set->k))
    {
        rightDiagonalStreak = 1;
        rightDiagonalStreak += recursiveRightDiagonal(ii, jj, player, set->m, set->n,set->k,1, board) ;
        ii++;
        jj++;

        if(rightDiagonalStreak >= set->k)
        {
            foundWinner = TRUE;
        }
    }

    /* Find the top right start position */
    ii = x;
    jj = y;
    while(ii < set->m -1 && jj > 0)
    {
        ii++;
        jj--;
    }
    
    /* 
        LEFT DIAGONAL:
        Stop/won't looping if winner is found OR 
        when ii or jj reached a point where it is impossible to get k consecutively (remaining unchecked ii or jj is smaller than k) OR
        when the required num consecutively to win(k) is bigger than with the width or length of the board
     */
    while((ii > 0) && (jj < set->n-1) && !foundWinner && (set->k <= set->m) && (ii >= set->k-1))
    {
        leftDiagonalStreak = 1;
        leftDiagonalStreak += recursiveLeftDiagonal(ii, jj, player, set->m, set->n,set->k,1, board) ;
        ii--;
        jj++;

        if(leftDiagonalStreak >= set->k)
        {
            foundWinner = TRUE;
        }
    }
    
    
    return foundWinner;
}

/*************************************************************************************************
    FUNCTION: inputPosition
    IMPORTS: player(char), x(int), y(int), board(Board)
    EXPORT: valid(int)   
    PURPOSE: return TRUE(!0) if the position on the board is not occupied and 
             places either X/O in the position passed from the parameter
             return FALSE(0) if the position on the board is occupied 
*************************************************************************************************/
int inputPosition(char player, int x, int y, Board board)
{
    int valid = TRUE;
    if (board[x][y].occupied == FALSE)
    {
        board[x][y].player = player;
        board[x][y].occupied = TRUE;
    }
    else
    {
        valid = FALSE;
    }
    
    return valid;
}

/************************************************************************************************  
    FUNCTION: printBoard
    IMPORTS: board(Board), set(Settings*)
    EXPORT: none 
    PURPOSE: freeing the malloced Board(2d array of Position) 
*************************************************************************************************/
void printBoard(Board board, Settings *set)
{
    int ii, jj, kk;
    int x = set->m;
    int y = set->n;
    printf("    ");

    /* numbers for the x coordinates */
    for (ii = 0; ii < x; ii++)
    {
        printf(" %d ", ii);
        if(ii < 10)
        {
            printf(" ");
        }
    }
    printf("\n  ");

    /* top border */
    for (ii = 0; ii < x * 4 + 3; ii++)
    {
        printf("=");
    }
    printf("\n");

    for(ii = 0; ii < y; ii++)
    {
        /* 
            print a space infront of numbers that have one digit and 
            don't print a space infront of numbers that have 2 digits(aesthetic)
         */
        if(ii < 10)
        {
            printf(" ");
        }
        /* numbers for the y coordinates */
        printf("%d||", ii);
    
        for(jj = 0; jj < x; jj++)
        {
            printf(" %c ", board[jj][ii].player);
            if (jj < x - 1)
            {
                printf("|");
            }
        }
        printf("||\n  ");
        /* don't print "-" on the last row of  */
        if (ii < y -1)
        {
            for (kk = 0; kk < x * 4 + 3; kk++)
            {
                printf("-");
            }
            printf("\n");
        }
    }

    /* bottom border */
    for (ii = 0; ii < x * 4 + 3; ii++)
    {
        printf("=");
    }
    printf("\n");
}
