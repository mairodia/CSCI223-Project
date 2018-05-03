// ============================================================================
// File: sortedll.h (Spring 2018)
// ============================================================================
// Programmer: Jennifer King
// Date: 5/2/2018
// Project: Sorted LL
// Professor: Scott Edwards
// Class: CSCI 223F | TR 4:30PM
// ============================================================================

#ifndef     SORTEDLL_H
#define     SORTEDLL_H


// defined constants
#define BUFLEN                  256
#define FALSE                   0
#define TRUE                    1


// structure declarations
typedef struct  LNode
{
    int                 value;
    struct  LNode      *next;

} LNode;


// function prototypes
LNode*  AddItem(LNode  *headPtr, int  newItem);
int     DisplayList(LNode  *nodePtr);
void    DisplayMenu(void);
int     ReleaseMemory(LNode  *nodePtr);
LNode*  RemoveItem(LNode  *headPtr, int  target);

#endif  // SORTEDLL_H
