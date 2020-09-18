/************************************************************************************************  
FILE: FileManager.c
AUTHOR: Bryan Wong  
LAST MODIFIED: 20/10/19
PURPOSE: Handle File input and output
Parts of this file comprise externally-obtained code
*************************************************************************************************/
#include "FileManager.h"
/************************************************************************************************  
    FUNCTION: dimensionValidation (static) 
    IMPORTS: count(int), upper(int), lower(int), setValue(int), dimesion(char)
    EXPORT: valid(int) 
    PURPOSE: returns 1 if the the dimension being checked is valid (M, N, K)
             returns 0 and prints out an error message if the dimension has duplicates, 
             doesn't exist or not in range (3 to 15);
*************************************************************************************************/
static int dimensionValidation(int count, int upper, int lower, int setValue, char dimension)
{
    int valid = 1;
    if (count != 1)
    {
        printf("Invalid %c count: %d\n", dimension, count);
        valid = 0;
    }
    else if(setValue < lower || setValue > upper)
    {
        printf("Invalid value for %c value (INTEGER between %d adn %d)\n", dimension, lower, upper);
        valid = 0;
    }
    return valid;
}


/************************************************************************************************  
    FUNCTION: settingsValidation 
    IMPORTS: mCount (int), nCount (int), kCount (int), settings (Settings*)
    EXPORT: valid (int)
    PURPOSE: Validates M,N and K
             returns TRUE(!0) if valid
             returns FALSE(0) if not valid
*************************************************************************************************/
static int settingsValidation(int mCount, int nCount, int kCount, Settings *settings)
{
    int valid = 0;
    int bigger = settings->n;
    
    valid += dimensionValidation(mCount, 15, 3, settings->m, 'M');
    valid += dimensionValidation(nCount, 15, 3, settings->n, 'N');

    /* Finds bigger value for K to compare to so that K is never bigger than the board dimensions */
    if(settings->m > settings->n)
    {
        bigger = settings->m;
    }

    /* if the bigger dimension is smaller than 3 means that M & N is not valid / not in range */
    if(bigger < 3)
    {
        printf("Ensure that M & N value is valid to validate K\n");
    }
    else
    {
        valid += dimensionValidation(kCount, bigger, 3, settings->k, 'K');
    }
    
    /* 
        Each valid dimension (M,N,K) adds 1 to valid(int), if valid is less than 3 the settings is invalid
    */
    if (valid == 3)
    {
        valid = TRUE;
    }
    else
    {
        valid = FALSE;
    }
    return valid;
}


/**************************************************************************************
    FUNCTION: isEmpty
    IMPORTS: f (FILE*)
    EXPORT: int (for boolean condition)
    PURPOSE: check if a file is empty by moving the file pointer to the end of the file 
             and get the size of the file in bytes (0 bytes if empty)
****************************************************************************************/
static int isEmpty(FILE* f)
{
    int isEmpty = FALSE;
    /* moving file pointer to the end of the file */
    fseek(f, 0, SEEK_END);
    /* checking for the size of the file in bytes */
    if (ftell(f) == 0)
    {
        isEmpty = TRUE;
        printf("File is Empty\n");
    }
    /* moving the pointer back to the beginning of the file */
    fseek(f, 0, SEEK_SET);
    return isEmpty;
}


/**********************************************************************************************  
    FUNCTION: settingReader
    IMPORTS: fileName (char*), f (FILE*), settings (Settings*)
    EXPORT: int (for boolean condition)
    PURPOSE: read a set of settings from a settings file, checks for the validity the format
             and value and exports an integer (0 for FALSE and !FALSE for TRUE)
**********************************************************************************************/
int settingReader(char *fileName, FILE *f, Settings *settings)
{
    int valid = TRUE;

    if (f == NULL)
    {
        printf("File input stream is NULL, exiting program \n");
    }
    else
    {
        /* checks for files that exist but has nothing in them, if so print an error message */
        if(!isEmpty(f))
        {
            int mCount, nCount, kCount, lineCount, value, equalsCount, ii;
            char *setType, *line, *stringValue;
            mCount = 0; nCount = 0, kCount = 0; lineCount = 0;
            line = (char*)malloc(sizeof(char) * 10);

            while(!feof(f) && fgets(line, 10, f) != NULL)
            {
                lineCount++;
                equalsCount = 0;
                /* skips line if it is empty  */
                if(line[0] != '\n')
                {
                    /* count the number of '='  */
                    for(ii = 0; ii < strlen(line); ii++)
                        {
                            if(line[ii] == '=')
                            {
                                equalsCount++;
                            }
                        }
                    /* if no '=' or it has more than one than throw an error */
                    if (equalsCount != 1)
                    {
                        printf("Invalid file format on line %d\n\tContent: %s\n", lineCount, line);
                        setType = line;
                        value = 0;
                        valid = FALSE;
                    }
                    else
                    {
                        /* get the String before and after the "=" */
                        setType = strtok(line, "=");
                        stringValue = strtok(NULL, "=");

                        /* getting rid of the '\n' as validateStringToInt doesn't take '\n' into consideration */
                        if(strstr(stringValue, "\n"))
                        {
                            stringValue = strtok(stringValue, "\n");
                        }

                        /* ensure that the string after the "=" is an integer */
                        if(!validateStringToInt(stringValue))
                        {
                            /* set value to a negative number so that it will print an error message during futher validation */
                            value = -10;
                        }
                        else
                        {
                            /* convert the string after the "=" to an integer if valid */
                            value = atoi(stringValue);
                        }

                        /* increase M,N or K count corresponding to string before the "=" and set the value for it */
                        if(strcasecmp(setType, "m") == 0)
                        {
                            
                            settings->m = value;
                            mCount++;
                        }
                        else if(strcasecmp(setType, "n") == 0)
                        {

                            settings->n = value;
                            nCount++;
                        }
                        else if(strcasecmp(setType, "k") == 0)
                        {
                            settings->k = value;
                            kCount++;
                        }
                    }
                }
            }
            /* if all the line format is valid check for duplicate and ensure that it is wihtin range and print error message if valid */
            if(valid == TRUE)
            {
                valid = settingsValidation(mCount, nCount, kCount, settings);
            }
            
            if(ferror(f))
            {
                printf("File error, closing stream \n");
                fclose(f);
            }
            
            free(line);
            line = NULL;
            fclose(f);
        }
    }
    return valid;
}


/**************************************************************************************
    FUNCTION: logSaver
    IMPORTS: list(LinkestList*), set(Settings*)
    EXPORT: none
    PURPOSE: create the file name based off the assignment specs and writing all 
             the logs into it 
****************************************************************************************/
void logSaver(LinkedList *list, Settings *set)
{
    char *fileName;
    time_t now;
    struct tm *local;
    FILE* f;
    /* get local time and date */
    /* Obtained from  tutorialspoint
       https://www.tutorialspoint.com/c_standard_library/c_function_localtime.htm
       (Accessed on 15 October 2019) */
    time(&now);
    local = localtime(&now);
    fileName = (char*)malloc(50 * sizeof(char));

    sprintf(fileName, "MNK_%d-%d-%d_%d-%d_%d-%d.log", 
                      set->m, set->n, set->k,
                      local->tm_hour, local->tm_min, local->tm_mday, local->tm_mon+1);

    f = fopen(fileName,"w");
    if(f == NULL)
    {
        printf("File output stream is NULL");
    }
    else
    {
        fprintLinkedList(f, list, &fprintLog);
    }
    
    fclose(f);
    free(fileName);
    fileName = NULL;
}
