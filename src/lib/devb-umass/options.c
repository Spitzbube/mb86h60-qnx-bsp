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
%C Driver for USB Mass Storage interface.

Syntax:
devb-umass [cam cam_options][umass umass_options...][blk io-blk_options...] &

Options:  All options are separated by commas.

cam options: 
    lun=mask    Enable Logical Unit Number (LUN) scan for the devices specified
                in mask. The mask is a hex bitmask specifying which IDs to scan
                for; the default is 0xffff.
    quiet       Be quiet: don't display any information on startup. 
    verbose     Be verbose: display full information about units (devices)
                on startup.
    pnp         Enable CAM plug and play (i.e. don't exit at startup when
                no devices are found).  Default off.

umass options:
    The umass options control the drivers interface to the USB device.
    If you've installed multiple devices, you can repeat these options
    for each device. Remember, however, to specify the umass keyword
    before each controller's set of options. 

    path=name        Connect to the specified USB stack.  Default "/dev/io-usb/io-usb"
    wait=num         Wait num seconds for USB stack (default 60 seconds).
    vid=vid          The vendor id of the device.
    did=did          The device id of the device.
    busno=bus        The bus number of the USB controller.
    devno=dev        The usb address of the device.
    config=cfg       The configuration number of the device.
    iface=if         The particular interface number of the device.
    priority=prio    Set the priority of the processing thread. Default 21.
    csw_ignore       Ignore CSW ( some devices return invalid data for CSW )
                     
Examples:
    Assume an usb controller, and list all connected devices: 
    devb-umass &

    Assume an usb controller, and list/wait for all connected devices: 
    devb-umass cam pnp &
#endif
*/
