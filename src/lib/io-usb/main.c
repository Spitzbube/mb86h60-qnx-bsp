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


#include "externs.h"

extern void* io_usb_dlopen(char*, int);
extern void* io_usb_dlsym(void*, char*);
extern int usbdi_io_mount(resmgr_context_t *ctp, io_mount_t *msg,
                      RESMGR_HANDLE_T *handle,
                      io_mount_extra_t *extra);
extern IOFUNC_OCB_T* usbdi_ocb_calloc(resmgr_context_t *ctp,
                     iofunc_attr_t *attr);
extern void usbdi_ocb_free(IOFUNC_OCB_T *ocb);
extern int usbdi_resmgr_open(resmgr_context_t *ctp, io_open_t *msg,
                      RESMGR_HANDLE_T *handle, void *extra);
extern int usbdi_resmgr_close(resmgr_context_t *ctp, void *reserved, IOFUNC_OCB_T *ocb);
extern int usbdi_resmgr_stat(resmgr_context_t *ctp, io_stat_t *msg, iofunc_ocb_t *ocb);
extern int usbdi_resmgr_devctl();
extern int usbdi_resmgr_unblock();
extern int usbdi_resmgr_pathconf();
extern int usbdi_resmgr_chmod();
extern int usbdi_resmgr_chown();
extern int usbdi_resmgr_utime();
extern int usbdi_resmgr_msg();
extern int udi_memory_info(uint32_t*);
extern void hub_start_driver(int argc, char* const argv[]);
extern void udi_start_driver(int argc, char* const argv[]);
extern void udi_transfer_done();
extern void udi_insertion();
extern void udi_removal();
extern int USBDRIV_Main(int argc, char* const argv[]);
extern struct ArrayClass* CLASS_RegisterDriver(struct Struct_10acec*);
extern int INIT_HCDClassInterface();
extern void stop_controllers();
extern void usb_port_monitor_start();
extern int CTRL_IsPCIDevice();
extern int usbdi_timeout_init(struct USB_Timer*);
extern int usbdi_init_server_globals(char*, struct USB_Timer*);
extern void usbdi_timeout_tick();
extern int io_usb_dlclose(void* handle);
extern void CTRL_FreeHCEntry(int);
extern void CTRL_StripArgs(char*);



extern int Data_11c6d0; //11c6d0
extern int Data_11ddf4; //11ddf4
extern int _iou_ex; //0x0011f3a4 
const resmgr_io_funcs_t ResmgrIOFuncs = //0x11f404
{
    26,
    0, //read
    0, //write
    usbdi_resmgr_close,
    usbdi_resmgr_stat,
    0,
    usbdi_resmgr_devctl,
    usbdi_resmgr_unblock,
    usbdi_resmgr_pathconf,
    0,
    usbdi_resmgr_chmod,
    usbdi_resmgr_chown,
    usbdi_resmgr_utime,
    0, 0, 0, 0, 0, 0,
    usbdi_resmgr_msg,
    0, 0, 0, 0, 0, 0, 0
};

const iofunc_funcs_t ResmgrOCBFuncs = //0x0011f470
{
    5,
    usbdi_ocb_calloc,
    usbdi_ocb_free,
    0, 0, 0
};

const resmgr_connect_funcs_t ResmgrCFuncs = //0x0011f488
{
    8,
    usbdi_resmgr_open,
    0, 0, 0, 0, 0, 0,
    usbdi_io_mount
};

extern struct USB_Controller usb_controllers[20]; //0x0011f590 +0x14*0x8c
extern pthread_mutex_t usb_mmutex; //0x120210
extern int usb_coid; //0x00121578
extern int usb_priority; //0x0012157c
extern int usb_chid; //0x00121580
extern int usb_dflt_timeout; //0x00121584
extern char* usb_prefix; //0x0012158c
struct USB_Timer usb_timer; //121590
extern int usb_verbosity; //0x001215a0
extern struct UdiCtrl UdiCtrl; //0x001215a4




/* 0x001052ac - complete */
int usb_slogf(int opcode, int severity, int v,
        const char* fmt, ...)
{
    int res;

    if (usb_verbosity < v)
    {
        return 0;
    }

    va_list arglist;

    va_start(arglist, fmt);
#if 0
    res = vslogf(opcode, severity, fmt, arglist);
#else
    res = vfprintf(stderr, fmt, arglist);
    fprintf(stderr, "\n");
#endif
    va_end( arglist );
    return res;
}



/* 0x001034f0 - complete */
struct USB_Controller* CTRL_HCLookup(uint32_t a)
{
#if 0
    fprintf(stderr, "CTRL_HCLookup: TODO\n");
#endif

    if ((a < 20) && (ausb_controllers[a] != 0))
    {
        return &usb_controllers[a];
    }

    return 0;
}


/* 0x0010356c - complete */
struct USB_Controller* CTRL_GetHCEntry()
{
#if 0
    fprintf(stderr, "CTRL_GetHCEntry\n");
#endif

    int i;
    struct USB_Controller* pController = NULL;

    for (i = 0; i < 20; i++)
    {
        if (ausb_controllers[i] == 0)
        {
            pController = &usb_controllers[i];

            memset(pController, 0, sizeof(struct USB_Controller));

            pController->Data_8 = i;

            ausb_controllers[i] = pController;

            pController->Data_0x7c = calloc(1, 20 * sizeof(struct USB_Controller_Inner_0x7c));
            if (pController->Data_0x7c == 0)
            {
                pController = NULL;
                break;
            }

            pController->Data_0x78 = calloc(1, 20*4);
            if (pController->Data_0x78 == 0)
            {
                free(pController->Data_0x78);
                pController = NULL;
                break;
            }

            break;
        }
    }

    return pController;
}


char* const io_usb_opts[] = 
{
    "ioport",
    "irq",
    "pindex",
    "priority",
    "bmstr",
    "vid",
    "did",
    "ports",
    NULL
};


/* 0x00103620 - todo */
int CTRL_GetOptions(char* a, 
    int32_t* sp4,
    unsigned long long* sp8, 
    uint32_t* sp_0xc,
    int32_t* sp_0x50,
    uint32_t* sp_0x54,
    uint16_t* sp_0x58,
    uint16_t* sp_0x5c,
    char r5[] /*sp_0x60*/)
{
#if 0
    fprintf(stderr, "CTRL_GetOptions\n");
#endif

    char* sp_0x24;
    char* sp_0x20;
    char* sp_0x1c;
    char* sp_0x10;

    if (a != 0)
    {
        sp_0x20 = sp_0x10 = strdup(a);
        //->loc_103888
        while ((sp_0x20 != 0) && (sp_0x20[0] != 0))
        {
            //loc_10366c
            switch (getsubopt(&sp_0x20, io_usb_opts, &sp_0x24))
            {
                case 0: //"ioport"
                    //0x001036a8
                    if (sp_0x24 != 0)
                    {
                        *sp8 = strtoull(sp_0x24, &sp_0x1c, 0);

                        if (sp_0x1c[0] != 0)
                        {
                            slogf(12, 2, "io-usb - error parsing ioport, expected value, got \"%s\"", sp_0x24);
                        }
                    }
                    break;

                case 1: //"irq"
                    //0x001036f4
                    if (sp_0x24 != 0)
                    {
                        *sp_0xc = strtoul(sp_0x24, 0, 0);

                    }
                    break;

                case 2: //"pindex"
                    //0x00103718
                    if (sp_0x24 != 0)
                    {
                        *sp4 = strtol(sp_0x24, 0, 0);

                    }
                    break;

                case 3: //"priority"
                    //0x0010373c
                    if (sp_0x24 != 0)
                    {
                        *sp_0x50 = strtol(sp_0x24, 0, 0);
                    }
                    break;

                case 4: //"bmstr"
                    //0x00103760
                    if (sp_0x24 != 0)
                    {
                        *sp_0x54 = strtoul(sp_0x24, 0, 0);
                    }
                    break;

                case 5: //"vid"
                    //0x00103784
                    if (sp_0x24 != 0)
                    {
                        *sp_0x58 = strtoul(sp_0x24, 0, 0);
                    }
                    break;                

                case 6: //"did"
                    //0x001037a8
                    if (sp_0x24 != 0)
                    {
                        *sp_0x5c = strtoul(sp_0x24, 0, 0);
                    }
                    break;                

                case 7: //"ports"
                    //0x001037cc
                    if (sp_0x24 != 0)
                    {
                        char* r0 = strtok(sp_0x24, ":");
                        if (r0 == 0)
                        {
                            slogf(12, 2, "io-usb: no ports specified?");
                        }
                        else
                        {
                            //loc_1037fc
                            r5[0] = atoi(r0);

                            int r4;
                            int r3;
                            int r2;

                            for (r4 = 1; r4 < 16; /*r4++*/)
                            {
                                //loc_103814
                                r0 = strtok(0, ":");
                                if (r0 == 0)
                                {
                                    //->loc_103888
                                    break;
                                }

                                r3 = atoi(r0);

                                int found = 0;
                                for (r2 = 0; r2 < r4; r2++)
                                {
                                    //loc_10384c
                                    if (r3 == r5[r2])
                                    {
                                        //loc_103858
                                        slogf(12, 2, "io-usb: port %d already specified, ignoring..", r3);
                                        //->loc_103814
                                        found = 1;
                                        break;
                                    }
                                    //loc_10386c
                                }
                                //loc_103878
                                if (!found)
                                {
                                    r5[r4] = r3;
                                    r4++;
                                }
                            }              
                            //loc_103888          
                        }
                    }
                    break;                

                default:
                    //loc_103888
                    break;
            }
        }
        //loc_1038a0
        free(sp_0x10);
    }
    //loc_1038a8
    return 0;
}


/* 0x001038dc - complete */
int CTRL_ProcessArgs(struct UsbdiGlobals_Inner_0x178* sp4, char* r5)
{
#if 0
    fprintf(stderr, "CTRL_ProcessArgs\n");
#endif

    int i;

    if ((r5 != 0) && (r5[0] != 0))
    {
        for (i = 0; (i < 10) && (r5 != 0); i++)
        {
            //loc_103924
            char* r4;
            
            if (((r4 = strstr(r5, "ioport")) == 0) &&
                ((r4 = strstr(r5, "pindex")) == 0))
            {
                //->loc_1039e8
                break;
            }
            //loc_10394c
            char* r8 = r4 + 1;

            if (((r5 = strstr(r8, "ioport")) != 0) ||
                ((r5 = strstr(r8, "pindex")) != 0))
            {
                //loc_103978
                r5[-1] = 0;
            }
            //loc_10397c
            if ((r4[0] == 'i') && (strstr(r4, "irq") == 0))
            {
                fwrite("Must specify irq with ioport option", 1, 0x23, stderr);

                return -1;
            }
            //loc_1039c0
            sp4->args[i] = r4;
        }
        //loc_1039e8
        sp4->Data_0x20 = i;
    }
    //loc_1039f8
    return 0;
}


static void* usb_interrupt_handler(void*);


/* 0x00103a90 - todo */
int CTRL_InitializeController(struct UsbdiGlobals_Inner_0x178 *r5,
        struct USB_Controller *r4,
        char* r7,
        int r6)
{
#if 0
    fprintf(stderr, "CTRL_InitializeController\n");
#endif

    pthread_attr_t sp_0x44;
    struct sched_param sp_0x1c;
    struct sigevent sp_0xc;

    if (((r4->chid = ChannelCreate(0x0a)) == -1) ||
        ((r4->coid = ConnectAttach(0, 0, r4->chid, 0x40000000, 0)) == -1))
    {
        fprintf(stderr, "Unable to attach channel and connection 0x%x\n", errno);

        return -1;
    }
    //loc_103b04
    sp_0xc.sigev_notify = 4;
    sp_0xc.sigev_coid = r4->coid;
    sp_0xc.sigev_code = 0;
    sp_0xc.sigev_priority = r6;
    sp_0xc.sigev_value.sival_int = 0;

    pthread_attr_init(&sp_0x44);
    pthread_attr_setschedpolicy(&sp_0x44, 2);

    sp_0x1c.sched_priority = 0x15;

    pthread_attr_setschedparam(&sp_0x44, &sp_0x1c);
    pthread_attr_setinheritsched(&sp_0x44, 2);
    pthread_attr_setdetachstate(&sp_0x44, 1);
    pthread_attr_setstacksize(&sp_0x44, 0x4000);

    r4->controller_methods = r5->pDllEntry->controller_methods;
    r4->ctrl_pipe_methods = r5->pDllEntry->ctrl_pipe_methods;
    r4->int_pipe_methods = r5->pDllEntry->int_pipe_methods;
    r4->bulk_pipe_methods = r5->pDllEntry->bulk_pipe_methods;
    r4->isoch_pipe_methods = r5->pDllEntry->isoch_pipe_methods;

    if (pthread_mutex_init(&r4->Data_0x24, 0) == -1)
    {
        fwrite("CTRL_InitializeController:  Unable to initialize hc mutex\n", 1, 0x3a, stderr);

        return -1;
    }
    //loc_103be8
    if (r4->controller_methods->Data_0x18 != 0)
    {
        //0x00103bf8
        int intr = r4->Data_4->bData_0x14[0] | 
            (r4->Data_4->bData_0x14[1] << 8) |
            (r4->Data_4->bData_0x14[2] << 16) |
            (r4->Data_4->bData_0x14[3] << 24);

        r4->Data_0x20 = InterruptAttachEvent(intr, &sp_0xc, 8);
        if (r4->Data_0x20 == -1)
        {
            fwrite("InterruptAttachEvent failed\n", 1, 0x1c, stderr);

            return -1;
        }
        //loc_103c54
        if ((r5->pDllEntry->controller_methods->controller_init)(r4, 0, r7) != 0)
        {
            slogf(12, 2, " Error Initializing Host Controller");

            InterruptDetach(r4->Data_0x20);

            return -1;
        }
        //loc_103c9c
    }
    else
    {
        //loc_103ce0
        if ((r5->pDllEntry->controller_methods->controller_init)(r4, 0, r7) != 0)
        {
            slogf(12, 2, " Error Initializing Host Controller");

            InterruptDetach(r4->Data_0x20);

            return -1;
        }
        //loc_103d28
        return 0;
    }
    //loc_103c9c
    if (pthread_create(&r4->Data_0x14, &sp_0x44, usb_interrupt_handler, r4) != 0)
    {
        fwrite("Unable to create controller interrupt thread\n", 1, 0x2d, stderr);

        return -1;
    }
    //loc_103d28
    return 0;
}


/* 0x00103d34 - todo */
int CTRL_RegisterControllerType(struct UsbdiGlobals_Inner_0x178* sp_0x20,
        int sp_0x28, char* c)
{
#if 0
    fprintf(stderr, "CTRL_RegisterControllerType\n");
#endif

    struct USB_Controller_Inner4* r4;

    unsigned long long sp_0xb0;
    uint8_t sp_0xac[4];
    int sp_0xa8;
    int sp_0xa4;
    uint32_t sp_0xa0 = 0;
    char sp_0x90[16];

    sp_0x20->Data_0x20 = 10;

    if (CTRL_ProcessArgs(sp_0x20, c) != 0)
    {
        return -1;
    }

    r4 = calloc(1, 0xf0);

    //sp_0x18 = sp_0x20;
    //r6 = 0;
    //sp_0x24 = 0;
    //sp_0x1c = 0;
    //fp = 0;
    //r8 = 0;
    //sp_0x2c = 0xffffea9f = -0x1561

    int sp_0x1c;

    for (sp_0x1c = 0; sp_0x1c < sp_0x20->Data_0x20; sp_0x1c++)
    {
        //loc_103dac
        sp_0xa4 = 0x15;
        Data_12021c = 0; //fp

        memset(r4, 0xff, 0xf0);
        memset(&sp_0x90[0], 0xff, 16);

        char* r5 = sp_0x20->args[sp_0x1c];

        if (CTRL_IsPCIDevice(r5, &sp_0xa8) != 0)
        {
            //0x00103e00

            //TODO!!!

            //->loc_104314
        }
        else
        {
            //loc_1041e4
#if 0
int CTRL_GetOptions(char* a, 
    int32_t* sp4,
    unsigned long long* sp8, 
    uint32_t* sp_0xc,
    int32_t* sp_0x50,
    uint32_t* sp_0x54,
    uint16_t* sp_0x58,
    uint16_t* sp_0x5c,
    char r5[] /*sp_0x60*/)
#endif            
            CTRL_GetOptions(sp_0x20->args/*r5*/, 
                &sp_0xa8, 
                &sp_0xb0, 
                &sp_0xac[0],
                &sp_0xa4, 
                &sp_0xa0, 
                &r4->wData_2,
                &r4->wData_0, 
                &sp_0x90[0]);

            r4->Data_0x68 = sp_0xb0;
            r4->Data_0x88 = sp_0xb0;

            r4->bData_0x98 = 0;
            r4->bData_0x99 = 0x10;
            r4->bData_0x9a = 0;
            r4->bData_0x9b = 0;

            r4->bData_0xa8 = 0;
            r4->bData_0xa9 = 0x10;
            r4->bData_0xaa = 0;
            r4->bData_0xab = 0;

            r4->bData_0x14[0] = sp_0xac[0];
            r4->bData_0x14[1] = sp_0xac[1];
            r4->bData_0x14[2] = sp_0xac[2];
            r4->bData_0x14[3] = sp_0xac[3];

            r4->bData_0x30 = sp_0xa0 & 0xff;
            r4->bData_0x31 = (sp_0xa0 >> 8) & 0xff;
            r4->bData_0x32 = (sp_0xa0 >> 16) & 0xff;
            r4->bData_0x33 = (sp_0xa0 >> 24) & 0xff;

            r4->bData_0x34 = 0;
            r4->bData_0x35 = 0;
            r4->bData_0x36 = 0;
            r4->bData_0x37 = 0;
        }
        //loc_104314
        if ((Data_12021c != 0) || 
            (/*sp_0x18*/sp_0x20->args[sp_0x1c] != 0))
        {
            //loc_104338
            struct USB_Controller* r7 = CTRL_GetHCEntry();
            if (r7 == NULL)
            {
                free(r4);

                return -1;
            }
            //loc_104354
            r7->Data_0x18 = Data_12021c;
            r7->Data_0x80 = sp_0x20;
            r7->Data_4 = r4;
            r7->Data_0x70 = 0;

            CTRL_StripArgs(/*sp_0x18*/sp_0x20->args[sp_0x1c]);

            if (CTRL_InitializeController(sp_0x20, 
                r7, 
                /*sp_0x18*/sp_0x20->args[sp_0x1c],
                sp_0xa4) != 0)
            {
                if (r7->Data_0x18 != 0)
                {
                    pci_detach_device(Data_12021c);
                }
                //loc_1043bc
                CTRL_FreeHCEntry(r7->Data_8);

                return -1;
            }
            //loc_1043cc
            if (sp_0x90[0] != -1)
            {
                //loc_104470
                int r4;

                for (r4 = 0; r4 < 16; r4++)
                {
                    //loc_1043e4
                    //TODO!!!

                    fprintf(stderr, "loc_1043e4: %d TODO!!!\n", r4);

                    //loc_104470
                } //for (r4 = 0; r4 < 16; r4++)
                //0x0010447c                
                memcpy(&Data_120220[r7->Data_8].bData_4[0], &sp_0x90[0], 16);
                //->loc_1044f0
            } //if (sp_0x90[0] != 0xff)
            else
            {
                //loc_1044a4
                int r4;

                for (r4 = 0; r4 < 16; r4++)
                {
                    //loc_1044ac
                    Data_120220[r7->Data_8].bData_4[r4] = r4;

                    pthread_mutex_init(&Data_120220[r7->Data_8].Data_0x14[r4].Data_4, 0);
                }
            }
            //loc_1044f0
            sp_0x20->Data_0x24[sp_0x1c] = r7;

            r4 = calloc(1, 0xf0);
        }
        //loc_104508
        //sp_0x18 += 4;
    } //for (sp_0x1c = 0; sp_0x1c < sp_0x20->Data_0x20; sp_0x1c++)
    //loc_104534
    free(r4);

    return 0;    
}


/* 0x00104564 - todo */
void* usb_interrupt_handler(void* a)
{
    int sp_0x40[4]; //TODO!
    iov_t sp_0x38; 
    char sp4[50]; //size???
    struct USB_Controller *r4 = a;

    sprintf(&sp4[0], "irq_handler_%d", r4->Data_8);

    pthread_setname_np(0, &sp4[0]);

    SETIOV(&sp_0x38, &sp_0x40[4], 16);

    while (1)
    {
#if 1
        fprintf(stderr, "usb_interrupt_handler\n");
#endif

        //loc_1045b0       
        if (MsgReceivev(r4->chid, &sp_0x38, 1, 0) == -1) 
        {
            //->loc_1045b0
            continue;
        }
        //0x001045cc
        //TODO!!!        
        fprintf(stderr, "usb_interrupt_handler: 0x001045cc TODO!!!\n");
    }
}


/* 10467c - complete */
struct Struct_10467c* usb_find_key(struct Struct_1047a8* a,
    int b, int c, int d, int e)
{
#if 0
    fprintf(stderr, "usb_find_key: TODO!!!\n");
#endif

    struct Struct_10467c* r0 = a->Data_4;

    while (r0 != NULL)
    {
        //loc_104690
        if ((r0->Data_0x10 == b) &&
            (r0->Data_0x14 == c) &&
            (r0->Data_0x18 == d) &&
            (r0->Data_0x1c == e))
        {
            //->loc_1046cc
            break;
        }
        //loc_1046c0
        r0 = r0->Data_0;
    }
    //loc_1046cc
    return r0;
}


/* 104760 - complete */
int usb_remove_data_key(struct Struct_1047a8* a, struct Struct_10467c* b)
{
#if 0
    fprintf(stderr, "usb_remove_data_key: TODO!!!\n");
#endif

    if (b->Data_0 != NULL)
    {
        b->Data_0->Data_4 = b->Data_4;
    }
    else
    {
        a->Data_8 = b->Data_4;
    }

    int r2 = b->Data_0;
    int* r3 = b->Data_4;
    *r3 = r2;

    if (b->Data_0x20 != NULL)
    {
        free(b->Data_0x20);
    }

    free(b);

    return 0;
}


/* 1047a8 - complete */
int usb_data_store_init(struct Struct_1047a8** a, int b)
{
#if 0
    fprintf(stderr, "usb_data_store_init: TODO!!!\n");
#endif

    struct Struct_1047a8* p = calloc(1, sizeof(struct Struct_1047a8));

    if (p == NULL)
    {
        return 12;
    }

    p->Data_4 = NULL;
    p->Data_8 = &p->Data_4;

    *a = p;

    return 0;
}


/* 1047dc - todo */
int usb_store_data_key(struct Struct_1047a8* r6, 
    int sb, 
    int r7, 
    int r8, 
    int fp, //arg0
    int arg4, //arg4
    void* arg8, //arg8
    int sl) //argc
{
#if 0
    fprintf(stderr, "usb_store_data_key: TODO!!!\n");
#endif

    struct Struct_10467c* r1 = usb_find_key(r6, r7, r8, fp, arg4);
    if (r1 != NULL)
    {
        usb_remove_data_key(r6, r1);
    }
    //loc_104824
    struct
    {
        int Data_0; //0
        struct
        {
            void* Data_0; //0

        }* Data_4; //4
        int Data_8; //8
        int fill_0xc; //12
        int Data_0x10; //0x10
        int Data_0x14; //0x14
        int Data_0x18; //0x18
        int Data_0x1c; //0x1c
        void* Data_0x20; //0x20
        int Data_0x24; //0x24
        //40 = 0x28
    }* r4 = calloc(1, 40);
    if (r4 == NULL)
    {
        return 12;
    }
    //0x0010483c
    void* r5 = malloc(sl);
    if (r5 == NULL)
    {
        free(r4);

        return 12;
    }
    //loc_10485c
    r4->Data_8 = sb;
    r4->Data_0x10 = r7;
    r4->Data_0x14 = r8;
    r4->Data_0x18 = fp;
    r4->Data_0x1c = arg4;

    memcpy(r5, arg8, sl);

    r4->Data_0x20 = r5;
    r4->Data_0x24 = sl;
    r4->Data_0 = 0;
    r4->Data_4 = r6->Data_8;
    r4->Data_4->Data_0 = r4;
    r6->Data_8 = r4;

    return 0;
}


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


/* 0x00105148 - complete */
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


/* 0x001052f0 - todo */
void stop_controllers(void)
{
#if 0
    fprintf(stderr, "stop_controllers\n");
#endif

    int i;

    UsbdiGlobals.Data_0x17c = 1;

    delay(101);

    if (pthread_rwlock_wrlock(&usb_rwlock) != 0)
    {
        usb_slogf(12, 2, 1, "%s: error acquiring wrlock",
            "stop_controllers");
    }

    struct UsbdiGlobals_Inner_0x178* r6 = UsbdiGlobals.Data_0x178;
    while (r6 != 0)
    {
        for (i = 0; i < 10; i++)
        {
            if (r6->Data_0x24[i] != 0)
            {
                if (r6->Data_0x24[i]->controller_methods->controller_shutdown != 0)
                {
                    (r6->Data_0x24[i]->controller_methods->controller_shutdown)();

                    if (r6->Data_0x24[i]->controller_methods->Data_0x18 != 0)
                    {
                        InterruptDetach(r6->Data_0x24[i]->Data_0x20);
                    }

                    pci_detach_device(r6->Data_0x24[i]->Data_0x18);
                }
            }
        }

        r6 = r6->Data_0x78;
    }

    if (pthread_rwlock_unlock(&usb_rwlock) != 0)
    {
        usb_slogf(12, 2, 1, "%s:  error releasing wrlock",
            "stop_controllers");
    }
}


/* 0x00105414 - complete */
void usb_signal_handler(void)
{
#if 0
    fprintf(stderr, "usb_signal_handler\n");
#endif

    siginfo_t info;
    sigset_t set;

    pthread_setname_np(0, "signal_handler");

    sigfillset(&set);
    sigdelset(&set, 0x0f);
    sigprocmask(0, &set, 0);
    sigemptyset(&set);
    sigaddset(&set, 0x0f);

    while (SignalWaitinfo(&set, &info) == -1)
    {
        /* loc_10546c */
    }

    stop_controllers();
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
    usb_enum_priority = 10;

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
                    //loc_10571c: Set type memory name (default non, using sysram)
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
    udi_memory_info(&UsbdiGlobals.Data_0x14);

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


/* 0x00105d70 - todo */
void udi_start_driver(int argc, char* const argv[])
{
#if 0
    fprintf(stderr, "udi_start_driver\n");
#endif

    struct Struct_10acec sp4;
    int opt;

    while ((opt = getopt(argc, argv, "v")) != -1)
    {
        //loc_105d94
        if (opt == 'v')
        {
            UdiCtrl.Data_4++;
        }
    }

    sp4.Data_0 = -1;
    sp4.Data_4 = -1;
    sp4.Data_8 = -1;
    sp4.Data_0x14 = -1;
    sp4.Data_0x18 = udi_transfer_done;
    sp4.on_insertion = udi_insertion;
    sp4.Data_0x20 = udi_removal;

    UdiCtrl.Data_8 = CLASS_RegisterDriver(&sp4);
}



/* 0x00105ea8 - complete */
int udi_memory_info(uint32_t* a)
{
#if 0
    fprintf(stderr, "udi_memory_info\n");
#endif

    struct USB_Controller* p = CTRL_HCLookup(0);
    if (p == NULL)
    {
        return 19;
    }

    *a |= (p->Data_0x6c >> 31);

    return 0;
}

typedef void (*USB_Bind)(int argc, char* const argv[]);
static const USB_Bind usb_bind_list[] = //0x0011c674
{
    hub_start_driver,
    udi_start_driver,
    0
};


/* 0x00109e48 - todo */
int USBDRIV_Main(int argc, char* const argv[])
{
#if 0
    fprintf(stderr, "USBDRIV_Main: TODO\n");
#endif

    if (pthread_mutex_init(&usb_mmutex, 0) == -1)
    {
        fwrite("HW_Init:  Unable to initialize mutex\n", 1, 0x25, stderr);

        return -1;
    }


    const USB_Bind* bind = &usb_bind_list[0];
    while ((*bind) != 0)
    {
        (*bind)(argc, argv);
        bind++;
    }

    if (INIT_HCDClassInterface() != 0)
    {

        fwrite("Error Initializing HCD/Class Interface\n", 1, 0x27, stderr);

        return -1;
    }

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


/* 114b8c - todo */
void* sub_114b8c(int a, void* b)
{
#if 1
    fprintf(stderr, "sub_114b8c: TODO!!!\n");
#endif

    return b;
}


/* 1177f8 - todo */
void usbd_free(void* a)
{
#if 1
    fprintf(stderr, "usbd_free: TODO!!!\n");
#endif

}


/* 117854 - todo */
void* sub_117854(void* a)
{
#if 0
    fprintf(stderr, "sub_117854: TODO!!!\n");
#endif

    return sub_114b8c(UsbdiGlobals.Data_8, a);
}


/* 117bbc - todo */
void* usbd_alloc(size_t size)
{
#if 0
    fprintf(stderr, "usbd_alloc: TODO!!!\n");
#endif

    return usbdi_memchunk_malloc(UsbdiGlobals.Data_8, size);
}


