
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>
#include <atomic.h>
#include <sys/usbdi.h>
#include "usbdi_priv.h"



/* 0x00008d08 - todo */
int usbd_io(struct usbd_urb *urb/*r5*/, 
        struct usbd_pipe *pipe/*r7*/, 
        void (*func)(struct usbd_urb *, struct usbd_pipe *, void *)/*sl*/, 
        void *handle/*sb*/, 
        _Uint32t timeout)
{
#if 0
    fprintf(stderr, "usbd_io: TODO!!!\n");
#endif

    struct
    {
        struct Struct_5a24_d1 Data_0; //0
        int Data_4; //4
        int Data_8; //8
        int fill_0xc[24]; //0xc
        //0x6c
    } sp4;

    int res; //r8
    int r4;
    struct usbd_device* r6 = pipe->Data_8;

    if ((r6->Data_8->Data_0x34 == -1) && 
        (pipe->bData_0x14 != 0))
    {
        return 9; //->loc_8e98
    }
    //loc_8d34
    r4 = 0;
    struct usbd_urb *r3 = urb;

    while (r3 != NULL)
    {
        //loc_8d60
        r4++;
        r3 = r3->Data_4;
    }

    if (r4 > 64)
    {
        return 0x1f; //->loc_8e98
    }
    //loc_8d7c
    res = usbdi_synchronise(r6, 1, r4);
    if (res != 0)
    {
        return res;
    }
    //0x00008d94
    urb->Data_0x3c = 0;
    urb->Data_0x50 = 0;
    urb->bData_0x28 = r6->Data_0x1c.path;
    urb->bData_0x29 = r6->Data_0x1c.devno;
    urb->wData_0x2a = r6->Data_0x1c.generation;
    urb->Data_0x2c = r6->Data_0x1c.config;
    urb->Data_0x30 = r6->Data_0x1c.iface;
    urb->Data_0x34 = r6->Data_0x1c.alternate;
    urb->Data_0x38 = pipe->bData_0x14;
    urb->Data_0x40 = timeout;
    urb->Data_0x10 = pipe;
    urb->Data_0x18 = handle;
    urb->Data_0x1c = func;
    if (func == NULL)
    {
        urb->Data_0x24 |= 0x40000;
    }
    else
    {
        urb->Data_0x24 &= ~0x40000;
    }

    if (pipe->bData_0x14 == 0)
    {
        //0x00008e14
        urb->Data_0x24 |= 0xc0000;

        sp4.Data_0.wData_2 = 0x6c;

        res = usbdi_sendcmd(r6->Data_8->Data_0x30, 5, urb, &sp4);

        urb->Data_0x3c = sp4.Data_4;
        urb->Data_0x50 = sp4.Data_8;

        usbdi_synchronise(r6, 1, -r4);
    }
    else
    {
        //loc_8e68
        res = usbdi_sendcmd(r6->Data_8->Data_0x30, 5, urb, NULL);
        if (res != 0)
        {
            //0x00008e88
            usbdi_synchronise(r6, 1, -r4);
        }
    }
    //loc_8e98
    return res;
}


/* 0x00008f70 - todo */
paddr_t usbd_mphys_cached(const void *ptr)
{
    paddr_t paddr = usbdi_memchunk_mphys(Data_b698.Data_0xc, ptr);

#if 1
    fprintf(stderr, "usbd_mphys_cached: ptr=%p -> paddr=%p\n", ptr, paddr);
#endif

    return paddr;
}


/* 0x00008f9c - todo */
paddr_t usbd_mphys(const void *ptr)
{
    paddr_t paddr = usbdi_memchunk_mphys(Data_b698.Data_8, ptr);

#if 1
    fprintf(stderr, "usbd_mphys(client): ptr=%p -> paddr=%p\n", ptr, paddr);
#endif

    return paddr;
}


/* 0x00009324 - todo */
void* usbd_alloc(size_t size)
{
#if 1
    fprintf(stderr, "usbd_alloc(client): size=%d\n", size);
#endif

    return usbdi_memchunk_malloc(Data_b698.Data_8, size);
}



/* 0x00008f10 - todo */
void usbd_free(void *ptr)
{
#if 1
    fprintf(stderr, "usbd_free(client): ptr=%p: TODO!!!\n", ptr);
#endif

    usbdi_memchunk_free(Data_b698.Data_8, ptr);
}


