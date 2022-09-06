#include <stdlib.h>
#include <string.h>
#include "uart.h"
#include "intToStr.h"

void multiplyMatricies( const int factorOne[][ MATRIX_1_COLS], const int 
          factorTwo[][ MATRIX_2_COLS ], int productMatrix[][ MATRIX_2_COLS ] );

int findDotProduct( const int row, const int col, const int 
        factorOne[][ MATRIX_1_COLS ], const int factorTwo[][ MATRIX_2_COLS ] );

int getRand();
void printMatrix(int matrix[][MATRIX_1_COLS], char* address);

// main program
int main()
   {
   
   // declare variables
   int rowIndex, colIndex;
   char* LED = (char*)0x00010000;
   char* UART = (char*)0x00010004;

   int matrixOne[ MATRIX_1_ROWS ][ MATRIX_1_COLS ]; 
   int matrixTwo[ MATRIX_2_ROWS ][ MATRIX_2_COLS ];
   int productMatrix[ MATRIX_1_ROWS ][ MATRIX_2_COLS ];
  

   srand(SEED);
 
   for(int i = 0; i < ITERATIONS; i++)
      {
      
      *LED = 1;
      
      // fill the matricies
      for(rowIndex = 0; rowIndex < MATRIX_1_ROWS; rowIndex++)
         {
         for(colIndex = 0; colIndex < MATRIX_1_COLS; colIndex++)
            {
            matrixOne[rowIndex][colIndex] = getRand();
            }
         }

      for(rowIndex = 0; rowIndex < MATRIX_2_ROWS; rowIndex++)
         {
         for(colIndex = 0; colIndex < MATRIX_2_COLS; colIndex++)
            {
            matrixTwo[rowIndex][colIndex] = getRand();
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


void printMatrix(int matrix[][MATRIX_1_COLS], char* address)
   {
   
   char intAsStr[33];
   int rowIndex, colIndex;


   for(rowIndex = 0; rowIndex < MATRIX_1_ROWS; rowIndex++)
      {
      for(colIndex = 0; colIndex< MATRIX_1_COLS; colIndex++)
         {
         
         getStr(matrix[rowIndex][colIndex], intAsStr);
         sendStringToUart(intAsStr, address); 
         sendStringToUart(", ", address);
         }
      sendStringToUart("\n\r", address);      
      }

   }

void multiplyMatricies( const int factorOne[][ MATRIX_1_COLS ], 
  const int factorTwo[][ MATRIX_2_COLS ], int productMatrix[][ MATRIX_2_COLS] )
   {
   // initialize function/variables
   int rowIndex, colIndex;

   // loop across the entire product array
   for( rowIndex = 0; rowIndex < MATRIX_1_ROWS; rowIndex++ )
      {
      for( colIndex = 0; colIndex < MATRIX_2_COLS; colIndex++ )
         {

         // set the row and col of the product matrix to the sum of the dot
                                                                     // product
         productMatrix[ rowIndex ][ colIndex ] = findDotProduct( rowIndex, 
                                              colIndex, factorOne, factorTwo );
   
         }
      }
   }




int findDotProduct( const int row, const int col, const int 
         factorOne[][ MATRIX_1_COLS ], const int factorTwo[][ MATRIX_2_COLS ] )
   {
   // intialize function/variables
   int dotProduct = 0, index;

   // loop from starting index to ending index
   for( index = 0; index < MATRIX_1_COLS; index++ )
      {
      // add the product of corresponding places in the factors 
      dotProduct += 
         ( factorOne[ row ][ index ] * factorTwo[ index ][ col ] );
      }
   

   // return the dot product
   return dotProduct;
   } 

int getRand()
   {

   int num = 0;

   while(num == 0)
      {
      num = rand() % 50;
      }
   return num;




   }
