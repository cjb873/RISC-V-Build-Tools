#ifndef UART_H
#define UART_H

void sendIntToUart(int num, char* address);
void sendCharToUart(char inChar, char* address);
void sendStringToUart(char inStr[], char* address);



#endif
