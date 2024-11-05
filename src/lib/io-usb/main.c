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
#include <errno.h>
#include <dlfcn.h>
#include <sys/neutrino.h>
#include <sys/slog.h>
#include <pthread.h>

#include "externs.h"

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
    int fill_0x100[30]; //0x100
    struct UsbdiGlobals_Inner_0x178* Data_0x178; //0x178
    int fill_0x17c; //0x17c
    int Data_0x180; //0x180
} UsbdiGlobals;


extern void* io_usb_dlopen(char*, int);
extern void* io_usb_dlsym(void*, char*);


extern int Data_11c6d0; //11c6d0
extern int _iou_ex; //0x0011f3a4 
extern int Data_1212c4; //1212c4
extern int usb_enum_priority; //0x00121574
extern int usb_coid; //0x00121578
extern int usb_priority; //0x0012157c
extern int usb_chid; //0x00121580
extern int usb_dflt_timeout; //0x00121584
extern char* usb_prefix; //0x0012158c
struct 
{
    int Data_0; //0
    int Data_4; //4
    int Data_8; //8
    uint16_t wData_0xc; //12
    uint16_t wData_0xe; //14
    //???
} usb_timer; //121590
extern int usb_verbosity; //0x001215a0


/* 0x00104f44 - todo */
int io_usb_dll_load(void** phDll/*r8*/, char* r5, char* r4, volatile unsigned int** sl)
{
#if 0
    fprintf(stderr, "io_usb_dll_load\n");
#endif

    struct UsbdiGlobals_Inner_0x178* r7;
    void* hDll; //r6
    struct io_usb_dll_entry_t* pDllEntry; //r5
    char sp_0xc[258];
    char* r0;
#if 0
    r0 = strchr(r4, '/');
    int r3 = (r5 != 0)? 0: 1;
    if (r0 != 0)
    {
        r3 |= 1;
    }
    if (r3 != 0)
#else
    if ((strchr(r4, '/') != 0) || (r5 == 0))
#endif
    {
        r0 = r4;
    }
    else
    {
        char* r6 = &sp_0xc[0];
        snprintf(r6, 257, "%s-%s.so", r5, r4);
        r0 = r6;
    }

    hDll = io_usb_dlopen(r0, 0);
    if (hDll != 0)
    {
        pDllEntry = io_usb_dlsym(hDll, "io_usb_dll_entry");
        if (pDllEntry == 0)
        {
            fwrite(" FAILED  - io_usb_dlsym\n", 1, 0x18, stderr);

            io_usb_dlclose(hDll);

            errno = 0;
            //->loc_10511c
            return 0;
        }
        //loc_105028
    }
    else
    {
        //loc_104ffc
        fwrite(" FAILED  - io_usb_dlopen\\n", 1, 0x19, stderr);

        errno = 0;
        //->loc_10511c
        return 0;
    }
    //loc_105028
    struct UsbdiGlobals_Inner_0x178* r4_ = UsbdiGlobals.Data_0x178;

    if (r4_ != 0)
    {
        //loc_10504c
        while (r4_->pDllEntry != pDllEntry)
        {
            //loc_105058
            r4_ = r4_->Data_0x78;
            if (r4_ == 0)
            {
                //->loc_105128
                goto loc_105128;
            }
            //->loc_10504c
        }
        //loc_105068
        if (r4_->Data_0x74 != 0)
        {
            //0x00105074
            pthread_cancel(r4_->Data_0x74);
        }
        //loc_105078
        (r4_->pDllEntry->shutdown)(r4_->hDll);

        r4_->Data_0x74 = 0;
        //->loc_105108
        io_usb_dlclose(hDll);

        r7 = 0;
        //loc_105114
        if (r4_ == 0)
        {
            r4_ = r7;
        }
        //loc_10511c
        return r4_;
    }
    //loc_105128
loc_105128:
    r7 = calloc(1, sizeof(struct UsbdiGlobals_Inner_0x178));
    if (r7 == 0)
    {
        //->loc_105094
        errno = 12;
        //->loc_105108
        io_usb_dlclose(hDll);

        r7 = 0;
        //loc_105114
    }
    else
    {
        //->loc_1050a4
        *phDll = hDll;

        r7->hDll = hDll;
        r7->pDllEntry = pDllEntry;
        r7->Data_0xc = 1;
        r7->Data_0x78 = UsbdiGlobals.Data_0x178;
        UsbdiGlobals.Data_0x178 = r7;

        (pDllEntry->init)(hDll, 0, &_iou_ex, 0);

        r7->Data_0x18 = 0;

        atomic_add(&r7->Data_0x1c, 1);

        *sl = &r7->Data_0x1c;
        //->loc_105114
    }
    //loc_105114
    if (r4_ == 0)
    {
        r4_ = r7;
    }
    //loc_10511c
    return r4_;
}


/* 105214 - todo */
static void* usb_event_handler(void* p)
{
#if 0
    fprintf(stderr, "usb_event_handler: TODO\n");
#endif

    struct
    {
        int fill_0; //0
        int8_t bData_4; //4
        int fill_8[2]; //8
        //16???
    } sp8;
    struct iovec sp;

    pthread_setname_np(0, "event_handler");

    sp.iov_base = &sp8;
    sp.iov_len = 16;

    while (1)
    {
        //loc_105248
        int r0 = MsgReceivev(usb_chid, &sp, 1, 0);

        if (r0 != -1)
        {
            if (sp8.bData_4 == 1)
            {
                usbdi_timeout_tick(0, 1, 0, 0);
            }
            else if (r0 != 0)
            {
                MsgReplyv(r0, 0x30, &sp, 1);
            }
        }
        //->loc_105248
    }

    return 0;
}


/* 0x0010548c - todo */
int main(int argc/*r4*/, char *argv[]/*fp*/)
{
    sigset_t sp_0xa8;
    pthread_attr_t sp_0x5c;
    struct sched_param sp_0x34;
    volatile unsigned int* sp_0x30;
    void* hDll; //sp_0x28

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
                    //TODO!!!
                    break;

                case 'd':
                    //loc_10580c: Hc DLL to load and options to pass to the DLL.
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
                        
                        r6 = io_usb_dll_load(&hDll, "devu", optarg, &sp_0x30);
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
                    }
                    break;

                case 'e':
                    //loc_1058e8: Priority of enumeration thread.
                    {
                        int r6 = atoi(optarg);
                        if ((r6 < sched_get_priority_min(2)) ||
                            (r6 > sched_get_priority_max(2)))
                        {
                            fprintf(stderr, "priority %d for option -e is out of range\n", r6);
                            slogf(12, 2, "io-usb: priority %d for option -e is out of range", r6);
                            exit(1);
                        }
                        //loc_105948
                        usb_enum_priority = r6;
                    }
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
                    //loc_105a28: Display server version and exit
                    fprintf(stderr, "USB v%x.%02x, v%x.%02x, %s %s\n",
                        1, 16, 1, 1, "Release", "Oct 21 2013");

                    stop_controllers();

                    exit(0);
                    break;

                default:
                    //->loc_105a90
                    break;
            }
        }
    }
    //0x00105a9c
    udi_memory_info(&Data_1212c4);

    usb_timer.Data_0 = 4;
    usb_timer.Data_4 = usb_coid;
    usb_timer.wData_0xc = 1;
    usb_timer.wData_0xe = usb_priority;
    usb_timer.Data_8 = 0;

    pthread_attr_init(&sp_0x5c);
    pthread_attr_setschedpolicy(&sp_0x5c, 2);
    sp_0x34.sched_priority = usb_priority;
    pthread_attr_setschedparam(&sp_0x5c, &sp_0x34);
    pthread_attr_setinheritsched(&sp_0x5c, 2);
    pthread_attr_setdetachstate(&sp_0x5c, 1);
    pthread_attr_setstacksize(&sp_0x5c, 0x4000);

    if (0 != pthread_create(0, &sp_0x5c, usb_event_handler, 0))
    {
        fwrite("Unable to create driver thread\n", 1, 0x1f, stderr);
        exit(1);
    }
    //loc_105b70
    if (usb_prefix == 0)
    {
        usb_prefix = "/dev/io-usb/io-usb";
    }

    if (usbdi_init_server_globals(usb_prefix, &usb_timer) != 0)
    {
        fprintf(stderr, "usbdi_init_server_globals %d\n");
        exit(1);
    }
    //loc_105bc8
    struct UsbdiGlobals_Inner_0x178* r4 = UsbdiGlobals.Data_0x178;

    while (r4 != 0)
    {
        //loc_105bdc
        register_dll_entry(r4);

        r4 = r4->Data_0x78;
    }
    //loc_105bf0
    if (procmgr_daemon(0, 6) == -1)
    {
        fwrite("usb:  procmgr_daemon\n", 1, 0x15, stderr);
        return -1;
    }
    //loc_105c20
    usb_port_monitor_start();
    usb_signal_handler();

    return 0;
}


/* 0x00109f7c - todo */
int io_usb_dlclose(void* handle)
{
#if 1
    fprintf(stderr, "io_usb_dlclose: TODO\n");
#endif

    if (handle != 0)
    {

        return dlclose(handle);
    }

    return 0;
}


/* 0x00109fac - todo */
void* io_usb_dlsym(void* r6, char* r5)
{
#if 1
    fprintf(stderr, "io_usb_dlsym\n");
#endif

    return dlsym(r6, r5);
}


/* 0x0010a02c - todo */
void* io_usb_dlopen(char* r5, int r8)
{
#if 1
    fprintf(stderr, "io_usb_dlopen: TODO\n");
#endif

    void* r6;

    if (Data_11c6d0 != 0)
    {

    }
    //loc_10a074
    r6 = dlopen(r5, r8);
    if (r6 == 0)
    {

        //loc_10a0ec
        fprintf(stderr, "DLL Error %s\n", dlerror());
    }
    //loc_10a108
    return r6;
}



