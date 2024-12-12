
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <errno.h>
#include <gulliver.h>
#include <sys/mman.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <sys/slog.h>
#include <sys/usbdi.h>
#include <pthread.h>
#include <arm/mb86h60.h>


//_GLOBAL_OFFSET_TABLE_ //0x0000bd5c

struct Mentor_Controller;
#define USB_CONTROLLER_PRIV_T struct Mentor_Controller
#include <sys/io-usb.h>
#include "my-io-usb.h"



struct Struct_0xa4;
struct Struct_0xa0;
struct Struct_0x94
{
    struct Struct_0xa0* Data_0; //0
};

struct Struct_0xa0
{
    volatile uint32_t Data_0; //0
    volatile uint32_t flags; //4
    int Data_8; //8
    void* pData; //0xc
    int Data_0x10; //0x10
    volatile uint32_t Data_0x14; //0x14
    int fill_0x18[4]; //0x18
    int status; //0x28
    struct Struct_0x94 Data_0x2c; //0x2c
    struct Struct_0xa4* Data_0x30; //0x30
    struct Struct_10bab4* Data_0x34; //0x34
    void (*Func_0x38)(); //0x38
    void (*Data_0x3c)(); //0x3c
    int fill_0x40; //0x40
    //0x44
};


struct Struct_0xa4
{
    struct Struct_0xa4* Data_0; //0
    struct Struct_0xa4* Data_4; //4
    struct Struct_0xa0* Data_8__; //8
    struct Struct_0x94* Data_0xc; //12
    int Data_0x10; //0x10 = 16
    int Data_0x14; //0x14 = 20
    uint16_t wData_0x18; //0x18 = 24
    uint8_t transferType; //0x1a = 26
    uint8_t bData_0x1b; //0x1b = 27
    uint8_t bData_0x1c; //0x1c = 28
    uint8_t bData_0x1d; //0x1d = 29
    uint8_t bData_0x1e; //0x1e = 30
    uint8_t bData_0x1f; //0x1f = 31
    int Data_0x20; //0x20
    int Data_0x24; //0x24
    int Data_0x28; //0x28
    int Data_0x2c; //0x2c
    struct fp_0x34_Inner_0x18_Inner_0x10* Data_0x30; //0x30
    struct Struct_112b08* Data_0x34; //0x34
    int Data_0x38; //0x38
    int fill_0x3c; //0x3c
    //0x40 = 64
};
    

struct Struct_0xe4
{
    int Data_0; //0
    void* Data_4; //4
    int fill_8; //8
    uint8_t bData_0xc; //0xc
    int Data_0x10; //0x10
    int fill_0x14[3]; //0x14
    //0x20
};


struct Mentor_Controller_Inner_0x8c
{
    int fill_0[6]; //0
    struct fp_0x34_Inner_0x18
    {
        int fill_0[2]; //8
        int Data_8; //8
        uint32_t Data_0xc; //12 = 0xc
        struct fp_0x34_Inner_0x18_Inner_0x10
        {
            int Data_0; //0
            int Data_4; //4
            int Data_8; //8
            struct fp_0x34_Inner_0x18* Data_0xc; //0xc 
            //16 = 0x10
        }* Data_0x10; //16 = 0x10
        //0x14
    } Data_0x18[]; //0x18, size???
    //???
};


struct Mentor_Controller
{
    struct USB_Controller* Data_0; //0
    pthread_mutex_t Data_4; //4
    pthread_mutex_t Data_0xc; //12
    void* Data_0x14; //0x14
    uint32_t Data_0x18; //0x18
    int fill_ox1c[3]; //0x1c
    int Data_0x28; //0x28
    int Data_0x2c; //0x2c
    int fill_0x30[2]; //0x30
    int Data_0x38; //0x38
    pthread_t Data_0x3c; //0x3c
    int Data_0x40; //0x40
    int Data_0x44; //0x44
    int Data_0x48; //0x48
    int Data_0x4c; //0x4c
    int Data_0x50; //0x50
    int Data_0x54; //0x54
    int Data_0x58; //0x58
    struct sigevent Data_0x5c;
    int Data_0x6c; //0x6c
    uint32_t Data_0x70; //0x70
    uint32_t Data_0x74; //0x74
    uint32_t verbosity; //0x78
    int Data_0x7c; //0x7c
    int fill_0x80; //0x80
    int Data_0x84; //0x84
    char* fconfig_string; //0x88
    struct Mentor_Controller_Inner_0x8c* Data_0x8c; //0x8c
    struct Struct_0x94 Data_0x90; //0x90
    struct Struct_0x94* Data_0x94; //0x94
    struct Struct_0xa0* Data_0x98; //0x98
    struct Struct_0xa0** Data_0x9c; //0x9c
    struct Struct_0xa0* Data_0xa0; //0xa0
    struct Struct_0xa4* Data_0xa4; //0xa4
    struct Struct_0xa4* Data_0xa8; //0xa8
    struct Struct_0xa4* Data_0xac; //0xac
    struct Struct_0xa4* Data_0xb0; //0xb0
    struct Struct_0xa4* Data_0xb4; //0xb4
    struct Struct_0xa4* Data_0xb8; //0xb8
    struct Struct_0xa4* Data_0xbc; //0xbc
    struct Struct_0xa4* Data_0xc0; //0xc0
    struct Struct_0xa0** Data_0xc4; //0xc4
    struct Struct_0xa4** Data_0xc8; //0xc8
    int fill_0xcc; //0xcc
    struct intrspin Data_0xd0; //0xd0
    uint16_t wData_0xd4; //0xd4
    struct Struct_0xe4* Data_0xe4; //0xe4
    //0xe8
};

#include "mentor.h"
#include "mu_hdrdf.h"


extern void MENTOR_LoadFIFO(struct Mentor_Controller*, uint16_t, int, uint16_t);
extern void MENTOR_ReadFIFO(struct Mentor_Controller*, struct Struct_0xa0*, uint16_t, int, uint16_t);


#ifdef MB86H60

volatile uint8_t bUsbIntStatus;

void* dma_regs = NULL;
uint32_t dma_dwUsbMode = 0;


void dma_SetUsbIntMask(struct Mentor_Controller* c, int a)
{
    ((volatile uint32_t*)(dma_regs))[MB86H60_DMA_USB_INT_MASK/sizeof(uint32_t)] = a;
}

uint32_t dma_GetUsbIntStatus(struct Mentor_Controller* c)
{
    return ((volatile uint32_t*)(dma_regs))[MB86H60_DMA_USB_INT_STATUS/sizeof(uint32_t)];
}

void dma_SetUsbIntClear(struct Mentor_Controller* c, int a)
{
    ((volatile uint32_t*)(dma_regs))[MB86H60_DMA_USB_INT_CLEAR/sizeof(uint32_t)] = a;
}

void dma_SetUsbMode_LengthInput(struct Mentor_Controller* c, int a)
{
	int mask = MB86H60_DMA_USB_MODE_LENGTH_INPUT;
	a = (a << 1) & mask;

	dma_dwUsbMode = (dma_dwUsbMode & ~mask) | a;

    ((volatile uint32_t*)(dma_regs))[MB86H60_DMA_USB_MODE/sizeof(uint32_t)] = dma_dwUsbMode;
}


uint8_t MGC_Read8(struct Mentor_Controller* c, uint16_t offset)
{
    uint8_t data;
	dma_SetUsbMode_LengthInput(c, 0);
    data = ((volatile uint32_t*)(c->Data_0x14))[offset];
    return data;
}


uint16_t MGC_Read16(struct Mentor_Controller* c, uint16_t offset)
{
    uint16_t data;
	dma_SetUsbMode_LengthInput(c, 1);
    data = ((volatile uint32_t*)(c->Data_0x14))[offset];
    return data;
}


uint32_t MGC_Read32(struct Mentor_Controller* c, uint16_t offset)
{
    uint32_t data;
	dma_SetUsbMode_LengthInput(c, 2);
    data = ((volatile uint32_t*)(c->Data_0x14))[offset];
    return data;
}


void MGC_Write8(struct Mentor_Controller* c, uint16_t offset, uint8_t data)
{
	dma_SetUsbMode_LengthInput(c, 0);
    ((volatile uint32_t*)(c->Data_0x14))[offset] = data;
}


void MGC_Write16(struct Mentor_Controller* c, uint16_t offset, uint16_t data)
{
	dma_SetUsbMode_LengthInput(c, 1);
    ((volatile uint32_t*)(c->Data_0x14))[offset] = data;
}


void MGC_Write32(struct Mentor_Controller* c, uint16_t offset, uint32_t data)
{
	dma_SetUsbMode_LengthInput(c, 2);
    ((volatile uint32_t*)(c->Data_0x14))[offset] = data;
}

#endif //MB86H60



/* 0x0000611c - complete */
int mentor_slogf(struct Mentor_Controller* a, 
        int opcode, int severity, int verbosity,
        const char* fmt, ...)
{
    int res;

    if (a->verbosity < verbosity)
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


/* 0x00004cbc - todo */
void MENTOR_ProcessControlDone(struct Mentor_Controller* r5)
{
#if 0
    fprintf(stderr, "MENTOR_ProcessControlDone: TODO\n");
#endif

    struct Struct_0xa0* r4 = r5->Data_0xc4[0];
    if (r4 == NULL)
    {
        //->loc_4ee8
        return;
    }

    struct Struct_0xa4* r6 = r4->Data_0x30;
    
    if (r6->bData_0x1f != 0)
    {
        //->loc_4ee8
        return;
    }
    //0x00004cf0
    int status; //r8
    uint16_t wCsr; //r7

#ifdef MB86H60
    wCsr = MGC_Read16(r5, 0x102);
#else
    wCsr = ((volatile uint16_t*)(r5->Data_0x14))[0x102/2];
#endif

    status = (wCsr & (1 << 2)/*RxStall*/)? USBD_STATUS_STALL: 0;

    if (wCsr & ((1 << 7)/*NAK Timeout*/ | (1 << 4)/*Error*/))
    {
        status = USBD_STATUS_NOT_ACCESSED;
        //->loc_4e3c
    }
    //0x00004d10
    if (status == 0)
    {
        //0x00004d18
        if (r4->flags & PIPE_FLAGS_TOKEN_IN) //4)
        {
            //0x00004d24
            uint16_t sl;
#ifdef MB86H60
            sl = MGC_Read16(r5, 0x108);
#else
            sl = ((volatile uint16_t*)(r5->Data_0x14))[0x108/2];
#endif
#if 0 //No printf in ISR
            fprintf(stderr, "MENTOR_ProcessControlDone: sl=%d\n", sl);
#endif
            int sb = sl;

            if (sl > (uint32_t)(r4->Data_0 - r4->Data_0x14))
            {
                status = USBD_STATUS_DATA_OVERRUN;
                //->0x00004e3c
            }
            else if (/*sl*/sb > 0)
            {
                //0x00004d50
                MENTOR_ReadFIFO(r5, r4, 0, 
                    (char*)(r4->pData) + r4->Data_0x14,
                    sl);

                r4->Data_0x14 += sl;

                if ((r6->wData_0x18 == sl) && (r4->Data_0 > r4->Data_0x14))
                {
                    //0x00004d94
                    HW_Write16(r5, 0x102, wCsr | 0x20);
                    //->loc_4ee8
                    return;
                }
                //0x00004e3c
            }
            //->0x00004e3c
        } //if (r4->flags & PIPE_FLAGS_TOKEN_IN) //4)
        //loc_4dac
        else if (r4->flags & PIPE_FLAGS_TOKEN_OUT) //8)
        {
            //0x00004db8
            if (r4->Data_0 > r4->Data_0x14)
            {
                //0x00004dc8
                uint32_t r6_ = r6->wData_0x18;
                if (r6_ >= (r4->Data_0 - r4->Data_0x14))
                {
                    r6_ = r4->Data_0 - r4->Data_0x14;
                }

                MENTOR_LoadFIFO(r5, 0, 
                    (char*)(r4->pData) + r4->Data_0x14,
                    r6_);

                r4->Data_0x14 += r6_;

#ifdef MB86H60
                MGC_Write16(r5, 0x102, MGC_Read16(r5, 0x102) | 0x02);
#else
                ((volatile uint16_t*)(r5->Data_0x14))[0x102/2] |= 0x02;
#endif
                //->loc_4ee8
                return;
            }
            //loc_4e3c
        } //else if (r4->flags & PIPE_FLAGS_TOKEN_OUT) //8)
        //loc_4e2c
        else if (r4->flags & PIPE_FLAGS_TOKEN_SETUP) //1)
        {
            r4->Data_0x14 = r4->Data_0;
        } //else if (r4->flags & 1)
    } //if (status == 0)
    //loc_4e3c
    r6->Data_0x20 = (wCsr >> 9) & 1;

    HW_Write16(r5, 0x102, 0);

    InterruptLock(&r5->Data_0xd0);

    r5->Data_0xc4[0] = NULL;
    r6->Data_8__ = r4->Data_0x2c.Data_0;
    if (r6->Data_8__ == 0)
    {
        r6->Data_0xc = &r6->Data_8__;
    }
    r6->Data_0x10 &= ~0x01;

    r4->status = status;
    r4->Data_0x2c.Data_0 = NULL;

    r5->Data_0x9c[0] = r4;
    r5->Data_0x9c = &r4->Data_0x2c.Data_0;

    InterruptUnlock(&r5->Data_0xd0);
    //loc_4ee8
    return;
}


/* 0x00004220 - todo */
struct fp_0x34_Inner_0x18_Inner_0x10* mentor_fifo_alloc(struct Mentor_Controller* r5,
        int fp_0x2c, 
        struct Struct_0xa4* c,
        int fp_0x30)
{
#if 0
    fprintf(stderr, "mentor_fifo_alloc: TODO!!!\n");
#endif

    struct fp_0x34_Inner_0x18_Inner_0x10* r0 = NULL;
    int r8;
    uint32_t r3;
    struct Mentor_Controller_Inner_0x8c* r4 = r5->Data_0x8c;
    int r6 = c->wData_0x18;
    //r7 = 0x24;
    //sb = 0x20;
    //->loc_4364
    while ((r8/*r0*/ = find_block_list(r4, r6)) != -1)
    {
        //loc_4250
#if 1
        fprintf(stderr, "mentor_fifo_alloc: r6=%d, fifo_size=%d\n", r6, r8);
#endif
        uint32_t sl = r4->Data_0x18[r8].Data_0xc;
        for (r3 = 0; r3 < r4->Data_0x18[r8].Data_8; r3++)
        {
#if 1
            fprintf(stderr, "mentor_fifo_alloc: r3=%d, sl=0x%04x\n", r3, sl);
#endif
            //if (sl & (1 << r3))
            if (sl & 1)
            {
                r4->Data_0x18[r8].Data_0xc = sl & ~(1 << r3);

#if 1
                fprintf(stderr, "mentor_fifo_alloc: fp_0x30=%d, ep=%d, fifo_add=%d\n", 
                    fp_0x30, fp_0x2c, r4->Data_0x18[r8].Data_0x10[r3].Data_4);
#endif

#ifdef MB86H60
                //MGC_SelectEnd(r5, fp_0x2c & 0xff);
                MGC_Write8(r5, MGC_O_HDRC_INDEX, fp_0x2c & 0xff);
#else
                ((volatile uint8_t*)(r5->Data_0x14))[0x0e/*INDEX*/] = fp_0x2c & 0xff;
#endif

                if (fp_0x30 != 0)
                {
                    //0x000042c0
#ifdef MB86H60
#if 0 //Dynfifo!
                    MGC_Write8(r5, MGC_O_HDRC_RXFIFOSZ, r8/*r0*/ & 0xff);
                    HW_Write16(r5, MGC_O_HDRC_RXFIFOADD, 
                        (r4->Data_0x18[r8].Data_0x10[r3].Data_4 << 13) >> 16);
#endif
#else
                    ((volatile uint8_t*)(r5->Data_0x14))[0x63/*RXFIFOSZ*/] = r8/*r0*/ & 0xff;
                    ((volatile uint16_t*)(r5->Data_0x14))[0x66/2/*RXFIFOADD*/] = 
                        (r4->Data_0x18[r8].Data_0x10[r3].Data_4 << 13) >> 16;
#endif
                    //->loc_4334
                }
                else
                {
                    //loc_42fc
#ifdef MB86H60
#if 0 //Dynfifo!
                    MGC_Write8(r5, MGC_O_HDRC_TXFIFOSZ, r8/*r0*/ & 0xff);
                    HW_Write16(r5, MGC_O_HDRC_TXFIFOADD, 
                        (r4->Data_0x18[r8].Data_0x10[r3].Data_4 << 13) >> 16);
#endif
#else
                    ((volatile uint8_t*)(r5->Data_0x14))[0x62/*TXFIFOSZ*/] = r8/*r0*/ & 0xff;
                    ((volatile uint16_t*)(r5->Data_0x14))[0x64/2/*TXFIFOADD*/] = 
                        (r4->Data_0x18[r8].Data_0x10[r3].Data_4 << 13) >> 16;
#endif
                }
                //loc_4334
                r0 = &r4->Data_0x18[r8].Data_0x10[r3];
                //->loc_437c
                return r0;
            }
            
            sl >>= 1;
        } //for (r3 = 0; r3 < r4->Data_0x18[r8].Data_8; r3++)
        //loc_4360
        r6 *= 2;
    } //while ((r8/*r0*/ = find_block_list(r4, r6)) != -1)
    //0x00004378
    return r0;
}


/* 0x00008284 - todo */
int MENTOR_AllocEtd(struct Mentor_Controller* r5, 
        struct Struct_0xa4* r6, 
        int r8)
{
#if 1
    fprintf(stderr, "MENTOR_AllocEtd: TODO!!!\n");
#endif

    int r4 = r6->Data_0x28;
    if ((r4 > 0) && (r4 < r5->Data_0x18))
    {
        //->loc_84f0
        return r4;
    }
    //loc_82b4
    for (r4 = 1; (r4 < r5->Data_0x18) && (r5->Data_0xc8[r4] != NULL); r4++)
    {
    }

    if (r4 >= r5->Data_0x18)
    {
        //loc_8304
        int r3 = r5->wData_0xd4;
        if (r3 != 0)
        {
            //0x00008310
            for (r4 = 1; (r4 < r5->Data_0x18) && 
                (r5->Data_0xc8[r4]->Data_0x10 & 0x01); r4++)
            {
                //loc_832c
            }

            if (r4 >= r5->Data_0x18)
            {
                //->loc_84ec
                return -1;
            }
            //loc_8344
            if (MENTOR_FreeEtd(r5, r5->Data_0xc8[r4]) < 0)
            {
                //0x000083f8
                mentor_slogf(r5, 12, 2, 1, 
                    "%s - %s: Trying to relinquish an unreserved ETD failed",
                    "devu-dm816x-mg.so", "MENTOR_AllocEtd");
            }
            //loc_8390
            r5->wData_0xd4 = 0;
            //->loc_8464
        }
        else
        {
            //loc_83b8
            for (r4 = 1; (r4 < r5->Data_0x18) && 
                (r5->Data_0xc8[r4]->Data_0x10 & 0x01); r4++)
            {
            }

            if (r4 >= r5->Data_0x18)
            {
                //->loc_84ec
                return -1;
            }
            //loc_83e8
            if (MENTOR_FreeEtd(r5, r5->Data_0xc8[r4]) < 0)
            {
                //0x000083f8
                mentor_slogf(r5, 12, 2, 1, 
                    "%s - %s: Trying to relinquish an unreserved ETD failed",
                    "devu-dm816x-mg.so", "MENTOR_AllocEtd");
            }
            //loc_8434
            r5->wData_0xd4 = 1;
            //->loc_8464
        }
    }
    //loc_8464
    r6->Data_0x30 = mentor_fifo_alloc(r5, r4, r6, r8);
    if (r6->Data_0x30 == 0)
    {
        //0x00008484
        mentor_slogf(r5, 12, 2, 1, 
            "%s - %s: Allocate FIFO failed, bEnd=%d, maxPacketSize=%d",
            "devu-dm816x-mg.so", "MENTOR_AllocEtd",
            r4, r6->wData_0x18);

        r4 = -1;
        //->loc_84f0
    }
    else
    {
        //loc_84d4
        r6->Data_0x28 = r4;
        r6->bData_0x1f = 0;
        r5->Data_0xc8[r4] = r6;
    }
    //loc_84f0
    return r4;
}


void MENTOR_EtdConfigureTX(struct Mentor_Controller* a, 
    struct Struct_0xa4* b, int c)
{
#if 0
    fprintf(stderr, "MENTOR_EtdConfigureTX: TODO!!!\n");
#endif

    int r4 = b->transferType;
    int r3 = c * 16;

    HW_Write16(a, 0x106 + r3, 0);

    if (b->Data_0x20 != 0)
    {
        //0x00004794
        HW_Write16(a, 0x102 + r3, 0x2308);
        //->loc_47c8
    }
    else
    {
        //loc_47b0
        HW_Write16(a, 0x102 + r3, 0x2048);
    }
    //loc_47c8
    int r2 = c * 8;

    HW_Write16(a, 0x80 + r2, (b->Data_0x14 >> 4) & 0x7f);

    if (b->bData_0x1c & 0x40)
    {
        //0x000047f4
        HW_Write8(a, 0x82 + r2, b->bData_0x1d);
        HW_Write8(a, 0x83 + r2, b->bData_0x1e);
    }
    //loc_481c
    HW_Write16(a, 0x10a + r3, 
        (r4 << 4) | (b->Data_0x14 & 0x0f) | b->bData_0x1c);
    
    if (r4 & 0x01)
    {
        //0x00004854
        HW_Write8(a, 0x10b + r3, b->Data_0x24);
    }
    else
    {
        //loc_4870
        HW_Write8(a, 0x10b + r3, 0);
    }
    //loc_4888
}


/* 0x00004898 - todo */
void MENTOR_EtdConfigureRX(struct Mentor_Controller* a, 
    struct Struct_0xa4* b, int c)
{
#if 1
    fprintf(stderr, "MENTOR_EtdConfigureRX: c=%d, addr=%d\n", 
        c, (b->Data_0x14 >> 4) & 0x7f);
#endif

    int r4 = b->transferType;
    int r3 = c * 16;

#ifdef MB86H60
    MGC_SelectEnd(a, c);
    MGC_Write16(a, 0x12, 0);
//    MGC_Write16(a, 0x102 + r3, 0);
#else
    ((volatile uint16_t*)(a->Data_0x14))[0x102/2 + r3] = 0;
#endif

    int r2 = c * 8;
#ifdef MB86H60
    MGC_Write8(a, 0x84 + c*8, (b->Data_0x14 >> 4) & 0x7f);
//    MGC_Write16(a, /*0x84 + r2*/MGC_BUSCTL_OFFSET(c, MGC_O_HDRC_RXFUNCADDR), 
//        (b->Data_0x14 >> 4) & 0x7f);
#else
    ((volatile uint16_t*)(a->Data_0x14))[0x84/2 + r2] = (b->Data_0x14 >> 4) & 0x7f;
#endif

    if (b->bData_0x1c != 0x40)
    {
        //0x000048e8
#ifdef MB86H60
        MGC_Write8(a, /*0x86 + r2*/MGC_BUSCTL_OFFSET(c, MGC_O_HDRC_RXHUBADDR), 
            b->bData_0x1d);
        MGC_Write8(a, /*0x87 + r2*/MGC_BUSCTL_OFFSET(c, MGC_O_HDRC_RXHUBPORT), 
            b->bData_0x1e);
#else
        ((volatile uint8_t*)(a->Data_0x14))[0x86 + r2] = b->bData_0x1d;
        ((volatile uint8_t*)(a->Data_0x14))[0x87 + r2] = b->bData_0x1e;
#endif
    }
    //loc_4910: Write RXTYPE
    uint8_t rxType = b->bData_0x1c | (r4 << 4) | (b->Data_0x14 & 0x0f);

#if 1
    fprintf(stderr, "MENTOR_EtdConfigureRX: rxType=0x%x, speed=0x%0x, protocol=%d, ep=%d\n", 
        rxType, b->bData_0x1c, r4, b->Data_0x14 & 0x0f);
#endif

#ifdef MB86H60
    MGC_Write8(a, 0x1c, rxType);
//    MGC_Write8(a, 0x10c + r3, rxType);
#else
    ((volatile uint8_t*)(a->Data_0x14))[0x10c + r3] = rxType;
#endif

#ifdef MB86H60
    MGC_Read16(a, 0x16);
//    int r2_ = MGC_Read16(a, 0x106 + r3);
#else
    int r2_ = ((volatile uint16_t*)(a->Data_0x14))[0x106/2 + r3];
#endif

    if (r4 & 0x01)
    {
#ifdef MB86H60
        MGC_Write8(a, 0x1d, b->Data_0x24); //RXINTERVAL
//        MGC_Write8(a, 0x10d + r3, b->Data_0x24); //RXINTERVAL
#else
        ((volatile uint8_t*)(a->Data_0x14))[0x10d + r3] = b->Data_0x24;
#endif
    }
    else
    {
#ifdef MB86H60
        MGC_Write8(a, 0x1b, 0); //TXINTERVAL

//        MGC_Write8(a, 0x10b + r3, 0); //TXINTERVAL
#else
        ((volatile uint8_t*)(a->Data_0x14))[0x10b + r3] = 0;
#endif
    }

    if (b->Data_0x20 != 0)
    {
        //0x0000497c
#ifdef MB86H60
        MGC_Write16(a, 0x16, 0x610);
//        MGC_Write16(a, 0x106 + r3, 0x610);
#else
        ((volatile uint16_t*)(a->Data_0x14))[0x106/2 + r3] = 0x610;
#endif
        //->loc_49b0
    }
    else
    {
        //loc_4998
#ifdef MB86H60
        MGC_Write16(a, 0x16, 0x90);
//        MGC_Write16(a, 0x106 + r3, 0x90);
#else
        ((volatile uint16_t*)(a->Data_0x14))[0x106/2 + r3] = 0x90;
#endif
    }
    //loc_49b0
#ifdef MB86H60
    MGC_Write16(a, 0x16, 0x10);
//    MGC_Write16(a, 0x106 + r3, 0x10);
#else
    ((volatile uint16_t*)(a->Data_0x14))[0x106/2 + r3] = 0x10;
#endif
}


/* 0x00006cc0 - todo */
void MENTOR_StartEtd(struct Mentor_Controller* r4, 
    struct Struct_0xa0* r6)
{
#if 1
    fprintf(stderr, "MENTOR_StartEtd: TODO!!!\n");
#endif

    int fp_0x30;
    //fp_0x2c = _GLOBAL_OFFSET_TABLE_;

    struct Struct_0xa4* r8 = r6->Data_0x30;

#if 1
    fprintf(stderr, "MENTOR_StartEtd: r8=%p, r8->Data_0x28=%d\n",
        r8, r8->Data_0x28);
#endif

    if (r8->Data_0x28 >= 0)
    {
        //0x00006cf4
        r8->bData_0x1f = 0;

        fp_0x30 = r8->Data_0x28;
        r4->Data_0xc4[fp_0x30] = r6;
        r6->flags |= 0x100;

        int r7 = fp_0x30 * 16;

        uint16_t wCsr;
        int retry/*r5*/ = 1000;
#ifdef MB86H60
        MGC_SelectEnd(r4, fp_0x30);
        while (((wCsr = MGC_Read16(r4, 0x12)) & 0x03) && retry--)

//        while (((wCsr = MGC_Read16(r4, 0x102 + r7)) & 0x03) && retry--)
#else
        while (((wCsr = ((volatile uint16_t*)r4->Data_0x14)[0x102/2 + r7]) & 0x03) && retry--)
#endif
        {
            //loc_6d68
#if 1
            fprintf(stderr, "MENTOR_StartEtd: r7=%d, wCsr=0x%04x, retry=%d\n", r7, wCsr, retry);
#endif
            nanospin_ns(1000);
        }

#if 1
        fprintf(stderr, "MENTOR_StartEtd: r7=%d, wCsr=0x%04x, retry=%d\n", r7, wCsr, retry);
#endif

        if (retry <= 0)
        {
            //loc_6d9c
            mentor_slogf(r4, 12, 2, 1, 
                " %s : MENTOR_StartEtd - %s: TX FIFO still not Empty (%x)",
                "devu-dm816x-mg.so", "MENTOR_StartEtd", wCsr);
        }
        //loc_6de0
        int r5 = r6->Data_0 - r6->Data_0x14;

#if 1
        fprintf(stderr, "MENTOR_StartEtd: r5=%d, r6->flags=0x%x\n",
            r5, r6->flags);
#endif

        if ((r6->flags & 0x400) &&
            (r4->Data_0x50 & 0x200) &&
            (r5 > r8->wData_0x18) &&
            ((r8->wData_0x18 & 0x3f) == 0) &&
            (r8->transferType == USB_ATTRIB_BULK)) //2))
        {
            //0x00006e24
            r6->Data_0x10 = r5;
            r6->flags |= 0x800;
            //->loc_6e58
        }
        else
        {
            //loc_6e38
            r6->flags &= ~0x800;
            r6->Data_0x10 = (r5 > r8->Data_0x30->Data_0)?
                r8->Data_0x30->Data_0: r5;
        }
        //loc_6e58
        if (r6->flags & 0x04)
        {
            //0x00006e64
#ifdef MB86H60
            int sb = MGC_Read16(r4, 0x16);
//            int sb = MGC_Read16(r4, 0x106 + r7);
            fprintf(stderr, "MENTOR_StartEtd: 0x106 -> 0x%x\n", sb);
#else
            int sb = ((volatile uint16_t*)r4->Data_0x14)[0x106/2 + r7];
#endif

            if ((r8->transferType == USB_ATTRIB_ISOCHRONOUS/*1*/) || 
                (r8->transferType == USB_ATTRIB_INTERRUPT/*3*/))
            {
                sb |= (1 << 12); //0x1000; /* PID Error ?*/
            }

            if (r6->flags & 0x800)
            {
                //0x00006e94
#ifdef MB86H60
                MGC_Write16(r4, 0x14, r8->wData_0x18);
                MGC_Write16(r4, 0x16, sb & 0x2792);
//                MGC_Write16(r4, 0x104 + r7, r8->wData_0x18);
//                MGC_Write16(r4, 0x106 + r7, sb & 0x2792);
#else
                ((volatile uint16_t*)r4->Data_0x14)[0x104/2 + r7] = r8->wData_0x18;
                ((volatile uint16_t*)r4->Data_0x14)[0x106/2 + r7] = sb & 0x2792;
#endif

                if (r6->flags & 0x400)
                {
                    //0x00006ec8
#if 1
                    fprintf(stderr, "MENTOR_StartEtd: 0x00006ec8: TODO!!!\n");
#endif
                    //TODO!!!
                }
                //loc_6f00
#ifdef MB86H60
                MGC_Write16(r4, 0x16, 
                    MGC_Read16(r4, 0x16) | 0x2040 | 0x2d);
//                MGC_Write16(r4, 0x106 + r7, 
//                    MGC_Read16(r4, 0x106 + r7) | 0x2040 | 0x2d);
#else
                ((volatile uint16_t*)r4->Data_0x14)[0x106/2 + r7] = 
                    ((volatile uint16_t*)r4->Data_0x14)[0x106/2 + r7] | 0x2040 | 0x2d;
#endif
                //->loc_71bc
            } //if (r6->flags & 0x800)
            else
            {
                //loc_6f24
                int fp_0x34;
                int fp_0x2c;

                fp_0x34 = fp_0x2c = r8->wData_0x18;
                int r0 = r6->Data_0x10 / r8->wData_0x18;
                int r3;
                if ((r0 - 1) <= 0)
                {
                    r3 = 0;
                    //->loc_6f58
                }
                else
                {
                    r3 = (r6->Data_0x10 / fp_0x34) - 1;
                }
                //loc_6f58: write RXMAXP
#ifdef MB86H60
                fprintf(stderr, "MENTOR_StartEtd: 0x104 <- 0x%x\n",
                    fp_0x2c | (r3 << 11));
                MGC_Write16(r4, 0x14, fp_0x2c | (r3 << 11));
//                MGC_Write16(r4, 0x104 + r7, fp_0x2c | (r3 << 11));
#else
                ((volatile uint16_t*)r4->Data_0x14)[0x104/2 + r7] = fp_0x2c | (r3 << 11);
#endif

                int sl;
                if ((r6->flags & 0x400) == 0)
                {
                    sl = sb & 0x9fff;
                    //->loc_6fc8
                }
                else
                {
                    //0x00006f84
                    sl = sb & 0x2792;
                    sl |= 0x6000;

#if 1
                    fprintf(stderr, "MENTOR_StartEtd: 0x00006f84: TODO!!!\n");
#endif
                    //TODO!!!
                }
                //loc_6fc8: write RxCSR
#ifdef MB86H60
                fprintf(stderr, "MENTOR_StartEtd: 0x106 <- 0x%x\n",
                    sl | 0x6d);
                MGC_Write16(r4, 0x16, sl | 0x6d); //01101101
//                MGC_Write16(r4, 0x106 + r7, sl | 0x6d); //01101101
                    //Clear: RxStall, DataError/NAK Timeout, Error, RxPktRdy
                    //Set: ReqPkt
#else
                ((volatile uint16_t*)r4->Data_0x14)[0x106/2 + r7] = sl | 0x6d;
#endif

#if 0
                int i;
                for (i = 0; i < 10; i++)
                {
                    delay(100);
                    uint16_t r0 = MGC_Read16(r4, 0x16);
                    fprintf(stderr, "MENTOR_StartEtd: 0x106 -> 0x%x\n", r0);
                }
#endif
            }
            //->loc_71bc
        } //if (r6->flags & 0x04)
        else
        {
            //loc_6fe4
            int32_t r0 = r6->Data_0x10;
            uint32_t sl = r8->wData_0x18;
            r0 = r0 - 1;
            r0 = r0 + sl;
            r0 = r0 / sl;
            r0 = r0 - 1;
            if (r0 <= 0)
            {
                r0 = 0; 
                //->loc_7024
            }
            else
            {
                //0x0000700c
                r0 = r6->Data_0x10;
                r0 = r0 - 1;
                r0 = r0 + sl;
                r0 = r0 / sl;
                r0 = r0 - 1;
            }
            //loc_7024
            int sb = HW_Read16(r4, 0x102 + r7);

            if (r6->flags & 0x600)
            {
                //0x00007044
#if 1
                fprintf(stderr, "MENTOR_StartEtd: 0x00007044: TODO!!!\n");
#endif
                //TODO!!!
            }
            //loc_7160
            HW_Write16(r4, 0x100 + r7, sl | (r0 << 11));

            MENTOR_LoadFIFO(r4, fp_0x30, r6->pData, r5);

            HW_Write16(r4, 0x102 + r7, 
                (sb & ~0x9400) | 0x2080 | 0x27);
        }
    }
    //loc_71bc
}


void mentor_start_dma_transfer(struct Mentor_Controller* a, 
    struct Struct_0xa4* b, struct Struct_0xa0* c, int d,
    int e, int f, int g, int h)
{
#if 1
    fprintf(stderr, "mentor_start_dma_transfer: TODO!!!\n");
#endif

}


void MENTOR_AbortDMA_TX(struct Mentor_Controller* a, struct Struct_0xa4* b)
{
#if 1
    fprintf(stderr, "MENTOR_AbortDMA_TX: TODO!!!\n");
#endif

}


void MENTOR_AbortDMA_RX(struct Mentor_Controller* a, struct Struct_0xa4* b)
{
#if 1
    fprintf(stderr, "MENTOR_AbortDMA_RX: TODO!!!\n");
#endif

}


/* 0x00005738 - todo */
int MENTOR_ProcessETDDone(struct Mentor_Controller* sl, uint16_t r5)
{
#if 0 //No printf in ISR
    fprintf(stderr, "MENTOR_ProcessETDDone: TODO!!!\n");
#endif

    int fp_0x34;
//    void* fp_0x30 = &sl->Data_0x54;
    int r7 = 16;
    int r6 = 1;

    while ((r5 >>= 1) != 0)
    {
        //loc_5768
        if (r5 & 0x01)
        {
            //0x00005770
            struct Struct_0xa0* r8 = sl->Data_0xc4[r6];
            if (r8 == NULL)
            {
                //0x00005780
#ifdef MB86H60
                MGC_Write16(sl, 0x106 + r7, 0);
                MGC_Write16(sl, 0x102 + r7, 0);
#else
                ((volatile uint16_t*)(sl->Data_0x14))[0x106/2 + r7] = 0;
                ((volatile uint16_t*)(sl->Data_0x14))[0x102/2 + r7] = 0;
#endif
                //->loc_59e8
            }
            else
            {
                //loc_57b0
                int fp_0x2c = r8->flags;
                struct Struct_0xa4* sb = r8->Data_0x30;

                if (sb->bData_0x1f == 0)
                {
                    //0x000057c8
                    if (fp_0x2c/*r2*/ & 0x04)
                    {
                        //0x000057d0
#if MB86H60
                        uint32_t r3 = MGC_Read16(sl, 0x106 + r7);
#else
                        uint32_t r3 = ((volatile uint16_t*)(sl->Data_0x14))[0x106/2 + r7];
#endif
                        r3 = r3 << 16;
                        uint32_t r4 = r3 >> 16;
                        r3 = (r3 >> 25) & 0x01;
                        sb->Data_0x20 = r3;

                        if ((r4 & 0x14c) == 0)
                        {
                            //0x00005800
                            if ((1 << r6) & sl->Data_0x54)
                            {
                                //->loc_582c
                                atomic_clr(/*fp_0x30*/&sl->Data_0x54);
                                r4 = 8;
                                //->loc_5848
                                if (r4 & 0x400)
                                {
                                    //0x00005854
                                    MENTOR_AbortDMA_RX(sl, sb);
                                }
                                //loc_5860
                                (r8->Func_0x38)(sl, r8, 0, r4);
                                //->loc_59e8
                            } //if ((1 << r6) & sl->Data_0x54)
                            else
                            {
                                //loc_587c
#ifdef MB86H60
                                r3 = MGC_Read16(sl, 0x108 + r7);
#else
                                r3 = ((volatile uint16_t*)(sl->Data_0x14))[0x108/2 + r7];
#endif
                                fp_0x34 = r3/*r1*/;
                                if ((r3/*r1*/ + r8->Data_0x14) > r8->Data_0)
                                {
                                    //0x000058a8
                                    (r8->Func_0x38)(sl, r8, 0, 8);
                                    //->loc_59e8
                                }
                                else
                                {
                                    //loc_58c4
                                    if (fp_0x2c & 0x200)
                                    {
                                        //0x000058d0

                                        mentor_start_dma_transfer(sl, sb, r8, 0, 
                                            r6, sb->Data_0x2c, 
                                            r8->Data_8 + r8->Data_0x14,
                                            r3/*r1*/);
                                        //->loc_59e8
                                    }
                                    else
                                    {
                                        //loc_5908
                                        if ((fp_0x2c & 0x600) == 0)
                                        {
                                            //0x00005914
                                            MENTOR_ReadFIFO(sl, r8, r6, 
                                                r8->pData + r8->Data_0x14,
                                                fp_0x34);

#ifdef MB86H60
                                            MGC_Write16(sl, 0x106 + r7, (uint16_t)(r4 & ~1));
#else
                                            ((volatile uint16_t*)(sl->Data_0x14))[0x106/2 + r7] = 
                                                (uint16_t)(r4 & ~1);
#endif
                                        }
                                        //loc_595c
                                        (r8->Func_0x38)(sl, r8, fp_0x34, 0);
                                        //->loc_59e8
                                    }
                                }
                            }
                        } //if ((r4 & 0x14c) == 0)
                        else
                        {
                            //loc_5818
                            if ((1 << r6) & sl->Data_0x54)
                            {
                                //->loc_582c
                                atomic_clr(/*fp_0x30*/&sl->Data_0x54);
                                r4 = 8;
                                //->loc_5848
                            }
                            else
                            {
                                //loc_583c
                                if (r4 & 0x40)
                                {
                                    r4 = 4;
                                }
                                else
                                {
                                    r4 = 0x0f;
                                }
                            }
                            //loc_5848
                            if (fp_0x2c & 0x400)
                            {
                                //0x00005854
                                MENTOR_AbortDMA_RX(sl, sb);
                            }
                            //loc_5860
                            (r8->Func_0x38)(sl, r8, 0, r4);
                            //->loc_59e8
                        }
                    } //if (fp_0x2c/*r2*/ & 0x04)
                    else
                    {
                        //loc_5978
#ifdef MB86H60
                        uint32_t r3 = MGC_Read16(sl, 0x102 + r7);
#else
                        uint32_t r3 = ((volatile uint16_t*)(sl->Data_0x14))[0x102/2 + r7];
#endif
                        r3 = r3 << 16;
                        uint32_t r2 = r3 >> 24;
                        sb->Data_0x20 = r2 & 0x01;
                        r3 = r3 >> 16;

                        int r4;
                        if ((r3 & 0xa4) == 0)
                        {
                            r4 = 0;
                            //->loc_59d0
                        }
                        else
                        {
                            //0x000059ac
                            if (r3 & 0x20)
                            {
                                r4 = 0x04;
                            }
                            else
                            {
                                r4 = 0x0f;
                            }

                            if (fp_0x2c & 0x400)
                            {
                                //0x000059c4
                                MENTOR_AbortDMA_TX(sl, sb);
                            }
                            //loc_59d0
                        }
                        //loc_59d0
                        (r8->Func_0x38)(sl, r8, r8->Data_0x10, r4);
                        //loc_59e8
                    }
                } //if (sb->bData_0x1f == 0)
                //loc_59e8
            }
            //loc_59e8
        }
        //loc_59e8
        r7 += 16;
        r6++;
        //->loc_5768
    } //while ((r5 >>= 1) != 0)
    //loc_59f8
    return 0;
}


int mentor_alloc_dma_sched(struct Mentor_Controller* a, struct Struct_0xa4* b)
{
#if 1
    fprintf(stderr, "mentor_alloc_dma_sched: TODO!!!\n");
#endif

    return 0;
}


int mentor_claim_dma_channel(struct Mentor_Controller* a, struct Struct_0xa0* b, int c, int* d)
{
#if 1
    fprintf(stderr, "mentor_claim_dma_channel: TODO!!!\n");
#endif

    return 0;
}



/* 0x00002a80 - complete */
void mentor_get_ext_intstatus(struct Mentor_Controller* ctrl, 
            uint16_t* int_rx, uint16_t* int_tx, uint16_t* int_usb)
{
#if 0
    fprintf(stderr, "mentor_get_ext_intstatus: TODO\n");
#endif

#ifdef MB86H60

    // Bit conversion???
    *int_usb = MGC_Read8(ctrl, MGC_O_HDRC_INTRUSB);
    *int_rx = MGC_Read16(ctrl, MGC_O_HDRC_INTRRX);
    *int_tx = MGC_Read16(ctrl, MGC_O_HDRC_INTRTX);

#else //DM8xx

#define AM35X_INTR_USB_SHIFT	0
#define AM35X_INTR_USB_MASK	(0x1ff << AM35X_INTR_USB_SHIFT)

#define AM35X_INTR_RX_SHIFT	16
#define AM35X_INTR_TX_SHIFT	0
#define AM35X_TX_EP_MASK	0xffff		/* EP0 + 15 Tx EPs */
#define AM35X_RX_EP_MASK	0xfffe		/* 15 Rx EPs */
#define AM35X_TX_INTR_MASK	(AM35X_TX_EP_MASK << AM35X_INTR_TX_SHIFT)
#define AM35X_RX_INTR_MASK	(AM35X_RX_EP_MASK << AM35X_INTR_RX_SHIFT)

    struct Struct_0xe4* r4 = ctrl->Data_0xe4;

    /* Get endpoint interrupts */
    uint32_t epintr = ((volatile uint32_t*)(r4->Data_0))[0x30/4];
    ((volatile uint32_t*)(r4->Data_0))[0x30/4] = epintr; //Clear

    *int_rx = (epintr & AM35X_RX_INTR_MASK) >> AM35X_INTR_RX_SHIFT;
    *int_tx = (epintr & AM35X_TX_INTR_MASK) >> AM35X_INTR_TX_SHIFT;

    uint32_t usbintr = ((volatile uint32_t*)(r4->Data_0))[0x34/4];
    ((volatile uint32_t*)(r4->Data_0))[0x34/4] = usbintr; //Clear

    *int_usb = (usbintr & AM35X_INTR_USB_MASK) >> AM35X_INTR_USB_SHIFT;
#endif
}


/* 0x00002ac4 - complete */
void mentor_clr_ext_int(struct Mentor_Controller* a)
{
#if 0
    fprintf(stderr, "mentor_clr_ext_int: TODO\n");
#endif

    /* Empty, because all active interrupts were already cleared
        when status registers were read.*/
}


int MENTOR_RemoveTDFromEndpoint(struct Mentor_Controller* a, 
    struct Struct_10bab4* b, 
    struct Struct_0xa4* c)
{
#if 1
    fprintf(stderr, "MENTOR_RemoveTDFromEndpoint: TODO!!!\n");
#endif

    return 0;
}


/* 0x000079c0 - todo */
void MENTOR_URB_complete(struct Mentor_Controller* r5,
    struct Struct_0xa4 * r7, 
    struct Struct_0xa0* r4, 
    int transferType, int err)
{
#if 1
    fprintf(stderr, "MENTOR_URB_complete: transferType=%d, r4->flags=0x%x, r4->Data_0=%d\n",
        transferType, r4->flags, r4->Data_0);

    if ((r4->flags & PIPE_FLAGS_TOKEN_IN) && 
        (r4->Data_0 != 0) && (r4->pData != NULL))
    {
        hex_dump("MENTOR_URB_complete", r4->pData, r4->Data_0);
    }
#endif

    struct Struct_10bab4* r6 = r4->Data_0x34;
    int r8 = r4->Data_0x14;

    if (r7->bData_0x1f != 0)
    {
        //->0x00007e14
        return;
    }

    r6->Data_8 = err/*fp4 = r2*/;

    switch (transferType)
    {
        case USB_ATTRIB_CONTROL: //0:
            //0x00007a1c
            if (err != 0)
            {
                //0x00007a24
                r7->Data_0x20 = 0;

                mentor_slogf(r5, 12, 2, 1, 
                    "%s - Error on Control Transfer ( %d, %x ) ",
                    "devu-dm816x-mg.so", err, r7->Data_0x14);
            }
            //0x00007a60
            pthread_sleepon_lock();

            r6->Data_4 = 1;

            if ((r4->flags & 1) == 0)
            {
                r6->Data_0x34 += r8;
            }

            InterruptLock(&r5->Data_0xd0);

            r4->flags = 0;
            r4->Data_0x2c.Data_0 = NULL;

            r5->Data_0x94->Data_0 = r4;
            r5->Data_0x94 = &r4->Data_0x2c;

            InterruptUnlock(&r5->Data_0xd0);

            pthread_sleepon_signal(&r6->Data_4);

            pthread_sleepon_unlock();
            //->0x00007e14
            break;

#if 0
        case USB_ATTRIB_ISOCHRONOUS: //1:
            //
            //TODO!!!
            break;
#endif

        case USB_ATTRIB_BULK: //2:
            //0x00007b00
            r6->Data_0x34/*r1*/ += r8;

            if (err != 0)
            {
                //0x00007b14
                //0x00007b28
                mentor_slogf(r5, 12, 2, 1, "%s - Error on %s status 0x%x",
                    "devu-dm816x-mg.so", 
                    (transferType != USB_ATTRIB_BULK/*2*/)? "Interrupt": "Bulk", err);

                InterruptLock(&r5->Data_0xd0);

                r4->flags = 0;
                r4->Data_0x2c.Data_0 = 0;
                r5->Data_0x94->Data_0 = r4;
                r5->Data_0x94 = &r4->Data_0x2c;

                InterruptUnlock(&r5->Data_0xd0);

                MENTOR_RemoveTDFromEndpoint(r5, r6, r7);

                if (r6->Func_0x58 != NULL)
                {
                    //0x00007be4
                    (r6->Func_0x58)(r6);
                }
                //->0x00007e14
            }
            else
            {
                //0x00007bf4
                if (((r6->Data_0 & 0x04) == 0) &&
                    ((r4->flags & 0x04) != 0))
                {
                    //0x00007c0c
                    if (/*r1*/r6->Data_0x34 != r6->dwLength)
                    {
                        r6->Data_8 = 9;
                    }
                }
                //0x00007c1c
                if (((r4->flags & 0x80000000 /*< 0*/) && (r4->flags & 0x08)) || 
                    (((r4->Data_0 != r8) || (r4->flags & 0x80000000 /*< 0*/)) 
                        && (r4->flags & 0x04)))
                {
                    //0x00007c58
                    InterruptLock(&r5->Data_0xd0);

                    r4->flags = 0;
                    r4->Data_0x2c.Data_0 = 0;
                    r5->Data_0x94->Data_0 = r4;
                    r5->Data_0x94 = &r4->Data_0x2c;

                    InterruptUnlock(&r5->Data_0xd0);

                    if (r6->Func_0x58 != NULL)
                    {
                        //0x00007cc8
                        (r6->Func_0x58)(r6);
                    }
                    //->0x00007e14
                }
                else
                {
                    //0x00007cd8
                    InterruptLock(&r5->Data_0xd0);

                    r4->flags = 0;
                    r4->Data_0x2c.Data_0 = 0;
                    r5->Data_0x94->Data_0 = r4;
                    r5->Data_0x94 = &r4->Data_0x2c;

                    InterruptUnlock(&r5->Data_0xd0);
                    //->0x00007e14
                }
            }
            //->0x00007e14
            break;

#if 0
        case USB_ATTRIB_INTERRUPT: //3:
            //
            //TODO!!!
            break;
#endif

        default:
            //->0x00007e14
#if 1
            fprintf(stderr, "MENTOR_URB_complete: transferType=%d: TODO!!!\n", transferType);
#endif
            break;
    }
    //0x00007e14
    return;
}


/* 0x00007e38 - todo */
void mentor_bottom_half(struct Mentor_Controller* r5)
{
#if 0
    fprintf(stderr, "mentor_bottom_half: TODO\n");
#endif

//    int* fp_0x34 = &r5->Data_0x98;
//    pthread_mutex_t* r6 = &r5->Data_4;
//    struct intrspin* r8 = r5->Data_0xd0;
//    int sl = 0x150;

    while (1)
    {
        //0x00007e7c
        InterruptLock(&r5->Data_0xd0);

        struct Struct_0xa0* r4 = r5->Data_0x98;

#if 0
        fprintf(stderr, "mentor_bottom_half: r5->Data_0x98=%p\n",
            r5->Data_0x98);
#endif

        if (r4 == NULL)
        {
            //->0x00007f50
            break;
        }
        //0x00007ebc
        r5->Data_0x98 = r4->Data_0x2c.Data_0;
        if (r5->Data_0x98 == NULL)
        {
            r5->Data_0x9c = &r5->Data_0x98; //fp_0x34;
        }

        InterruptUnlock(&r5->Data_0xd0);

        if (pthread_mutex_lock(&r5->Data_4) != 0)
        {
            fprintf(stderr, "mutex lock %s %d\n",
                "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c", 0x943);
        }
        //0x00007f0c
        MENTOR_URB_complete(r5, 
            r4->Data_0x30, 
            r4, 
            r4->Data_0x30->transferType,
            r4->status);

        if (pthread_mutex_unlock(&r5->Data_4) != 0)
        {
            fprintf(stderr, "mutex lock %s %d\n",
                "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c", 0x946);
        }
        //->0x00007e7c
    } //while (1)
    //0x00007f50
    InterruptUnlock(&r5->Data_0xd0);
}


/* 0x00005a04 - todo */
const struct sigevent * mentor_interrupt_handler(void* a, int b)
{
//    fprintf(stderr, "mentor_interrupt_handler: TODO\n");

    struct Mentor_Controller *r4 = a;
    uint16_t int_usb;
    uint16_t int_tx;
    uint16_t int_rx;

#ifdef MB86H60
    int status = dma_GetUsbIntStatus(r4);
    if (status & 1) //USB General IRQ?
    {
#endif
    mentor_get_ext_intstatus(r4, &int_rx, &int_tx, &int_usb);

    if (int_tx & 1) //EP0?
    {
        MENTOR_ProcessControlDone(r4);
    }

    uint16_t r1 = (int_rx | int_tx) & 0xfffe;
    if (r1 != 0)
    {
        MENTOR_ProcessETDDone(r4, r1);
    }

    if (int_usb != 0)
    {
#ifdef MB86H60
#if 1
        bUsbIntStatus = int_usb;
#endif
        if ((int_usb & (1 << 6)/*Sess Req*/) != 0)
        {
            MGC_Write8(r4, MGC_O_HDRC_DEVCTL, MGC_M_DEVCTL_SESSION);
        }
#endif
        if ((int_usb & (1 << 4)/*Conn???*/) != 0)
        {
            r4->Data_0x6c = (r4->Data_0x6c | 0x02) & ~0x04;
        }
        //loc_5a80
        else if ((int_usb & 
            ((1 << 7)/*VBus Error???*/ || 
            (1 << 5)/*Discon???*/ || 
            (1 << 2)/*Reset/Babble???*/)) != 0)
        {
            r4->Data_0x6c &= ~(0x02 | 0x04);
        }
    }
    //loc_5a90
    mentor_clr_ext_int(r4);
#ifdef MB86H60
        dma_SetUsbIntClear(r4, 1);
    } //if (status & 1)
#endif

    if (r4->Data_0x98 == 0)
    {
        return NULL;
    }

    return &r4->Data_0x5c;
}


/* 0x00007f88 - todo */
static void* mentor_interrupt_thread(void* a)
{
    fprintf(stderr, "mentor_interrupt_thread: TODO\n");

    struct USB_Controller* r7 = a;
    struct Mentor_Controller* r4 = r7->hc_data;

    if (ThreadCtl(1, 0) == -1)
    {
        mentor_slogf(r4, 12, 2, 1, "%s - %s: Unable to obtain I/O privity.",
            "devu-dm816x-mg.so", "mentor_interrupt_thread");
        return (void*)-1;
    }
    //loc_8000
    r4->Data_0x5c.sigev_notify = 4;
    r4->Data_0x5c.sigev_id = r4->Data_0x44;
    r4->Data_0x5c.sigev_priority = getprio(0);
    r4->Data_0x5c.sigev_value.sival_int = 0;
    r4->Data_0x5c.sigev_code = 1;

    while ((r4->Data_0x50 & 0x10) == 0)
    {
        //loc_803c
        delay(1);
    }
    //loc_8050
#ifdef MB86H60
    r4->Data_0x48 = MB86H60_INTR_USB; //r7->Data_4->bData_0x14;
#else
//    r4->Data_0x48 = r7->pci_inf->bData_0x14...; //TODO!!!
#endif

    r4->Data_0x4c = InterruptAttach(r4->Data_0x48, mentor_interrupt_handler, r4, 0xe8, 8);
    if (r4->Data_0x4c == -1)
    {
        mentor_slogf(r4, 12, 2, 1, "%s - %s: InterruptAttach failed.",
            "devu-dm816x-mg.so", "mentor_interrupt_thread");

        return (void*)-1;
    }
    //loc_80e0
    while (1)
    {
        //loc_8100
        struct 
        {
            int fill_0; //0
            int8_t bData_4; //4
            int fill_8[2]; //8
            //16
        } fp_0x30;

        if (MsgReceivePulse(r4->Data_0x40, &fp_0x30, 16, 0) == -1)
        {
            //->loc_8154
            InterruptDetach(r4->Data_0x4c);
            break;
        }
        //0x0000811c
        if (fp_0x30.bData_4 == 1)
        {
            //0x00008128
            mentor_bottom_half(r4);
        }
        else
        {
            //loc_8134
            mentor_slogf(r4, 12, 2, 1, "%s - %s: Unknown pulse",
                "devu-dm816x-mg.so", "mentor_interrupt_thread");
        }
        //->loc_8100
    } //while (1)

    return NULL;
}


/* 0x000041b8 - todo */
int find_block_list(struct Mentor_Controller_Inner_0x8c* a, unsigned long b)
{
#if 0
    fprintf(stderr, "find_block_list: TODO!!!\n");
#endif

    int r2 = 1;

    while (r2 < b)
    {
        r2 *= 2;
    }

    uint32_t r3 = r2;

    for (r2 = 0; ((r3 % 2) == 0) && (r2 < 14); r2++)
    {
        r3 /= 2;
    }

    r2 = r2 - 3;
    if (r2 > 10)
    {
        return -1;
    }

    return r2 < 0? 0: r2;
}


/* 0x000043a0 - todo */
int mentor_init_fifo_config(struct Mentor_Controller* fp_0x40, 
        char* fconfig_string/*r6*/)
{
#if 0
    fprintf(stderr, "mentor_init_fifo_config: TODO\n");
#endif

    char* fconfig_default; //fp_0x3c
    int fp_0x38 = 64;

    struct Mentor_Controller_Inner_0x8c* fp_0x34;
    int32_t fp_0x30;
    char* fp_0x2c;
//    int sb;

    fp_0x34 = calloc(1, 0xf4);
    if (fp_0x34 == NULL)
    {
        return 12; //->loc_45bc
    }

//    fp_0x38 = 64;
    if (fconfig_string != NULL)
    {
        fconfig_default = NULL;
        //->loc_4408
//        fp_0x38 = 64;
//        sb = 4;
        //->loc_442c
    }
    else
    {
        //0x000043ec
        fconfig_default = strdup("16:8;4:16;8:64;2:128;14:512");
        if (fconfig_default != NULL)
        {
            fconfig_string = fconfig_default;
            //loc_4408
//            fp_0x38 = 64;
//            sb = 4;
            //->loc_442c
        }
        else
        {
            //loc_4418
            free(fp_0x34);
            return 12; //->loc_45bc
        }
    }
#if 0
    //loc_4428
#endif
    for (; fconfig_string != NULL; fconfig_string = fp_0x2c)
    {
        //loc_442c
        fp_0x2c = strchr(fconfig_string, 0x3b);
        if (fp_0x2c != NULL)
        {
            *fp_0x2c++ = 0;
        }

        char* r4 = strchr(fconfig_string, 0x3a);
        if (r4 != NULL)
        {
            //0x00004464
            *r4++ = 0;

            fp_0x30 = strtoul(fconfig_string, NULL, 0);

            if (r4 != NULL)
            {
                //0x00004484
                unsigned long r4_, r5; 
                r4_ = strtoul(r4, NULL, 0);
                r5 = r4_;

                *fconfig_string = 0;

                int r6_ = find_block_list(fp_0x34, r4_);
                //r7 = r6_ * 20;
                //sl = r7 + 0x18;
                //sl = fp_0x34 + sl;
                //r7 = fp_0x34 + r7;
                //r7->Data_0x20 = fp_0x30;
#if 1
                fprintf(stderr, "mentor_init_fifo_config: r6_=%d, fp_0x30=%d, r4_=%d\n",
                    r6_, fp_0x30, r4_);
#endif
                fp_0x34->Data_0x18[r6_].Data_8 = fp_0x30;
                fp_0x34->Data_0x18[r6_].Data_0x10 = calloc(fp_0x30, 16);

                if (fp_0x34->Data_0x18[r6_].Data_0x10 == NULL)
                {
                    //loc_44fc
                    free(fconfig_default);
                    return 12; //->loc_45bc
                }
                //0x000044ec
//                if (fp_0x30/*r7*/ > 0)
                {
                    //loc_450c
//                    int r0 = fp_0x38;
                    int32_t r3; // = 0;
                    //r1 = &fp_0x34->Data_0x18[r6_].Data_0x10;
                    //ip = &fp_0x34->Data_0x18[r6_].Data_0xc;
                    //r8 = 1;
                    for (r3 = 0; r3 < fp_0x30/*r7*/; r3++)
                    {
                        //loc_452c
                        //r2 = r3*16;
                        fp_0x34->Data_0x18[r6_].Data_0x10[r3].Data_0 = r4_;
                        fp_0x34->Data_0x18[r6_].Data_0x10[r3].Data_4 = fp_0x38/*r0*/;
                        fp_0x34->Data_0x18[r6_].Data_0x10[r3].Data_0xc = 
                            &fp_0x34->Data_0x18[r6_]/*sl*/;
                        fp_0x34->Data_0x18[r6_].Data_0x10[r3].Data_8 = r3;

                        fp_0x34->Data_0x18[r6_].Data_0xc |= (1/*r8*/ << r3);
                        
                        fp_0x38/*r0*/ += r5;
                    } //for (r3 = 0; r3 < fp_0x30/*r7*/; r3++)
                    //0x00004578
//                    fp_0x38 += r5 + (fp_0x30 - 1) * r5;
                }
                //loc_4590
            }
            //loc_4590
        }
        //loc_4590
//        fconfig_string = fp_0x2c;
        //loc_442c
    }
//    while (fp_0x2c != NULL);
    //0x0000459c
    if (fconfig_default != NULL)
    {
        free(fconfig_default);
    }

    fp_0x40->Data_0x8c = fp_0x34;

    return 0;
}


/* 0x000045cc - complete */
int mentor_fifo_init(struct Mentor_Controller* cntrl, char* fconfig)
{
#if 0
    fprintf(stderr, "mentor_fifo_init: TODO\n");
#endif

    uint8_t epInfo;
    uint8_t configData;
    uint8_t dynFifo;

    uint8_t rxFifoSize;
    uint8_t txFifoSize;
    uint16_t rxFifoAddr;
    uint16_t txFifoAddr;


#if 1
    fprintf(stderr, "hwvers=0x%x\n", MGC_Read16(cntrl, 0x6c));

    epInfo = MGC_Read8(cntrl, 0x78);
    fprintf(stderr, "mentor_fifo_init: epInfo=0x%x, Rx=%d, Tx=%d\n", 
        epInfo, (epInfo >> 4), (epInfo & 0x0f));

    int i;
    for (i = 0; i < 6; i++)
    {
        MGC_SelectEnd(cntrl, i);

        if (i == 0)
        {
            configData = MGC_Read8(cntrl, 0x1f);
            dynFifo = (configData & (1 << 2))? 1: 0;

            fprintf(stderr, "mentor_fifo_init: configData=0x%x DynFIFO=%d, SoftConE=%d\n", 
                configData,
                dynFifo,
                (configData & (1 << 1))? 1: 0);
        }
        else
        {
            uint8_t fifoSize = MGC_Read8(cntrl, 0x1f);
            rxFifoSize = (fifoSize >> 4);
            txFifoSize = (fifoSize & 0x0f);

            fprintf(stderr, 
                "mentor_fifo_init: FifoSize[%d]=0x%x, Rx=0x%x(%d bytes), Tx=0x%x(%d bytes)\n", 
                i, fifoSize,
                rxFifoSize, 1 << rxFifoSize,
                txFifoSize, 1 << txFifoSize);
        }
    }

    if (dynFifo)
    {
        for (i = 1; i < 6; i++)
        {
            MGC_SelectEnd(cntrl, i);

            rxFifoSize = MGC_Read8(cntrl, MGC_O_HDRC_RXFIFOSZ);
            txFifoSize = MGC_Read8(cntrl, MGC_O_HDRC_TXFIFOSZ);
            rxFifoAddr = MGC_Read16(cntrl, MGC_O_HDRC_RXFIFOADD);
            txFifoAddr = MGC_Read16(cntrl, MGC_O_HDRC_TXFIFOADD);

            fprintf(stderr, "mentor_fifo_init(1): %d: Rx(%d/%d), Tx(%d/%d)\n", i,
                rxFifoSize, rxFifoAddr, txFifoSize, txFifoAddr);
        }
    }
#endif

#ifdef MB86H60
    if (dynFifo)
    {
        MGC_SelectEnd(cntrl, 0);
        MGC_Write8(cntrl, MGC_O_HDRC_RXFIFOSZ, 3);
        MGC_Write16(cntrl, MGC_O_HDRC_RXFIFOADD, 0);
        MGC_Write8(cntrl, MGC_O_HDRC_TXFIFOSZ, 3);
        MGC_Write16(cntrl, MGC_O_HDRC_TXFIFOADD, 0);
    }
#else
    ((volatile uint8_t*)(cntrl->Data_0x14))[0x0e] = 0;
    ((volatile uint8_t*)(cntrl->Data_0x14))[0x63] = 0x03; //RXFIFOSZ
    ((volatile uint16_t*)(cntrl->Data_0x14))[0x66/2] = 0; //RXFIFOADD
    ((volatile uint8_t*)(cntrl->Data_0x14))[0x62] = 0x03; //TXFIFOSZ
    ((volatile uint16_t*)(cntrl->Data_0x14))[0x64/2] = 0; //TXFIFOADD
#endif

    mentor_init_fifo_config(cntrl, fconfig);

#if 1
    if (dynFifo)
    {
        int j;
        for (j = 0; j < 6; j++)
        {
            MGC_SelectEnd(cntrl, j);

            fprintf(stderr, "mentor_fifo_init(2): %d: Rx(%d/%d), Tx(%d/%d)\n", j,
                MGC_Read8(cntrl, MGC_O_HDRC_RXFIFOSZ),
                MGC_Read16(cntrl, MGC_O_HDRC_RXFIFOADD),
                MGC_Read8(cntrl, MGC_O_HDRC_TXFIFOSZ),
                MGC_Read16(cntrl, MGC_O_HDRC_TXFIFOADD));
        }
    }
#endif

    return 0;
}


/* 0x00004f3c - complete */
int mentor_init()
{
#if 0
    fprintf(stderr, "mentor_init\n");
#endif

    return 0;
}


/* 0x00004f44 - complete */
int mentor_shutdown()
{
    fprintf(stderr, "mentor_shutdown\n");

    return 0;
}


/* 0x00004fa8 - todo */
int mentor_controller_shutdown()
{
    fprintf(stderr, "mentor_controller_shutdown\n");

    return 0;
}


/* 0x00005f98 - todo */
int MENTOR_AllocateTD(struct Mentor_Controller* r4)
{
#if 0
    fprintf(stderr, "MENTOR_AllocateTD: TODO!!!\n");
#endif

    uint32_t i;
    struct Struct_0xa0* r5;

    r4->Data_0x90.Data_0 = NULL;
    r4->Data_0x94 = &r4->Data_0x90;

    r4->Data_0x98 = NULL;
    r4->Data_0x9c = &r4->Data_0x98;

    r5 = calloc(1, (r4->Data_0x74 + 1) * sizeof(struct Struct_0xa0));
    if (r5 == NULL)
    {
        return 12;
    }

    r4->Data_0xa0 = r5;

    memset(r5, 0, (r4->Data_0x74 + 1) * sizeof(struct Struct_0xa0));

    for (i = 0; i < r4->Data_0x74; i++)
    {
        r5->Data_0x2c.Data_0 = NULL;
        r4->Data_0x94->Data_0 = r5;
        r4->Data_0x94 = &r5->Data_0x2c;
        r5++;
    }

    return 0;
}


/* 0x00006050 - todo */
int MENTOR_AllocateED(struct Mentor_Controller* r5)
{
#if 0
    fprintf(stderr, "MENTOR_AllocateED: TODO!!!\n");
#endif

    uint32_t i;
    struct Struct_0xa4* r4;
    
    r4 = calloc(1, (r5->Data_0x70 + 1) * sizeof(struct Struct_0xa4));
    if (r4 == NULL)
    {
        return 12;
    }

    r5->Data_0xa4 = r4;

    memset(r4, 0, (r5->Data_0x70 + 1) * sizeof(struct Struct_0xa4));

    r4->Data_8__ = 0;
    r4->Data_0xc = &r4->Data_8__;
    r4->Data_0x10 = 0;
    r5->Data_0xa8 = r4;

    for (i = 0; i < r5->Data_0x70; i++)
    {
        r4->Data_0x2c = -1;
        r4->Data_0 = r4 + 1;
        r4->Data_0->Data_4 = r4;
        r4->Data_0->Data_8__ = 0;
        r4->Data_0->Data_0xc = &r4->Data_0->Data_8__;
        r4->Data_0->Data_0x10 = 0;

        r4++;
    }

    r4->Data_0 = r5->Data_0xa8;
    r5->Data_0xa8->Data_4 = r4;

    return 0;
}



/* 0x00005340 - todo */
struct Struct_0xa4* MENTOR_GetEDPool(struct Mentor_Controller* a)
{
#if 0
    fprintf(stderr, "MENTOR_GetEDPool: TODO!!!\n");
#endif

    struct Struct_0xa4* r4;
    struct Struct_0xa4* r6 = a->Data_0xa8;

    if (pthread_mutex_lock(&a->Data_4) != 0)
    {
        fprintf(stderr, "mutex error\n"/*TODO*/);
    }
    //loc_538c
    r4 = r6->Data_0;
    if (r4 == r6)
    {
        if (pthread_mutex_unlock(&a->Data_4) == 0)
        {
            r4 = 0;
            //->loc_5428
        }
        else
        {
            fprintf(stderr, "mutex error\n"/*TODO*/);
            r4 = 0;
            //->loc_5428
        }
    }
    else
    {
        //loc_53d4
        r6->Data_0 = r4->Data_0;
        r4->Data_0->Data_4 = r6;
        r4->Data_0x10 |= 0x80000000;
        r4->Data_0x38 = 0;

        if (pthread_mutex_unlock(&a->Data_4) != 0)
        {
            fprintf(stderr, "mutex error\n"/*TODO*/);
        }
    }
    //loc_5428
    return r4;
}



/* 0x0000544c - todo */
int MENTOR_BuildEDList(struct Mentor_Controller* a, struct Struct_0xa4** b)
{
#if 0
    fprintf(stderr, "MENTOR_BuildEDList: TODO!!!\n");
#endif

    struct Struct_0xa4* r3;
    
    r3 = MENTOR_GetEDPool(a);
    if (r3 == NULL)
    {
        return 12;
    }

    *b = r3;
    r3->Data_0x10 |= 0x40000008;
    r3->Data_8__ = 0;
    r3->Data_0xc = &r3->Data_8__;
    r3->Data_4 = r3;
    r3->Data_0 = r3;

    return 0;

}


/* 0x00002e08 - todo */
int mentor_board_specific_init1(struct Mentor_Controller* r6)
{
#if 1
    fprintf(stderr, "mentor_board_specific_init1: TODO!!!\n");
#endif

    struct Struct_0xe4* r5;

    int sl;

    struct USB_Controller* r4 = r6->Data_0;

    r6->Data_0x38 = 0x400;
    r6->Data_0x18 = 16;
    r6->Data_0x50 |= 0x200;
    r6->Data_0xe4 = r5 = calloc(1, 0x20);

    if (r5 == NULL)
    {
        mentor_slogf(r6, 12, 2, 0, "mentor_board_specific_init1: calloc error1\n"/*TODO*/);
        sl = 12;
        //->loc_35fc
        return sl;
    }
    //loc_2e90
#ifdef MB86H60
    dma_regs = mmap_device_memory(NULL/*void * addr*/,
                           MB86H60_DMA_SIZE/*size_t len*/,
                           0xb00/*int prot*/,
                           0x10001/*int flags*/,
                            MB86H60_DMA_BASE);
#else
    r5->Data_4 = mmap_device_memory(NULL, 0x8000, 0xb00, 0x10001, 
                    0x47400000); //MB86H60: TODO!!!
    if (r5->Data_4 == -1)
    {
        mentor_slogf(r6, 12, 2, 0, "mentor_board_specific_init1: mmap_device_memory error1\n"/*TODO*/);
        sl = 12;
        //->loc_35f4
        free(r5);
        return sl;
    }
    //loc_2ef0
    r5->Data_0 = r4->pci_inf->Data_0x68 - 0x47400400 + r5->Data_4;

    if (r4->pci_inf->Data_0x68 == 0x47401c00)
    {
        r5->bData_0xc = 1;
    }
    else
    {
        //loc_2f78
        r5->bData_0xc = 0;
    }
    //loc_2f80
    ((volatile uint32_t*)(r5->Data_0))[0x14/4] = 1;

    while (((volatile uint32_t*)(r5->Data_0))[0x14/4] & 1)
    {
        //loc_2fa8
        delay(1);
    }
    //loc_2fc4
    ((volatile uint32_t*)(r5->Data_0))[0xe8/4] = 0;
    ((volatile uint32_t*)(r5->Data_0))[0xe0/4] = 2;
    ((volatile uint32_t*)(r5->Data_0))[0x70/4] = 0;
    ((volatile uint32_t*)(r5->Data_0))[0x74/4] = 0;
    ((volatile uint32_t*)(r5->Data_0))[0x14/4] &= ~0x10;
    ((volatile uint32_t*)(r5->Data_0))[0xd0/4] = 0;
#endif

    mentor_fifo_init(r6, r6->fconfig_string);

    if ((r6->Data_0x50 & 1) == 0)
    {
        sl = 0;
        //->loc_35fc
        return sl;
    }
    //0x00003030
    r5->Data_0x10 = 0x11;

//    r4 = r6->Data_0xe4;

    mentor_slogf(r6, 12, 2, 3, "devu-dm816x-mg.so: init dma");

    fprintf(stderr, "mentor_board_specific_init1: init dma: TODO!!!\n");

    //TODO!!!

    return 0;

}


/* 0x000029b4 - complete */
int mentor_board_specific_init2(struct Mentor_Controller* ctrl)
{
#if 0
    fprintf(stderr, "mentor_board_specific_init2: TODO!!!\n");
#endif

#ifdef MB86H60

    MGC_Write16(ctrl, MGC_O_HDRC_INTRTXE, 0xffff);
    MGC_Write16(ctrl, MGC_O_HDRC_INTRRXE, 0xfffe);
    MGC_Write8(ctrl, MGC_O_HDRC_INTRUSBE, (1 << 4)); //0xff);
    dma_SetUsbIntMask(ctrl, 0x7e); //Bit 0: USB General IRQ
    //TODO: USB DMA Endpoint Read/Write Request IRQ (for endpoints 1, 2, 3)

#else
    struct Struct_0xe4* r3 = ctrl->Data_0xe4;

    ((volatile uint32_t*)(r3->Data_0))[0x40/4] = 0xfffeffff; //Rx/Tx?
    ((volatile uint32_t*)(r3->Data_0))[0x44/4] = 0x1ff; //Usb Core?

    ((volatile uint16_t*)(ctrl->Data_0x14))[0x06/2] = 0xffff; //INTRTXE?
    ((volatile uint16_t*)(ctrl->Data_0x14))[0x08/2] = 0xfffe; //INTRRXE?
    ((volatile uint8_t*)(ctrl->Data_0x14))[0x0b] = /*0xf6;*/ //INTRUSBE
        (1 << 7)/*VBus Error?*/ |
        (1 << 6)/*Sess Req*/ |
        (1 << 5)/*Discon*/ |
        (1 << 4)/*Conn*/ |
        (1 << 2)/*Reset/Babble*/ |
        (1 << 1)/*Resume*/;

    ((volatile uint32_t*)(r3->Data_0))[0x38/4] = 0xfffeffff;
    ((volatile uint32_t*)(r3->Data_0))[0x3c/4] = 0x1ff;
#endif

    return 0;

}


int mentor_board_specific_shutdown2(struct Mentor_Controller* ctrl)
{
#if 1
    fprintf(stderr, "mentor_board_specific_shutdown2: TODO!!!\n");
#endif

    return 0;

}


int mentor_board_specific_shutdown1(struct Mentor_Controller* a)
{
#if 1
    fprintf(stderr, "mentor_board_specific_shutdown1: TODO!!!\n");
#endif

    return 0;

}


int MENTOR_FreeED(struct Mentor_Controller* a)
{
#if 1
    fprintf(stderr, "MENTOR_FreeED: TODO!!!\n");
#endif

    return 0;
}


int MENTOR_FreeTD(struct Mentor_Controller* a)
{
#if 1
    fprintf(stderr, "MENTOR_FreeTD: TODO!!!\n");
#endif

    return 0;
}


int mentor_destroy_completion_thread(struct USB_Controller* a)
{
#if 1
    fprintf(stderr, "mentor_destroy_completion_thread: TODO!!!\n");
#endif

    return 0;
}


char* mentor_opts[] = 
{
    "verbose",
    "num_ed",
    "num_td",
    "prio",
    "dirq",
    "nodma",
    "fconfig",
    "dma_reserve",
    "num_dma",
    "isoc_pio",
    "no_cfg_pmic",
    "ctrl_noping",
    0,
};


/* 0x0000615c - todo */
int mentor_controller_init(struct USB_Controller* r7, int b, char* r5)
{
    fprintf(stderr, "mentor_controller_init: r5='%s'\n", r5);

    struct Mentor_Controller* r4;

#ifdef MB86H60
    r7->cname = "mb86h60";
#else
    r7->cname = "dm816x";
#endif

    if ((r7->hc_data = r4 = calloc(1, 0xe8)) == NULL)
    {
        return 12;
    }

    r4->Data_0 = r7;
    r4->Data_0x58 = 0x18;
    r4->verbosity = 5; //0;
    r4->Data_0x70 = 0xaa;
    r4->Data_0x74 = 0x60;
    r4->Data_0x7c = 1000;
    r4->Data_0x6c = 0x04;
    r4->Data_0x50 = 0x40 | 0x04; // | 0x01/*dma?*/;
    r4->Data_0x2c = -1;
    r4->Data_0x28 = -1;
    r4->Data_0x18 = 4;
    r4->Data_0x38 = 0x200;

    pthread_mutexattr_t fp_0x48;
    char* fp_0x4c = r5;
    char* fp_0x50;
    struct sched_param fp_0x78;
    pthread_attr_t fp_0xc4;

    if (r5 != NULL)
    {
        //loc_6414
        //r8 = &fp_0x4c;
        //sl = 0xf0;
        while (r5[0] != 0)
        {
            //loc_6218
            switch (getsubopt(&fp_0x4c, mentor_opts, &fp_0x50))
            {
                case 0:
                    //loc_6264: "verbose"
                    if (fp_0x50 == NULL)
                    {
                        r4->verbosity = 5;
                    }
                    else
                    {
                        r4->verbosity = strtol(fp_0x50, 0, 10);
                    }
                    //->loc_6404
                    break;

                case 5:
                    //loc_6328?: "nodma"
                    r4->Data_0x50 &= ~1;
                    //->loc_6404
                    break;

                case 6:
                    //loc_6338: "fconfig"
                    if (fp_0x50 != NULL)
                    {
                        r4->fconfig_string = strdup(fp_0x50);
                    }
                    //->loc_6404
                    break;

                default:
                    //loc_63d4
#if 0
                    mentor_slogf(r4, 12, 2, 0, "%s : %s - Unknown option %s", "", "", fp_0x50);
#endif
                    break;
            }
            //loc_6404
            r5 = fp_0x4c;
            if (r5 == NULL)
            {
                //->loc_6448
                break;
            }
        } //while (r5[0] != 0)
        //loc_6448
    }
    //loc_6448
    r7->MaxTransferSize = 0x8000;

    pthread_mutexattr_init(&fp_0x48);
    pthread_mutexattr_setrecursive(&fp_0x48, 2);
    int res = pthread_mutex_init(&r4->Data_4/*r8*/, &fp_0x48);
    if (res != 0)
    {
        mentor_slogf(r4, 12, 2, 0, "%s : %s - Unable to initialize mutex", "", "");
        //->loc_69d4
        free(r4);
        return res;
    }
    //loc_64c0
    res = pthread_mutex_init(&r4->Data_0xc/*sl*/, &fp_0x48);
    if (res != 0)
    {
        mentor_slogf(r4, 12, 2, 0, "%s : %s - Unable to initialize mutex", "", "");
        //->loc_69cc
        pthread_mutex_destroy(&r4->Data_4/*r8*/);
        free(r4);
        return res;
    }
    //loc_6518
    r4->Data_0x14 = mmap_device_memory(NULL/*void * addr*/,
                           0x2000/*size_t len*/,
                           0xb00/*int prot*/,
                           0x10001/*int flags*/,
#ifndef MB86H60
                            0);
//                           *(uint64_t*)(char*)&(r7->Data_4->Data_0x68)/*uint64_t physical*/);
                            //UNALIGNED_RET64(r7->Data_4->Data_0x68_));
                            //ENDIAN_BE64(*((uint64_t*)(r7->Data_4->Data_0x68_))));
#else
                            MB86H60_USB_BASE);
#endif
    if (r4->Data_0x14 == -1)
    {
        return errno;
    }
    //loc_6584
    struct Mentor_Controller* sb = r7->hc_data;

    sb->Data_0x40 = ChannelCreate(0x08);
    if (sb->Data_0x40 < 0)
    {
        mentor_slogf(r4, 12, 2, 0, "%s : %s - Unable to create channel", "", "");
        //->loc_66f8
        //TODO!!!
    }
    else
    {
        //loc_65e4
        sb->Data_0x44 = ConnectAttach(0, 0, sb->Data_0x40, 0x40000000, 0);
        if (sb->Data_0x44 < 0)
        {
            mentor_slogf(r4, 12, 2, 0, "%s : %s - Unable to connect to channel", "", "");
            //->loc_66f0
            //TODO
        }
        else
        {
            //loc_6648
            pthread_attr_init(&fp_0xc4/*r5*/);
            pthread_attr_setschedpolicy(&fp_0xc4, 2);
            fp_0x78.sched_priority = sb->Data_0x58;
            pthread_attr_setschedparam(&fp_0xc4, &fp_0x78);
            pthread_attr_setinheritsched(&fp_0xc4, 2);
            pthread_attr_setdetachstate(&fp_0xc4, 1);

            res = pthread_create(&sb->Data_0x3c, &fp_0xc4, mentor_interrupt_thread, r7);
            if (res != 0)
            {
                mentor_slogf(r4, 12, 2, 0, "%s : %s - Unable to create interrupt thread", "", "");

                ConnectDetach(sb->Data_0x44);
                //loc_66f0
                ChannelDestroy(sb->Data_0x40);
                //loc_66f8
                //TODO!!!
            }
            else
            {
                //loc_6700
                struct Mentor_Controller* r2 = r7->hc_data;

                r7->AvailableBandwidth = 1000;
                r7->capabilities = 0x4000064f;
                r7->MaxTransferSize = 0x8000;
                r7->MaxUnalignedTransferSize = 0x8000;
                r7->buff_alignment_mask = 3;

                if ((r2->Data_0x50 & 0x01) == 0)
                {
                    r7->capabilities = 0x4000044f;
                }

                res = MENTOR_AllocateTD(r4);
                if (res != 0)
                {
                    //->loc_69a8
                }
                else
                {
                    res = MENTOR_AllocateED(r4);
                    if (res != 0)
                    {
                        //->loc_69a0
                    }
                    else
                    {
                        res = MENTOR_BuildEDList(r4, &r4->Data_0xac);
                        if (res != 0)
                        {
                            //->loc_6998
                        }
                        else
                        {
                            res = MENTOR_BuildEDList(r4, &r4->Data_0xb0);
                            if (res != 0)
                            {
                                //->loc_6998
                            }
                            else
                            {
                                r4->Data_0xbc = r4->Data_0xb0;

                                res = MENTOR_BuildEDList(r4, &r4->Data_0xb8);
                                if (res != 0)
                                {
                                    //->loc_6998
                                }
                                else
                                {
                                    r4->Data_0xc0 = r4->Data_0xb8;

                                    res = MENTOR_BuildEDList(r4, &r4->Data_0xb4);
                                    if (res != 0)
                                    {
                                        //->loc_6998
                                    }
                                    else
                                    {
                                        //0x000067b8
                                        res = mentor_board_specific_init1(r4);
                                        if (res != 0)
                                        {
                                            mentor_slogf(r4, 12, 2, 0, "%s : %s - mentor_board_specific_init1 failed", "", "");
                                            //->loc_6998
                                        }
                                        else
                                        {
                                            //loc_6808
#ifdef MB86H60
                                            MGC_Write8(r4, MGC_O_HDRC_TESTMODE, 0);
                                            MGC_Write8(r4, MGC_O_HDRC_DEVCTL, 0);
#else
                                            ((volatile uint8_t*)(r4->Data_0x14))[0x0f] = 0;
                                            ((volatile uint8_t*)(r4->Data_0x14))[0x60] = 0;
                                            ((volatile uint32_t*)(r4->Data_0x14))[0x414/4] = 0;
                                            ((volatile uint32_t*)(r4->Data_0x14))[0x404/4] = 0x1008;
#endif

                                            res = mentor_board_specific_init2(r4);
                                            if (res != 0)
                                            {
                                                mentor_slogf(r4, 12, 2, 0, "%s : %s - mentor_board_specific_init2 failed", "", "");
                                                //->loc_6990
                                            }
                                            else
                                            {
                                                //loc_6898
                                                r4->Data_0xc4 = calloc(r4->Data_0x18, 4);
                                                if (r4->Data_0xc4 == NULL)
                                                {
                                                    mentor_slogf(r4, 12, 2, 0, "%s : %s - calloc failed", "", "");
                                                    //->loc_6984
                                                }
                                                else
                                                {
                                                    //loc_68f0
                                                    r4->Data_0xc8 = calloc(r4->Data_0x18, 4);
                                                    if (r4->Data_0xc8 == NULL)
                                                    {
                                                        mentor_slogf(r4, 12, 2, 0, "%s : %s - calloc failed", "", "");
                                                        free(r4->Data_0xc4);
                                                        //->loc_6984
                                                        //TODO!!!
                                                    }
                                                    else
                                                    {
                                                        //loc_6950
                                                        r4->Data_0x50 |= 0x10;

#ifdef MB86H60
                                                        MGC_Write8(r4, MGC_O_HDRC_POWER,
                                                            MGC_M_POWER_SOFTCONN|MGC_M_POWER_HSENAB);
                                                        MGC_Write8(r4, MGC_O_HDRC_DEVCTL, MGC_M_DEVCTL_SESSION);
#else
                                                        ((volatile uint8_t*)(r4->Data_0x14))[0x01] = 0x60;
                                                        ((volatile uint8_t*)(r4->Data_0x14))[0x60] = 0x01;
#endif

                                                        return 0;
                                                    }
                                                }
                                                //loc_6984
                                                mentor_board_specific_shutdown2(r4);
                                                res = 12;
                                            }
                                            //loc_6990
                                            mentor_board_specific_shutdown1(r4);
                                        }
                                    }
                                }
                            }
                        }
                        //loc_6998
                        MENTOR_FreeED(r4);
                    }
                    //loc_69a0
                    MENTOR_FreeTD(r4);
                }
                //loc_69a8
                InterruptDetach(r4->Data_0x4c);
                mentor_destroy_completion_thread(r7);
                //loc_69b8
                munmap_device_memory(r4->Data_0x14, 0x2000);
                //loc_69c4
                pthread_mutex_destroy(&r4->Data_0xc/*sl*/);
                //loc_69cc
                pthread_mutex_destroy(&r4->Data_4/*r8*/);
                //loc_69d4
                free(r4);
            }
        }
    }

    return res;
}


void mentor_ulpi_write()
{
    fprintf(stderr, "mentor_ulpi_write: TODO!!!\n");

}


void mentor_board_specific_reset()
{
    fprintf(stderr, "mentor_board_specific_reset: TODO!!!\n");

}


/* 0x00006b1c - todo */
int mentor_check_port_status(struct USB_Controller* a, uint32_t* b)
{
    struct Mentor_Controller* r4 = a->hc_data;

#if 0
    fprintf(stderr, "mentor_check_port_status: r4->Data_0x6c=0x%x\n", r4->Data_0x6c);
#endif

    if (r4->Data_0x6c & 0x04)
    {
        *b = 0;
    }
    else
    {
        *b = 1;

        r4->Data_0x6c |= 0x04;

        if ((r4->Data_0x6c & 0x02) == 0)
        {
#ifdef MB86H60
            if ((MGC_Read8(r4, MGC_O_HDRC_DEVCTL) & MGC_M_DEVCTL_SESSION) == 0)
            {
                uint8_t r3 = MGC_Read8(r4, MGC_O_HDRC_DEVCTL);
#else
            if ((((volatile uint8_t*)(r4->Data_0x14))[0x60] & (1 << 0)/*Session?*/) == 0)
            {
                uint8_t r3 = ((volatile uint8_t*)(r4->Data_0x14))[0x60];
#endif

                mentor_slogf(r4, 12, 2, 1, "%s - %s: Session off %x, trying to recover ...",
                    "devu-dm816x-mg.so", "mentor_check_port_status", r3);

                delay(10);

                if (r4->Data_0x50 & 0x100)
                {
                    mentor_ulpi_write(r4, 0x05, 0x20);

                    delay(5);
                    //->loc_6bf4
                }
                else
                {
                    //loc_6bec
                    mentor_board_specific_reset(r4);
                }
                //loc_6bf4
#ifdef MB86H60
                MGC_Write8(r4, MGC_O_HDRC_DEVCTL, MGC_M_DEVCTL_SESSION);
#else
                ((volatile uint8_t*)(r4->Data_0x14))[0x60] = 1;
#endif

                delay(1);

#ifdef MB86H60
                if ((MGC_Read8(r4, MGC_O_HDRC_DEVCTL) & MGC_M_DEVCTL_SESSION) == 0)
                {
                    uint8_t r3 = MGC_Read8(r4, MGC_O_HDRC_DEVCTL);
#else
                if ((((volatile uint8_t*)(r4->Data_0x14))[0x60] & (1 << 0)/*Session?*/) == 0)
                {
                    //0x00006c18
                    uint8_t r3 = ((volatile uint8_t*)(r4->Data_0x14))[0x60];
#endif

                    mentor_slogf(r4, 12, 2, 1, "%s - %s: Session recover failed %x",
                        "devu-dm816x-mg.so", "mentor_check_port_status", r3);
                    //->loc_6c9c
                }
                else
                {
                    //loc_6c60
                    mentor_slogf(r4, 12, 2, 1, "%s - %s: Session recover sucessful",
                        "devu-dm816x-mg.so", "mentor_check_port_status");
                }
            } //if ((((volatile uint8_t*)(r4->Data_0x14))[0x60] & (1 << 0)/*Session?*/) == 0)
            //loc_6c9c
        } //if ((r4->Data_0x6c & 0x02) == 0)
        //loc_6c9c
    }
    //loc_6c9c
    return 0;
}


/* 0x00004f00 - complete */
int mentor_check_device_connected(struct USB_Controller* a, int b)
{
#if 1
    fprintf(stderr, "mentor_check_device_connected: b = %d, TODO!!!\n", b);
#endif

    return ((a->hc_data->Data_0x6c & 0x02) == 0)? -1: 0;
}


/* 0x00005044 - complete */
int mentor_clear_port_feature(struct USB_Controller* a, int b, int c)
{
#if 1
    fprintf(stderr, "mentor_clear_port_feature: b=%d, c=%d, TODO!!!\n", b, c);
#endif

    struct Mentor_Controller* ctrl = a->hc_data;

    switch (c)
    {
        case 3:
#ifdef MB86H60
            MGC_Write8(ctrl, MGC_O_HDRC_POWER, 
                MGC_Read8(ctrl, MGC_O_HDRC_POWER) & ~MGC_M_POWER_SUSPENDM);
            MGC_Write8(ctrl, MGC_O_HDRC_POWER, 
                MGC_Read8(ctrl, MGC_O_HDRC_POWER) | MGC_M_POWER_SUSPENDM);
#else
            ((volatile uint8_t*)(ctrl->Data_0x14))[1] &= ~(1 << 1);
            ((volatile uint8_t*)(ctrl->Data_0x14))[1] |= (1 << 1);
#endif

            delay(20);

#ifdef MB86H60
            if (MGC_Read8(ctrl, MGC_O_HDRC_POWER) & MGC_M_POWER_SUSPENDM)
#else
            if (((volatile uint8_t*)(ctrl->Data_0x14))[1] & (1 << 1))
#endif
            {
                return -1;
            }
            break;
    }

    return 0;
}


/* 0x000050a8 - complete */
int mentor_set_port_feature(struct USB_Controller* a, int b, int c)
{
#if 1
    fprintf(stderr, "mentor_set_port_feature: b=%d, c=%d, TODO!!!\n", b, c);
#endif

    struct Mentor_Controller* ctrl = a->hc_data;

    switch (c)
    {
        case 2:
            //loc_50cc
#ifdef MB86H60

#if 1
            MGC_Write8(ctrl, MGC_O_HDRC_POWER, 
                MGC_Read8(ctrl, MGC_O_HDRC_POWER) | MGC_M_POWER_RESET);
#endif
            {
                uint8_t bData = MGC_Read8(ctrl, MGC_O_HDRC_POWER);
                uint16_t wData = MGC_Read16(ctrl, 0x12);
                fprintf(stderr, "bData=0x%02x, wData=0x%04x\n", bData, wData);
            }
#else
            ((volatile uint8_t*)(ctrl->Data_0x14))[1] |= (1 << 3);
#endif

            delay(20);

#ifdef MB86H60

#if 1
            MGC_Write8(ctrl, MGC_O_HDRC_POWER, 
                MGC_Read8(ctrl, MGC_O_HDRC_POWER) & ~MGC_M_POWER_RESET);
#endif

            {
                uint8_t bData = MGC_Read8(ctrl, MGC_O_HDRC_POWER);
                uint16_t wData = MGC_Read16(ctrl, 0x12);
                fprintf(stderr, "bData=0x%02x, wData=0x%04x\n", bData, wData);
            }

#else
            ((volatile uint8_t*)(ctrl->Data_0x14))[1] &= ~(1 << 3);
#endif
            break;

        case 3:
            //loc_50f8
#ifdef MB86H60
            MGC_Write8(ctrl, MGC_O_HDRC_POWER, 
                MGC_Read8(ctrl, MGC_O_HDRC_POWER) | MGC_M_POWER_SUSPENDM);
#else
            ((volatile uint8_t*)(ctrl->Data_0x14))[1] |= (1 << 1);
#endif
            break;

        default:
            break;
    }

    return 0;
}


/* 0x00005110 - complete */
int mentor_get_root_device_speed(struct USB_Controller* a, int b)
{
#if 1
    fprintf(stderr, "mentor_get_root_device_speed: b=%d, TODO!!!\n", b);
#endif

    struct Mentor_Controller* ctrl = a->hc_data;

    delay(200);

#ifdef MB86H60
    if ((MGC_Read8(ctrl, MGC_O_HDRC_DEVCTL) & MGC_M_DEVCTL_LSDEV) != 0)
    {
        return 1;
    }
    else if ((MGC_Read8(ctrl, MGC_O_HDRC_POWER) & MGC_M_POWER_HSMODE) != 0)
    {
        return 2;
    }
#else
    if ((((volatile uint8_t*)(ctrl->Data_0x14))[0x60] & 0x20) != 0)
    {
        return 1;
    }
    else if ((((volatile uint8_t*)(ctrl->Data_0x14))[0x01] & 0x10) != 0)
    {
        return 2;
    }
#endif

    return 0;
}


int mentor_get_timer_from_controller(struct USB_Controller* a)
{
#if 1
    fprintf(stderr, "mentor_get_timer_from_controller: TODO!!!\n");
#endif

    return 0;
}



/* 5278 - todo */
void MENTOR_PutEDPool(struct Mentor_Controller* r4, struct Struct_0xa4* r5)
{
#if 1
    fprintf(stderr, "MENTOR_PutEDPool: TODO!!!\n");
#endif

}


/* 99d0 - todo */
int MENTOR_InitializeEndpoint(struct Mentor_Controller* r7, 
    struct USB_Controller_Inner_0x7c* r5, 
    struct Struct_112b08* r4)
{
#if 1
    fprintf(stderr, "MENTOR_InitializeEndpoint: TODO!!!\n");
#endif

    struct Struct_0xa4* r1 = r4->Data_0xc;
    if (r1 == NULL)
    {
        r1 = MENTOR_GetEDPool(r7);
        if (r1 == NULL)
        {
            mentor_slogf(r7, 12, 2, 1, "%s - No ED for Endpoint",
                "devu-dm816x-mg.so");

            return 12;
        }
        //9a40
        r4->Data_0xc = r1;
        r1->Data_0x34 = r4;
        r1->Data_0x28 = -1;
    }
    //9a50
    r1->transferType = r4->endpoint_descriptor.bmAttributes & 0x03;
    r1->wData_0x18 = r4->endpoint_descriptor.wMaxPacketSize;
    r1->bData_0x1b = r4->endpoint_descriptor.bEndpointAddress & ~0x7f;
    r1->Data_0x20 = 0;
    r1->Data_0x14 = ((r5->device_address & 0x7f) << 4) | 
            (r4->endpoint_descriptor.bEndpointAddress & 0x0f);

    switch (r5->bData_0xc & 0x03)
    {
        case 1:
            r1->bData_0x1c = 0xc0;
            break;

        case 2:
            r1->bData_0x1c = 0x40;
            break;

        case 0:
            r1->bData_0x1c = 0x80;
            break;
    }
    //9ac4
    r1->Data_0x24 = r4->endpoint_descriptor.bInterval;

    if ((r1->bData_0x1c != 0x40) &&
        (r5->Data_0x1c != NULL))
    {
        struct USB_Controller_Inner_0x7c* r3;
        while (1)
        {
            //9ae4
            r3 = r5->Data_0x1c;

            if (r3->bData_0xc == 2)
            {
                break;
            }

            if (r3->Data_0x1c == NULL)
            {
                break;
            }
            
            r5 = r3;
        }
        //9b04
        if (r5 == NULL)
        {
            MENTOR_PutEDPool(r7, r1);

            return -1;
        }
        //9b1c
        r1->bData_0x1d = r3->device_address;
        r1->bData_0x1e = r5->Data_0x20;

        return 0;
    }
    //9b34
    return 0;
}


int MENTOR_FreeEtd(struct Mentor_Controller* a, 
    struct Struct_0xa4* r4)
{
#if 1
    fprintf(stderr, "MENTOR_FreeEtd: TODO!!!\n");
#endif

}


/* 51b4 - todo */
int MENTOR_HookED(struct Mentor_Controller* a, 
    struct Struct_0xa4* r6, 
    struct Struct_0xa4* r4)
{
#if 1
    fprintf(stderr, "MENTOR_HookED: TODO!!!\n");
#endif

    if (pthread_mutex_lock(&a->Data_4) != 0)
    {
        fprintf(stderr, "mutex lock %s %d\n", 
            "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c", 0x2f2);
    }
    //5204
    r6->Data_4->Data_0 = r4;
    r4->Data_0 = r6;
    r6->Data_4 = r4;
    r4->Data_4 = r6->Data_4;
    r4->Data_8__ = 0;
    r4->Data_0xc = &r4->Data_8__;

    if (pthread_mutex_unlock(&a->Data_4) != 0)
    {
        fprintf(stderr, "mutex lock %s %d\n", 
            "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c", 0x2fd);
    }

    return 0;
}


/* 9c9c - complete */
int mentor_ctrl_endpoint_enable(struct USB_Controller* a, 
    struct USB_Controller_Inner_0x7c* b, 
    struct Struct_112b08* c)
{
#if 1
    fprintf(stderr, "mentor_ctrl_endpoint_enable: a=%p, b=%p, c=%p\n",
        a, b, c);
#endif

    struct Mentor_Controller* r5 = a->hc_data;
    struct Struct_0xa4* r7 = c->Data_0xc;

#if 1
    fprintf(stderr, "mentor_ctrl_endpoint_enable: r5=%p, r7=%p\n",
        r5, r7);
#endif

    int r4 = MENTOR_InitializeEndpoint(r5, b, c);

    if (r4 == 0)
    {
        if (r7 == NULL)
        {
            c->Data_0xc->Data_0x24 = 0;

            MENTOR_HookED(r5, r5->Data_0xac, c->Data_0xc);
        }
    }

    return r4;
}


/* 0x00008184 - todo */
struct Struct_0xa0* MENTOR_TD_Setup(struct Mentor_Controller* a, 
    struct Struct_10bab4* b, struct Struct_0xa4* c, int flags)
{
#if 0
    fprintf(stderr, "MENTOR_TD_Setup: TODO!!!\n");
#endif

    struct Struct_0xa0* td; //r4

    InterruptLock(&a->Data_0xd0);

    td = a->Data_0x90.Data_0;
    if (td == NULL)
    {
        b->Data_8 = 12;

        InterruptUnlock(&a->Data_0xd0);

        mentor_slogf(a, 12, 2, 1, "%s - No TD's available",
            "devu-dm816x-mg.so");
    }
    else
    {
        a->Data_0x90.Data_0 = td->Data_0x2c.Data_0;
        if (a->Data_0x90.Data_0 == NULL)
        {
            a->Data_0x94 = &a->Data_0x90;
        }

        InterruptUnlock(&a->Data_0xd0);

        td->flags = flags & 0x8000003f;
        td->Data_0x14 = 0;
        td->status = 0;
        td->Data_0x30 = c;
        td->Data_0x34 = b;
    }

    return td;
}


/* 0x00004628 - todo */
void MENTOR_ReadFIFO(struct Mentor_Controller* a, 
    struct Struct_0xa0* b, uint16_t r6, int d, uint16_t r7)
{
#ifdef MB86H60
#if 0
    fprintf(stderr, "MENTOR_ReadFIFO: b=%d, r8=%d\n", b, r8);
#endif
    int i;
    for (i = 0; i < r7; i++)
    {
#if 0
        fprintf(stderr, "MENTOR_ReadFIFO: c[%d]=0x%02x\n", i, ((uint8_t*)c)[i]);
#endif

        ((uint8_t*)d)[i] = MGC_Read8(a, MGC_FIFO_OFFSET(r6));
    }
#else
    if (r7 > 3)
    {
        //0x00004640
        //TODO!!!
    }
    //loc_4688
    if (r7 != 0)
    {
        //0x00004690
        uint32_t r2;

        r2 = ((volatile uint32_t*)(a->Data_0x14))[MGC_FIFO_OFFSET(r6)/4];

        if (r7 & 2)
        {
            uint16_t wData = r2 & 0xffff;
            *((uint16_t*)d) = wData;
            d += 2;
            r2 >>= 16;
        }

        if (r7 & 1)
        {
            uint8_t bData = r2 & 0xff;
            *((uint8_t*)d) = bData;
        }
    }
#endif
    //loc_46c0
}



/* 0x000046c8 - todo */
void MENTOR_LoadFIFO(struct Mentor_Controller* a, uint16_t b, int c, uint16_t r8)
{
#ifdef MB86H60
    fprintf(stderr, "MENTOR_LoadFIFO: b=%d, r8=%d\n", b, r8);
    hex_dump("MENTOR_LoadFIFO", c, r8);
    int i;
    for (i = 0; i < r8; i++)
    {
        MGC_Write8(a, MGC_FIFO_OFFSET(b), ((uint8_t*)c)[i]);
    }
#else
    int r7;
    int r6;
    int r5;

//    b &= 0xffff;
//    uint16_t r8 = d & 0xffff;

    if (r8 > 3)
    {
//        r6 = b * 4;
        r8 -= 4;
        r7 = r8 / 4;
        //r5 = c + 4 + r7 * 4;
        uint32_t* r3 = c;
        
        do
        {
            //loc_4704
            ((volatile uint32_t*)(a->Data_0x14))[MGC_FIFO_OFFSET(b)/4] = *r3++;
        }
        while (r3 != /*r5*/(c + 4 + r7 * 4));
        
        r7++;
        c = c + r7 * 4;
        r8 = r8 & 0x03;
    }
    //loc_472c
    if (r8 & 2)
    {
        ((volatile uint16_t*)(a->Data_0x14))[MGC_FIFO_OFFSET(b)] = *((uint16_t*)c);
        c += 2;
    }
    if (r8 & 1)
    {
        ((volatile uint8_t*)(a->Data_0x14))[MGC_FIFO_OFFSET(b)] = *((uint8_t*)c);
    }
#endif
}


/* 0x00005b54 - todo */
int mentor_transfer_abort(struct USB_Controller* a, 
        struct Struct_10bab4* b, struct Struct_112b08* r5_)
{
#if 0
    fprintf(stderr, "mentor_transfer_abort: TODO!!!\n");
#endif

    struct Mentor_Controller* r4 = a->hc_data;

    if (pthread_mutex_lock(&r4->Data_4/*r7*/) != 0)
    {
        //0x00005b88
        fprintf(stderr, "mutex lock %s %d\n", 
            "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c",
            0x38b);
    }
    //0x00005ba8
    struct Struct_0xa4* r5;
    int r8;

    if (((r5 = r5_->Data_0xc) == NULL) || ((r8 = r5->Data_0x28) < 0))
    {
        //0x00005bc0
        if (pthread_mutex_unlock(&r4->Data_4/*r7*/) != 0)
        {
            //0x00005bd8
            fprintf(stderr, "mutex lock %s %d\n", 
                "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c",
                0x38e);
        }
        
        return 2;
    }
    //0x00005c00
    struct Struct_0xa0* r2 = r5->Data_8__;
    r5->bData_0x1f = 1;
    if (r8 == 0)
    {
        //0x00005c14
        HW_Write16(r4, 0x102, 0x100);
        //->0x00005d40
    }
    else
    {
        //0x00005c2c
        if (r5->bData_0x1b & 0x80)
        {
            //0x00005c38
            if ((r2 != NULL) && (r2->flags & 0x600))
            {
                MENTOR_AbortDMA_RX(r4, r5);
            }
            //0x00005c58
            HW_Write8(r4, 0x10d + r8*16, 0);
            HW_Write8(r4, 0x10b + r8*16, 0);
            uint32_t r2 = (HW_Read16(r4, 0x106 + r8*16) & 0x3f92) | 0x10;
            HW_Write16(r4, 0x106 + r8*16, r2);
            HW_Write16(r4, 0x106 + r8*16, r2);
            //->0x00005d40
        }
        else
        {
            //0x00005cc0
            if ((r2 != NULL) && (r2->flags & 0x600))
            {
                MENTOR_AbortDMA_TX(r4, r5);
            }
            //0x00005ce0
            HW_Write8(r4, 0x10b + r8*16, 0);
            HW_Write8(r4, 0x10b + r8*16, 0);
            uint32_t r2 = (HW_Read16(r4, 0x102 + r8*16) & 0x7f58) | 0x08;
            HW_Write16(r4, 0x102 + r8*16, r2);
            HW_Write16(r4, 0x102 + r8*16, r2);
        }
        //0x00005d40
    }
    //0x00005d40
    InterruptLock(&r4->Data_0xd0);

    struct Struct_0xa0* r3 = r5->Data_8__;
    while (r3 != NULL)
    {
        //0x00005d88
        r5->Data_8__ = r3->Data_0x2c.Data_0;
        if (r5->Data_8__  == NULL)
        {
            r5->Data_0xc = &r5->Data_8__;
        }
        r3->flags = 0;
        r3->Data_0x2c.Data_0 = NULL;
        r4->Data_0x94->Data_0 = r3;
        r4->Data_0x94 = &r3->Data_0x2c;
        r3 = r5->Data_8__;
    }
    //0x00005dbc
    InterruptUnlock(&r4->Data_0xd0);

    r4->Data_0xc4[r8] = NULL;

    MENTOR_FreeEtd(r4, r5);

    if (r5->transferType == USB_ATTRIB_INTERRUPT) //3)
    {
        r4->Data_0x84--;
    }

    r5->Data_0x10 &= ~0x01;

    if (pthread_mutex_unlock(&r4->Data_4/*r7*/) != 0)
    {
        fprintf(stderr, "mutex lock %s %d\n", 
            "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c",
            0x3dc);
    }

    return 0;
}


/* 0x00009378 - todo */
int MENTOR_WaitEndControl(struct USB_Controller* fp_0x30, 
    struct Struct_10bab4* r4, 
    struct Struct_112b08* fp_0x2c,
    struct Struct_0xa0* fp_0x34)
{
#if 1
    fprintf(stderr, "MENTOR_WaitEndControl: TODO!!!\n");
#endif

    struct Mentor_Controller* r8 = fp_0x30->hc_data;

#if 0
    uint16_t wData;
    int i;
    for (i = 0; i < 10; i++)
    {
        wData = MGC_Read16(r8, 0x102);

        fprintf(stderr, "MENTOR_WaitEndControl: 0x%04x\n", wData);

        if (wData & 0x200)
        {
            break;
        }
    }
    MGC_Write16(r8, 0x102, wData | 0x20);
#endif

    pthread_sleepon_lock();
    //->loc_9444
    while (r4->Data_4 == 0)
    {
        //->loc_93b4
        if (pthread_sleepon_timedwait(&r4->Data_4, 
                1000000ULL * r4->Data_0x1c) != 0)
        {
            //0x000093d4
            pthread_sleepon_unlock();

            int r2 = fp_0x34->flags;
#ifdef MB86H60
            uint16_t wCsr = MGC_Read16(r8, 0x102);
#else
            uint16_t wCsr = ((volatile uint16_t*)(r8->Data_0x14))[0x102/2];
#endif

            mentor_slogf(r8, 12, 2, 1, 
                "%s - Timeout on Control Transfer Status 0x%x 0x%x ",
                "devu-dm816x-mg.so", r2, wCsr);

            mentor_transfer_abort(fp_0x30, r4, fp_0x2c);

            r4->Data_8 = 0x0f;

            return -1;
        }
        //->loc_9444
    }
    //0x00009450
    pthread_sleepon_unlock();

    if (r4->Data_8 != 0)
    {
        return -1;
    }

    return 0;
}


/* 0x000074ec - todo */
int MENTOR_ProcessInComplete(struct Mentor_Controller* r6,
        struct Struct_0xa0* r5, int r8, int r7)
{
#if 0
    fprintf(stderr, "MENTOR_ProcessInComplete: TODO!!!\n");
#endif

    struct Struct_0xa4* r4;

    r4 = r5->Data_0x30;
    if (r4->bData_0x1f == 0)
    {
        //0x0000751c
        r5->Data_0x14 += r8;

        if ((r7 != 0) || (r5->Data_0x14 >= r5->Data_0) ||  
            ((r8 % r4->wData_0x18) || ((1 - r8) > 0)))  //TODO!!!
        {
            //0x00007564
#ifdef MB86H60
            HW_Write16(r6, 0x106 + r4->Data_0x28 * 16, 0);
#else
            ((volatile uint16_t*)(r6->Data_0x14))[0x106 + r4->Data_0x28 * 16] = 0;
#endif

            InterruptLock(&r6->Data_0xd0);

            r6->Data_0xc4[r4->Data_0x28] = NULL;
            r4->Data_0x10 &= ~0x01;
            r5->status = r7;
            r4->Data_8__ = r5->Data_0x2c.Data_0;
            if (r4->Data_8__ == 0)
            {
                r4->Data_0xc = &r4->Data_8__;
            }
            r5->Data_0x2c.Data_0 = 0;
            *(r6->Data_0x9c) = r5;
            r6->Data_0x9c = &r5->Data_0x2c;

            InterruptUnlock(&r6->Data_0xd0);
            //->0x00007620
        }
        else
        {
            //0x00007614
            MENTOR_StartEtd(r6, r5);
        }
    }
    //0x00007620
    return 0;
}


/* 0x0000549c - todo */
int MENTOR_ProcessOutComplete(struct Mentor_Controller* r6,
        struct Struct_0xa0* r4, int r2, int r3)
{
#if 0
    fprintf(stderr, "MENTOR_ProcessOutComplete: TODO!!!\n");
#endif

    struct Struct_0xa4* r5 = r4->Data_0x30;
    if (r5->bData_0x1f == 0)
    {
        //0x000054c4
        r4->Data_0x14 += r2;

        if ((r3 != 0) ||
            (r4->Data_0x14 >= r4->Data_0))
        {
            //loc_54e8
            InterruptLock(&r6->Data_0xd0);

            r6->Data_0xc4[r5->Data_0x28] = NULL;
            r5->Data_0x10 &= ~0x01;

            HW_Write16(r6, 0x102 + r5->Data_0x28 * 16, 0);

            r4->Data_0x10 = 0;
            r4->status = r3;

            r5->Data_8__ = r4->Data_0x2c.Data_0;
            if (r5->Data_8__ == NULL)
            {
                r5->Data_0xc = &r5->Data_8__;
            }
            r4->Data_0x2c.Data_0 = NULL;

            *(r6->Data_0x9c) = r4;
            r6->Data_0x9c = &r4->Data_0x2c;

            InterruptUnlock(&r6->Data_0xd0);
            //->loc_56d0
        }
        else
        {
            //0x0000559c
            r4->flags &= ~0x800;

            uint32_t r3 = r5->Data_0x30->Data_0;
            int r1 = r4->Data_0;
            int r2 = r4->Data_0x14;
            r2 = r1 - r2;
            if (r3 >= r2)
            {
                r3 = r4->Data_0 - r4->Data_0x14;
            }
            r4->Data_0x10 = r3;
            int r0 = r4->Data_0x10;
            uint32_t r7 = r5->wData_0x18;
            int r8 = r7;
            r0 = r0 - 1;
            r0 = r0 + r7;
            r0 = r0 / r7;
            r0 = r0 - 1;
            uint32_t r0_;
            if (r0 <= 0)
            {
                r0_ = 0;
                //->0x00005614
            }
            else
            {
                //0x000055fc
                r0 = r4->Data_0x10;
                r0 = r0 - 1;
                r0 = r0 + r7;
                r0_ = (r0 / r7) - 1;
            }
            //0x00005614
            HW_Write16(r6, 0x100 + r5->Data_0x28 * 16,
                r7 | (r0_ << 11));

            if (r4->flags & 0x600)
            {
                //0x00005640
#if 1
                fprintf(stderr, "MENTOR_ProcessOutComplete: 0x00005640: TODO!!!\n");
#endif
                //TODO!!!

                //->0x000056d0
            }
            else
            {
                //0x0000568c
                MENTOR_LoadFIFO(r6, r5->Data_0x28, 
                    r4->pData + r4->Data_0x14, r4->Data_0x10);
                
                HW_Write16(r6, 0x102 + r5->Data_0x28 * 16, 
                    HW_Read16(r6, 0x102 + r5->Data_0x28 * 16) | 0x01);
            }
        }
    }
    //loc_56d0
    return 0;
}


int MENTOR_ProcessOutDMAComplete(struct Mentor_Controller* a,
        struct Struct_0xa0* b, int c, int d)
{
#if 1
    fprintf(stderr, "MENTOR_ProcessOutDMAComplete: TODO!!!\n");
#endif

    return 0;
}


/* 0x00008e20 - todo */ /* refer musb_transfer */
int mentor_bulk_transfer(struct USB_Controller* ctrl, 
    struct Struct_10bab4* r8, 
    struct Struct_112b08* r2, 
    void* buffer/*fp_0x34*//*fp52*/, 
    int length/*fp4*/, 
    int flags/*sb*//*arg4*/)
{
#if 1
    fprintf(stderr, "mentor_bulk_transfer: buffer=%p, length=%d, flags=0x%x: TODO!!!\n",
        buffer, length, flags);

    if ((buffer != NULL) && (length > 0))
    {
        hex_dump("mentor_bulk_transfer", buffer, length);
    }
#endif

    struct Mentor_Controller* r6 = ctrl->hc_data;
    struct Struct_0xa4* r5 = r2->Data_0xc;
    struct Struct_0xa0* td; //r4;

    if (pthread_mutex_lock(&r6->Data_4/*sl*/) != 0)
    {
        fprintf(stderr, "mutex lock %s %d\n", 
            "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c",
            0x505);
    }
    //loc_8e80
    td = MENTOR_TD_Setup(r6, r8, r5, flags/*sb*/);
    if (td == NULL)
    {
        if (pthread_mutex_unlock(&r6->Data_4/*sl*/) != 0)
        {
            fprintf(stderr, "mutex lock %s %d\n", 
                "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c",
                0x508);
        }
        //loc_8ecc
        r8->Data_8 = 0x2000010;
        return 12; //->loc_932c
    }
    //loc_8edc
    td->pData = buffer; //fp_0x34;
    td->Data_8 = r8->Data_0x5c->pData;
    td->Data_0 = length;

#if 1
    fprintf(stderr, "mentor_bulk_transfer: r6->Data_0x50=0x%x\n",
        r6->Data_0x50);
#endif

    if (r6->Data_0x50 & 0x01)
    {
        //0x00008f04
#if 1
        fprintf(stderr, "mentor_bulk_transfer: 0x00008f04: TODO!!!\n");
#endif
        if (flags/*sb*/ & 0x20/*PIPE_FLAGS_MULTI_XFER?*/)
        {
            //0x00008f0c
            struct
            {
                int fill_0[2]; //0
                int Data_8; //8

            }* r3 = r8 + 1;

        }
        //0x00008fa8

        //TODO!!!
    }
    //0x00009038
    if (flags/*sb*/ & 0x04/*PIPE_FLAGS_TOKEN_IN?*/)
    {
        //0x00009040
        td->Data_0x3c = td->Func_0x38 = MENTOR_ProcessInComplete;
        //->0x00009088
    }
    else
    {
        //0x00009054
        td->Func_0x38 = MENTOR_ProcessOutComplete;

        if ((r6->Data_0x38 & 0x400) == 0)
        {
            //0x0000906c
            td->Data_0x3c = MENTOR_ProcessOutComplete;
        }
        else
        {
            //0x0000907c
            td->Data_0x3c = MENTOR_ProcessOutDMAComplete;
        }
        //0x00009088
    }
    //0x00009088
    InterruptLock(&r6->Data_0xd0);

    td->Data_0x2c.Data_0 = NULL;
    r5->Data_0xc->Data_0 = td;

    struct Struct_0x94* fp_0x30 = &td->Data_0x2c;
    r5->Data_0xc = fp_0x30;

    if ((r5->Data_0x10 & 0x01) == 0)
    {
        //0x000090e4
        InterruptUnlock(&r6->Data_0xd0);

        if (r5->Data_0x28 == -1)
        {
            //0x00009108
            if (MENTOR_AllocEtd(r6, r5, td->flags & 0x04) < 0)
            {
                //0x00009124
                mentor_slogf(r6, 12, 2, 1, "%s - %s Call to MENTOR_AllocEtd() failed",
                    "devu-dm816x-mg.so", "mentor_bulk_transfer");

                InterruptLock(&r6->Data_0xd0);

                r5->Data_8__ = td->Data_0x2c.Data_0;
                if (r5->Data_8__ == 0)
                {
                    r5->Data_0xc = &r5->Data_8__;
                }
                td->Data_0x2c.Data_0 = NULL;
                r6->Data_0x94->Data_0 = td;
                r6->Data_0x94 = fp_0x30;

                InterruptUnlock(&r6->Data_0xd0);

                if (pthread_mutex_unlock(&r6->Data_4/*sl*/) != 0)
                {
                    fprintf(stderr, "mutex lock %s %d\n", 
                        "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c",
                        0x55f);
                }
                //0x00009208
                r8->Data_8 = 0x10;
                return 12; //->loc_932c
            } //if (MENTOR_AllocEtd() < 0)
            //0x00009218
            if (flags/*sb*/ & 0x04/*PIPE_FLAGS_TOKEN_IN?*/)
            {
                //0x00009220
                MENTOR_EtdConfigureRX(r6, r5, r5->Data_0x28);
                //->0x00009244
            }
            else
            {
                //0x00009234
                MENTOR_EtdConfigureTX(r6, r5, r5->Data_0x28);
            }
        }
        //0x00009244
        if ((td->flags & 0x600) && 
            (r5->Data_0x38 == 0))
        {
            //0x0000925c
            r5->Data_0x38 = mentor_alloc_dma_sched(r6, r5);
            if (r5->Data_0x38 == 0)
            {
                td->flags &= ~0x600;
            }

            if (((r6->Data_0x50 & 0x04) == 0) &&
                (r5->Data_0x2c == -1))
            {
                //0x00009288
                if (mentor_claim_dma_channel(r6, td, 
                        r5->Data_0x28, &r5->Data_0x2c) != 0)
                {
                    td->flags &= ~0x600;
                }
            }
            //0x000092b8
        }
        //0x000092b8
        if (r5->Data_8__ != 0)
        {
            //0x000092c4
            r5->Data_0x10 |= 0x01;
            r6->Data_0xbc = r5;

            MENTOR_StartEtd(r6, r5->Data_8__);
        }
        //0x000092f8
    } //if ((r5->Data_0x10 & 0x01) == 0)
    else
    {
        //0x000092e0
        InterruptUnlock(&r6->Data_0xd0);
    }
    //0x000092f8
    if (pthread_mutex_unlock(&r6->Data_4/*sl*/) != 0)
    {
        fprintf(stderr, "mutex lock %s %d\n", 
            "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c",
            0x584);
    }
    //loc_932c
    return 0;    
}


/* 0x0000947c - todo */
int mentor_ctrl_transfer(struct USB_Controller* sl, 
    struct Struct_10bab4* r8, 
    struct Struct_112b08* sb, 
    uint8_t* buffer/*fp_0x34*//*fp52*/, 
    uint32_t length/*fp4*/, 
    uint32_t flags/*fp8*/)
{
#if 1
    fprintf(stderr, "mentor_ctrl_transfer: buffer=%p, length=%d, flags=0x%x\n", 
        buffer, length, flags);

    if ((flags & PIPE_FLAGS_TOKEN_SETUP) && (length == 8) && (buffer != NULL))
    {
        fprintf(stderr, "mentor_ctrl_transfer: Setup Packet:\n");
        fprintf(stderr, "mentor_ctrl_transfer: bmRequestType.Recipient=%d\n", buffer[0] & 0x1f);
        fprintf(stderr, "mentor_ctrl_transfer: bmRequestType.Type=%d\n", (buffer[0] >> 5) & 0x03);
        fprintf(stderr, "mentor_ctrl_transfer: bmRequestType.Direction=%d\n", (buffer[0] >> 7) & 0x01);
        fprintf(stderr, "mentor_ctrl_transfer: bRequest=0x%02x\n", buffer[1]);
        fprintf(stderr, "mentor_ctrl_transfer: wValue=0x%04x\n", buffer[2] | (buffer[3] << 8));
        fprintf(stderr, "mentor_ctrl_transfer: wIndex=0x%04x\n", buffer[4] | (buffer[5] << 8));
        fprintf(stderr, "mentor_ctrl_transfer: wLength=0x%04x\n", buffer[6] | (buffer[7] << 8));
    }
#endif

    int res;

    struct Struct_0xa0* td; //fp_0x38
    struct Mentor_Controller* r5 = sl->hc_data;
    struct Struct_0xa4* fp_0x30/*fp48*/ = sb->Data_0xc;

    if (pthread_mutex_lock(&r5->Data_0xc/*r7*/) != 0)
    {
        fprintf(stderr, "mutex lock %s %d\n", 
            "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c", 0x4c9);
    }

    if (pthread_mutex_lock(&r5->Data_4/*r6*/) != 0)
    {
        fprintf(stderr, "mutex lock %s %d\n", 
            "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c", 0x4ca);
    }
    //loc_9518
    if ((r5->Data_0x6c & 0x06) != 0x06)
    {
        if (pthread_mutex_unlock(&r5->Data_4/*r6*/) != 0)
        {
            fprintf(stderr, "mutex lock %s %d\n", 
                "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c", 0x4cd);
        }
        //loc_9558
        if (pthread_mutex_unlock(&r5->Data_0xc/*r7*/) != 0)
        {
            fprintf(stderr, "mutex lock %s %d\n", 
                "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c", 0x4ce);
        }
        //loc_9588
        r8->Data_8 = 0x2000005;

        return 0x13;
        //->loc_9988
    }
    //loc_9598
    td = MENTOR_TD_Setup(r5, r8, fp_0x30, flags/*fp8*/);
    if (td == NULL)
    {
        //0x000095b8
        if (pthread_mutex_unlock(&r5->Data_4/*r6*/) != 0)
        {
            fprintf(stderr, "mutex lock %s %d\n", 
                "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c", 0x4cd);
        }
        //0x000095e8
        if (pthread_mutex_unlock(&r5->Data_0xc/*r7*/) != 0)
        {
            fprintf(stderr, "mutex lock %s %d\n", 
                "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c", 0x4ce);
        }
        //0x00009618
        r8->Data_8 = 0x2000010;

        return 0x0c;
        //->loc_9988
    }
    //0x00009628
    td->pData = buffer; //fp_0x34;
    td->Data_0 = length/*fp4*/;

    r8->Data_4 = 0;
    //0x00009648
    InterruptLock(&r5->Data_0xd0);
    //0x0000967c
    td->Data_0x2c.Data_0 = NULL;
    fp_0x30->Data_0xc->Data_0 = td;
    fp_0x30->Data_0xc = &td->Data_0x2c;

    if ((fp_0x30->Data_0x10 & 1) == 0)
    {
        //0x000096a4
        fp_0x30->Data_0x10 |= 1;
        fp_0x30->Data_0x28 = 0;

        r5->Data_0xc4[0] = td;
        //0x000096bc
        InterruptUnlock(&r5->Data_0xd0);
        //0x000096d0
        struct Struct_0xa0* r2 = fp_0x30->Data_8__;
#if 1
        fprintf(stderr, "r2->Data_0=0x%x, r2->flags=0x%x, r2->pData=%p, \n",
            r2->Data_0, r2->flags, r2->pData);
#endif

        fp_0x30 = r2->Data_0x30;
        r2->flags |= 0x100;
        fp_0x30->bData_0x1f = 0; //r3; //TODO!!!

        int fp_0x34_;
        uint32_t wCsrH; //r1;
        if (r2->flags & PIPE_FLAGS_TOKEN_SETUP) //1)
        {
            //0x00009700
            fp_0x30->Data_0x20 = 0;

            fp_0x34_ = 0x08;
            //->0x00009760
            wCsrH = 0;
            //0x00009764
        }
        //0x00009714
        else if (r2->flags & PIPE_FLAGS_TOKEN_STATUS) //2)
        {
            //0x00009720
            fp_0x30->Data_0x20 = 1;

            fp_0x34_ = 0x40;
            wCsrH = 0x200;
            //->0x00009764
        }
        else
        {
            //0x0000973c
            if (fp_0x30->Data_0x20 != 0)
            {
                fp_0x34_ = 0;
                wCsrH = 0x200;
                //->0x00009764
            }
            else
            {
                //0x00009758
                fp_0x34_ = 0;
                wCsrH = 0;
            }
        }
        //0x00009764
        wCsrH |= (r5->Data_0x50 & 0x80)? 0x800: 0;
        wCsrH |= 0x500;
        wCsrH &= 0xf00;

#if 1
        fprintf(stderr, "mentor_ctrl_transfer: wCsrH=0x%04x, fp_0x30->Data_0x14=0x%x\n", 
            wCsrH, fp_0x30->Data_0x14);
#endif

        HW_Write16(r5, 0x102, wCsrH);
        HW_Write16(r5, 0x80, (fp_0x30->Data_0x14 >> 4) & 0x7f);

        if (fp_0x30->bData_0x1c != 0x40)
        {
            //0x000097b8
#ifdef MB86H60
            fprintf(stderr, "mentor_ctrl_transfer: fp_0x30->bData_0x1d=0x%x, fp_0x30->bData_0x1e=0x%x\n", 
                fp_0x30->bData_0x1d, fp_0x30->bData_0x1e);

            MGC_Write8(r5, MGC_BUSCTL_OFFSET(0/*bEnd*/, MGC_O_HDRC_TXHUBADDR),
                fp_0x30->bData_0x1d);
            MGC_Write8(r5, MGC_BUSCTL_OFFSET(0/*bEnd*/, MGC_O_HDRC_TXHUBPORT),
                fp_0x30->bData_0x1e);
#else
            ((volatile uint8_t*)(r5->Data_0x14))[0x82] = fp_0x30->bData_0x1d;
            ((volatile uint8_t*)(r5->Data_0x14))[0x83] = fp_0x30->bData_0x1e;
#endif
        }
        //0x000097d8
#ifdef MB86H60
        MGC_Write8(r5, 0x10b, 0); //TxInterval?
#else
        ((volatile uint8_t*)(r5->Data_0x14))[0x10b] = 0;
#endif

        uint16_t r2_;
        if (r2->flags & PIPE_FLAGS_TOKEN_SETUP) //1)
        {
            //0x000097f8
            MENTOR_LoadFIFO(r5, 0, r2->pData, r2->Data_0 & 0xffff);

            r2_ = fp_0x34_ | (1 << 3)/*SetupPkt*/ | (1 << 1)/*TxPktRdy*/; //0x0a;
            //->0x0000987c
        }
        //0x0000981c
        else if (r2->flags & PIPE_FLAGS_TOKEN_OUT) //8)
        {
            //0x00009828
            int r3 = fp_0x30->wData_0x18;
            if (r3 > r2->Data_0)
            {
                r3 = r2->Data_0;
            }

            r2->Data_0x14 += r3;

            if (r3 > 0)
            {
                //0x00009850
                MENTOR_LoadFIFO(r5, 0, r2->pData, r3 & 0xffff);
            }
            //0x00009868
            r2_ = fp_0x34_ | (1 << 1)/*TxPktRdy*/; //0x02;
            //->0x0000987c
        }
        else
        {
            //0x00009874
            r2_ = fp_0x34_ | (1 << 5)/*ReqPkt*/; //0x20;
        }
        //0x0000987c
#ifdef MB86H60
        fprintf(stderr, "mentor_ctrl_transfer: r2_=0x%04x, fp_0x30->bData_0x1c=0x%x\n", 
            r2_, fp_0x30->bData_0x1c);

        MGC_Write16(r5, 0x10a, fp_0x30->bData_0x1c);
        MGC_Write16(r5, 0x102, MGC_Read16(r5, 0x102) | r2_);
#else
        ((volatile uint16_t*)(r5->Data_0x14))[0x10a/2] = fp_0x30->bData_0x1c;
        ((volatile uint16_t*)(r5->Data_0x14))[0x102/2] |= r2_;
#endif
        //->0x000098c8
    }
    else
    {
        //0x000098b0
        InterruptUnlock(&r5->Data_0xd0);
    }
    //0x000098c8
    if (pthread_mutex_unlock(&r5->Data_4/*r6*/) != 0)
    {
        fprintf(stderr, "mutex lock %s %d\n", 
            "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c", 0x4ed);
    }
    //0x000098f8
    if (flags/*fp8*/ & 0x80000000) // < 0)
    {
        //0x00009904
        res = MENTOR_WaitEndControl(sl, r8, sb, td);

        if (pthread_mutex_unlock(&r5->Data_0xc/*r7*/) != 0)
        {
            fprintf(stderr, "mutex lock %s %d\n", 
                "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c", 0x4f1);
        }
        //0x00009988
    }
    else
    {
        //0x00009950
        if (pthread_mutex_unlock(&r5->Data_0xc/*r7*/) != 0)
        {
            fprintf(stderr, "mutex lock %s %d\n", 
                "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c", 0x4f1);
        }

        res = 0;
    }
    //loc_9988
    return res;
}


int mentor_ctrl_transfer_abort(struct USB_Controller* a, 
    struct Struct_10bab4* b, 
    struct Struct_112b08* c)
{
#if 1
    fprintf(stderr, "mentor_ctrl_transfer_abort: TODO!!!\n");
#endif

    return 0;
}



int mentor_ctrl_endpoint_disable(struct USB_Controller* a, struct Struct_112b08* b)
{
#if 1
    fprintf(stderr, "mentor_ctrl_endpoint_disable: TODO!!!\n");
#endif

    return 0;
}



/* 0x00009c24 - complete */
int mentor_bulk_endpoint_enable(struct USB_Controller* a, 
    struct USB_Controller_Inner_0x7c* b, 
    struct Struct_112b08* r6)
{
#if 1
    fprintf(stderr, "mentor_bulk_endpoint_enable: a=%p, b=%p, r6=%p\n",
        a, b, r6);
#endif

    struct Mentor_Controller* r5 = a->hc_data;
    struct Struct_0xa4* r4 = r6->Data_0xc;

#if 1
    fprintf(stderr, "mentor_bulk_endpoint_enable: r5=%p, r4=%p\n",
        r5, r4);
#endif

    int r7 = MENTOR_InitializeEndpoint(r5, b, r6);

    if ((r7 == 0) && (r4 == NULL))
    {
        r4 = r6->Data_0xc;

        MENTOR_HookED(r5, r5->Data_0xb0, r4);
    }
    else
    {
        //loc_9c6c
        if (r4 != NULL)
        {
            if (r4->Data_0x28 > 0)
            {
                MENTOR_FreeEtd(r5, r4);
            }
        }
    }
    //loc_9c8c
    r4->Data_0x24 = 0;

    return r7;
}


int mentor_bulk_endpoint_disable(struct USB_Controller* a, struct Struct_112b08* b)
{
#if 1
    fprintf(stderr, "mentor_bulk_endpoint_disable: TODO!!!\n");
#endif

    return 0;
}



static hc_methods_t mentor_controller_methods; //0x0000bf64
static hc_pipe_methods_t mentor_ctrl_pipe_methods; //0x0000bf98
static hc_pipe_methods_t mentor_bulk_pipe_methods; //0x0000bfc0

struct _io_usb_dll_entry io_usb_dll_entry = //0x0000bf40
{
    "devu-mb86h60-mg.so",
    0xffffffff,
    mentor_init,
    mentor_shutdown,
    &mentor_controller_methods,
    &mentor_ctrl_pipe_methods,
#if 1 //TODO
    0, //&mentor_int_pipe_methods,
    &mentor_bulk_pipe_methods,
    0, //&mentor_isoch_pipe_methods,
#endif
};


static hc_methods_t mentor_controller_methods = //0x0000bf64
{
    9,
    mentor_controller_init,
    mentor_controller_shutdown,
    0, //mentor_set_bus_state,
    0, 0, 0,
    mentor_set_port_feature,
    mentor_clear_port_feature,
    mentor_check_port_status,
    mentor_check_device_connected,
    mentor_get_root_device_speed,
    mentor_get_timer_from_controller,
};


static hc_pipe_methods_t mentor_ctrl_pipe_methods = //0x0000bf98
{
    mentor_ctrl_endpoint_enable,
    mentor_ctrl_endpoint_disable,
    mentor_ctrl_transfer,
    mentor_ctrl_transfer_abort,
    NULL
};


static hc_pipe_methods_t mentor_bulk_pipe_methods = //0x0000bfc0
{
    mentor_bulk_endpoint_enable,
    mentor_bulk_endpoint_disable,
    mentor_bulk_transfer,
    mentor_transfer_abort,
    NULL
};

