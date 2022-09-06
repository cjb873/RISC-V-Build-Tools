#include "intToStr.h"

void getStr(int num, char* str)
   {

   int divisor = 10;
   int counter = 0;
   int result;
   
   if(num > 9)
      {
      while(num > 0)
         {
      
         result = (num % divisor) / (divisor / 10);
         num -= num % divisor;
      
         str[counter] = result + '0';
      
         counter++;
         divisor *= 10;
      
         }
   
      str[counter] = 0;   
   
      reverseStr(str);
      }
   else
      {
      str[0] = num + '0';
      str[1] = 0;
      }
   }

void reverseStr(char* str)
   {

   int frontIndex, rearIndex;   

   for(frontIndex = 0, rearIndex = strlen(str) - 1; frontIndex < rearIndex;
                                                    frontIndex++, rearIndex --)
      {

      char tmp = str[rearIndex];
      str[rearIndex] = str[frontIndex];
      str[frontIndex] = tmp;

      }


   
   }
