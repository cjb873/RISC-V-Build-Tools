#include <stdbool.h>
#include <stdlib.h>
#include "intToStr.h"
#include "uart.h"

// Macros - used only for array initialization
#define KERNEL_INIT 3

// Global Constants
const int KERNEL_ROWS = 3;
const int KERNEL_COLS = 3;


// Prototypes
void convolution( const int matrix[][ MATRIX_COLS ], const int 
                        kernel[][ KERNEL_COLS ], int result[][ MATRIX_COLS ] );
bool hasNeighbors( const int matrix[][ MATRIX_COLS ], int row, int col );
int findValue( const int matrix[][ MATRIX_COLS ], const int 
                                   kernel[][ KERNEL_COLS ], int row, int col );
void printMatrix( int matrix[ MATRIX_ROWS * MATRIX_COLS * 3 ], char* address );


// Main Program
int main()
   {

   int startCycles = 0, endCycles = 0;
   char* LED = ( char* )0x00010000;
   char* UART = ( char* )0x00010004;
   int rowIndex, colIndex, iteration = 0;

   srand( SEED );

   *LED = 1;



   // Declare Variables
   int matrix[ MATRIX_ROWS ][ MATRIX_COLS ];

   int result_matrix[ MATRIX_ROWS ][ MATRIX_COLS ];
   
   int kernel[][ KERNEL_INIT ] = {
                                 { 0, 0, 0 },
				 { 0, 1, 0,},
				 { 0, 0, 0 },
				 }; // identity kernel
   

   for( iteration = 0; iteration < ITERATIONS; iteration++ )
      {
      for( rowIndex = 0; rowIndex < MATRIX_ROWS; rowIndex++ )
         {
         for( colIndex = 0; colIndex < MATRIX_COLS; colIndex++ )
            {

	    matrix[ rowIndex ][ colIndex ] = rand() % 4684;
         
	    }
         }

      asm volatile( "li tp, 1"); 

      // Process the two dimension convolution
      convolution( matrix, kernel, result_matrix );


      }

   *LED = 8;

   asm volatile( "li tp, 2" );
   
   
   // printMatrix( result_matrix, UART ); 


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


void printMatrix( int matrix[MATRIX_ROWS * MATRIX_COLS * 3], char* address )
   {

   char intAsStr[33];
   int index; 
   int length = 27;


   for( index = 0; index < length; index++ )
      {
      
      /*
      if( index % ( MATRIX_ROWS * MATRIX_COLS ) == 0 )
         {
         
	 if( index == 0 )
	    {
            sendStringToUart( "Factor One:", address );
	    }
	 else if( index == MATRIX_ROWS * MATRIX_COLS )
	    {
            sendStringToUart( "Factor Two:", address );
	    }
	 else
	    {
            sendStringToUart( "Product:", address );
            }
	 }
      if( index % MATRIX_COLS == 0 )
         {
         sendStringToUart( "\n\r", address );
	 }
      */
      getStr( matrix[ index ], intAsStr );
      sendStringToUart( intAsStr, address );
      sendStringToUart( ", ", address );
     

      }

   }
