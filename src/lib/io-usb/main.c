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
#include <libgen.h>
#include <sys/neutrino.h>
#include <sys/slog.h>
#include <sys/dispatch.h>
#include <sys/iofunc.h>
#include <pthread.h>

#include "externs.h"

extern void* io_usb_dlopen(char*, int);
extern void* io_usb_dlsym(void*, char*);
extern int usbdi_resmgr_open(resmgr_context_t *ctp, io_open_t *msg,
                      RESMGR_HANDLE_T *handle, void *extra);
extern int usbdi_io_mount(resmgr_context_t *ctp, io_mount_t *msg,
                      RESMGR_HANDLE_T *handle,
                      io_mount_extra_t *extra);
extern iofunc_ocb_t* usbdi_ocb_calloc(resmgr_context_t *ctp,
                     iofunc_attr_t *attr);
extern void usbdi_ocb_free(iofunc_ocb_t *ocb);

iofunc_funcs_t ResmgrOCBFuncs = //0x11950c
{
    5,
    usbdi_ocb_calloc,
    usbdi_ocb_free
};

extern int Data_11c6d0; //11c6d0
extern int Data_11ddf4; //11ddf4
extern int _iou_ex; //0x0011f3a4 
resmgr_io_funcs_t ResmgrIOFuncs = //0x11f404
{
    26,
    //TODO!!!
};
resmgr_connect_funcs_t ResmgrCFuncs = //0x0011f488
{
    8,
    usbdi_resmgr_open,
    0, 0, 0, 0, 0, 0,
    usbdi_io_mount
};

struct
{
#if 0
    int fill_0[4]; //0
#else
    pthread_mutex_t Data_0; //0
#endif
    int Data_8; //8
    int Data_0xc; //0xc
    int Data_0x10; //0x10
    int fill_0x14[2]; //0x14
    dispatch_t* dpp; //0x1c
    void* Data_0x20; //0x20
    int Data_0x24; //0x24
    void* Data_0x28; //0x28
    int Data_0x2c; //0x2c
    int Data_0x30; //0x30
    int Data_0x34; //0x34
    int fill_0x38[2]; //0x38
    int Data_0x40; //0x40
    int fill_0x44[2]; //0x44
    iofunc_mount_t Data_0x4c; //0x4c
    iofunc_attr_t iofunc_attr; //0x64
    dev_t Data_0xb8; //0xb8
    resmgr_attr_t resmgr_attr; //0xbc
    thread_pool_attr_t Data_0xdc;
    pthread_attr_t Data_0x120; //0x120
    //TODO
    struct UsbdiGlobals_Inner_0x178* Data_0x178; //0x178
    int fill_0x17c; //0x17c
    int Data_0x180; //0x180
} UsbdiGlobals; //0x001212b0

extern int Data_1212c4; //1212c4
extern int usb_enum_priority; //0x00121574
extern int usb_coid; //0x00121578
extern int usb_priority; //0x0012157c
extern int usb_chid; //0x00121580
extern int usb_dflt_timeout; //0x00121584
extern char* usb_prefix; //0x0012158c
struct USB_Timer usb_timer; //121590
extern int usb_verbosity; //0x001215a0


/* 0x00104f44 - todo */
struct UsbdiGlobals_Inner_0x178* io_usb_dll_load(void** phDll/*r8*/, char* r5, char* r4, volatile unsigned int** sl)
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


/* 0x00105148 - todo */
int register_dll_entry(struct UsbdiGlobals_Inner_0x178* r4)
{
#if 0
    fprintf(stderr, "register_dll_entry\n");
#endif

    char sp_0x14[260];

    char* r6 = strdup(usb_prefix);

    sprintf(&sp_0x14[0], "%s/%s", dirname(r6), r4->pDllEntry->Data_0);

    r4->Data_0x10 = resmgr_attach(UsbdiGlobals.dpp, //dispatch_t *dpp
        &UsbdiGlobals.resmgr_attr, //resmgr_attr_t *attr
        &sp_0x14[0], //path
        0x0b, //enum _file_type file_type
        0x200, //flags
        &ResmgrCFuncs, //resmgr_connect_funcs_t *connect_funcs
        0, //resmgr_io_funcs_t *io_funcs
        r4 //RESMGR_HANDLE_T *handle
        );

    if (r4->Data_0x10 == -1)
    {
        fprintf(stderr, "resmgr_attach unable to register %s \n", 
            r4->pDllEntry->Data_0);

        free(r6);

        return -1;
    }

    free(r6);

    return 0;
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
    UsbdiGlobals.Data_0xdc.lo_water = 1; //wData_0xf8 = 1;
    UsbdiGlobals.Data_0xdc.hi_water = 4; //wData_0xfc = 4;
    UsbdiGlobals.Data_0xdc.increment = 1; //wData_0xfa = 1;
    UsbdiGlobals.Data_0xdc.maximum = 8; //wData_0xfe = 8;
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
                        struct UsbdiGlobals_Inner_0x178* r6;
                        
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
                            CTRL_RegisterControllerType(r6, r6->pDllEntry->Data_4, r6->Data_8);

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
                    UsbdiGlobals.Data_0xdc.hi_water = atoi(optarg);
                    break;

                case 'm':
                    //loc_105970: Maximum number of threads in the thread pool (8).
                    UsbdiGlobals.Data_0xdc.maximum = atoi(optarg);
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

    int r2 = usbdi_init_server_globals(usb_prefix, &usb_timer);
    if (r2 != 0)
    {
        fprintf(stderr, "usbdi_init_server_globals %d\n", r2);
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


static int nonblockevent(message_context_t *ctp, int code, unsigned flags, void *handle);


/* 0x00115dec - todo */
int usbdi_init_server_globals(char* r5, struct USB_Timer* r6)
{
#if 0
    fprintf(stderr, "usbdi_init_server_globals\n");
#endif

    int r4;
    ino64_t inode; //sp_0x98; //TODO
    resmgr_attr_t sp_0x78;
    struct stat sp_0x30;
    pthread_mutexattr_t sp_0x10;

    if (stat(r5, &sp_0x30) != -1)
    {
        fprintf(stderr, "io-usb already attached to %s\n", r5);
        //->loc_1160f8
        r4 = 16;
        return r4;
    }
    //loc_115e2c
    pthread_mutexattr_init(&sp_0x10);
    pthread_mutexattr_setrecursive(&sp_0x10, 2);
    r4 = pthread_mutex_init(&UsbdiGlobals.Data_0, &sp_0x10);

    if (r4 != 0)
    {
        if (r4 == 16)
        {
            r4 = 0;
        }
        return r4;
    }
    //loc_115e68
    r4 = usbdi_memchunk_init(&Data_11ddf4, 8, &UsbdiGlobals.Data_8, 0);
    if (r4 != 0)
    {
        return r4;
    }

    r4 = usbdi_memchunk_init(&Data_11ddf4, 8, &UsbdiGlobals.Data_0xc, 1);
    if (r4 != 0)
    {
        return r4;
    }

    UsbdiGlobals.Data_0x24 = 0;
    UsbdiGlobals.Data_0x28 = &UsbdiGlobals.Data_0x24;

    iofunc_attr_init(&UsbdiGlobals.iofunc_attr, 0x21a4, 0, 0);

    UsbdiGlobals.Data_0x4c.flags = 0x100;
    UsbdiGlobals.Data_0x4c.conf = 3;
    UsbdiGlobals.Data_0x4c.blocksize = 1;
    UsbdiGlobals.Data_0x4c.funcs = &ResmgrOCBFuncs;
    UsbdiGlobals.iofunc_attr.mount = &UsbdiGlobals.Data_0x4c;

    UsbdiGlobals.dpp = dispatch_create();

    if (UsbdiGlobals.dpp == 0)
    {
        r4 = errno;
        return r4;
    }
    //loc_115f14
#if 1
    memset(&sp_0x78, 0, sizeof(sp_0x78));
#else
    sp_0x78.flags = 0;
    sp_0x78.other_func = 0;
    sp_0x78.reserved[0] = 0;
    sp_0x78.reserved[1] = 0;
    sp_0x78.reserved[2] = 0;
    sp_0x78.reserved[3] = 0;
#endif

    sp_0x78.nparts_max = 0x41;
    sp_0x78.msg_max_size = 0x2214;

    resmgr_attach(UsbdiGlobals.dpp,
        &sp_0x78,
        0,
        0x0b,
        0x100,
        &ResmgrCFuncs,
        0,
        0);

    UsbdiGlobals.resmgr_attr.nparts_max = 0x41;

    UsbdiGlobals.Data_0xdc.handle = UsbdiGlobals.dpp;
    UsbdiGlobals.Data_0xdc.context_alloc = dispatch_context_alloc;
    UsbdiGlobals.Data_0xdc.context_free = dispatch_context_free;
    UsbdiGlobals.Data_0xdc.block_func = dispatch_block;
    UsbdiGlobals.Data_0xdc.handler_func = dispatch_handler;
    UsbdiGlobals.Data_0xdc.tid_name = "usb_resmgr";
    UsbdiGlobals.Data_0xdc.attr = &UsbdiGlobals.Data_0x120;

    pthread_attr_init(&UsbdiGlobals.Data_0x120);
    pthread_attr_setdetachstate(&UsbdiGlobals.Data_0x120, 1);
    pthread_attr_setstacksize(&UsbdiGlobals.Data_0x120, 0x4000);

    UsbdiGlobals.Data_0x30 = resmgr_attach(UsbdiGlobals.dpp,
        &UsbdiGlobals.resmgr_attr,
        r5,
        0x0b,
        0x300,
        &ResmgrCFuncs,
        &ResmgrIOFuncs,
        &UsbdiGlobals.iofunc_attr);

    if (UsbdiGlobals.Data_0x30 == -1)
    {
        r4 = errno;
        return r4;
    }
    //loc_116030
    resmgr_devino(UsbdiGlobals.Data_0x30, &UsbdiGlobals.Data_0x4c.dev, &inode);

    UsbdiGlobals.Data_0xb8 = UsbdiGlobals.Data_0x4c.dev;
    UsbdiGlobals.iofunc_attr.inode = inode; //TODO: only 32bit

    UsbdiGlobals.Data_0x2c = message_connect(UsbdiGlobals.dpp, 0x200);

    if (UsbdiGlobals.Data_0x2c == -1)
    {
        r4 = errno;
        return r4;
    }
    //loc_116078
    r4 = usbdi_timeout_init(r6);
    if (r4 != 0)
    {
        return r4;
    }

    UsbdiGlobals.Data_0x34 = pulse_attach(UsbdiGlobals.dpp, 
        2, 0, nonblockevent, 0);

    if (UsbdiGlobals.Data_0x34 == -1)
    {
        r4 = errno;
        return r4;
    }
    //loc_1160bc
    UsbdiGlobals.Data_0x20 = thread_pool_create(&UsbdiGlobals.Data_0xdc, 0);
    
    if (UsbdiGlobals.Data_0x20 == 0)
    {
        r4 = errno;
        return r4;
    }
    //loc_1160e4
    if (thread_pool_start(UsbdiGlobals.Data_0x20) == -1)
    {
        r4 = errno;
        return r4;
    }
    //loc_1160f8
    return 0;
}


/* 116120 - todo */
static int nonblockevent(message_context_t *ctp, int code, unsigned flags, void *handle)
{
#if 1
    fprintf(stderr, "nonblockevent\n");
#endif

}


