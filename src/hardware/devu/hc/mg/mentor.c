
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <gulliver.h>
#include <sys/mman.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <pthread.h>
#include <arm/mb86h60.h>
#include "mu_hdrdf.h"


struct Mentor_Controller;
#define USB_CONTROLLER_PRIV_T struct Mentor_Controller
#include "io-usb.h"


//#define ENABLE_DELAY

struct Struct_0xa4;
struct Struct_0xa0;
struct Struct_0x94
{
    struct Struct_0xa0* Data_0; //0
};

struct Struct_0xa0
{
    int Data_0; //0
    int Data_4; //4
    int fill_8; //8
    void* Data_0xc; //0xc
    int fill_0x10; //0x10
    int Data_0x14; //0x14
    int fill_0x18[4]; //0x18
    int Data_0x28; //0x28
    struct Struct_0x94 Data_0x2c; //0x2c
    struct Struct_0xa4* Data_0x30; //0x30
    struct Struct_10bab4* Data_0x34; //0x34
    int fill_0x38[3]; //0x38
    //0x44
};


struct Struct_0xa4
{
    struct Struct_0xa4* Data_0; //0
    struct Struct_0xa4* Data_4; //4
    int Data_8; //8
    struct Struct_0x94* Data_0xc; //12
    int Data_0x10; //0x10 = 16
    int Data_0x14; //0x14 = 20
    uint16_t wData_0x18; //0x18 = 24
    uint8_t bData_0x1a; //0x1a = 26
    uint8_t bData_0x1b; //0x1b = 27
    uint8_t bData_0x1c; //0x1c = 28
    uint8_t bData_0x1d; //0x1d = 29
    uint8_t bData_0x1e; //0x1e = 30
    uint8_t bData_0x1f; //0x1f = 31
    int Data_0x20; //0x20
    int Data_0x24; //0x24
    int Data_0x28; //0x28
    int Data_0x2c; //0x2c
    int fill_0x30; //0x30
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


struct Mentor_Controller
{
    struct USB_Controller* Data_0; //0
    pthread_mutex_t Data_4; //4
    pthread_mutex_t Data_0xc; //12
    void* Data_0x14; //0x14
    int Data_0x18; //0x18
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
    int fill_0x54; //0x54
    int Data_0x58; //0x58
    struct sigevent Data_0x5c;
    int Data_0x6c; //0x6c
    uint32_t Data_0x70; //0x70
    uint32_t Data_0x74; //0x74
    int Data_0x78; //0x78
    int Data_0x7c; //0x7c
    int fill_0x80[2]; //0x80
    int Data_0x88; //0x88
    int fill_0x8c; //0x8c
    struct Struct_0x94 Data_0x90; //0x90
    struct Struct_0x94* Data_0x94; //0x94
    int Data_0x98; //0x98
    int* Data_0x9c; //0x9c
    struct Struct_0xa0* Data_0xa0; //0xa0
    struct Struct_0xa4* Data_0xa4; //0xa4
    struct Struct_0xa4* Data_0xa8; //0xa8
    struct Struct_0xa4* Data_0xac; //0xac
    struct Struct_0xa4* Data_0xb0; //0xb0
    struct Struct_0xa4* Data_0xb4; //0xb4
    struct Struct_0xa4* Data_0xb8; //0xb8
    struct Struct_0xa4* Data_0xbc; //0xbc
    struct Struct_0xa4* Data_0xc0; //0xc0
    void* Data_0xc4; //0xc4
    void* Data_0xc8; //0xc8
    int fill_0xcc; //0xcc
    struct intrspin Data_0xd0; //0xd0
    struct Struct_0xe4* Data_0xe4; //0xe4
    //0xe8
};



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


#endif



#ifdef MB86H60

void mb86h60_debug_regs(struct Mentor_Controller* r4)
{
    int i;

    fprintf(stderr, "hwvers=0x%x\n", MGC_Read16(r4, 0x6c));

#if 0
    ((volatile uint32_t*)(dma_regs))[0x14/4] = 0 << 1; //dma_dwUsbMode;
    for (i = 0; i < 0xff; i++)
    {
        int reg = ((volatile uint32_t*)(r4->Data_0x14))[i];
        fprintf(stderr, "reg[0x%02x]=0x%x\n", i, reg);
    }
#endif

#if 0
    ((volatile uint32_t*)(r4->Data_0x14))[0x0f] = 0;
    ((volatile uint32_t*)(r4->Data_0x14))[0x60] = 0;
    int devctl = ((volatile uint32_t*)(r4->Data_0x14))[0x60];
    fprintf(stderr, "devctl=0x%x\n", devctl);

    for (i = 1; i < 15; i++)
    {
        ((volatile uint32_t*)(r4->Data_0x14))[0x0e] = i;
        int ep_size = ((volatile uint32_t*)(r4->Data_0x14))[0x1f];
        fprintf(stderr, "ep_size[%d]=0x%x\n", i, ep_size);
    }
#endif
}

#endif //MB86H60


void mentor_slogf(/*struct Mentor_Controller* a, int b, int c, int d,
        char* e, char* f, char* g, char* h*/)
{
    fprintf(stderr, "mentor_slogf: TODO\n");
}


void MENTOR_ProcessControlDone(struct Mentor_Controller* a)
{
#if 0
    fprintf(stderr, "MENTOR_ProcessControlDone: TODO\n");
#endif

}


void MENTOR_ProcessETDDone(struct Mentor_Controller* a, uint16_t b)
{
#if 0
    fprintf(stderr, "MENTOR_ProcessETDDone: TODO\n");
#endif

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
//            MGC_Write8(r4, MGC_O_HDRC_DEVCTL, MGC_M_DEVCTL_SESSION);
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
    struct Mentor_Controller* r4 = r7->Data_0x84;

    if (ThreadCtl(1, 0) == -1)
    {
        mentor_slogf(r4, 12, 2, 1, "%s - %s: Unable to obtain I/O privity.",
            "devu-dm816x-mg.so", "mentor_interrupt_thread");
        return -1;
    }
    //loc_8000
    r4->Data_0x5c.sigev_notify = 4;
    r4->Data_0x5c.sigev_id = r4->Data_0x44;
    r4->Data_0x5c.sigev_priority = getprio(0);
    r4->Data_0x5c.sigev_value.sival_int = 0;
    r4->Data_0x5c.sigev_code = 1;

#if 0 //TODO!!!
    while ((r4->Data_0x50 & 0x10) == 0)
    {
        //loc_803c
#ifdef ENABLE_DELAY
        delay(1);
#endif
    }
#endif
    //loc_8050
#ifdef MB86H60
    r4->Data_0x48 = MB86H60_INTR_USB; //r7->Data_4->bData_0x14;
#else
    r4->Data_0x48 = r7->Data_4->bData_0x14...;
#endif

    r4->Data_0x4c = InterruptAttach(r4->Data_0x48, mentor_interrupt_handler, r4, 0xe8, 8);
    if (r4->Data_0x4c == -1)
    {
        mentor_slogf(r4, 12, 2, 1, "%s - %s: InterruptAttach failed.",
            "devu-dm816x-mg.so", "mentor_interrupt_thread");

        return -1;
    }
    //loc_80e0
    while (1)
    {
        //loc_8100
        struct 
        {
            int fill_0[4]; //0
            //16
        } fp_0x30;

        if (MsgReceivePulse(r4->Data_0x40, &fp_0x30, 16, 0) == -1)
        {
            //->loc_8154
            InterruptDetach(r4->Data_0x4c);
            break;
        }

        fprintf(stderr, "mentor_interrupt_thread: msg handling: TODO!!!\n");
    }

    return NULL;
}


int mentor_init_fifo_config(struct Mentor_Controller* r0, int b)
{
#if 1
    fprintf(stderr, "mentor_init_fifo_config: TODO\n");
#endif

}


/* 0x000045cc - complete */
int mentor_fifo_init(struct Mentor_Controller* cntrl, int b)
{
#if 0
    fprintf(stderr, "mentor_fifo_init: TODO\n");
#endif

#ifdef MB86H60
    MGC_SelectEnd(cntrl, 0);
    MGC_Write8(cntrl, MGC_O_HDRC_RXFIFOSZ, 3);
    MGC_Write16(cntrl, MGC_O_HDRC_RXFIFOADD, 0);
    MGC_Write8(cntrl, MGC_O_HDRC_TXFIFOSZ, 3);
    MGC_Write16(cntrl, MGC_O_HDRC_TXFIFOADD, 0);
#else
    ((volatile uint8_t*)(cntrl->Data_0x14))[0x0e] = 0;
    ((volatile uint8_t*)(cntrl->Data_0x14))[0x63] = 0x03; //RXFIFOSZ
    ((volatile uint16_t*)(cntrl->Data_0x14))[0x66/2] = 0; //RXFIFOADD
    ((volatile uint8_t*)(cntrl->Data_0x14))[0x62] = 0x03; //TXFIFOSZ
    ((volatile uint16_t*)(cntrl->Data_0x14))[0x64/2] = 0; //TXFIFOADD
#endif

    mentor_init_fifo_config(cntrl, b);

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

    r4->Data_0x98 = 0;
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

    r4->Data_8 = 0;
    r4->Data_0xc = &r4->Data_8;
    r4->Data_0x10 = 0;
    r5->Data_0xa8 = r4;

    for (i = 0; i < r5->Data_0x70; i++)
    {
        r4->Data_0x2c = -1;
        r4->Data_0 = r4 + 1;
        r4->Data_0->Data_4 = r4;
        r4->Data_0->Data_8 = 0;
        r4->Data_0->Data_0xc = &r4->Data_0->Data_8;
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
    r3->Data_8 = 0;
    r3->Data_0xc = &r3->Data_8;
    r3->Data_4 = r3;
    r3->Data_0 = r3;

    return 0;

}


/* 0x00002e08 - todo */
int mentor_board_specific_init1(struct Mentor_Controller* r6)
{
#if 0
    fprintf(stderr, "mentor_board_specific_init1: TODO!!!\n");
#endif

    struct Struct_0xe4* r5;

    int sl;

    struct USB_Controller* r4 = r6->Data_0;

    r6->Data_0x38 = 0x400;
    r6->Data_0x18 = 0x10;
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
    r5->Data_0 = r4->Data_4->Data_0x68 - 0x47400400 + r5->Data_4;

    if (r4->Data_4->Data_0x68 == 0x47401c00)
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

    mentor_fifo_init(r6, r6->Data_0x88);

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
    MGC_Write8(ctrl, MGC_O_HDRC_INTRUSBE, 0xff);
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

    r7->Data_0 = "dm816x";

    if ((r7->Data_0x84 = r4 = calloc(1, 0xe8)) == NULL)
    {
        return 12;
    }

    r4->Data_0 = r7;
    r4->Data_0x58 = 0x18;
    r4->Data_0x78 = 0;
    r4->Data_0x70 = 0xaa;
    r4->Data_0x74 = 0x60;
    r4->Data_0x7c = 1000;
    r4->Data_0x6c = 0x04;
    r4->Data_0x50 = 0x45;
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
                        r4->Data_0x78 = 5;
                    }
                    else
                    {
                        r4->Data_0x78 = strtol(fp_0x50, 0, 10);
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
    r7->Data_0x60 = 0x8000;

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
    struct Mentor_Controller* sb = r7->Data_0x84;

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
#if 1
                                            mb86h60_debug_regs(r4);
#endif

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
    struct Mentor_Controller* r4 = a->Data_0x84;

#if 1
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

#ifdef ENABLE_DELAY
                delay(10);
#endif

                if (r4->Data_0x50 & 0x100)
                {
                    mentor_ulpi_write(r4, 0x05, 0x20);

#ifdef ENABLE_DELAY
                    delay(5);
#endif
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

#ifdef ENABLE_DELAY
                delay(1);
#endif

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

    return ((a->Data_0x84->Data_0x6c & 0x02) == 0)? -1: 0;
}


/* 0x00005044 - complete */
int mentor_clear_port_feature(struct USB_Controller* a, int b, int c)
{
#if 1
    fprintf(stderr, "mentor_clear_port_feature: b=%d, c=%d, TODO!!!\n", b, c);
#endif

    struct Mentor_Controller* ctrl = a->Data_0x84;

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
#ifdef ENABLE_DELAY
            delay(20);
#endif
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

    struct Mentor_Controller* ctrl = a->Data_0x84;

    switch (c)
    {
        case 2:
            //loc_50cc
#ifdef MB86H60
            MGC_Write8(ctrl, MGC_O_HDRC_POWER, 
                MGC_Read8(ctrl, MGC_O_HDRC_POWER) | MGC_M_POWER_RESET);
#else
            ((volatile uint8_t*)(ctrl->Data_0x14))[1] |= (1 << 3);
#endif
#ifdef ENABLE_DELAY
            delay(20);
#else
            {
                int i;
                for (i = 0; i < 1000000; i++)
                {
                    /*delay*/
                }
            }
#endif
#ifdef MB86H60
            MGC_Write8(ctrl, MGC_O_HDRC_POWER, 
                MGC_Read8(ctrl, MGC_O_HDRC_POWER) & ~MGC_M_POWER_RESET);
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

    struct Mentor_Controller* ctrl = a->Data_0x84;

#ifdef ENABLE_DELAY
    delay(200);
#endif

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
    r1->bData_0x1a = r4->bData_3 & 0x03;
    r1->wData_0x18 = r4->wData_4;
    r1->bData_0x1b = r4->bData_2 & ~0x7f;
    r1->Data_0x20 = 0;
    r1->Data_0x14 = ((r5->Data_0 & 0x7f) << 4) | (r4->bData_2 & 0x0f);

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
    r1->Data_0x24 = r4->bData_6;

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
        r1->bData_0x1d = r3->Data_0;
        r1->bData_0x1e = r5->Data_0x20;

        return 0;
    }
    //9b34
    return 0;
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
    r4->Data_8 = 0;
    r4->Data_0xc = &r4->Data_8;

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
    fprintf(stderr, "mentor_ctrl_endpoint_enable: TODO!!!\n");
#endif

    struct Mentor_Controller* r5 = a->Data_0x84;
    struct Struct_0xa4* r7 = c->Data_0xc;

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
    struct Struct_10bab4* b, struct Struct_0xa4* c, int d)
{
#if 0
    fprintf(stderr, "MENTOR_TD_Setup: TODO!!!\n");
#endif

    struct Struct_0xa0* r4;

    InterruptLock(&a->Data_0xd0);

    r4 = a->Data_0x90.Data_0;
    if (r4 == NULL)
    {
        b->Data_8 = 12;

        InterruptUnlock(&a->Data_0xd0);

        mentor_slogf(a, 12, 2, 1, "%s - No TD's available",
            "devu-dm816x-mg.so");
    }
    else
    {
        a->Data_0x90.Data_0 = r4->Data_0x2c.Data_0;
        if (a->Data_0x90.Data_0 == NULL)
        {
            a->Data_0x94 = &a->Data_0x90;
        }

        InterruptUnlock(&a->Data_0xd0);

        r4->Data_4 = d & 0x8000003f;
        r4->Data_0x14 = 0;
        r4->Data_0x28 = 0;
        r4->Data_0x30 = c;
        r4->Data_0x34 = b;
    }

    return r4;
}


/* */
void MENTOR_LoadFIFO(struct Mentor_Controller* a, uint16_t b, int c, uint16_t r8)
{
#if 0
    fprintf(stderr, "MENTOR_LoadFIFO: TODO!!!\n");
#endif

    int r7;
    int r6;
    int r5;
    uint32_t* r3;

//    b &= 0xffff;
//    uint16_t r8 = d & 0xffff;

    if (r8 > 3)
    {
        r6 = b * 4;
        r8 -= 4;
        r7 = r8 >> 18;
        r5 = c + 4;
        r5 = r5 + r7 * 4;
        r3 = c;

        while (1)
        {
            //loc_4704
            ((volatile uint32_t*)(a->Data_0x14))[0x20 + r6] = *r3++;

            if (r3 == r5)
            {
                break;
            }
        }
        
        r7++;
        c = c + r7 * 4;
    }
    //loc_472c
    if (r8 & 2)
    {
        ((volatile uint16_t*)(a->Data_0x14))[0x20 + b] = *((uint16_t*)c);
        c += 2;
    }
    if (r8 & 1)
    {
        ((volatile uint8_t*)(a->Data_0x14))[0x20 + b] = *((uint8_t*)c);
    }
}


/* */
int MENTOR_WaitEndControl()
{
#if 1
    fprintf(stderr, "MENTOR_WaitEndControl: TODO!!!\n");
#endif

    return 0;
}


/* 0x0000947c - todo */
int mentor_ctrl_transfer(struct USB_Controller* sl, 
    struct Struct_10bab4* r8, 
    struct Struct_112b08* sb, 
    void* fp_0x34/*fp52*/, 
    int e/*fp4*/, 
    int f/*fp8*/)
{
#if 0
    fprintf(stderr, "mentor_ctrl_transfer: TODO!!!\n");
#endif

    int res;

    struct Struct_0xa0* fp_0x38;
    struct Mentor_Controller* r5 = sl->Data_0x84;
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
    fp_0x38 = MENTOR_TD_Setup(r5, r8, fp_0x30, f/*fp8*/);
    if (fp_0x38 == NULL)
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
    fp_0x38->Data_0xc = fp_0x34;
    fp_0x38->Data_0 = e/*fp4*/;

    r8->Data_4 = 0;
    //0x00009648
    InterruptLock(&r5->Data_0xd0);
    //0x0000967c
    fp_0x38->Data_0x2c.Data_0 = NULL;
    fp_0x30->Data_0xc->Data_0 = fp_0x38;
    fp_0x30->Data_0xc = &fp_0x38->Data_0x2c;

    if ((fp_0x30->Data_0x10 & 1) == 0)
    {
        //0x000096a4
        fp_0x30->Data_0x10 |= 1;
        fp_0x30->Data_0x28 = 0;

        *((int*)(r5->Data_0xc4)) = fp_0x38; //r1;
        //0x000096bc
        InterruptUnlock(&r5->Data_0xd0);
        //0x000096d0
        struct Struct_96d0
        {
            uint32_t Data_0; //0
            int Data_4; //4
            int fill_8; //8
            int Data_0xc; //0xc
            int fill_0x10; //0x10
            int Data_0x14; //0x14
            int fill_0x18[6]; //0x18
            int Data_0x30; //0x30
        }* r2;

        r2 = fp_0x30->Data_8;

        fp_0x30 = r2->Data_0x30;
        r2->Data_4 |= 0x100;
        fp_0x30->bData_0x1f = 0; //r3; //TODO!!!

        int fp_0x34_;
        uint32_t r1;
        if (r2->Data_4 & 1)
        {
            //0x00009700
            fp_0x30->Data_0x20 = 0;

            fp_0x34_ = 0x08;
            //->0x00009760
            r1 = 0;
            //0x00009764
        }
        //0x00009714
        else if (r2->Data_4 & 2)
        {
            //0x00009720
            fp_0x30->Data_0x20 = 1;

            fp_0x34_ = 0x40;
            r1 = 0x200;
            //->0x00009764
        }
        else
        {
            //0x0000973c
            if (fp_0x30->Data_0x20 != 0)
            {
                fp_0x34_ = 0;
                r1 = 0x200;
                //->0x00009764
            }
            else
            {
                //0x00009758
                fp_0x34_ = 0;
                r1 = 0;
            }
        }
        //0x00009764
        r1 |= (r5->Data_0x50 & 0x80)? 0x800: 0;
        r1 |= 0x500;
        r1 &= 0xf00;

        ((volatile uint16_t*)(r5->Data_0x14))[0x102/2] = r1;
        ((volatile uint16_t*)(r5->Data_0x14))[0x80/2] = (fp_0x30->Data_0x14 >> 4) & 0x7f;

        if (fp_0x30->bData_0x1c != 0x40)
        {
            //0x000097b8
            ((volatile uint8_t*)(r5->Data_0x14))[0x82] = fp_0x30->bData_0x1d;
            ((volatile uint8_t*)(r5->Data_0x14))[0x83] = fp_0x30->bData_0x1e;
        }
        //0x000097d8
        ((volatile uint8_t*)(r5->Data_0x14))[0x10b] = 0;

        uint16_t r2_;
        if (r2->Data_4 & 1)
        {
            //0x000097f8
            MENTOR_LoadFIFO(r5, 0, r2->Data_0xc, r2->Data_0 & 0xffff);

            r2_ = fp_0x34_ | 0x0a;
            //->0x0000987c
        }
        //0x0000981c
        else if (r2->Data_4 & 8)
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
                MENTOR_LoadFIFO(r5, 0, r2->Data_0xc, r3 & 0xffff);
            }
            //0x00009868
            r2_ = fp_0x34_ | 0x02;
            //->0x0000987c
        }
        else
        {
            //0x00009874
            r2_ = fp_0x34_ | 0x20;
        }
        //0x0000987c
        ((volatile uint16_t*)(r5->Data_0x14))[0x10a/2] = fp_0x30->bData_0x1c;
        ((volatile uint16_t*)(r5->Data_0x14))[0x102/2] |= r2_;
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
    if (f/*fp8*/ < 0)
    {
        //0x00009904
        res = MENTOR_WaitEndControl(sl, r8, sb, fp_0x38);

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



static struct io_usb_controller_methods_t mentor_controller_methods; //0x0000bf64
static struct io_usb_ctrl_pipe_methods_t mentor_ctrl_pipe_methods; //0x0000bf98

struct io_usb_dll_entry_t io_usb_dll_entry = //0x0000bf40
{
    "devu-mb86h60-mg.so",
    0xffffffff,
    mentor_init,
    mentor_shutdown,
    &mentor_controller_methods,
    &mentor_ctrl_pipe_methods,
#if 0 //TODO
    &mentor_int_pipe_methods,
    &mentor_bulk_pipe_methods,
    &mentor_isoch_pipe_methods,
#endif
};


static struct io_usb_controller_methods_t mentor_controller_methods = //0x0000bf64
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
#if 0 //TODO
    mentor_get_timer_from_controller,
#endif
};


static struct io_usb_ctrl_pipe_methods_t mentor_ctrl_pipe_methods = //0x0000bf98
{
    mentor_ctrl_endpoint_enable,
    0, //mentor_ctrl_endpoint_disable,
    mentor_ctrl_transfer,
    mentor_ctrl_transfer_abort,
    NULL
};



