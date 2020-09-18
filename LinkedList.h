#ifndef LINKEDLIST_HEADER_FILE
#define LINKEDLIST_HEADER_FILE
    #include <stdlib.h>
    #include <stdio.h>

    /*********************************************************************************
       Node(struct): self reference struct that is used to store data and point 
                     to the next/prev node in a LinkedList
            previous(Node*)- used to point to the previous Node
            next(Node*)- used to point to the next Node
    *********************************************************************************/
    typedef struct Node
    {
        struct Node* previous;
        struct Node* next;
        void* data;
    }Node;

    /*********************************************************************************
       LinkedList(struct): struct which has pointer pointing to the start and end 
                           of linked Nodes 
            head(Node*)- used to point to the start Node
            tail(Node*)- used to point to the end Node
    *********************************************************************************/
    typedef struct
    {
        Node* head;
        Node* tail;
        int count;
    }LinkedList;

    /* typedef that points to a function that imports a void* and returns void */
    typedef void (*GeneticF) (void*);

    /* typedef that points to a function that imports a void* & FILE* and returns void */
    typedef void (*GeneticFileF) (void*, FILE*);

    LinkedList* createLinkedList();

    void insertStart(LinkedList*, void*);

    void* removeStart(LinkedList*);

    void insertLast(LinkedList*, void*);

    void* removeLast(LinkedList*);

    void printLinkedList(LinkedList* list, GeneticF printPtr);

    void freeLinkedList(LinkedList**, GeneticF freeFunc);

    void fprintLinkedList(FILE*, LinkedList*, GeneticFileF);
#endif 