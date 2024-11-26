

#include <sys/syspage.h>
#include "externs.h"



/* 0x00114c28 - todo */
int usbdi_memchunk_init(int* sp4, int sb, int* sp_0x14, int r5)
{
#if 1
    fprintf(stderr, "usbdi_memchunk_init\n");
#endif

    int sp_0x10;
    int r6;
    int r4 = sb * 12  + 0x24;

    struct
    {
        pthread_mutex_t Data_0; //0
        int Data_8; //8
        int Data_0xc; //0xc
        int Data_0x10; //0x10
        int Data_0x14; //0x14
        //???
    }* r7 = malloc(r4);
    if (r7 == NULL)
    {
        sp_0x10 = 12;
        //->loc_114f00
        *sp_0x14 = 0;
        //loc_114f0c
        return sp_0x10;
    }

    sp_0x10 = pthread_mutex_init(&r7->Data_0, 0);
    if (sp_0x10 != 0)
    {
        //loc_114ef8
        free(r7);
        //loc_114f00
        *sp_0x14 = 0;
        //loc_114f0c
        return sp_0x10;
    }
    //0x00114c7c
    r7->Data_8 = sysconf(_SC_PAGE_SIZE);
    if (r7->Data_8 == -1)
    {
        //0x00114c90
        r7->Data_8 = _SYSPAGE_ENTRY(_syspage_ptr,system_private)->pagesize;
    }
    //loc_114cac
    int r3;
    if (r5 != 0)
    {
        r3 = 0;
        //->loc_114d14
    }
    else
    {
        //0x00114cb8
        //TODO!!!
    }
    //loc_114d14
    r7->Data_0xc = r3;
    r7->Data_0x14 = r4;
    r7->Data_0x10 = 0;

    //TODO!!!

    for (r6 = 0; r6 < sb; r6++)
    {
        //loc_114d5c

        //TODO!!!
    }
    //0x00114e58

    //TODO!!!

    return 0;
}




/* 0x001153c8 - todo */
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


