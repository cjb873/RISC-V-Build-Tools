#ifndef UART_H
#define UART_H

void sendIntToUart(const int num, char* address);
void sendCharToUart(const char inChar, char* address);
void sendStringToUart(const char inStr[], char* address);



#endif
