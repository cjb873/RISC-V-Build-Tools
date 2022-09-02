#include <stdbool.h>
#include "uart.h"

// Macros - used only for array initialization
#define MATRIX_INIT 5
#define KERNEL_INIT 3

// Global Constants
const int MATRIX_ROWS = 5;
const int MATRIX_COLS = 5;

const int KERNEL_ROWS = 3;
const int KERNEL_COLS = 3;


// Prototypes
void convolution( const int matrix[][ MATRIX_COLS ], const int 
                        kernel[][ KERNEL_COLS ], int result[][ MATRIX_COLS ] );
bool hasNeighbors( const int matrix[][ MATRIX_COLS ], int row, int col );
int findValue( const int matrix[][ MATRIX_COLS ], const int 
                                   kernel[][ KERNEL_COLS ], int row, int col );


// Main Program
int main()
   {

   int startCycles = 0, endCycles = 0;
   int* LED = (int*)0x00010000;

   *LED = 1;

   asm volatile( "addi %0, tp, 0"
                 :"=r" ( startCycles )
		 :"r" ( startCycles )
		 :"cc"
		 );


   // Declare Variables
   int matrix[][ MATRIX_INIT ] = {
                                 { 1, 25, 24, 26, 3 },
				 { 2, 32, 18, 12, 50 },
				 { 6, 72, 12, 11, 20 },
				 { 16, 17, 21, 0, 22 },
				 { 12, 11, 10, 8, 7 }
                                 };
   int kernel[][ KERNEL_INIT ] = {
                                 { 0, 0, 0 },
				 { 0, 1, 0,},
				 { 0, 0, 0 },
				 }; // identity kernel

   int result_matrix[ MATRIX_ROWS ][ MATRIX_COLS ];


   // Process the two dimension convolution
   convolution( matrix, kernel, result_matrix );

   *LED = 8;

   asm volatile( "addi %0, tp, 0"
                 :"=r" ( endCycles )
		 :"r" ( endCycles )
		 :"cc"
		 );
   
   
   // Print the resulting matrix - remove for vivado
   for( int rowIndex = 0; rowIndex < MATRIX_ROWS; rowIndex++ )
      {
      for( int colIndex = 0; colIndex < MATRIX_COLS; colIndex++ )
         {
	 sendIntToUart(result_matrix[rowIndex][colIndex]);
	 }
      }
 


   }


// function implementation
void convolution( const int matrix[][ MATRIX_COLS ], const int 
                         kernel[][ KERNEL_COLS ], int result[][ MATRIX_COLS ] )
   {
   // function/variable initialization
   int rowIndex, colIndex;


   // loop through the matrix
   for( rowIndex = 0; rowIndex < MATRIX_ROWS; rowIndex++ )
      {
      for( colIndex = 0; colIndex < MATRIX_COLS; colIndex++ )
         {
         
	 // check if the "pixel" has neighbors
         if( hasNeighbors( matrix, rowIndex, colIndex ) )
            {

            // run the convolution
            result[ rowIndex ][ colIndex ] = 
	                       findValue( matrix, kernel, rowIndex, colIndex );

            }
	 // otherwise, assume the "pixel" is on the edge
         else
            {

	    // copy the value straight to the result
	    result[ rowIndex ][ colIndex ] = matrix[ rowIndex ][ colIndex ];
	   
	   }
         }   
      }
   }


bool hasNeighbors( const int matrix[][ MATRIX_COLS ], int row, int col )
   {

 
   // check if the four places around the given "pixel" are in bounds
   return ( KERNEL_ROWS <= MATRIX_ROWS && row + KERNEL_ROWS / 2 < MATRIX_ROWS ) &&
          ( KERNEL_COLS <= MATRIX_COLS && col + KERNEL_COLS / 2 < MATRIX_COLS );

   }


int findValue( const int matrix[][ MATRIX_COLS ], const int 
                                    kernel[][ KERNEL_COLS ], int row, int col )
   {
   // function/variable initialization
   int rowLowerLimit = row - KERNEL_ROWS / 2;
   int rowUpperLimit = row + KERNEL_ROWS / 2;
   
   int colLowerLimit = col - KERNEL_COLS / 2;
   int colUpperLimit = col + KERNEL_COLS / 2;

   int dotProduct = 0, rowIndex, colIndex;                                                   
                                                                                 
   // loop from starting index to ending index                                  
   for( rowIndex = rowLowerLimit; rowIndex <= rowUpperLimit; rowIndex++ )                             
      {
      for( colIndex = colLowerLimit; colIndex <= colUpperLimit; colIndex++ )
         {
         // add the product of corresponding places in the factors                 
         dotProduct += matrix[ rowIndex][ colIndex ] *
	        kernel[ rowIndex - rowLowerLimit ][ colIndex - colLowerLimit ];             
       	 }
      }
                                                                                                


   // return that dot product
   return dotProduct;




   }
