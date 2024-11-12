
#include "externs.h"


struct ArrayClass  ArrayClass[8]; //0x00127230

static void* usb_port_enum_handler(void*);


/* 0x0010a498 - complete */
int usb_port_monitor_wait_init_complete(void)
{
#if 0
    fprintf(stderr, "usb_port_monitor_wait_init_complete\n");
#endif

    pthread_sleepon_lock();

    while ((UsbdiGlobals.Data_0x10 & (1 << 31)) == 0)
    {
        pthread_sleepon_wait(&UsbdiGlobals.Data_0x10);
    }

    pthread_sleepon_unlock();

    return 0;
}


/* 0x0010a4d8 - complete */
int usb_port_monitor_start()
{
#if 0
    fprintf(stderr, "usb_port_monitor_start\n");
#endif

    pthread_sleepon_lock();

    UsbdiGlobals.Data_0x10 |= (1 << 31);

    pthread_sleepon_signal(&UsbdiGlobals.Data_0x10);

    pthread_sleepon_unlock();

    return 0;
}


/* 0x00110884 - todo */
int INIT_HCDClassInterface()
{
#if 0
    fprintf(stderr, "INIT_HCDClassInterface\n");
#endif

    pthread_attr_t fp_0x50;
    struct sched_param fp_0x78;

    if (pthread_rwlock_init(&usb_rwlock, 0) == -1)
    {
        fwrite("INIT_ScanUSBController:  Unable to initialize rwlock\n", 1, 0x35, stderr);
        return 1;
    }
    //loc_1108d0
    pthread_attr_init(&fp_0x50);
    pthread_attr_setschedpolicy(&fp_0x50, 2);
    fp_0x78.sched_priority = usb_enum_priority;
    pthread_attr_setschedparam(&fp_0x50, &fp_0x78);
    pthread_attr_setinheritsched(&fp_0x50, 2);
    pthread_attr_setdetachstate(&fp_0x50, 1);
    pthread_attr_setstacksize(&fp_0x50, 0x4000);

    if (pthread_create(NULL, &fp_0x50, usb_port_enum_handler, NULL) != 0)
    {
        fwrite("Unable to create thread\n", 1, 0x18, stderr);
        return 1;
    }

    return 0;
}


/* 10db1c - todo */
int sub_10db1c()
{
#if 1
    fprintf(stderr, "sub_10db1c: TODO!!!\n");
#endif

    return 0;
}


/* 113ed0 - todo */
int sub_113ed0(struct USB_Controller* fp_0x18, int fp_0x1c)
{
#if 0
    fprintf(stderr, "sub_113ed0: %d: TODO!!!\n", fp_0x1c);
#endif

    int fp_0x10;

    pthread_mutex_lock(&Data_120220[fp_0x18->Data_8].Data_0x14[fp_0x1c].Data_4);

    fp_0x10 = Data_120220[fp_0x18->Data_8].Data_0x14[fp_0x1c].Data_0 & 1;

    Data_120220[fp_0x18->Data_8].Data_0x14[fp_0x1c].Data_0 &= ~1;

    pthread_mutex_unlock(&Data_120220[fp_0x18->Data_8].Data_0x14[fp_0x1c].Data_4);

    return fp_0x10;
}


/* 110b48 - todo */
void sub_110b48(int a, int b)
{
#if 1
    fprintf(stderr, "sub_110b48: TODO!!!\n");
#endif

}


/* 106124 - todo */
void sub_106124(int a, int b, int c, int d, int e)
{
#if 1
    fprintf(stderr, "sub_106124: TODO!!!\n");
#endif

}


/* 1109a0 - todo */
int sub_1109a0(int a, int b)
{
#if 1
    fprintf(stderr, "sub_1109a0: TODO!!!\n");
#endif

    return 0;
}


/* 110b74 - todo */
void sub_110b74(int fp_0x28)
{
#if 1
    fprintf(stderr, "sub_110b74: %d: TODO!!!\n", fp_0x28);
#endif

    struct USB_Controller* fp_0x10;
    uint8_t* fp_0x14;
    uint32_t fp_0x18;
    uint32_t fp_0x1c;
    int fp_0x20 = 0;
    uint32_t fp_0x24;

    fp_0x14 = &Data_120220[fp_0x28].bData_4[0];
    fp_0x10 = &usb_controllers[fp_0x28];

    (fp_0x10->controller_methods->check_port_status)(fp_0x10, &fp_0x24);

    for (fp_0x18 = 0; fp_0x18 < 16; fp_0x18++)
    {
        //loc_110bf0
        fp_0x1c = fp_0x14[fp_0x18];

        if (fp_0x1c < 16)
        {
            if ((sub_113ed0(fp_0x10, fp_0x1c) != 0) ||
                ((fp_0x24 >> fp_0x1c) & 1))
            {
                //loc_110c44
                sub_110b48(fp_0x28, fp_0x1c);

                if (Data_120220[fp_0x28].Data_0x14[fp_0x1c].Data_0 & 0x02)
                {
                    //0x00110c98
                    sub_106124(fp_0x28, 0, 0, fp_0x1c, 0);

                    Data_120220[fp_0x28].Data_0x14[fp_0x1c].Data_0 &= ~0x02;
                }
                //loc_110d30
                fp_0x20 = sub_1109a0(fp_0x28, fp_0x1c);

                if (fp_0x20 != 0)
                {
                    if (fp_0x20 != 0x13)
                    {
                        //0x00110d5c
                        sub_106124(fp_0x28, 0, 0, fp_0x1c, 1);

                        Data_120220[fp_0x28].Data_0x14[fp_0x1c].Data_0 |= 0x02;
                    }
                    //loc_110dfc
                }
                //loc_110dfc
            }
            //loc_110dfc
        } //if (fp_0x1c < 16)
        //loc_110df8
        //loc_110dfc
    }
}



/* 10a51c - todo */
int sub_10a51c(int a)
{
#if 1
    fprintf(stderr, "sub_10a51c: %d: TODO!!!\n", a);
#endif

    struct USB_Controller* ctrl;
    uint32_t i;

    for (i = 0; i < 20; i++)
    {
        //sub_10a51c
        ctrl = CTRL_HCLookup(i);

        if ((ctrl != NULL) &&
            ((ctrl->Data_0x6c & 0x100) == a))
        {
            sub_110b74(i);
        }
    }

    return 0;
}



/* 10a5a4 - todo */
void sub_10a5a4()
{
#if 1
    fprintf(stderr, "sub_10a5a4: TODO!!!\n");
#endif

}



/* 0x0010a6c0 - todo */
static void* usb_port_enum_handler(void* a)
{
#if 0
    fprintf(stderr, "usb_port_enum_handler\n");
#endif

    int r3;
    struct USB_Controller* fp_0x14;
    struct Inner8* fp_0x18;
    timer_t fp_0x1c;
    struct itimerspec fp_0x2c;
    struct sigevent fp_0x3c;
    struct
    {
        int fill_0; //0
        uint8_t bData_4; //4
        struct Inner8
        {
            int Data_0; //0
            int fill_4[2]; //4
            uint8_t fill_0xc;
            uint8_t bData_0xd; //0xd
            int Data_0x10; //0x10
            int fill_0x14[29]; //0x14
            int Data_0x88; //0x88
            int fill_0x8c[2]; //0x8c
            pthread_mutex_t Data_0x94; //0x94
            pthread_cond_t Data_0x9c; //0x9c
            int Data_0xa4; //0xa4
            int Data_0xa8; //0xa8
            //???
        }* Data_8; //8 
        int fill_0xc; //12
        //16???
    } fp_0x4c;
    iov_t fp_0x54;

    if (pthread_setname_np(0, "port_enum_hdl") != 0)
    {
        usb_slogf(12, 2, 0, "%s: Setting thread name failed %s(%d)",
            "CLASS_ThreadHandler",
            strerror(errno), errno);
    }
    //loc_10a73c
    Data_1273b0 = ChannelCreate(0x0a);

    if ((Data_1273b0 == -1) ||
        ((Data_127814 = ConnectAttach(0, 0, Data_1273b0, 0x40000000, 0)) == -1))
    {
        //loc_10a7bc
        usb_slogf(12, 2, 0, "%s: Enum channel create failed %s(%d)",
            "CLASS_ThreadHandler",
            strerror(errno), errno);
    }
    //loc_10a80c
    fp_0x3c.sigev_notify = 4;
    fp_0x3c.sigev_coid = Data_127814;
    fp_0x3c.sigev_priority = usb_enum_priority;
    fp_0x3c.sigev_value.sival_int = 0;
    fp_0x3c.sigev_code = 1;

    if (timer_create(2, &fp_0x3c, &fp_0x1c) == -1)
    {
        usb_slogf(12, 2, 0, "%s: Enum Timer create failed %s(%d)",
            "CLASS_ThreadHandler",
            strerror(errno), errno);
    }
    //loc_10a8bc
    usb_port_monitor_wait_init_complete();

#if 1
    fprintf(stderr, "usb_port_enum_handler: after usb_port_monitor_wait_init_complete: TODO\n");
#else
    delay(20);
#endif

    fp_0x2c.it_value.tv_sec = 0;
    fp_0x2c.it_value.tv_nsec = 100; //100000000;
    fp_0x2c.it_interval.tv_sec = 0;
    fp_0x2c.it_interval.tv_nsec = 100; //100000000;

    timer_settime(fp_0x1c, 0, &fp_0x2c, 0);

    SETIOV(&fp_0x54, &fp_0x4c, 16);

    while (1)
    {
        //loc_10a924
#if 0
        fprintf(stderr, "usb_port_enum_handler: before MsgReceivev\n");
#endif
        int fp_0x10 = MsgReceivev(Data_1273b0, &fp_0x54, 1, 0);
#if 1
        fprintf(stderr, "usb_port_enum_handler: after MsgReceivev\n");
#endif
        if (fp_0x10 == -1)
        {
            continue;
        }
        //loc_10a968
        if (pthread_rwlock_rdlock(&usb_rwlock) != 0)
        {
            usb_slogf(12, 2, 1, "%s: error acquiring rdlock",
                "CLASS_ThreadHandler");
        }
        //loc_10a9a4
        if (UsbdiGlobals.Data_0x17c != 0)
        {
            if (pthread_rwlock_unlock(&usb_rwlock) != 0)
            {
                usb_slogf(12, 2, 1, "%s: error releasing rdlock",
                    "CLASS_ThreadHandler");
                //->loc_10ace4
            }
            //->loc_10ace0
            break;
        }
        else
        {
            //loc_10a9f8
            switch (fp_0x4c.bData_4)
            {
                case 2:
                    //loc_10aa28
                    sub_10a51c(0x100); //usb_check_rport_change???
                    //->loc_10aca0
                    break;
                    
                case 1:
                    //loc_10aa34
                    sub_10a51c(0x00); //usb_check_rport_change???
                    //->loc_10aca0
                    break;

                case 3:
                    //loc_10aa40
                    sub_10a5a4(); //usb_check_eport_change???
                    //->loc_10aca0
                    break;
                    
                case 4:
                    //loc_10aa48
                    fp_0x18 = fp_0x4c.Data_8;

                    usb_slogf(12, 2, 1, "Processing Reset Event: path %d dno %d, refcnt %d",
                        fp_0x18->Data_0x88, 
                        fp_0x18->Data_0, 
                        fp_0x18->Data_0xa8);

                    pthread_mutex_lock(&fp_0x18->Data_0x94);

                    fp_0x14 = CTRL_HCLookup(fp_0x18->Data_0x88);

                    if ((fp_0x14 == NULL) ||
                        ((fp_0x18->bData_0xd & 1) == 0))
                    {
                        //loc_10aad4
                        fp_0x18->Data_0xa4 = 0x13;
                    }
                    else
                    {
                        //loc_10aae4
                        fp_0x18->Data_0xa4 = sub_10db1c(fp_0x14, fp_0x18);
                    }
                    //loc_10ab00
                    pthread_cond_broadcast(&fp_0x18->Data_0x9c);

                    pthread_mutex_unlock(&fp_0x18->Data_0x94);
                    //->loc_10aca0
                    break;
                    
                case 6:
                    //loc_10ab24
                    fp_0x18 = fp_0x4c.Data_8;

                    usb_slogf(12, 2, 1, "Processing Detach Event: path %d dno %d, refcnt %d",
                        fp_0x18->Data_0x88, 
                        fp_0x18->Data_0, 
                        fp_0x18->Data_0xa8);

                    fp_0x14 = CTRL_HCLookup(fp_0x18->Data_0x88);

                    if ((fp_0x14 == NULL) ||
                        (fp_0x18 == NULL)

                        //TODO!!!

                        )
                    {
                        //loc_10ac10
                        usb_slogf(12, 2, 1, "Processing Detach Event (hold off): path %d dno %d, refcnt %d, opening %d, Status %x",
                            fp_0x18->Data_0x88, 
                            fp_0x18->Data_0, 
                            fp_0x18->Data_0xa8,
                            fp_0x18->Data_0x10,
                            fp_0x18->bData_0xd);
                    }
                    //loc_10aca0
                    break;
                    
                case 5:
                    //loc_10ac9c
                    /* Not handled */
                    //loc_10aca0
                    break;
                    
                default:
                    //loc_10ac68
                    usb_slogf(12, 2, 0, "%s: Enum unhandled pulse code(%d)",
                        "CLASS_ThreadHandler", fp_0x4c.bData_4);
                    //->loc_10aca0
                    break;
            } //switch (fp_0x4c.bData_4)
            //loc_10aca0
            if (pthread_rwlock_unlock(&usb_rwlock) != 0)
            {
                usb_slogf(12, 2, 1, "%s: error releasing rdlock", 
                    "CLASS_ThreadHandler");
                //->loc_10a924
            }
            //->loc_10a920
        }
    } //while (1)
    //loc_10ace4
}


/* 0x0010acec - todo */
struct ArrayClass* CLASS_RegisterDriver(struct Struct_10acec* a)
{
#if 0
    fprintf(stderr, "CLASS_RegisterDriver\n");
#endif

    uint32_t i;
    struct ArrayClass* p = &ArrayClass[0];

    for (i = 0; i < 8; p++, i++)
    {
        if (p->bData_0x2c == 0)
        {
            p->Data_0 = a->Data_0;
            p->Data_4 = a->Data_4;
            p->Data_8 = a->Data_8;
            p->Data_0xc = a->Data_0xc;
            p->Data_0x10 = a->Data_0x10;
            p->Data_0x14 = a->Data_0x14;
            p->Data_0x20 = a->Data_0x18;
            p->Data_0x24 = a->Data_0x1c;
            p->Data_0x28 = a->Data_0x20;
            p->bData_0x2c = 1;

            return p;
        }
    }

    return 0;
}


