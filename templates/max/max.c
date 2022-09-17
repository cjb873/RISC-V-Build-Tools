#include <stdlob.h>
#include "intToStr.h"
#include "uart.h"


// constants
const int LARGEST_VALUE_POSSIBLE = 24959;
const int NOT_FOUND = -99999;

int findLargestNumber( int arr[] );



// main function
int main()
   {





   // declare variables
   int arr[ CAPACITY ];
   int *largestPtr = (int*)0x00020000; // placed at 32768 in memory
   int loopIndex;


   srand( SEED );

   // add the first 277 nodes
   for( loopIndex = 0; loopIndex < CAPACITY; loopIndex++ )
      {

      arr[ loopIndex ] = rand();

      }

   asm( "li tp, 1" );


   // find the largest value
   //largestInSet = findLargestNumber( headNode );
   *largestPtr = findLargestNumber( arr );



   /* print the results
   printf( "The largest value is: %d\n", largestInSet );
   */

   // set value to stop timer
   asm( "li tp, 2" );

   // return
   return 0;

   }


int findLargestNumber( int arr[] )
   {
   // initialize function/variables
   int currentLargest = arr[ 0 ];
   int loopIndex;


   for( loopIndex = 0; loopIndex < CAPACITY; loopIndex++ )
      {

      if( arr[ loopIndex ] > currentLargest )
         {
	 currentLargest = arr[ loopIndex ];
	 }
      }


   // return
   return currentLargest;

   }
