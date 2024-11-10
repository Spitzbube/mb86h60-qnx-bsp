

#include "externs.h"

extern int usbdi_memchunk_init();
extern void* usbdi_memchunk_calloc(int a, int b, int c);
extern void usbdi_memchunk_free(int, void*);

extern void usbdi_client_destroy();

extern int Data_11ddf4; //11ddf4

extern const resmgr_io_funcs_t ResmgrIOFuncs; //0x11f404
extern const iofunc_funcs_t ResmgrOCBFuncs; //0x0011f470
extern const resmgr_connect_funcs_t ResmgrCFuncs; //0x0011f488


/* 0x001155f4 - complete */
void usbdi_ocb_free(IOFUNC_OCB_T *ocb)
{
#if 0
    fprintf(stderr, "usbdi_ocb_free\n");
#endif

    usbdi_memchunk_free(UsbdiGlobals.Data_0xc, ocb);
}


/* 0x00115610 - todo */
IOFUNC_OCB_T* usbdi_ocb_calloc(resmgr_context_t *ctp,
                     iofunc_attr_t *attr)
{
#if 1
    fprintf(stderr, "usbdi_ocb_calloc: sizeof(iofunc_ocb_t)=%d / %d TODO!!!\n",
        sizeof(IOFUNC_OCB_T), 28);
#endif

    IOFUNC_OCB_T* ocb = usbdi_memchunk_calloc(UsbdiGlobals.Data_0xc, 1, 
                    sizeof(*ocb)/*28*/);

    if (ocb == 0)
    {
        errno = 23;
    }

    return ocb;
}



/* 0x00115b70 - complete */
int _iofunc_callout(int (*func)(), 
        resmgr_context_t *ctp, io_stat_t *msg, iofunc_ocb_t *ocb)
{
#if 0
    fprintf(stderr, "_iofunc_callout\n");
#endif

    int res = iofunc_attr_lock(ocb->attr);
    if (res == 0)
    {
        res = (func)(ctp, msg, ocb);

        iofunc_attr_unlock(ocb->attr);
    }

    return res;
}



/* 0x00115c80 - complete */
int usbdi_resmgr_stat(resmgr_context_t *ctp, io_stat_t *msg, iofunc_ocb_t *ocb)
{
#if 1
    fprintf(stderr, "usbdi_resmgr_stat\n");
#endif

    return _iofunc_callout(iofunc_stat_default, ctp, msg, ocb);
}



/* 0x00115d34 - todo */
int usbdi_resmgr_open(resmgr_context_t *ctp, io_open_t *msg,
                      RESMGR_HANDLE_T *handle, void *extra)
{
#if 1
    fprintf(stderr, "usbdi_resmgr_open\n");
#endif

    int r4;
    IOFUNC_OCB_T* ocb;

    if (msg->connect.extra_type != 0)
    {
        return 0x59;
    }

    r4 = iofunc_attr_lock(&UsbdiGlobals.iofunc_attr);
    if (r4 == 0)
    {
        r4 = iofunc_open(ctp, msg, &UsbdiGlobals.iofunc_attr, 0, 0);
        if (r4 == 0)
        {
            ocb = usbdi_ocb_calloc(ctp, &UsbdiGlobals.iofunc_attr);
            if (ocb != NULL)
            {
                r4 = iofunc_ocb_attach(ctp, msg, &ocb->hdr, 
                        &UsbdiGlobals.iofunc_attr, &ResmgrIOFuncs);

                if (r4 == 0)
                {
                    iofunc_attr_unlock(&UsbdiGlobals.iofunc_attr);

                    return r4;
                }

                usbdi_ocb_free(ocb);
            }

        }

        iofunc_attr_unlock(&UsbdiGlobals.iofunc_attr);
    }

    return r4;
}


/* 0x00115ce8 - complete */
int usbdi_resmgr_close(resmgr_context_t *ctp, void *reserved, IOFUNC_OCB_T *ocb)
{
#if 1
    fprintf(stderr, "usbdi_resmgr_close\n");
#endif

    iofunc_attr_t* r5 = ocb->hdr.attr;

    iofunc_attr_lock(r5);

    iofunc_ocb_detach(ctp, &ocb->hdr);

    if (ocb->Data_0x18 != 0)
    {
        usbdi_client_destroy(ocb->Data_0x18);
    }

    usbdi_ocb_free(ocb);
    iofunc_attr_unlock(r5);

    return 0;
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


