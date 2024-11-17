/*
 * $QNXLicenseC:
 * Copyright 2010, QNX Software Systems.
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
 * MB86H60 general-purpose timer support
 */

#include "callout.ah"
#include <arm/mb86h60.h>


/*
 * --------------------------------------------------------------------------
 * Routine to patch callout code
 *
 * On entry:
 *  r0 - physical address of syspage
 *  r1 - virtual  address of syspage
 *  r2 - offset from start of syspage to start of the callout routine
 *  r3 - offset from start of syspage to read/write data used by callout
 * --------------------------------------------------------------------------
 */
patch_timer_mb86h60:
    stmdb   sp!, {r4, lr}
    add     r4, r0, r2                  // address of callout routine

    /*
     * Map registers
     */
    mov     r0, #MB86H60_TIMER_SIZE      // size of registers
    ldr     r1, Lpaddr
    bl      callout_io_map

    /*
     * Patch the callout routine
     */
    CALLOUT_PATCH   r4, r0, r1, r2, ip

    /*
     * Map uart registers
     */
    mov     r0, #MB86H60_UART_SIZE      // size of registers
    ldr     r1, Lpaddr_uart
    bl      callout_io_map

    /*
     * Patch the callout routine
     */
    CALLOUT_PATCH   r4, r0, r1, r2, ip

    ldmia   sp!, {r4, pc}

Lpaddr: .word   MB86H60_TIMER0_BASE
Lpaddr_uart: .word   MB86H60_UART0_BASE
count_pre: .word   88/*2147483647*/

.macro uart_tx reg_base, scratch_reg, ch
0:  ldr     \scratch_reg, [\reg_base, #MB86H60_UART_FR]
    tst     \scratch_reg, #(MB86H60_UART_FR_TXFF|MB86H60_UART_FR_BUSY)
    bne     0b
    mov     \scratch_reg, #\ch
    str     \scratch_reg, [\reg_base, #MB86H60_UART_DR]
.endm

/*
 * --------------------------------------------------------------------------
 * Set clock resolution, and enable interrupt triggering as a side effect.
 * The interrupt remains masked until it is enabled via intr_unmask_omap
 *
 * On entry:
 *  r0 - pointer to syspage_entry
 *  r1 - pointer to qtime_entry
 * --------------------------------------------------------------------------
 */
CALLOUT_START(timer_load_mb86h60, 0, patch_timer_mb86h60)
    /*
     * Get the address of the timer registers (patched)
     */
    mov     ip,     #0x000000ff
    orr     ip, ip, #0x0000ff00
    orr     ip, ip, #0x00ff0000
    orr     ip, ip, #0xff000000

   	/*
	 * Get the uart base address (patched)
	 */
	mov		r2,     #0x000000ff
	orr		r2, r2, #0x0000ff00
	orr		r2, r2, #0x00ff0000
	orr		r2, r2, #0xff000000

    /*
     *  Stop the timer
     */
    ldr     r0, [ip, #MB86H60_TIMER_ENABLE]
    bic     r0, r0, #MB86H60_TIMER_EN_ENABLE
    str     r0, [ip, #MB86H60_TIMER_ENABLE]

    /*
     * Get the load value 
     */

    ldr     r1, [r1, #QT_TIMER_LOAD]


    /* Debug */
    /*
    uart_tx r2, r0, 't'
    uart_tx r2, r0, 'i'
    uart_tx r2, r0, 'm'
    uart_tx r2, r0, 'e'
    uart_tx r2, r0, 'r'
    uart_tx r2, r0, '_'
    uart_tx r2, r0, 'l'
    uart_tx r2, r0, 'o'
    uart_tx r2, r0, 'a'
    uart_tx r2, r0, 'd'
    uart_tx r2, r0, ':'
    */

/*
    ldr     r1, =0x1999999a
loop:
    umull   r0, r3, r4, r1     
    sub     r0, r4, r3, lsl #3
    sub     r0, r0, r3, lsl #1 

    add     r0, r0, #'0'
    str     r0, [r2, #MB86H60_UART_DR]

    mov    r4, r3
    cmp    r4, #0
    bne     loop
*/

    /*
    uart_tx r2, r0, 0x0d
    uart_tx r2, r0, 0x0a
    */

    /*
     * Adjust the load value to suit the OMAP's formula
     * for computing Tint
     */
    /*
    rsb     r4, r4, #0
    */

    /*
     * Load counter value
     */
    str     r1, [ip, #MB86H60_TIMER_COUNT_LOW]

    /*
     * Enable overflow interrupt
     */
    
    ldr     r0, [ip, #MB86H60_TIMER_ENABLE]
    orr     r0, r0, #MB86H60_TIMER_EN_IRQ
    str     r0, [ip, #MB86H60_TIMER_ENABLE]    

    /*
     *  Start the timer
     */
    
    ldr     r0, [ip, #MB86H60_TIMER_ENABLE]
    orr     r0, r0, #(MB86H60_TIMER_EN_ENABLE | MB86H60_TIMER_EN_ENDLESS)
    str     r0, [ip, #MB86H60_TIMER_ENABLE]
    

    mov     pc, lr
CALLOUT_END(timer_load_mb86h60)


/*
 * --------------------------------------------------------------------------
 * Read the current timer value, relative to the last clock tick
 *
 * On entry:
 *  r0 - pointer to syspage_entry
 *  r1 - pointer to qtime_entry
 *
 * NOTE: this doesn't deal with the counter wrapping, eg. ClockCycles just
 *        at the point where the clock interrupt is triggerred.
 * --------------------------------------------------------------------------
 */
CALLOUT_START(timer_value_mb86h60, 0, patch_timer_mb86h60)
    /*
     * Get the address of the timer registers (patched)
     */
    mov     ip,     #0x000000ff
    orr     ip, ip, #0x0000ff00
    orr     ip, ip, #0x00ff0000
    orr     ip, ip, #0xff000000

   	/*
	 * Get the uart base address (patched)
	 */
	mov		r2,     #0x000000ff
	orr		r2, r2, #0x0000ff00
	orr		r2, r2, #0x00ff0000
	orr		r2, r2, #0xff000000

    /* Debug */
    /*
    uart_tx r2, r0, 't'
    uart_tx r2, r0, 'i'
    uart_tx r2, r0, 'm'
    uart_tx r2, r0, 'e'
    uart_tx r2, r0, 'r'
    uart_tx r2, r0, '_'
    uart_tx r2, r0, 'v'
    uart_tx r2, r0, 'a'
    uart_tx r2, r0, 'l'
    uart_tx r2, r0, 'u'
    uart_tx r2, r0, 'e'
    uart_tx r2, r0, 0x0d
    uart_tx r2, r0, 0x0a
    */

    /*
     * Latch the current timer value and return qtp->timer_load - value
     */

    ldr     r0, [ip, #MB86H60_TIMER_COUNT_LOW]
    ldr     r1, [r1, #QT_TIMER_LOAD]
	sub		r0, r1, r0

    mov     pc, lr
CALLOUT_END(timer_value_mb86h60)


/*
 * --------------------------------------------------------------------------
 * Clear timer interrupt.
 *
 * On entry:
 *  r0 - pointer to syspage_entry
 *  r1 - pointer to qtime_entry
 * --------------------------------------------------------------------------
 */
CALLOUT_START(timer_reload_mb86h60, 0, patch_timer_mb86h60)
    /*
     * Get the address of the timer registers (patched)
     */
    mov     ip,     #0x000000ff
    orr     ip, ip, #0x0000ff00
    orr     ip, ip, #0x00ff0000
    orr     ip, ip, #0xff000000

   	/*
	 * Get the uart base address (patched)
	 */
	mov		r2,     #0x000000ff
	orr		r2, r2, #0x0000ff00
	orr		r2, r2, #0x00ff0000
	orr		r2, r2, #0xff000000

    /* Debug */
    /*
    uart_tx r2, r0, 't'
    uart_tx r2, r0, 'i'
    uart_tx r2, r0, 'm'
    uart_tx r2, r0, 'e'
    uart_tx r2, r0, 'r'
    uart_tx r2, r0, '_'
    uart_tx r2, r0, 'r'
    uart_tx r2, r0, 'e'
    uart_tx r2, r0, 'l'
    uart_tx r2, r0, 'o'
    uart_tx r2, r0, 'a'
    uart_tx r2, r0, 'd'
    uart_tx r2, r0, 0x0d
    uart_tx r2, r0, 0x0a
    */

    /*
     * Clear overflow interrupt status
     */
    mov     r0, #1
    str     r0, [ip, #MB86H60_TIMER_IRQ_RESET]

    mov     pc, lr
CALLOUT_END(timer_reload_mb86h60)

#ifdef __QNXNTO__
#ifdef __USESRCVERSION
.section .ident, "SM",%progbits,1;
.asciz "$URL: http://svn/product/branches/6.6.0/trunk/hardware/startup/boards/mb86h60/callout_timer_mb86h60.S $ $Rev: 735852 $";
.previous
#endif
#endif 
