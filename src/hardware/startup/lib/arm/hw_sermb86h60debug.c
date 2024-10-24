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



#include "startup.h"
#include "arm/mb86h60.h"


/*
 * Syntax: base^shift.baud.clock
 * Where:
 *
 *	base  = physical address (0x90003400)
 *	shift = not used by driver code (typically set to 0)
 *	baud  = baud rate
 *	clock = clock frequency (typically 3686400, but may be different)
 */
static void
parse_line(unsigned channel, const char *line, unsigned *baud, unsigned *clk)
{
	/*
	 * Get device base address and register stride
	 */
	if (*line != '.' && *line != '\0') {
		//dbg_device[channel].base = strtoul(line, (char **)&line, 16);
		dbg_device[channel].base = MB86H60_UART0_BASE; //fix me hardcoded
		if (*line == '^')
			dbg_device[channel].shift = strtoul(line+1, (char **)&line, 0);
	}

	/*
	 * Get baud rate
	 */
	if (*line == '.')
		++line;
	if (*line != '.' && *line != '\0')
		*baud = strtoul(line, (char **)&line, 0);

	/*
	 * Get clock rate
	 */
	if (*line == '.')
		++line;
	if (*line != '.' && *line != '\0')
		*clk = strtoul(line, (char **)&line, 0);
}


/*
 * Initialise one of the serial ports
 * buad rates fixed to default- 115200
 * so options are disabled
 */
void
init_mb86h60_debug(unsigned channel, const char *init, const char *defaults)
{
	console_send_string("init_mb86h60_debug\n");

	unsigned	baud, clk, base;

	parse_line(channel, defaults, &baud, &clk);
	parse_line(channel, init, &baud, &clk);
	base = dbg_device[channel].base;

}

/*
 * Send a character
 */
void
put_mb86h60(int data)
{
	console_write_byte(data);
}
