//#include <stdio.h>
#include "uart.h"
#include <stdlib.h>


// Global Constants
const int SEARCH_VALUE = 7200;

// Function Prototypes
void binarySearch( int keyValue, int *counter, int array[], int upper,
                                                                   int lower );




int main()
   {
   
   
   





   
   // variable initialization
   int array[ DATA_SIZE ];

   int startCycles = 0, endCycles = 0, int totalCycles = 0;
   int* LED = (int*)0x00010000;

   /* change variables for use in vivado */
   unsigned int* searchCounter = (int*)0x00000500; // 320 in memory
   int loopIndex;
   *searchCounter = 0;

   for( loopIndex = 0; loopIndex < DATA_SIZE; loopIndex++ )
      {

      // set the value of loop index * 12 in the array
      array[ loopIndex ] = loopIndex * 12;
      
      }

   for(int i = 0; i < ITERATIONS; i ++)
      {

      asm volatile( "mv %0. tp"
                   :"=r" ( startCycles )
		   :"r" ( startCycles )
		   :"cc"
		   );

      binarySearch( SEARCH_VALUE, searchCounter, array, DATA_SIZE, 0 );
   

      asm volatile("mv %0, tp"
                   :"=r" ( endCycles )
	 	   :"r" ( endCycles )
		   :"cc"
		   );
      totalCycles += (endCycles - startCycles);
      }
   sendIntToUart( totalCycles / ITERATIONS );

   return 0;
   }


// Function Implementation
void binarySearch( int keyValue, int *counter, int array[], int upper, 
                                                              int lower )
   {


   // function/variable initialization
   *counter = *counter + 1;
   int middle = ( upper + lower ) / 2;

   // check if the value at the middle is less than the key
   if( array[ middle ] < keyValue )
      {

      binarySearch( keyValue, counter, array, upper, middle );

      }
   // otherwise, check if the value at the middle is greater than the key
   else if( array[ middle ] > keyValue )
      {

      binarySearch( keyValue, counter, array, middle, lower );

      }

   /*else if( array[ middle ] == keyValue )
      {
      
      printf( "\nThe search key %d was found at index %d after %d searches.\n"
      , keyValue, middle, *counter );

      }*/

   sendIntToUart( keyValue );
   


   return;
   }
