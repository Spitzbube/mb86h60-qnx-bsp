

#include <sys/syspage.h>
#include <sys/rsrcdbmgr.h>
#include "externs.h"


/* 0x00114c28 - todo */
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
#if 1
            fprintf(stderr, "usbdi_memchunk_init: r7->Data_0x18[%d].wData_0=%d, wData_2=%d\n",
                r4, r7->Data_0x18[r4].wData_0, r7->Data_0x18[r4].wData_2);
#endif

            if (UsbdiGlobals.Data_0x14 & 0x02)
            {
                r7->Data_0x18[r4].wData_2 = 1;
            }

            r7->Data_0x18[r4].Data_4 = 0; //r8
            r7->Data_0x18[r4].Data_8 = NULL; //r8

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
        r7->Data_0x18[sb].Data_8 = NULL; 

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


/* 114b5c - complete */
int sub_114b5c(struct USB_Memchunk_Inner_0x18* a,
        struct USB_Memchunk_Inner_0x18_Inner_8* b)
{
#if 0
    fprintf(stderr, "sub_114b5c: TODO!!!\n");
#endif

    struct
    {
        struct USB_Memchunk_Inner_0x18_Inner_8* Data_0; //0

    }* r0 = b->Data_4;
    b->Data_4 = r0->Data_0;
    b->wData_0xc++;
    r0->Data_0 = b;
    a->Data_4--;

    return r0;
}


/* 1169e4 - todo */
int usbdi_get_dma_memory(void* a, int b)
{
#if 1
    fprintf(stderr, "usbdi_get_dma_memory: TODO!!!\n");
#endif

    return 0;
}


/* 1151dc - todo */
void* alloc_resource(int r5, int r3, int* r4)
{
#if 1
    fprintf(stderr, "alloc_resource: r5=%d, r3=0x%x: TODO!!!\n",
        r5, r3);
#endif

#if 1
    fprintf(stderr, "alloc_resource: UsbdiGlobals.Data_0x40=%d, .Data_0x48=%d, .Data_0x14=0x%x\n",
        UsbdiGlobals.Data_0x40, UsbdiGlobals.Data_0x48, UsbdiGlobals.Data_0x14);
#endif

    void* r5_;
    rsrc_request_t sp_0x10;
    int sp_0xc;                

    if (UsbdiGlobals.Data_0x40 == -1)
    {
        //0x00115204
        if (UsbdiGlobals.Data_0x48 == 0)
        {
            //0x00115218
            if ((UsbdiGlobals.Data_0x14 & 1) == 0)
            {
                //0x0011522c
                r5_ = mmap(NULL, r5, r3 | 0x300, 0x90002, -1, 0);

#if 1
                fprintf(stderr, "alloc_resource: mmap(1): r5_=%p\n", r5_);
#endif

                if (r4 != NULL)
                {
                    //0x0011525c
                    *r4 = mphys(r5_);
                }
                //->loc_1153a4
//                goto loc_1153a4;
            }
            else
            {
                //loc_1153b0
                if (usbdi_get_dma_memory(&sp_0xc, r5) != 0)
                {
                    //loc_11535c
                    errno = 12;
                    r5_ = -1;
                    //->loc_1153a4
                }
                else
                {
                    //loc_115370
                    if (r4 != NULL)
                    {
                        *r4 = sp_0xc;
                    }
                    r5_ = mmap_device_memory(0, r5, 0xb00, 0x10001, sp_0xc);
#if 1
                    fprintf(stderr, "alloc_resource: mmap_device_memory(1): r5_=%p\n", r5_);
#endif
                }
                //loc_1153a4
//                goto loc_1153a4;
            }
        }
        else
        {
            //loc_11529c
            memset(&sp_0x10, 0, sizeof(rsrc_request_t));

            sp_0x10.length = (uint64_t)r5;
            sp_0x10.align = 4;
            sp_0x10.start = sp_0x10.end;
            sp_0x10.flags = r3 | 0x2200;
            sp_0x10.name = UsbdiGlobals.Data_0x48;

            if (rsrcdbmgr_attach(&sp_0x10, 1) != 0)
            {
                //0x00115314
                errno = 12;
                r5_ = -1;
                //->loc_1153a4
            }
            else
            {
                //loc_115328
                if (r4 != NULL)
                {
                    *r4 = sp_0x10.start;
                }

                r5_ = mmap_device_memory(0, r5, 0xb00, 0x10001, sp_0x10.start);
                //->loc_1153a4
#if 1
                fprintf(stderr, "alloc_resource: mmap_device_memory(2): r5_=%p\n", r5_);
#endif
            }
        }
    }
    else
    {
        //loc_115268
        r5_ = mmap(NULL, r5, r3 | 0x300, 0x0001, 
                UsbdiGlobals.Data_0x40, 0);
#if 1
        fprintf(stderr, "alloc_resource: mmap(2): r5_=%p\n", r5_);
#endif
        if (r4 != NULL)
        {
            //0x00115290
            *r4 = mphys(r5_);
        }
        //->loc_1153a4
//        goto loc_1153a4;
    }

//loc_1153a4:
    //loc_1153a4
    return r5_;
}



/* 0x001153c8 - todo */
void* usbdi_memchunk_malloc(int h, int r7)
{
#if 1
    fprintf(stderr, "usbdi_memchunk_malloc: %d TODO!!!\n", r7);

//    return malloc(b);
#endif

    struct
    {
        int Data_0; //0
        int Data_4; //4
        int Data_8[]; //8
        //0xc
    }* r5_;
    struct USB_Memchunk* r5 = h;

    if (r7 == 0)
    {
        return &r5->Data_0x10;
    }

    pthread_mutex_lock(&r5->mutex/*r8*/);

    struct USB_Memchunk_Inner_0x18* r4 = NULL;
    struct USB_Memchunk_Inner_0x18* r4_ = &r5->Data_0x18[0];
    while (r4_->wData_0 != 0)
    {
        //loc_115410
        if ((r7 + 4) <= r4_->wData_0)
        {
            r4 = r4_;
            break;
        }

        r4_++;
    }
    //loc_115420
    if (r4 != NULL)
    {
        //0x00115428
        struct USB_Memchunk_Inner_0x18_Inner_8* r1 = r4->Data_8;
        while (r1 != NULL)
        {
            //0x00115434
            if (r1->Data_4 != 0)
            {
                //loc_115450
                int r0 = sub_114b5c(r4, r1);
                //->loc_115544
                if (r0 != 0)
                {
                    r5_ = r0 + 4;
                    //->loc_115594
                    goto loc_115594;
                }
                //->loc_115550
                goto loc_115550;
            }
            else
            {
                //loc_11545c
                r1 = r1->next;
            }
        } //while (r1 != NULL)
        //loc_115468
        struct 
        {
            int Data_0; //0
            int Data_4; //4
            int Data_8; //8
            uint16_t wData_0xc; //0xc
            uint16_t wData_0xe; //0xe
            //0x10???
        }* r6 = alloc_resource(r4->wData_2 * r4->wData_0 + 0x10, r5->Data_0xc, NULL);
        if (r6 != -1)
        {
            //0x00115490
            memset(r6, 0, r4->wData_2 * r4->wData_0 + 0x10);

            r4->Data_4 += r4->wData_2;

            r6->Data_0 = r4->Data_8;
            r6->Data_8 = mphys(r6);
            r6->wData_0xc = 0;
            r6->wData_0xe = (r4 - &r5->Data_0x18[0]);
            r4->Data_8 = r6;
            int* r3 = r6 + 1;
            r6->Data_4 = r3;

            int r2 = r4->wData_2;
            while (--r2 > 0)
            {
                //loc_115514
                int* r1 = ((char*)r3) + r4->wData_0;
                *r3 = r1;
                r3 = r1;
            }
            //loc_115530
            *r3 = 0;

            int r0 = sub_114b5c(r4, r6);
            //loc_115544
            if (r0 != 0)
            {
                r5_ = r0 + 4;
                //->loc_115594
                goto loc_115594;
            }
        }
        //loc_115550
    } //if (r4 != NULL)
    //loc_115550
loc_115550:
    r7 = r7 + 8;
    r5_ = alloc_resource(r7, r5->Data_0xc, NULL);
    if (r5_ == -1)
    {
        r5_ = NULL;
        //->loc_115594
    }
    else
    {
        memset(r5_, 0, r7);
        r5_->Data_0 = r7;
        r5_->Data_4 = 0;
        r5_ = &r5_->Data_8[0];
    }
    //loc_115594
loc_115594:
    pthread_mutex_unlock(&r5->mutex/*r8*/);
    //loc_11559c
#if 1
    fprintf(stderr, "usbdi_memchunk_malloc: r5_=%p\n", r5_);

//    return malloc(b);
#endif
    return r5_;
}



/* 0x001155a4 - todo */
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


void usbdi_memchunk_free(int a, void* b)
{
#if 1
    fprintf(stderr, "usbdi_memchunk_free\n");
#endif

}


