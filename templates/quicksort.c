//#include <stdio.h>
#include <stdlib.h>

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
   char* LED = (char*)0x00010000;
   int* UART = (int*)0x00010004;
   int totalCycles = 0, endCycles = 0, startCycles = 0;
   srand(SEED);

   for(int i = 0; i < ITERATIONS; i++) 
      {
      for(int j = 0; j < DATA_SIZE; j++)
         {
         array[j] = rand();
         }

      asm volatile("addi %0, tp, 0"
                   :"=r" (startCycles)
		   :"r" (startCycles)
		   :"cc"
		   );


      // sort the array
      runQuickSort( array, DATA_SIZE );



    /* //print the results
    printf( "\n" );
    for( int i = 0; i < DATA_SIZE; i++ )
       {
       printf( "%3d", array[ i ] );
       
       if( ( i + 1 ) % 10 == 0 )
          {
          printf( "\n" );
          }
       }
   printf( "\n" );*/
      *LED = 4;

      asm volatile("addi %0, tp, 0"
                   :"=r" (endCycles)
		   :"r" (endCycles)
		   :"cc"
		   );

   //sendIntToUart(endCycles - startCycles);

     /* for( int i = 0; i < DATA_SIZE; i++ )
         {
         sendIntToUart( array[i] );
         }
      */

      totalCycles += (endCycles - startCycles);
      
      }
  
   *LED = 8;

   *UART = (totalCycles / ITERATIONS) >> 24;
   *UART = (totalCycles / ITERATIONS) >> 16;
   *UART = (totalCycles / ITERATIONS) >> 8;
   *UART = (totalCycles / ITERATIONS);

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


   }

