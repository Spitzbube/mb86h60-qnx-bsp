
#include "externs.h"


struct ArrayClass  ArrayClass[8]; //0x00127230

static void* usb_port_enum_handler(void*);


/* 0x0010a4d8 - complete */
int usb_port_monitor_start()
{
#if 0
    fprintf(stderr, "usb_port_monitor_start\n");
#endif

    pthread_sleepon_lock();

    UsbdiGlobals.Data_0x10 |= 0x80000000;

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

    if (pthread_create(0, &fp_0x50, usb_port_enum_handler, 0) != 0)
    {
        fwrite("Unable to create thread\n", 1, 0x18, stderr);
        return 1;
    }

    return 0;
}


/* 0x0010a6c0 - todo */
static void* usb_port_enum_handler(void* a)
{
#if 0
    fprintf(stderr, "usb_port_enum_handler\n");
#endif

    int r3;
    timer_t fp_0x1c;
    struct itimerspec fp_0x2c;
    struct sigevent fp_0x3c;
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
    sub_10a498();

    delay(20);

    fp_0x2c.it_value.tv_sec = 0;
    fp_0x2c.it_value.tv_nsec = 100000000;
    fp_0x2c.it_interval.tv_sec = 0;
    fp_0x2c.it_interval.tv_nsec = 100000000;

    timer_settime(fp_0x1c, 0, &fp_0x2c, 0);

    while (1)
    {
        //loc_10a924
        int fp_0x10 = MsgReceivev(Data_1273b0, &fp_0x54, 1, 0);
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
        //TODO!!!
        
        fprintf(stderr, "usb_port_enum_handler: loc_10a9a4: TODO!!!\n");
    }
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


