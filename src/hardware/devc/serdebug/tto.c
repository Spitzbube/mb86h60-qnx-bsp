/*
 * Copyright 2008-2009, QNX Software Systems.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You may not
 * reproduce, modify or distribute this software except in compliance with the
 * License. You may obtain a copy of the License at:
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" basis, WITHOUT
 * WARRANTIES OF ANY KIND, either express or implied.
 *
 * This file may contain contributions from others, either as contributors under
 * the License or as licensors under other terms.  Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 */



#include "externs.h"

#if 1

int
tto(TTYDEV *ttydev, int action, int arg1)
{
    fprintf(stderr, "tto: action=%d\n", action);

#if 0 //TODO
	TTYBUF 		*bup = &ttydev->obuf;
	DEV_USART	*dev = (DEV_USART *)ttydev;
	uintptr_t	base = dev->base;
	uint8_t		c;

	switch (action) {
	case TTO_STTY:
		ser_stty(dev);
		return 0;
 
	case TTO_CTRL:
		return 0;

	case TTO_LINESTATUS:
		return in32(base + BCM2835_UART0_FR); ;

	case TTO_DATA:
		break;

	default:
		return 0;
	}
	while ((bup->cnt > 0 ))
		{
		while ( in32(base + BCM2835_UART0_FR) & BCM2835_DBGU_IE_SR_TXRDY )
		{}
			dev_lock(&dev->tty);
         	c = tto_getchar(&dev->tty);
			dev_unlock(&dev->tty);
			dev->tty.un.s.tx_tmr = 3;		/* Timeout 3 */
			out32(base + BCM2835_UART0_DR, c);
			/*
			 * Clear the OSW_PAGED_OVERRIDE flag as we only want
			 * one character to be transmitted in this case.
			 */
			if (dev->tty.xflags & OSW_PAGED_OVERRIDE)
			{
				atomic_clr(&dev->tty.xflags, OSW_PAGED_OVERRIDE);
				break;
		    }
	}

	/*
	 * If anyone is waiting to write, kick them when buffer drains to 1/4 full.
	 */
	return (tto_checkclients(&dev->tty));
#else
    return 0;
#endif
}

#endif
