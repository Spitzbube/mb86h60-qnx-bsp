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
%C - Display USB device configuration

Usage:
%C [options]*

Options:
  -N name       Name of the USB manager to query (e.g. "/dev/io-usb/io-usb" )
  -b busno      Display devices on specific 'busno' only
  -d devno      Display device 'devno' only
  -D            Get descriptor data from device, instead of stored data.
                (io-usb by default stores standard descriptor information)
  -t            Alternative output format (tree-like)
  -v            Increase level of verbosity
  -V            Display vendor-unique descriptors (at given verbosity level)
#endif
*/
