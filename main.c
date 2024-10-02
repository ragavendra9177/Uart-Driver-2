

#include <stdint.h>
#include <stdio.h>
#include "uart2.h"

int main() {

	Clock_initialization();
    UARTDriverState uartState;

    initialize_UART(&uartState);

   while(1)
   {
	   char ch;
  ch=uart_readchar(&uartState);
  delay_ms(500);
  uart_writechar(&uartState,ch);
 }
    return 0;
}
