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
 * TI AM335x specific interrupt callouts.
 * Note: It is same as the OMAP2420 interrupt callout except it has 128 interrupt
 * instead of 96 interrupt in OMAP2420
 * 
 * interrupt_id_* and interrupt_eoi_* are copied and intermixed with other
 * kernel code during initialisation.
 *
 * They do not follow normal calling conventions, and must fall through
 * to the end, rather than attempting to perform a return instruction.
 *
 * The INTR_GENFLAG_* bits in the intrinfo_entry defines which of the
 * following values can be loaded on entry to these code fragments:
 *
 *  r5 - holds the syspageptr               (INTR_GENFLAG_SYSPAGE  set)
 *  r6 - holds the intrinfo_entry pointer   (INTR_GENFLAG_INTRINFO set)
 *  r7 - holds the interrupt mask count     (INTR_GENFLAG_INTRMASK set)
 *
 * The interrupt_id_* routine returns the (controller-relative) level in r4
 */

#include "callout.ah"
#include "arm/mb86h60.h"


/*
 * -----------------------------------------------------------------------
 * Routines to patch callout code
 *
 * On entry:
 *  r0 - physical address of syspage
 *  r1 - virtual  address of syspage
 *  r2 - offset from start of syspage to start of the callout routine
 *  r3 - offset from start of syspage to read/write data used by callout
 * -----------------------------------------------------------------------
 */

interrupt_patch_mb86h60:
    stmdb   sp!, {r4, lr}
    add     r4, r0, r2                  // address of callout routine

    /*
     * Map interrupt controller registers
     */
    mov     r0, #MB86H60_VIC_SIZE     // size to map
    ldr     r1, [sp, #8]
    ldr     r1, [r1]
    bl      callout_io_map

	/*
	 * Patch the callout routine
	 */
	CALLOUT_PATCH	r4, r0, r1, r2, ip

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

Lpaddr_uart: .word   MB86H60_UART0_BASE

.macro uart_tx reg_base, scratch_reg, ch
0:  ldr     \scratch_reg, [\reg_base, #MB86H60_UART_FR]
    tst     \scratch_reg, #(MB86H60_UART_FR_TXFF|MB86H60_UART_FR_BUSY)
    bne     0b
    mov     \scratch_reg, #\ch
    str     \scratch_reg, [\reg_base, #MB86H60_UART_DR]
.endm

/* -----------------------------------------------------------------------
 * Returns interrupt number in r4
 * -----------------------------------------------------------------------
 */
CALLOUT_START(interrupt_id_mb86h60, 0, interrupt_patch_mb86h60)
    /*
     * Get the AINTC interrupt controller base address (patched)
     */
    mov     ip,     #0x000000ff
    orr     ip, ip, #0x0000ff00
    orr     ip, ip, #0x00ff0000
    orr     ip, ip, #0xff000000

   	/*
	 * Get the uart base address (patched)
	 */
	mov		r1,     #0x000000ff
	orr		r1, r1, #0x0000ff00
	orr		r1, r1, #0x00ff0000
	orr		r1, r1, #0xff000000

    ldr     r2, [ip, #MB86H60_VIC_IRQSTATUS]

	/* Scan for first set bit (starting with MSb) */
	mov		r4, #32
	mov		r3, #1
3:
	subs	r4, r4, #1
	blt		0f			/* r4 has rolled to -1 */
	tst		r2, r3, lsl r4
	beq		3b

	/* clear (and disable/mask) the interrupt */
	mov     r0, #0 /*ldr		r0, [ip, #MB86H60_VIC_INTENCLEAR]*/
	orr		r0, r0, r3, lsl r4
	str		r0, [ip, #MB86H60_VIC_INTENCLEAR]

    cmp     r4, #MB86H60_INTR_UART0
    beq     1f    
    cmp     r4, #MB86H60_INTR_TIMER0
    beq     1f

0:
    /* Debug the interrupt id */
    uart_tx r1, r0, 'i'
    uart_tx r1, r0, 'n'
    uart_tx r1, r0, 't'
    uart_tx r1, r0, 'e'
    uart_tx r1, r0, 'r'
    uart_tx r1, r0, 'r'
    uart_tx r1, r0, 'u'
    uart_tx r1, r0, 'p'
    uart_tx r1, r0, 't'
    uart_tx r1, r0, '_'
    uart_tx r1, r0, 'i'
    uart_tx r1, r0, 'd'
    uart_tx r1, r0, ':'
    mov     r0, #0x30
    add     r0, r0, r4
    str     r0, [r1, #MB86H60_UART_DR]
    uart_tx r1, r0, 0x0d
    uart_tx r1, r0, 0x0a

    /*
     * Mask the interrupt
     */

    /*
     * Acknowledge IRQ
     */
1:
CALLOUT_END(interrupt_id_mb86h60)


/*
 * -----------------------------------------------------------------------
 * Acknowledge specified interrupt
 *
 * On entry:
 *  r4 contains the interrupt number
 *  r7 contains the interrupt mask count
 * -----------------------------------------------------------------------
 */
CALLOUT_START(interrupt_eoi_mb86h60, 0, interrupt_patch_mb86h60)
    /*
     * Get the AINTC interrupt controller base address (patched)
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

    cmp     r4, #MB86H60_INTR_UART0
    beq     1f
    cmp     r4, #MB86H60_INTR_TIMER0
    beq     1f

    /* Debug the interrupt number and the interrupt mask count */
    uart_tx r2, r0, 'i'
    uart_tx r2, r0, 'n'
    uart_tx r2, r0, 't'
    uart_tx r2, r0, 'e'
    uart_tx r2, r0, 'r'
    uart_tx r2, r0, 'r'
    uart_tx r2, r0, 'u'
    uart_tx r2, r0, 'p'
    uart_tx r2, r0, 't'
    uart_tx r2, r0, '_'
    uart_tx r2, r0, 'e'
    uart_tx r2, r0, 'o'
    uart_tx r2, r0, 'i'
    uart_tx r2, r0, ':'
    mov     r0, #0x30
    add     r0, r0, r4
    str     r0, [r2, #MB86H60_UART_DR]
    uart_tx r2, r0, '/'
    mov     r0, #0x30
    add     r0, r0, r7
    str     r0, [r2, #MB86H60_UART_DR]
    uart_tx r2, r0, 0x0d
    uart_tx r2, r0, 0x0a

1:
    /*
     * Only unmask interrupt if mask count is zero
     */
    teq     r7, #0
    bne     2f

    /*
     * unmask interrupt
     */
	ldr		r0, [ip, #MB86H60_VIC_INTENABLE]  // unmask or enable
	mov		r3, #1
	orr		r0, r0, r3, lsl r4
	str		r0, [ip, #MB86H60_VIC_INTENABLE]

2:
CALLOUT_END(interrupt_eoi_mb86h60)


/*
 * -----------------------------------------------------------------------
 * Mask specified interrupt
 *
 * On entry:
 *  r0 - syspage_ptr
 *  r1 - interrupt number
 *
 * Returns:
 *  r0 - error status
 * -----------------------------------------------------------------------
 */
CALLOUT_START(interrupt_mask_mb86h60, 0, interrupt_patch_mb86h60)
    /*
     * Get the AINTC interrupt controller base address (patched)
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

    /* Debug the interrupt number */
    uart_tx r2, r0, 'i'
    uart_tx r2, r0, 'n'
    uart_tx r2, r0, 't'
    uart_tx r2, r0, 'e'
    uart_tx r2, r0, 'r'
    uart_tx r2, r0, 'r'
    uart_tx r2, r0, 'u'
    uart_tx r2, r0, 'p'
    uart_tx r2, r0, 't'
    uart_tx r2, r0, '_'
    uart_tx r2, r0, 'm'
    uart_tx r2, r0, 'a'
    uart_tx r2, r0, 's'
    uart_tx r2, r0, 'k'
    uart_tx r2, r0, ':'
    mov     r0, #0x30
    add     r0, r0, r1
    str     r0, [r2, #MB86H60_UART_DR]
    uart_tx r2, r0, '('
    uart_tx r2, r0, 'T'
    uart_tx r2, r0, 'O'
    uart_tx r2, r0, 'D'
    uart_tx r2, r0, 'O'
    uart_tx r2, r0, ')'
    uart_tx r2, r0, 0x0d
    uart_tx r2, r0, 0x0a

    /*
     * Mask the interrupt
     */

    mov     r0, #0
    mov     pc, lr
CALLOUT_END(interrupt_mask_mb86h60)


/*
 * -----------------------------------------------------------------------
 * Unmask specified interrupt
 *
 * On entry:
 *  r0 - syspage_ptr
 *  r1 - interrupt number
 *
 * Returns:
 *  r0 - error status
 * -----------------------------------------------------------------------
 */
CALLOUT_START(interrupt_unmask_mb86h60, 0, interrupt_patch_mb86h60)
    /*
     * Get the AINTC interrupt controller base address (patched)
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

    /* Debug the interrupt number */
    uart_tx r2, r0, 'i'
    uart_tx r2, r0, 'n'
    uart_tx r2, r0, 't'
    uart_tx r2, r0, 'e'
    uart_tx r2, r0, 'r'
    uart_tx r2, r0, 'r'
    uart_tx r2, r0, 'u'
    uart_tx r2, r0, 'p'
    uart_tx r2, r0, 't'
    uart_tx r2, r0, '_'
    uart_tx r2, r0, 'u'
    uart_tx r2, r0, 'n'
    uart_tx r2, r0, 'm'
    uart_tx r2, r0, 'a'
    uart_tx r2, r0, 's'
    uart_tx r2, r0, 'k'
    uart_tx r2, r0, ':'
    mov     r0, #0x30
    add     r0, r0, r1
    str     r0, [r2, #MB86H60_UART_DR]
    uart_tx r2, r0, 0x0d
    uart_tx r2, r0, 0x0a

    /*
     * Unmask the interrupt
     */
	ldr		r0, [ip, #MB86H60_VIC_INTENABLE]  // unmask or enable
	mov		r2, #1
	orr		r0, r0, r2, lsl r1
	str		r0, [ip, #MB86H60_VIC_INTENABLE]

    mov     r0, #0
    mov     pc, lr
CALLOUT_END(interrupt_unmask_mb86h60)

#ifdef __QNXNTO__
#ifdef __USESRCVERSION
.section .ident, "SM",%progbits,1;
.asciz "$URL: http://svn/product/branches/6.6.0/trunk/hardware/startup/boards/mb86h60/callout_interrupt_mb86h60.S $ $Rev: 710799 $";
.previous
#endif
#endif 
