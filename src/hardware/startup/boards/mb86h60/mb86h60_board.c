

#include "startup.h"
#include "gpio.h"
#include "uart.h"


Uart_Module* main_hUart0 = 0;


void mb86h60_board_init(void)
{
	gpio_init();
	uart_setup();

	Uart_Init_Params uartParams;

	uartParams.index = 0;

	uartParams.rxPin.bPin = 32;
	uartParams.rxPin.dwOutFunction = 0xff;
	uartParams.rxPin.dwInFunction = 21; //GPIO_IN_UART0_DATA

	uartParams.txPin.bPin = 33;
	uartParams.txPin.dwOutFunction = 23; //GPIO_OUT_UART0_DATA
	uartParams.txPin.dwInFunction = 0xff;

	uart_init(&uartParams, &main_hUart0);
	console_init(main_hUart0);
}

