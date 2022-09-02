#include <stdlib.h>
#include <string.h>
//#include "uart.h"


void sendCharToUart(const char inChar, char* address);
void sendStringToUart(const char inStr[], char* address);

void main()
   {

   char* LED = (char*)0x00010000;
   char* UART = (char*)0x00010004;
   char str[] = "\nHello World!\r\n";   
   //*UART = 0; 
   
   *LED = 1;
   

   sendStringToUart("\nHello World!\r\n", UART);
   //sendCharToUart('A', UART);
    

   *LED = 8; 


   //sendCharToUart(0, UART); 
   }

void sendCharToUart(const char inChar, char* address)
   {
   
   *address = inChar;
      
   }

void sendStringToUart(const char inStr[], char* address)
   {

   int len = strlen(inStr);
   int index;
   
   
   sendCharToUart('0' + len, address);

   for(index = 0; index <= len ; index++)
      {
      
      sendCharToUart(inStr[index], address);

      }
   }
