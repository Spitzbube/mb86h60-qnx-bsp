/*
 * $QNXLicenseC:
 * Copyright 2009, QNX Software Systems.
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

void init_mb86h60_debug(unsigned, const char *, const char *);
void put_mb86h60(int);
extern struct callout_rtn display_char_mb86h60;


const struct debug_device debug_devices[] = {
	{ 	"mb86h60",
		{	"0xFFFFEE00^0.0.133000000.16",	/* Use whatever boot loader baud rate */
		},
		init_mb86h60_debug,
		put_mb86h60,
		{	&display_char_mb86h60,
#if 0 //TODO
			&poll_key_mb86h60,
			&break_detect_mb86h60,
#endif
		}
	},
};




/*
 * main()
 *	Startup program executing out of RAM
 *
 * 1. It gathers information about the system and places it in a structure
 *    called the system page. The kernel references this structure to
 *    determine everything it needs to know about the system. This structure
 *    is also available to user programs (read only if protection is on)
 *    via _syspage->.
 *
 * 2. It (optionally) turns on the MMU and starts the next program
 *    in the image file system.
 */

int
main(int argc, char **argv, char **envv)
{
	console_send_string("Hello QNX!\n");

#if 0 //TODO
	add_callout_array(callouts, sizeof(callouts));
#endif //TODO

	kprintf("main: before select_debug\n");

	/*
	 * Initialise debugging output
	 */
	select_debug(debug_devices, sizeof(debug_devices));

	kprintf("main: after select_debug\n");

	return 0;
}
