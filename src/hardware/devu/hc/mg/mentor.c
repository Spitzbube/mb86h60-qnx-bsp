
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


struct Mentor_Controller;
#define USB_CONTROLLER_PRIV_T struct Mentor_Controller
#include "io-usb.h"


#ifdef MB86H60
void* dma_regs = NULL;
#endif


struct Struct_0xa0;
struct Struct_0x94
{
    struct Struct_0xa0* Data_0; //0
};

struct Struct_0xa0
{
    int fill_0[11]; //0
    struct Struct_0x94 Data_0x2c; //0x2c
    int fill_0x30[5]; //0x30
    //0x44
};


struct Struct_0xa4
{
    struct Struct_0xa4* Data_0; //0
    struct Struct_0xa4* Data_4; //4
    int Data_8; //8
    int* Data_0xc; //12
    int Data_0x10; //0x10 = 16
    int fill_0x14[6]; //0x14 = 20
    int Data_0x2c; //0x2c
    int fill_0x30[2]; //0x30
    int Data_0x38; //0x38
    int fill_0x3c; //0x3c
    //0x40 = 64
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
    int fill_0x48; //0x48
    int Data_0x4c; //0x4c
    int Data_0x50; //0x50
    int fill_0x54; //0x54
    int Data_0x58; //0x58
    int fill_0x5c[4]; //0x5c
    int Data_0x6c; //0x6c
    uint32_t Data_0x70; //0x70
    uint32_t Data_0x74; //0x74
    int Data_0x78; //0x78
    int Data_0x7c; //0x7c
    int fill_0x80[4]; //0x80
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
    int fill_0xc8[8]; //0xc8
    //0xe8
};

#ifdef MB86H60

void mb86h60_debug_regs(struct Mentor_Controller* r4)
{
    int i;

    ((volatile uint32_t*)(dma_regs))[0x14/4] = 1 << 1; //dma_dwUsbMode;
    int hwvers = ((volatile uint32_t*)(r4->Data_0x14))[0x6c];
    fprintf(stderr, "hwvers=0x%x\n", hwvers);

#if 0
    ((volatile uint32_t*)(dma_regs))[0x14/4] = 0 << 1; //dma_dwUsbMode;
    for (i = 0; i < 0xff; i++)
    {
        int reg = ((volatile uint32_t*)(r4->Data_0x14))[i];
        fprintf(stderr, "reg[0x%02x]=0x%x\n", i, reg);
    }
#endif

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

}

#endif //MB86H60


void mentor_slogf(/*struct Mentor_Controller* a, int b, int c, int d,
        char* e, char* f, char* g, char* h*/)
{
    fprintf(stderr, "mentor_slogf: TODO\n");
}


static void* mentor_interrupt_thread(void* a)
{
    fprintf(stderr, "mentor_interrupt_thread: TODO\n");

}


/* 0x00004f3c - complete */
int mentor_init()
{
    fprintf(stderr, "mentor_init\n");

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


int mentor_board_specific_init1(struct Mentor_Controller* a)
{
#if 1
    fprintf(stderr, "mentor_board_specific_init1: TODO!!!\n");
#endif

    return 0;

}


int mentor_board_specific_init2(struct Mentor_Controller* a)
{
#if 1
    fprintf(stderr, "mentor_board_specific_init2: TODO!!!\n");
#endif

    return 0;

}


int mentor_board_specific_shutdown2(struct Mentor_Controller* a)
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
    r4->Data_0x6c = 4;
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
#ifdef MB86H60
    dma_regs = mmap_device_memory(NULL/*void * addr*/,
                           0x800/*size_t len*/,
                           0xb00/*int prot*/,
                           0x10001/*int flags*/,
                            0xc7000000);

#endif

    r4->Data_0x14 = mmap_device_memory(NULL/*void * addr*/,
                           0x2000/*size_t len*/,
                           0xb00/*int prot*/,
                           0x10001/*int flags*/,
#if 0
//                           *(uint64_t*)(char*)&(r7->Data_4->Data_0x68)/*uint64_t physical*/);
                            //UNALIGNED_RET64(r7->Data_4->Data_0x68_));
                            //ENDIAN_BE64(*((uint64_t*)(r7->Data_4->Data_0x68_))));
#else
                            0xc7000800);
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

                                            ((volatile uint8_t*)(r4->Data_0x14))[0x0f] = 0;
                                            ((volatile uint8_t*)(r4->Data_0x14))[0x60] = 0;
                                            ((volatile uint32_t*)(r4->Data_0x14))[0x414/4] = 0;
                                            ((volatile uint32_t*)(r4->Data_0x14))[0x404/4] = 0x1008;

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

                                                        ((volatile uint8_t*)(r4->Data_0x14))[0x01] = 0x60;
                                                        ((volatile uint8_t*)(r4->Data_0x14))[0x60] = 0x01;

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


static struct io_usb_controller_methods_t mentor_controller_methods; //0x0000bf64

struct io_usb_dll_entry_t io_usb_dll_entry = //0x0000bf40
{
    "devu-mb86h60-mg.so",
    0xffffffff,
    mentor_init,
    mentor_shutdown,
    &mentor_controller_methods,
#if 0 //TODO
    &mentor_ctrl_pipe_methods,
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
#if 0 //TODO
    mentor_set_bus_state,
    0, 0, 0,
    mentor_set_port_feature,
    mentor_clear_port_feature,
    mentor_check_port_status,
    mentor_check_device_connected,
    mentor_get_root_device_speed,
    mentor_get_timer_from_controller,
#endif
};



