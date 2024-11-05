/*
 * $QNXLicenseC:
 * Copyright 2008-2009, QNX Software Systems.
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
#ifdef __USAGE
%C - USB Server  ( Universal Serial Bus )

%C [options] &
Options:
  -c 				Don't auto select a configuration if a device
                    has more than 1 configuration.
  -d dll [opts]     Hc DLL to load and options to pass to the DLL.
  -e                Priority of enumeration thread.
  -h num            Hi water mark for thread pool (4).
  -m num            Maximum number of threads in the thread pool (8).
  -n name           Set server name. ( default "/dev/io-usb/io-usb" )
  -t memory=	    Set type memory name (default non, using sysram)
  -r num	    Set number of enumeration retry (default 3)
  -P                Priority of server.
  -v                Be verbose
  -V                Display server version and exit

Examples:

    USB Host Controllers connected to PCI Bus ( UHCI, OHCI, EHCI )

      io-usb -duhci -dohci -dehci
#endif
*/
