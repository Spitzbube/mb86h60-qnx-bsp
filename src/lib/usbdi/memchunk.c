
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



int usbdi_memchunk_init()
{
    fprintf(stderr, "usbdi_memchunk_init: TODO!!!\n");

    return 0;
}


void usbdi_memchunk_destroy()
{
    fprintf(stderr, "usbdi_memchunk_destroy: TOOD!!!\n");

    
}


void* usbdi_memchunk_malloc(int a, int b)
{
#if 0
    if (b == 0)
    {
        return a + 16;
    }
#else
    fprintf(stderr, "usbdi_memchunk_malloc: %d\n", b);

    return malloc(b);
#endif
}


void usbdi_memchunk_free(int a, void* b)
{
#if 1
    fprintf(stderr, "usbdi_memchunk_free\n");
#endif

}


void* usbdi_memchunk_calloc(int a, int b, int c)
{
    int r5 = b * c;

    void* r4 = usbdi_memchunk_malloc(a, r5);
    if (r4 != NULL)
    {
        memset(r4, 0, r5);
    }

    return r4;
}


/* 0x000060a4 - todo */
paddr_t usbdi_memchunk_mphys(int r5, const void* ptr/*r6*/)
{
#if 1
    fprintf(stderr, "usbdi_memchunk_mphys: TODO!!!\n");
#endif

    return mphys(ptr);
}


