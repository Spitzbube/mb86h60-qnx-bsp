/*
 * $QNXLicenseC:
 * Copyright 2008, QNX Software Systems. 
 * 
 * Licensed under the Apache License, Version 2.0 (the "License"). You 
 * may not reproduce, modify or distribute this software except in 
 * compliance with the License. You may obtain a copy of the License 
 * at: http://www.apache.org/licenses/LICENSE-2.0 
 * 
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" basis, 
 * WITHOUT WARRANTIES OF ANY KIND, either express or implied.
 *
 * This file may contain contributions from others, either as 
 * contributors under the License or as licensors under other terms.  
 * Please review this entire file for other proprietary rights or license 
 * notices, as well as the QNX Development Suite License Guide at 
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */


/*
 * MB86H60 processor with ARM 1176 core
 *
 *
 */

#ifndef MB86H60_H_
#define MB86H60_H_


#define MB86H60_UART0_BASE  0xc2000000
#define	MB86H60_UART_DR		    0x00	/* Data register */
#define	MB86H60_UART_RSR		0x04	/* Receive status register */
#define	MB86H60_UART_ECR		0x04	/* Error Clear register */
#define	MB86H60_UART_FR		    0x18	/* Flag register */
#define	MB86H60_UART_ILPR		0x20	/* IrDA low-power counter register */
#define	MB86H60_UART_IBRD		0x24	/* Integer baud rate register */
#define	MB86H60_UART_FBRD		0x28	/* Fractional baud rate register */
#define	MB86H60_UART_LCR_H		0x2C	/* Line control register */
#define	MB86H60_UART_CR		    0x30	/* Control register */
#define	MB86H60_UART_IFLS		0x34	/* Interrupt FIFO level select register */
#define	MB86H60_UART_IMSC		0x38	/* Interrupt mask set/clear register */
#define	MB86H60_UART_RIS		0x3C	/* Raw interrupt status register */
#define	MB86H60_UART_MIS		0x40	/* Masked interrupt status register */
#define	MB86H60_UART_ICR		0x44	/* Interrupt clear register */
#define MB86H60_UART_SIZE       0x48

#define	MB86H60_UART_FR_TXFF		(1 << 5)	/* Transmit FIFO full */
#define	MB86H60_UART_FR_BUSY		(1 << 3)	/* UART Busy */



#endif /* MB86H60_H_ */
