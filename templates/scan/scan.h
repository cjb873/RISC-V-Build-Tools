#ifndef SCAN_H
#define SCAN_H

// header files
#include <stdio.h>
#include <stdlib.h>


// data structures
typedef struct nodeStruct
   {

   int value;
   struct nodeStruct *nextNode;


   } node;

// constants
extern const int LARGEST_VALUE_POSSIBLE;
extern const int LINKED_LIST_CAPACITY;
extern const int NOT_FOUND;

// function prototypes
node *addNode( node *headNode, int nextNodeVal );
node *clearLinkedList( node *headNode );
int findLargestNumber( node *headNode );









#endif    // SCAN_H
