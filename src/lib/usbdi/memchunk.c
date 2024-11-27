
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>
#include <atomic.h>
#include <sys/syspage.h>
#include <sys/usbdi.h>
#include "usbdi_priv.h"



/* 0x00006140 - todo */
int usbdi_memchunk_init(uint32_t* sp4, int sb, int* sp_0x14, int r5_)
{
#if 0
    fprintf(stderr, "usbdi_memchunk_init\n");
#endif

    int res; //sp_0x10;
    int r6;
    int r4 = sb * 12  + 0x24;

    struct USB_Memchunk* r7 = malloc(r4);
    
    if (r7 == NULL)
    {
        res = 12;
        goto loc_114f00;
    }

    res = pthread_mutex_init(&r7->mutex, 0);
    if (res == 0)
    {
        //0x00114c7c
        r7->Data_8 = sysconf(_SC_PAGE_SIZE);
        if (r7->Data_8 == -1)
        {
            //0x00114c90
            r7->Data_8 = _SYSPAGE_ENTRY(_syspage_ptr,system_private)->pagesize;
        }
        //loc_114cac
        int r3 = 0;
        if (r5_ == 0)
        {
            //0x00114cb8
            struct cacheattr_entry* cacheattr = _SYSPAGE_ENTRY(_syspage_ptr,cacheattr);
            int cache = _SYSPAGE_ENTRY(_syspage_ptr,cpuinfo)->data_cache;
            while (cache != CACHE_LIST_END)
            {
                if ((cacheattr[cache].flags & CACHE_FLAG_SNOOPED) == 0)
                {
                    break;
                }
                cache = cacheattr[cache].next;
            }
            //->loc_114d10
            r3 = 0x800;
        }
        //loc_114d14
        r7->Data_0xc = r3;
        r7->Data_0x14 = r4;
        r7->Data_0x10 = 0;

        uint32_t sp = r7->Data_8 - 0x10;
        int r5_ = 0;

        for (r6 = 0; r6 < sb; r6++)
        {
            //loc_114d5c
            uint32_t r5 = sp4[r6];
            if (r5 < 8)
            {
                r5 = 8;
            }

            r5 = ((r5 + 3) & ~0x03) + 4;

            for (r4 = 0; r4 < r6; r4++)
            {
                //loc_114d8c
                if ((r5 != 0) && (r5 < r7->Data_0x18[r4].wData_0))
                {
                    //0x00114da0
                    memmove(&r7->Data_0x18[r4 + 1], &r7->Data_0x18[r4], (r6 - r4) * 12);
                    //->loc_114ddc
                    break;
                }
                //loc_114dcc
            } //for (r4 = 0; r4 < r6 r4++)
            //loc_114ddc
            r7->Data_0x18[r4].wData_0 = r5;
            r7->Data_0x18[r4].wData_2 = (sp <= r5)? 1: sp / r5;

            if (Data_b698.Data_0x14 & 0x02)
            {
                r7->Data_0x18[r4].wData_2 = 1;
            }

            r7->Data_0x18[r4].Data_4 = 0; //r8
            r7->Data_0x18[r4].Data_8 = 0; //r8

            r5_ = sb;
        } //for (r6 = 0; r6 < sb; r6++)
        //0x00114e58
        while (--r5_ > 0)
        {
            //loc_114e84
            if ((r7->Data_0x18[r5_].wData_0 - r7->Data_0x18[r5_ - 1].wData_0) <= 7)
            {
                //0x00114e98
                memmove(&r7->Data_0x18[r5_ - 1], 
                    &r7->Data_0x18[r5_], 
                    (sb-- - r5_) * 12);
            }
            //loc_114ec0
        } //while (--r5_ > 0)

        r7->Data_0x18[sb].wData_2 = 0;
        r7->Data_0x18[sb].wData_0 = 0; 
        r7->Data_0x18[sb].Data_8 = 0; 

        *sp_0x14 = r7;
        //->loc_114f0c
    }
    else
    {
        //loc_114ef8
        free(r7);
        //loc_114f00
loc_114f00:            
        *sp_0x14 = 0;
    }
    //loc_114f0c
    return res;
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


