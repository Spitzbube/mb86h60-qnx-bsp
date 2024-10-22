
typedef struct
{
	char bData_0; //0
	Struct_20401328 txPin; //4
	Struct_20401328 rxPin; //16
	//28?
} Uart_Init_Params;


typedef struct
{
	volatile unsigned int FREG_UART_DR; //0
	int fill_4[5]; //4
	volatile unsigned int FREG_UART_FR; //24
	volatile unsigned int fill_28[2]; //28
	volatile unsigned int FREG_UART_IBRD; //0x24
	volatile unsigned int FREG_UART_FBRD; //0x28
	volatile unsigned int FREG_UART_LCRH; //0x2c
	volatile unsigned int FREG_UART_CR; //0x30

} Uart_Regs;

typedef struct
{
	char bData_0; //0
	Uart_Regs* Data_4; //4
	//8
} Uart_Module;

extern int uart_setup(void);
extern char uart_init(Uart_Init_Params* pParams, Uart_Module** ppModule);
extern int uart_write_byte(Uart_Module* r0, unsigned char ch);
extern unsigned char uart_read_byte(Uart_Module* r0);
