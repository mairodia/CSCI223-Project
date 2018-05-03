// ============================================================================
// File: sortedll.c (Spring 2018)
// ============================================================================
// Programmer: Jennifer King
// Date: 5/1/2018
// Project: Sorted LL
// Professor: Scott Edwards
// Class: CSCI 223F | TR 430PM
// Description:
// This program allows the user to insert, remove and display integer values
// in a linked list.  Every entry in the list is dynamically allocated, so the
// user should be able to enter as many values as desired.  The list is
// maintained in sorted ascending order, so each insertion requires the list be
// traversed to find the correct location for a new value.  Duplicate values
// are permitted.  Once the user quits the program, all allocated memory is
// released before the program ends.
// ============================================================================

#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <ctype.h>
#include    "sortedll.h"


// ==== main ==================================================================
//
// ============================================================================

int     main(void)
{
    auto    int             intVal;
    auto    LNode           *headPtr = NULL;
    auto    char            buf[BUFLEN];
    auto    int             result;

    do  {
        // ask the user what they want to do
        DisplayMenu();
        printf("Please enter a selection: ");
        fgets(buf, BUFLEN, stdin);
        *buf = toupper(*buf);
        switch (*buf)
            {
            case   'A':
                // prompt the user for a value; if we get one, add it to the
                // list
                printf("Please enter an integer value to add: ");
                fgets(buf, BUFLEN, stdin);
                if (1 != sscanf(buf, "%d", &intVal))
                    {
                    puts("Error reading the integer value...");
                    }
                else
                    {
                    headPtr = AddItem(headPtr, intVal);
                    }
                break;

            case   'R':
                // if the list is empty display a message; else, get a value
                // from the user and attempt to remove it from the list
                if (NULL == headPtr)
                    {
                    puts("The list is currently empty...");
                    }
                else
                    {
                    printf("Please enter an integer value to remove: ");
                    fgets(buf, BUFLEN, stdin);
                    if (1 != sscanf(buf, "%d", &intVal))
                        {
                        puts("Error reading the integer value...");
                        }
                    else
                        {
                        headPtr = RemoveItem(headPtr, intVal);
                        }
                    }
                break;

            case   'D':
                // display the current contents of the list
                result = DisplayList(headPtr);
                printf("Currently there %s %d node%s in the list.\n"
                                    , (result != 1) ? "are" : "is"
                                    , result
                                    , (result != 1) ? "s" : "");
                break;

            case   'Q':
                // release all allocated memory and set the head pointer to
                // NULL to indicate that it is empty
                result = ReleaseMemory(headPtr);
                printf("There %s %d node%s released."
                                    , (result != 1) ? "were" : "was"
                                    , result
                                    , (result != 1) ? "s" : "");
                headPtr = NULL;
                break;

            default:
                puts("Unrecognized option; please try again.");
                break;
            }
        puts(" ");

        } while ('Q' != *buf);

    puts("Thanks for playing!  Bye!!\n");
    return  0;

}  // end of "main"



// ==== AddItem ===============================================================
//
// This function inserts an item into the list by dynamically allocating a node
// to store the value and locating the correct position for the new item so
// that the list is maintained in ascending sorted order.
//
// Input:
//      headPtr     -- a pointer to the head of the list.
//
//      newItem     -- the new item to insert into the list.
//
// Output:
//      A pointer to the (potentially new) head of the linked list.
//
// ============================================================================

LNode*  AddItem(LNode  *headPtr, int  newItem)
{
    LNode *newEntry;
    newEntry = malloc(sizeof(LNode));
    newEntry -> value = newItem;
    auto        int     traversals = 0;

    if(headPtr == NULL) // list is empty
    {
        headPtr = newEntry;
        newEntry -> next = NULL;
    }
    else
    {
        LNode *traverseNode;
        traverseNode = headPtr;
        while((traverseNode != NULL) && ((traverseNode -> value) < (newEntry -> value)))
        {
            if(traverseNode -> next == NULL)
            {
                break;
            }
            if(traverseNode -> next -> value > newEntry -> value)
            {
                break;
            }
            traverseNode = traverseNode -> next;
            traversals ++;
        }

        if(traverseNode == NULL) //adding to the end of the list
        {
            newEntry -> next = NULL;
            traverseNode -> next = newEntry;
        }
        else
        {
            if(traverseNode -> value > newEntry -> value) //tN is less than nE
            {
                newEntry -> next = traverseNode;
                if(traversals == 0)
                {
                    headPtr = newEntry;
                }
            }
            else //tN is less than nE
            {
                if(traverseNode -> next == NULL) //adding to the end of the list
                {
                    traverseNode -> next = newEntry;
                }
                else //adding to the middle of the list
                {
                    newEntry -> next = traverseNode -> next;
                    traverseNode -> next = newEntry;
                }
            }
        }
    }
    return headPtr;


}  // end of "AddItem"



// ==== DisplayList ===========================================================
//
// This function displays all of the values contained in the linked list to the
// standard output stream.
//
// Input:
//      nodePtr     -- a pointer to the head of the linked list
//
// Output:
//      The total number of nodes displayed is returned.
//
// ============================================================================

int     DisplayList(LNode  *nodePtr)
{
    auto    int         counter = 0;

    // if the list is empty, indicate as such and return zero
    if (NULL == nodePtr)
        {
        return 0;
        }

    while (NULL != nodePtr)
        {
        printf("%d\n", nodePtr->value);
        nodePtr = nodePtr->next;
        counter++;
        }

    return counter;

}  // end of "DisplayList"



// ==== DisplayMenu ===========================================================
//
// This function displays the menu to stdout.
//
// Input:
//      Nothing
//
// Output:
//      Nothing
//
// ============================================================================

void    DisplayMenu(void)
{
    puts("A)dd a value");
    puts("R)emove a value");
    puts("D)isplay the list");
    puts("Q)uit");

}  // end of "DisplayMenu"



// ==== ReleaseMemory =========================================================
//
// This function traverses the linked list and releases the memory allocated
// for each individual node.
//
// Input:
//      headPtr     -- a pointer to the head of the linked list
//
// Output:
//      The total number of nodes released is returned.
//
// ============================================================================

int     ReleaseMemory(LNode  *headPtr)
{
    int counter = 0;
    if(headPtr == NULL)
    {
        return 0;
    }
    else if(headPtr -> next == NULL)
    {
        return 1;
    }
    else
    {
        counter = 1;
        while(headPtr -> next != NULL)
        {
            counter ++;
            headPtr = headPtr -> next;
        }
    }
    return counter;

}  // end of "ReleaseMemory"



// ==== RemoveItem ============================================================
//
// This function removes an item from the list.  If the target item is located
// in the list, the memory allocated for its node is released and any adjacent
// nodes are joined so as not to break the list.  If the target item is not
// found in the list, an appropriate error message is displayed to stdout.
//
// Input:
//      target      -- the item to remove
//
// Output:
//      A pointer to the head of the linked list.
//
// ============================================================================

LNode*  RemoveItem(LNode  *headPtr, int  target)
{
    LNode *searchNode;
    searchNode = headPtr;

    if(headPtr -> next == NULL)
    {
        if(headPtr -> value == target)
        {
            free(headPtr);
            return NULL;
        }
        else
        {
            puts("Item not in list.");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        if(searchNode -> value == target)
        {
            headPtr = searchNode -> next;
            free(searchNode);
        }
        else
        {
            while((searchNode -> next -> value != target) || (searchNode -> next != NULL))
            {
                searchNode = searchNode -> next;
            }
            if(searchNode -> next -> value == target)
            {
                if(searchNode -> next -> next != NULL)
                {
                    searchNode -> next = searchNode -> next -> next;
                    searchNode = searchNode -> next;
                }
                else
                {
                    searchNode = searchNode -> next;
                }
                free(searchNode);
            }
            else
            {
                puts("Item not in list.");
                exit(EXIT_FAILURE);
            }
        }
        return headPtr;
    }
}  // end of "RemoveItem"
