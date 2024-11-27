
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


int usbd_io(struct usbd_urb *urb, 
        struct usbd_pipe *pipe, 
        void (*func)(struct usbd_urb *, struct usbd_pipe *, void *), 
        void *handle, 
        _Uint32t timeout)
{
#if 1
    fprintf(stderr, "usbd_io: TODO!!!\n");
#endif

    return 0;
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
    fprintf(stderr, "usbd_mphys: ptr=%p -> paddr=%p\n", ptr, paddr);
#endif

    return paddr;
}


