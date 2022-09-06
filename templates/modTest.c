int main()
   {

   int num = 8 % 100;
   char* UART = (char*)0x00010004;

   *UART = ((char) num) + '0';   
   *UART = '\n';  

   while(1);
   return 0;
   }
