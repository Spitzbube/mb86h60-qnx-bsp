
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>
#include <atomic.h>
#include <sys/mman.h>
#include <sys/syspage.h>
#include <sys/rsrcdbmgr.h>
#include <drvr/support.h> //-> mphys
#include <sys/usbdi.h>
#include "usbdi_priv.h"



/* 0x00006140 - todo */
int usbdi_memchunk_init(uint32_t* sp4, int sb, int* sp_0x14, int cached/*r5*/)
{
#if 0
    fprintf(stderr, "usbdi_memchunk_init\n");
#endif

    int res; //sp_0x10;
    int r6;
    int r4 = sb * sizeof(struct USB_Memchunk_Inner_0x18)  + 0x24;

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
        r7->pagesize = sysconf(_SC_PAGE_SIZE);
        if (r7->pagesize == -1)
        {
            //0x00114c90
            r7->pagesize = _SYSPAGE_ENTRY(_syspage_ptr,system_private)->pagesize;
        }
        //loc_114cac
        int prot = 0;
        if (cached == 0)
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
            prot = PROT_NOCACHE; //0x800;
        }
        //loc_114d14
        r7->prot = prot;
        r7->size = r4;
        r7->Data_0x10 = 0;

        uint32_t pagesize = r7->pagesize - 0x10;
        int r5_ = 0;

        for (r6 = 0; r6 < sb; r6++)
        {
            //loc_114d5c
            uint32_t size = sp4[r6];
            if (size < 8)
            {
                size = 8;
            }

            size = ((size + 3) & ~0x03) + 4;

            int r4;
            for (r4 = 0; r4 < r6; r4++)
            {
                //loc_114d8c
                if ((size != 0) && (size < r7->Data_0x18[r4].size))
                {
                    //0x00114da0
                    memmove(&r7->Data_0x18[r4 + 1], &r7->Data_0x18[r4], (r6 - r4) * 12);
                    //->loc_114ddc
                    break;
                }
                //loc_114dcc
            } //for (r4 = 0; r4 < r6 r4++)
            //loc_114ddc
            r7->Data_0x18[r4].size = size;
            r7->Data_0x18[r4].count = (pagesize <= size)? 1: pagesize / size;
#if 1
            fprintf(stderr, "usbdi_memchunk_init(client): r7->Data_0x18[%d].size=%d, count=%d\n",
                r4, r7->Data_0x18[r4].size, r7->Data_0x18[r4].count);
#endif

            if (Data_b698.Data_0x14 & 0x02)
            {
                r7->Data_0x18[r4].count = 1;
            }

            r7->Data_0x18[r4].avail = 0; //r8
            r7->Data_0x18[r4].Data_8 = NULL; //r8

            r5_ = sb;
        } //for (r6 = 0; r6 < sb; r6++)
        //0x00114e58
        while (--r5_ > 0)
        {
            //loc_114e84
            if ((r7->Data_0x18[r5_].size - r7->Data_0x18[r5_ - 1].size) <= 7)
            {
                //0x00114e98
                memmove(&r7->Data_0x18[r5_ - 1], 
                    &r7->Data_0x18[r5_], 
                    (sb-- - r5_) * 12);
            }
            //loc_114ec0
        } //while (--r5_ > 0)

        r7->Data_0x18[sb].count = 0;
        r7->Data_0x18[sb].size = 0; 
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


/* 0x00006074 - complete */
int UseFreeEntry(struct USB_Memchunk_Inner_0x18* a,
        struct USB_Memchunk_Inner_0x18_Inner_8* b)
{
#if 0
    fprintf(stderr, "UseFreeEntry: TODO!!!\n");
#endif

    struct USB_Memchunk_Inner_0x18_Inner_8* p = b->Data_4;
    b->Data_4 = p->next;
    b->wData_0xc++;
    p->next = b;

    a->avail--;

    return p;
}


/* 0x00008038 - todo */
int usbdi_get_dma_memory(void* a, int b)
{
#if 1
    fprintf(stderr, "usbdi_get_dma_memory: TODO!!!\n");
#endif

    return 0;
}


/* 0x00006724 - todo */
void* alloc_resource(int size/*r5*/, int prot/*r3*/, paddr_t* phys/*r4*/)
{
#if 0
    fprintf(stderr, "alloc_resource: size=%d, prot=0x%x: TODO!!!\n",
        size, prot);
#endif

#if 0
    fprintf(stderr, "alloc_resource: Data_b698.typed_mem_fd=%d, .Data_0x48=%p, .Data_0x14=0x%x\n",
        Data_b698.typed_mem_fd, Data_b698.Data_0x48, Data_b698.Data_0x14);
#endif

    void* ptr; //r5
    rsrc_request_t sp_0x10;
    int sp_0xc;                

    if (Data_b698.typed_mem_fd == -1)
    {
        //0x00115204
        if (Data_b698.Data_0x48 == NULL)
        {
            //0x00115218
            if ((Data_b698.Data_0x14 & 1) == 0)
            {
                //0x0011522c
                ptr = mmap(NULL, size, 
                        prot | PROT_READ|PROT_WRITE, 
                        MAP_ANON|MAP_PHYS|MAP_PRIVATE, //0x90002, 
                        -1, 0);

#if 0
                fprintf(stderr, "alloc_resource: mmap(private): ptr=%p\n", ptr);
#endif

                if (phys != NULL)
                {
                    //0x0011525c
                    *phys = mphys(ptr);
                }
                //->loc_1153a4
//                goto loc_1153a4;
            } //if ((Data_b698.Data_0x14 & 1) == 0)
            else
            {
                //loc_6900
                if (usbdi_get_dma_memory(&sp_0xc, size) != 0)
                {
                    //loc_68ac
                    errno = 12;
                    ptr = -1;
                    //->loc_1153a4
                }
                else
                {
                    //loc_68c0
                    if (phys != NULL)
                    {
                        *phys = sp_0xc;
                    }
                    ptr = mmap_device_memory(NULL, size, 
                            PROT_NOCACHE|PROT_READ|PROT_WRITE, //0xb00, 
                            MAP_PHYS|MAP_SHARED, //0x10001, 
                            sp_0xc);
#if 0
                    fprintf(stderr, "alloc_resource: mmap_device_memory(1): ptr=%p\n", ptr);
#endif
                }
                //loc_1153a4
//                goto loc_1153a4;
            }
        } //if (Data_b698.Data_0x48 == NULL)
        else
        {
            //loc_67ec
            memset(&sp_0x10, 0, sizeof(rsrc_request_t));

            sp_0x10.length = (uint64_t)size;
            sp_0x10.align = 4;
            sp_0x10.start = sp_0x10.end;
            sp_0x10.flags = prot | 0x2200;
            sp_0x10.name = Data_b698.Data_0x48;

            if (rsrcdbmgr_attach(&sp_0x10, 1) != 0)
            {
                //0x00115314
                errno = 12;
                ptr = -1;
                //->loc_1153a4
            }
            else
            {
                //loc_6878
                if (phys != NULL)
                {
                    *phys = sp_0x10.start;
                }

                ptr = mmap_device_memory(NULL, size, 
                        PROT_NOCACHE|PROT_READ|PROT_WRITE, //0xb00,
                        MAP_PHYS|MAP_SHARED, //0x10001, 
                        sp_0x10.start);
                //->loc_1153a4
#if 0
                fprintf(stderr, "alloc_resource: mmap_device_memory(2): ptr=%p\n", ptr);
#endif
            }
        }
    } //if (Data_b698.typed_mem_fd == -1)
    else
    {
        //loc_67b8
        ptr = mmap(NULL, size, 
                prot | PROT_READ|PROT_WRITE, 
                MAP_SHARED, //0x0001, 
                Data_b698.typed_mem_fd, 0);
#if 0
        fprintf(stderr, "alloc_resource: mmap(shared): ptr=%p\n", ptr);
#endif
        if (phys != NULL)
        {
            //0x00115290
            *phys = mphys(ptr);
        }
        //->loc_1153a4
//        goto loc_1153a4;
    }

//loc_1153a4:
    //loc_1153a4
    return ptr;
}


/* 0x00006920 - todo */
void* usbdi_memchunk_malloc(int h, int size/*r7*/)
{
#if 1
    fprintf(stderr, "usbdi_memchunk_malloc(client): %d\n", size);

//    return malloc(b);
#endif
    void* ptr; //r5
    struct USB_Memchunk* r5 = h;
    int r0;

    if (size == 0)
    {
        return &r5->Data_0x10;
    }

    pthread_mutex_lock(&r5->mutex/*r8*/);

    struct USB_Memchunk_Inner_0x18* r4 = NULL;
    struct USB_Memchunk_Inner_0x18* r4_ = &r5->Data_0x18[0];
    while (r4_->size != 0)
    {
        //loc_115410
        if ((size + 4) <= r4_->size)
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
                r0 = UseFreeEntry(r4, r1);
                //->loc_6a9c
                goto loc_6a9c;
#if 0                
                if (r0 != 0)
                {
                    ptr = r0 + 4;
                    //->loc_115594
                    goto loc_115594;
                }
                //->loc_115550
                goto loc_115550;
#endif                
            }
            else
            {
                //loc_11545c
                r1 = r1->next;
            }
        } //while (r1 != NULL)
        //loc_115468
        struct USB_Memchunk_Inner_0x18_Inner_8* r6;
        
        r6 = alloc_resource(sizeof(struct USB_Memchunk_Inner_0x18_Inner_8) + 
                r4->size * r4->count, 
                r5->prot, NULL);

        if (r6 != -1)
        {
            //0x00115490
            memset(r6, 0, 
                sizeof(struct USB_Memchunk_Inner_0x18_Inner_8) + r4->size * r4->count);

            r4->avail += r4->count;

            r6->next = r4->Data_8;
            r6->phys = mphys(r6);
            r6->wData_0xc = 0;
            r6->wData_0xe = (r4 - &r5->Data_0x18[0]);
            r4->Data_8 = r6;
            struct USB_Memchunk_Inner_0x18_Inner_8* r3 = r6 + 1;
            r6->Data_4 = r3;

            int r2 = r4->count;
            while (--r2 > 0)
            {
                //loc_115514
                void* next = ((char*)r3) + r4->size;
                r3->next = next;
                r3 = next;
            }
            //loc_115530
            r3->next = NULL;

            r0 = UseFreeEntry(r4, r6);
            //loc_6a9c
loc_6a9c:            
            if (r0 != 0)
            {
                ptr = r0 + 4;
                //->loc_115594
                goto loc_115594;
            }
        } //if (r6 != -1)
        //loc_115550
    } //if (r4 != NULL)
    //loc_115550
loc_115550:
    {
        struct
        {
            int Data_0; //0
            int Data_4; //4
            //8
        }* r5_;

        size += sizeof(*r5_);
        r5_ = alloc_resource(size, r5->prot, NULL);
        if (r5_ == -1)
        {
            ptr = NULL;
            //->loc_115594
        }
        else
        {
            memset(r5_, 0, size);
            r5_->Data_0 = size;
            r5_->Data_4 = 0;
            ptr = r5_ + 1;
        }
    }
    //loc_115594
loc_115594:
    pthread_mutex_unlock(&r5->mutex/*r8*/);
    //loc_11559c
#if 0
    fprintf(stderr, "usbdi_memchunk_malloc: r5_=%p\n", ptr);
#endif
    return ptr;
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
paddr_t usbdi_memchunk_mphys(int h/*r5*/, const void* ptr/*r6*/)
{
#if 1
    fprintf(stderr, "usbdi_memchunk_mphys: ptr=%p\n", ptr);
#endif

    struct USB_Memchunk* r5 = h;
    void* r4 = (-r5->pagesize) & (uint32_t)ptr;

    pthread_mutex_lock(&r5->mutex/*r7*/);

    struct USB_Memchunk_Inner_0x18* r5_ = &r5->Data_0x18[0];
    while (r5_->size != 0)
    {
        //loc_60d4
        struct USB_Memchunk_Inner_0x18_Inner_8* r3 = r5_->Data_8;
        while (r3 != NULL)
        {
            //loc_60ec
            if (r4 == r3)
            {
                //loc_60f4
                paddr_t phys = r3->phys + ((uint8_t*)ptr - (uint8_t*)r3); 

                pthread_mutex_unlock(&r5->mutex/*r7*/);

                return phys;
            }
            //loc_610c
            r3 = r3->next;
        }
        //loc_6118
        r5_++;
    } //while (r5_->size != 0)
    //loc_6124
    pthread_mutex_unlock(&r5->mutex/*r7*/);

    return mphys(ptr);
}


