#include "uart.h"
#include <string.h>


void sendStringToUart(char inStr[], char* address)
   {

   int index;
   int length = (int) strlen(inStr);

   for(index = 0; index < length; index++)
      {
      
      sendCharToUart(inStr[index], address);

      }

   }


void sendCharToUart(char inChar, char* address)
   {


   *address = inChar;


   }



void sendIntToUart(int num, char* address)
   {
   
   (*address) = num >> 24;
   (*address) = num >> 16;
   (*address) = num >> 8;
   (*address) = num;

   }
