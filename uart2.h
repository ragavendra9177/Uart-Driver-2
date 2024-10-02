






#define USART2_Base (0x40004400UL)

struct UARTDevice{
	unsigned int status;
	unsigned int DATA;
	unsigned int BRR;
	unsigned int CR1;
};

typedef struct {
struct UARTDevice* UART;
int is_initialized;
}UARTDriverState;

//Control Registers mask bits
#define UART_Enable   0x2000    //Uart Enable mask bit
#define TE            0x0008    //Transmit enable mask bit
#define RE            0x0004    //RECEIVE  enable mask bit
#define TC            0x0040    //Transmission complete bit it indicates dat transmission cmplete
#define RXNE          0x0020    //received data bit mask
#define RXNEIE        0x0020    //Received data interrupt enable bit maskenable



void delay_ms(int);
void USART2_IRQHandler(UARTDriverState*);
void initialize_UART(UARTDriverState*);
void uart_writechar(UARTDriverState*,char);
char uart_readchar(UARTDriverState*);
void uart_sendstring(UARTDriverState*,char *);
char* uart_readstring(UARTDriverState*,char *,char);
void Clock_initialization(void);

