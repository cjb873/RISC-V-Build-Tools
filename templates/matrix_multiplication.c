#include <stdlib.h>
#include <string.h>
#include "uart.h"
#include "intToStr.h"

void multiplyMatricies( const int factorOne[][ MATRIX_COLS], const int
          factorTwo[][ MATRIX_COLS ], int productMatrix[][ MATRIX_COLS ] );
int findDotProduct( const int row, const int col, const int
        factorOne[][ MATRIX_COLS ], const int factorTwo[][ MATRIX_COLS ] );
void printMatrix(int matrix[][MATRIX_COLS], char* address);

// main program
int main()
   {

   // declare variables
   int rowIndex, colIndex;
   char* LED = (char*)0x00010000;
   char* UART = (char*)0x00010004;

   int matrixOne[ MATRIX_ROWS ][ MATRIX_COLS ];
   int matrixTwo[ MATRIX_ROWS ][ MATRIX_COLS ];
   int productMatrix[ MATRIX_ROWS ][ MATRIX_COLS ];


   srand(SEED);

   for(int i = 0; i < ITERATIONS; i++)
      {

      *LED = 1;

      // fill the matricies
      for(rowIndex = 0; rowIndex < MATRIX_ROWS; rowIndex++)
         {
         for(colIndex = 0; colIndex < MATRIX_COLS; colIndex++)
            {
            matrixOne[rowIndex][colIndex] = rand() % 4634;
            }
         }

      for(rowIndex = 0; rowIndex < MATRIX_ROWS; rowIndex++)
         {
         for(colIndex = 0; colIndex < MATRIX_COLS; colIndex++)
            {
            matrixTwo[rowIndex][colIndex] = rand() % 4634;
	    }
         }



      asm volatile( "li tp, 1");

      // multiply the matricies together

      multiplyMatricies( matrixOne, matrixTwo, productMatrix );

      *LED = 4;



   }

   asm volatile( "li tp, 2");

   sendStringToUart("Done\n\r", UART);

   *LED = 5;


   /*
   sendStringToUart("Factor One:\n\r", UART);
   printMatrix(matrixOne, UART);

   sendStringToUart("Factor Two:\n\r", UART);
   printMatrix(matrixTwo, UART);

   */




   sendStringToUart("\nProduct:\n\r", UART);
   printMatrix(productMatrix, UART);


   *LED = 8;

   while(1);


   // end the program
   return 0;

   }


void printMatrix(int matrix[][MATRIX_COLS], char* address)
   {

   char intAsStr[33];
   int rowIndex, colIndex;


   for(rowIndex = 0; rowIndex < MATRIX_ROWS; rowIndex++)
      {
      for(colIndex = 0; colIndex< MATRIX_COLS; colIndex++)
         {

         getStr(matrix[rowIndex][colIndex], intAsStr);
         sendStringToUart(intAsStr, address);
         sendStringToUart(", ", address);
         }
      sendStringToUart("\n\r", address);
      }

   }

void multiplyMatricies( const int factorOne[][ MATRIX_COLS ],
  const int factorTwo[][ MATRIX_COLS ], int productMatrix[][ MATRIX_COLS] )
   {
   // initialize function/variables
   int rowIndex, colIndex;

   // loop across the entire product array
   for( rowIndex = 0; rowIndex < MATRIX_ROWS; rowIndex++ )
      {
      for( colIndex = 0; colIndex < MATRIX_COLS; colIndex++ )
         {

         // set the row and col of the product matrix to the sum of the dot
                                                                     // product
         productMatrix[ rowIndex ][ colIndex ] = findDotProduct( rowIndex,
                                              colIndex, factorOne, factorTwo );

         }
      }
   }




int findDotProduct( const int row, const int col, const int
         factorOne[][ MATRIX_COLS ], const int factorTwo[][ MATRIX_COLS ] )
   {
   // intialize function/variables
   int dotProduct = 0, index;

   // loop from starting index to ending index
   for( index = 0; index < MATRIX_COLS; index++ )
      {
      // add the product of corresponding places in the factors
      dotProduct +=
         ( factorOne[ row ][ index ] * factorTwo[ index ][ col ] );
      }


   // return the dot product
   return dotProduct;
   }
