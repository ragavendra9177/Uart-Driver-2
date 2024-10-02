#include"uart2.h"





static char rxbuffer[40];
static char index =0;

volatile unsigned int *AHB1ENR =(unsigned int*)0x40023830;
volatile unsigned int *APB1ENR =(unsigned int*)0x40023840;
volatile unsigned int *GPIOMODER =(unsigned int*)0x40020000;
volatile unsigned int *GPIOAFRL =(unsigned int*)0x40020020;

/* UART Initialization  */

Clock_initialization()
{

	//Enable clock access for GPIOA
		*AHB1ENR |= (1<<0);
		//Enable clock access for USART2
		*APB1ENR |= (1<<17);
		//Configure the GPIO Mode register to alt function
		//set PA2 to ALT FUNC
		*GPIOMODER &=~(1<<4);
	    *GPIOMODER |=(1<<5);

	     //set PA3 to ALT FUNC
	     *GPIOMODER &=~(1<<6);
	     *GPIOMODER |=(1<<7);

	     //Configure the ALT Function to AFRL For PA2 and PA3
	          //PA2
	          *GPIOAFRL|=(1<<8);
	          *GPIOAFRL |=(1<<9);
	          *GPIOAFRL |=(1<<10);
	          *GPIOAFRL &=~(1<<11);
	          //PA3
	          *GPIOAFRL|=(1<<12);
	          *GPIOAFRL |=(1<<13);
	          *GPIOAFRL |=(1<<14);
	          *GPIOAFRL &=~(1<<15);

}

void initialize_UART(UARTDriverState* state) {
    // Code to initialize the I2C hardware

	state->UART= (struct UARTDevice*)USART2_Base;

	state->UART->BRR = ((104 << 4) | 3);
    state->UART->CR1 |= UART_Enable;
    state->UART->CR1 |= TE;
    state->UART->CR1 |= RE;
    state->UART->CR1 |= RXNEIE;
    state->is_initialized = 1;
}


/* UART writing character  */



void uart_writechar(UARTDriverState* state,char ch)
{

	         state->UART->DATA= ch;   // LOad the Data
		     while(!((state->UART->status)&TC));  // Wait for TC to SET.. This indicates that the data has been transmitted
}

/* UART reading single byte character */


char uart_readchar(UARTDriverState* state)
{
		char Temp;

		while (!((state->UART->status)&RXNE));  // Wait for RXNE to SET.. This indicates that the data has been Received
		Temp =state->UART->DATA;  // Read the data.
		return Temp;
}


/* UART send string  */

void uart_sendstring(UARTDriverState* state,char *string)
{
	while(*string)
	{
		uart_writechar(state, *string);
		string++;
	}
}

/* UART reading String  */

char * uart_readstring(UARTDriverState* state,char *string,char length)
{
	char i;
	for(i=0;i<length;i++)
	{
		while (!((state->UART->status)&RXNE));  // Wait for RXNE to SET.. This indicates that the data has been Received
		string[i]=state->UART->DATA;  // Read the data.
		if(string[i]=='\n')
			break;
	}
	string[i]='\0';  //putting Null character at the end
}

/* UART interrupt handler for receving data*/


void USART2_IRQHandler(UARTDriverState* state)
{

	while (!((state->UART->status)&RXNE));  // Wait for RXNE to SET.. This indicates that the data has been Received
			rxbuffer[index++]=state->UART->DATA;  // Read the data.
			if(rxbuffer[index]=='\n')
			{
				rxbuffer[index]='\0';
			}
}

void  delay_ms(int v)
{
    while(v--)
    {
        for(int i = 0; i < 8000; i++);  // Delay loop (assuming ~1ms per iteration)
    }
}
