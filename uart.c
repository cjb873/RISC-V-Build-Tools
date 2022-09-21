#include "uart.h"
#include <string.h>

void sendCharToUart(const char inChar, char* address)                           
   {                                                                            
                                                                                
   *address = inChar;                                                           
                                                                                
   }                                                                            
                                                                                
void sendStringToUart(const char inStr[], char* address)                        
   {                                                                            
                                                                                
   int len = strlen(inStr);                                                     
   int index;                                                                   
                                                                                
   for(index = 0; index <= len; index++)                                       
      {                                                                         
                                                                                
      sendCharToUart(inStr[index], address);                                    
                                                                                
      }                                                                         
   }   

