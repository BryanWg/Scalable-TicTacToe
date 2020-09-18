/************************************************************************************************  
FILE: LinkedList.c
AUTHOR: Bryan Wong
LAST MODIFIED: 20/10/19
PURPOSE: To create, free and manipulate a linked list
*referenced from P07 LinkedList.c*
*************************************************************************************************/
#include "LinkedList.h"
/**************************************************************************************
    FUNCTION: createLinkedList
    IMPORTS: none
    EXPORT: list(LinkedList*)
    PURPOSE:  returns a pointer to a malloced and initialised LinkedList
****************************************************************************************/
LinkedList* createLinkedList()
{
    LinkedList* list;
    list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
    return list;
}

/**************************************************************************************
    FUNCTION: insertStart
    IMPORTS: list(LinkedList*), indata(void*)
    EXPORT: none
    PURPOSE: insert indata(void*) at the start of the list(LinkedList*)
****************************************************************************************/
void insertStart(LinkedList* list, void* indata)
{
    /* create pointer to a node with indata stored */
    Node* newNode;
    newNode = (Node*)malloc(sizeof(Node));
    newNode->data = indata;

    /* case where there's nothing in the list, assign the head and tail the address of newNode  */
    if(list->head == NULL && list->tail == NULL)
    {
        newNode->next = NULL;
        newNode->previous = NULL;
        list->head = newNode;
        list->tail = newNode;
        list->count = 0;
    }
    else
    {
        /* insert the new node to the start of the list and assign head the address of newNode */
        newNode->next = list->head;
        newNode->previous = NULL;
        list->head->previous = newNode;
        list->head = newNode;
        list->count++;
    }
}

/**************************************************************************************
    FUNCTION: removeStart
    IMPORTS: list(LinkedList*)
    EXPORT: data(void*)
    PURPOSE: remove the data stored at the start of the list and returning it 
****************************************************************************************/
void* removeStart(LinkedList* list)
{
    void* data = NULL;
    /* check there's any data stored in the list */
    if(list->head == NULL)
    {
        printf("Can't remove from an empty array\n");
    }
    else    
    {
        data = list->head->data;
        list->head = list->head->next;

        /* if list's head is null it means that there is only one node stored */
        if (list->head == NULL)
        {
            free(list->tail);
            list->tail = NULL;
        }
        else
        {
            /* free malloced Node */
            free(list->head->previous);
            list->head->previous = NULL;
        }   
        list->count--;     
    }
    return data;
}

/**************************************************************************************
    FUNCTION: insertLast
    IMPORTS: list(LinkedList*), indata(void*)
    EXPORT: none
    PURPOSE: insert indata(void*) at the end of the list(LinkedList*)
****************************************************************************************/
void insertLast(LinkedList* list, void* indata)
{
    /* create pointer to a node with indata stored */
    Node* newNode;
    newNode = (Node*)malloc(sizeof(Node));
    newNode->data = indata;
    
    /* case where there's nothing in the list, assign the head and tail the address of newNode  */
    if(list->head == NULL && list->tail == NULL)
    {
        newNode->next = NULL;
        newNode->previous = NULL;
        list->head = newNode;
        list->tail = newNode;
        list->count = 0;
    }
    else
    {
        /* insert the new node to the start of the list and assign tail the address of newNode */
        newNode->previous = list->tail;
        newNode->next = NULL;
        list->tail->next = newNode;
        list->tail = newNode;
        list->count++;
    }
}

/**************************************************************************************
    FUNCTION: removeLast
    IMPORTS: list(LinkedList*)
    EXPORT: data(void*)
    PURPOSE: remove the data stored at the start of the list and returning it 
****************************************************************************************/
void* removeLast(LinkedList* list)
{
    void* data = NULL;
    /* check there's any data stored in the list */
    if(list->head == NULL)
    {
        printf("Can't remove from an empty array\n");
    }
    else    
    {
        data = list->tail->data;
        list->tail = list->tail->previous;

        /* if list's tail is null it means that there is only one node stored */
        if (list->tail == NULL)
        {
            free(list->head);
            list->head = NULL;
        }
        else
        {
            /* free malloced Node */
            free(list->tail->next);
            list->tail->next = NULL;
        }   
        list->count--;     
    }
    return data;
}

/**************************************************************************************
    FUNCTION: printLinkedList
    IMPORTS: list(LinkedList*), printFunc(GeneticF)
    EXPORT: none
    PURPOSE: print the data contained by the list using a function pointer 
****************************************************************************************/
void printLinkedList(LinkedList* list, GeneticF printFunc)
{
    if (list == NULL || list->head == NULL)
    {
        printf("Linked list is empty\n");
    }
    else
    {
        Node* curNode;
        curNode = list->head;

        /* iterate through the entire list */
        while(curNode != NULL)
        {
            /* dereference printFunc to call the function */
            (*printFunc)(curNode->data);
            curNode = curNode->next;
            
        }
    }
    
}

/**************************************************************************************
    FUNCTION: freeLinkedList
    IMPORTS: listPtr(LinkedList**), freeFunc(GeneticF)
    EXPORT: none
    PURPOSE: free the malloced list using a function pointer 
****************************************************************************************/
void freeLinkedList(LinkedList** listPtr, GeneticF freeFunc)
{
    /* NULL and empty linked list check */
    if(listPtr == NULL || (*listPtr) == NULL)
    {
        printf("LinkedList is already freed\n");
    }
    else
    {
        Node *curNode, *nextNode;
        curNode = (*listPtr)->head;

        /* iterate through the entire list */
        while(curNode != NULL)
        {
            nextNode = curNode->next;
            /* derefenced freeFunc to call the function which will free the data* */
            (*freeFunc)(curNode->data);
            free(curNode);
            curNode = NULL;
            curNode = nextNode;
        }
        free(*listPtr);
        *listPtr = NULL;
    }    
    
}

/**************************************************************************************
    FUNCTION: fprintLinkedList
    IMPORTS: f(FILE*), list(LinkedList*), filePrintFunc(GeneticFileF)
    EXPORT: none
    PURPOSE: to print the data stored in the list to a file which f(FILE*) has the input
             stream opened using a function pointer 
****************************************************************************************/
void fprintLinkedList(FILE* f, LinkedList *list, GeneticFileF filePrintFunc)
{
    /* NULL and empty list check */
    if (list == NULL || list->head == NULL)
    {
        printf("Array is empty\n");
    }
    else
    {   
        Node* curNode;
        curNode = list->head;
        /* iterate through the entire list */
        while(curNode != NULL)
        {
            (*filePrintFunc)(curNode->data, f);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
            curNode = curNode->next; 
        }
        if(ferror(f))
        {
            perror("Error while reading a file");
        }
    }
}