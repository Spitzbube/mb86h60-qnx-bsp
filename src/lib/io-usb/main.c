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


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <atomic.h>
#include <signal.h>
#include <sys/neutrino.h>


struct
{
    int fill_0[4]; //0
    int Data_0x10; //0x10
    int fill_0x14[11]; //0x14
    int Data_0x40; //0x40
    int fill_0x44[45]; //0x44
    uint16_t wData_0xf8; //0xf8
    uint16_t wData_0xfa; //0xfa
    uint16_t wData_0xfc; //0xfc
    uint16_t wData_0xfe; //0xfe
    int fill_0x100[32]; //0x100
    int Data_0x180; //0x180
} UsbdiGlobals;

extern int usb_coid; //0x00121578
extern int usb_priority; //0x0012157c
extern int usb_chid; //0x00121580
extern int usb_dflt_timeout; //0x00121584
extern char* usb_prefix; //0x0012158c
extern int usb_verbosity; //0x001215a0


int
main(int argc/*r4*/, char *argv[]/*fp*/)
{
    struct 
    {
        int fill_0; //0
        struct 
        {
            int fill_0; //0
            int Data_4; //4
            //???
        }* Data_4; //4
        char* Data_8; //8
        //???
    }* r6;
    
    sigset_t sp_0xa8;
    volatile unsigned int* sp_0x30;
    int sp_0x28;

    UsbdiGlobals.Data_0x180 = 3;
    UsbdiGlobals.wData_0xf8 = 1;
    UsbdiGlobals.wData_0xfc = 4;
    UsbdiGlobals.wData_0xfa = 1;
    UsbdiGlobals.wData_0xfe = 8;
    UsbdiGlobals.Data_0x40 = -1;

    usb_prefix = 0;
    usb_priority = 0x15;
    usb_verbosity = 0;
    usb_dflt_timeout = 10;

    sigfillset(&sp_0xa8);
    pthread_sigmask(0, &sp_0xa8, 0);

    if (ThreadCtl(1, 0) == -1)
    {
    	fprintf(stderr, "%s: ThreadCtrl\n", argv[0]);
        exit(1);
    }

    usb_chid = ChannelCreate(0x0a);
    if (usb_chid == -1)
    {
        int* r3 = __get_errno_ptr();
        fprintf(stderr, "Unable to attach channel and connection 0x%x\n", *r3);
        exit(1);
    }

    usb_coid = ConnectAttach(0, 0, usb_chid, 0x40000000, 0);
    if (usb_coid == -1)
    {
        int* r3 = __get_errno_ptr();
        fprintf(stderr, "Unable to attach channel and connection 0x%x\n", *r3);
        exit(1);
    }

    if (0 != USBDRIV_Main(0, 0))
    {
        usb_slogf(12, 2, 1, "Error Intializing USB Stack");
        exit(1);
    }
    //->loc_105a70
    while (optind < argc)
    {
        //loc_1055f8
        int r0 = getopt(argc, argv, "cCt:d:e:h:m:n:P:r:vV");
        if (r0 == -1)
        {
            optind++;
            //->loc_105a90
        }
        else
        {
            switch (r0)
            {
                case 'c':
                    //loc_1056fc: Don't auto select a configuration if a device
                                //has more than 1 configuration.
                    UsbdiGlobals.Data_0x10 |= 1;
                    break;

                case 'C': //0x43
                    //loc_10570c
                    UsbdiGlobals.Data_0x10 |= 0x40000000;
                    break;

                case 't':
                    //loc_10571c
                    break;

                case 'd':
                    //loc_10580c
                    r6 = io_usb_dll_load(&sp_0x28, "devu", optarg, &sp_0x30);
                    if (r6 != 0)
                    {
                        //0x00105834
                        if ((argv[optind] == 0) || (argv[optind][0] == '-'))
                        {
                            //loc_105850
                            r6->Data_8 = 0;
                        }
                        else
                        {
                            //loc_10585c
                            r6->Data_8 = strdup(argv[optind]);
                        }
                        //loc_105864
                        CTRL_RegisterControllerType(r6, r6->Data_4->Data_4, r6->Data_8);

                        atomic_sub(sp_0x30, 1);
                    }
                    else
                    {
                        //loc_105888
                        char* r6 = optarg;

                        if (strchr(r6, '/') != 0)
                        {
                            //0x001058a8
                            fprintf(stderr, "unable to load dll %s\n", r6);
                        }
                        else
                        {
                            //loc_1058c4
                            fprintf(stderr, "unable to load dll %s-%s\n", "devu", r6);
                        }
                    }
                    break;

                case 'e':
                    //loc_1058e8
                    break;

                case 'h':
                    //loc_105958: Hi water mark for thread pool (4).
                    UsbdiGlobals.wData_0xfc = atoi(optarg);
                    break;

                case 'm':
                    //loc_105970: Maximum number of threads in the thread pool (8).
                    UsbdiGlobals.wData_0xfe = atoi(optarg);
                    break;

                case 'n':
                    //loc_105988: Set server name. ( default "/dev/io-usb/io-usb" )
                    usb_prefix = optarg;
                    break;

                case 'P':
                    //loc_1059a4: Priority of server.
                    usb_priority = strtol(optarg, 0, 0);
                    break;

                case 'r':
                    //loc_1059cc: Set number of enumeration retry (default 3)
                    UsbdiGlobals.Data_0x180 = (strtol(optarg, 0, 0) > 0)? 
                        strtol(optarg, 0, 0): 1;
                    break;

                case 'v':
                    //loc_105a10
                    usb_verbosity++;
                    break;

                case 'V':
                    //loc_105a28
                    break;

                default:
                    //->loc_105a90
                    break;
            }
        }
    }
    //0x00105a9c

    return 0;
}

