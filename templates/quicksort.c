//#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
#include "intToStr.h"


// Prototypes
void runQuickSort( int array[], int size );
void runQuickSortHelper( int array[], int lowIndex, int highIndex );
int runPartition( int array[], int lowIndex, int highIndex );



// Main Program
int main()
   {
  

   // intitialize variables
   int array[ DATA_SIZE ];
   int loopIndex, arrIndex;
   char* LED = ( char* )0x00010000;
   char* UART = ( char* )0x00010004;
   char intAsStr[ 33 ];
   srand( SEED );
   int index, iteration;

   for( iteratiom = 0; iteration < ITERATIONS; iteration++ ) 
      {
      for( index = 0; index < DATA_SIZE; index++)
         {
         array[ index ] = rand();
         }

      asm volatile( "li tp, 1" );


      // sort the array
      runQuickSort( array, DATA_SIZE );



      *LED = 4;



      
      }


   asm volatile( "li tp, 2" );
   sendStringToUart( "Done\n\rArray:\n\r", UART );

   
   for( index = 0; i < DATA_SIZE; index++ ) 
      {
      getStr( array[ index ], intAsStr );
      sendStringToUart( intAsStr, UART );
      sendStringToUart( ", ", UART );
      }


   *LED = 8;

   while( 1 );   

   return 0;
   }



// Function Implementation

void runQuickSort( int array[], int size )
   {

   // run the helper function
   runQuickSortHelper( array, 0, size - 1 );

   }

void runQuickSortHelper( int array[], int lowIndex, int highIndex )
   {
   // initialize function/variables
   int pivotIndex;

   // check if low index is less than high index
   if( lowIndex < highIndex )
      {
      // call partition to get the pivot value
      pivotIndex = runPartition( array, lowIndex, highIndex );
      
      // run the quicksort on the left and right sides of the list
      runQuickSortHelper( array, lowIndex, pivotIndex - 1 );
      runQuickSortHelper( array, pivotIndex + 1, highIndex );

      }
   }

int runPartition( int array[], int lowIndex, int highIndex )
   {

   // intialize function/variables
   int workingIndex, pivotIndex = lowIndex, temp;
   int pivot = array[ lowIndex ]; // set the pivot as the first element

   // loop across the array
   for( workingIndex = lowIndex; workingIndex <= highIndex; workingIndex++ )
      {  
      // check if the element at working index is less than the pivot
      if( array[ workingIndex ] < pivot )
         {
 
         // increment the pivot index
         pivotIndex++;

         // swap the working index and the pivot index
         temp = array[ workingIndex ];
         array[ workingIndex ] = array[ pivotIndex ];
         array[ pivotIndex ] = temp;        

         }


      }

   // swap the pivot with the pivot index
   temp = array[ pivotIndex ];
   array[ pivotIndex ] = pivot;
   array[ lowIndex ] = temp;
   
   // return the pivot index   
   return pivotIndex;

