#include "uart.h"
#include <stdlib.h>
#include "intToStr.h"



// Function Prototypes
void binarySearch( int keyValue, int *counter, int array[], int upper,
                                                       int lower, char* UART );




int main()
   {
   
   
 
   // variable initialization
   int array[ DATA_SIZE ];

   char* LED = (char*)0x00010000;
   char* UART = (char*)0x00010004;


   /* change variables for use in vivado */
   unsigned int* searchCounter = (int*)0x00000500; // 320 in memory
   int loopIndex;
   *searchCounter = 0;
   int offsetVal, searchVal;

   srand( SEED );

   offsetVal = rand() % 14 + 1;
   searchVal = rand() % DATA_SIZE * offsetVal;

   for( loopIndex = 0; loopIndex < DATA_SIZE; loopIndex++ )
      {

      // set the value of loop index * 12 in the array
      array[ loopIndex ] = loopIndex * offsetVal;
      
      }

   for(int i = 0; i < ITERATIONS; i ++)
      {

      asm volatile("li tp, 1");
      binarySearch( searchVal, searchCounter, array, DATA_SIZE, 0, UART );
   
      
      }

   asm volatile("li tp, 2");


   

   return 0;
   }


// Function Implementation
void binarySearch( int keyValue, int *counter, int array[], int upper, 
                                                        int lower, char* UART )
   {


   // function/variable initialization
   *counter = *counter + 1;
   int middle = ( upper + lower ) / 2;
   char intAsStr[ 33 ];

   // check if the value at the middle is less than the key
   if( array[ middle ] < keyValue )
      {

      binarySearch( keyValue, counter, array, upper, middle, UART );

      }
   // otherwise, check if the value at the middle is greater than the key
   else if( array[ middle ] > keyValue )
      {

      binarySearch( keyValue, counter, array, middle, lower, UART );

      }

   else
      {
      
      sendStringToUart( "The search key was found after ", UART );
      getStr( *counter, intAsStr );
      sendStringToUart( intAsStr, UART );
      sendStringToUart( "searches. The value was ", UART );
      getStr( keyValue, intAsStr );
      sendStringToUart( ".\n\r", UART );

      }

   


   return;
   }
