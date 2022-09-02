#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// function prototypes
void multiplyMatricies( const int factorOne[][ MATRIX_1_COLS], const int 
          factorTwo[][ MATRIX_2_COLS ], int productMatrix[][ MATRIX_2_COLS ] );

int findDotProduct( const int row, const int col, const int 
        factorOne[][ MATRIX_1_COLS ], const int factorTwo[][ MATRIX_2_COLS ] );

void sendStringToUart(const char inStr[], char* address);
void sendCharToUart(const char inChar, char* address);

// main program
int main()
   {
   
   // declare variables
   int startCycles = 0, endCycles = 0, totalCycles = 0;
   int rowIndex, colIndex;
   char* LED = (char*)0x00010000;
   char* UART = (char*)0x00010004;

   char cycleStr[] = "Average number of cycles: ";
   char* factorOneStr = "Factor One: "; 
   char* factorTwoStr = "Factor Two: ";
   char* productStr = "Factor Three: ";
   char intAsStr[25];

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
	    matrixOne[rowIndex][colIndex] = (rand() % 50);
	    }
         }

      for(rowIndex = 0; rowIndex < MATRIX_2_ROWS; rowIndex++)
         {
         for(colIndex = 0; colIndex < MATRIX_2_COLS; colIndex++)
            {
	    matrixTwo[rowIndex][colIndex] = (rand() % 50);
	    }
         }
      
       
      /*
      asm volatile( "addi %0, tp, 0"
                   :"=r" ( startCycles )
	           :"r" ( startCycles )
	           :"cc"
	          );
      */ 
      // multiply the matricies together
      
      multiplyMatricies( matrixOne, matrixTwo, productMatrix );
      sendStringToUart("Multiplying\n", UART);

      *LED = 4;
      
      /* 
      asm volatile( "addi %0, tp, 0"
                   :"=r" ( endCycles )
	           :"r" ( endCycles )
	           :"cc"
	          );
      */
      //totalCycles += endCycles - startCycles;
      
      }

   /*
   for(int i = 0; i < MATRIX_1_ROWS; i++)
      {
      for(int j = 0; j < MATRIX_1_COLS; j++)
         {
         sprintf(intAsStr, "%d, ", matrixOne[i][j]);
         strcat(factorOneStr, intAsStr);
         
         sprintf(intAsStr, "%d, ", matrixTwo[i][j]);
         strcat(factorTwoStr, intAsStr);
         
         sprintf(intAsStr, "%d, ", productMatrix[i][j]);
         strcat(productStr, intAsStr);
         }
      
      strcat(factorOneStr, "\n");
      strcat(factorTwoStr, "\n");
      strcat(productStr, "\n");
      }
   */      
   //sprintf(outStr, "\nAvg. Cycles: %d\n", totalCycles / ITERATIONS);
    
   sendStringToUart(factorOneStr, UART);
   sendStringToUart(factorTwoStr, UART);
   sendStringToUart(productStr, UART);
   //sendStringToUart(cycleStr, UART);

   


   *LED = 8;
   
   while(1);
   
   /*  print the result
   for( rowIndex = 0; rowIndex < MATRIX_1_ROWS; rowIndex++ ) 
      {
      for( colIndex = 0; colIndex < MATRIX_2_COLS; colIndex++ )
	 {
         sendIntToUart( productMatrix[ rowIndex ][ colIndex ] );
	 }
      }
   */

   // end the program
   return 0;

   }


void sendCharToUart(const char inChar, char* address)
   {
   
   *address = inChar;
      
   }

void sendStringToUart(const char inStr[], char* address)
   {

   int len = strlen(inStr);
   int index;
   
   for(index = 0; index <= len ; index++)
      {
      
      sendCharToUart(inStr[index], address);

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
