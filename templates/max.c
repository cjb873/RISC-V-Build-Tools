#include <stdlib.h>
#include "uart.h"
#include "intToStr.h"

// constants


// function declaration
void findLargestNumber( const int* arr, int* store );



// main function
void main()
   {

   // declare variables
   int arr[ DATA_SIZE ];
   int store[ 2 ];
   int loopIndex;
   int maxValIndex;
   int maxVal;
   char* LED = ( char* )0x00010000;
   char* UART = ( char* )0x00010004;
   char intAsStr[ 33 ];

   srand( SEED );

   *LED = 1;

   maxVal = rand();
   maxValIndex = rand() % DATA_SIZE;
   
   getStr( maxVal, intAsStr );
   sendStringToUart( "The max value should be ", UART );
   sendStringToUart( intAsStr, UART );
   sendStringToUart( "\n\r", UART );
   
   *LED = 2;
   

   // add the nodes
   for( loopIndex = 0; loopIndex < DATA_SIZE; loopIndex++ )
      {

      if( loopIndex != maxValIndex )
         {
         
	 arr[ loopIndex ] = rand() % maxVal - 1;
         
	 }
      else
         {

         arr[ loopIndex ] = maxVal;
	 
	 }
      
      }
 
   *LED = 3;

   asm( "li tp, 1" );


   // find the largest value
   findLargestNumber( arr, store );



   // set value to stop timer
   asm( "li tp, 2" );
  
   *LED = 4;
   


   getStr( store[ 0 ], intAsStr );
   sendStringToUart( "The max value was found to be ", UART );
   sendStringToUart( intAsStr, UART );
   sendStringToUart( "\n\r", UART );

   *LED = 8;


   while( 1 );


   }


// functions
void findLargestNumber( const int* arr, int* store )
   {
   // initialize function/variables
   store[ 0 ] = arr[ 0 ];
   int loopIndex;

   for( loopIndex = 0; loopIndex < DATA_SIZE; loopIndex++ )
      {

      if( arr[ loopIndex ] > store[ 0 ] )
         {
	 
	 store[ 0 ] = arr[ loopIndex ];
	 store[ 1 ] = loopIndex;

	 }
      }
   }
