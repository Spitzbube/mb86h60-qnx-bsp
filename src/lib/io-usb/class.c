
#include "externs.h"



struct UsbInterface UsbInterfaces[80]; //0x001215b0
struct UsbEndpoint UsbEndpoints[320]; //0x00122230
struct ArrayClass  ArrayClass[8]; //0x00127230
struct UsbConfiguration UsbConfigurations[40]; //0x001273b4


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


/* 113914 - todo */
struct USB_Controller_Inner_0x7c* sub_113914(struct USB_Controller* fp_0x10, int fp_0x14, int fp_0x18)
{
#if 0
    fprintf(stderr, "sub_113914: TODO!!!\n");
#endif

    struct USB_Controller_Inner_0x7c* fp_0xc;
    uint32_t fp8;

    for (fp8 = 0; fp8 < 20; fp8++)
    {
        if (fp_0x10->Data_0x78[fp8] != NULL)
        {
            fp_0xc = &fp_0x10->Data_0x7c[fp8];

            if ((fp_0xc->Data_0x1c == ((fp_0x14 != 0)? fp_0x10->Data_0x78[fp_0x14 - 1]: NULL)) &&
                (fp_0xc->Data_0x20 == fp_0x18) &&
                ((fp_0xc->bData_0xd & 1) != 0))
            {
                return fp_0xc;
            }
        }
    }

    return NULL;
}



/* 10c748 - todo */
int sub_10c748(struct USB_Controller* a, void* b)
{
#if 1
    fprintf(stderr, "sub_10c748: TODO!!!\n");
#endif

    return 0;
}




/* 10c904 - todo */
int CLASS_ExtractDevice(int fp_0x10, int fp_0x14, int fp_0x18)
{
#if 0
    fprintf(stderr, "CLASS_ExtractDevice: TODO!!!\n");
#endif

    struct USB_Controller* fp_0xc;
    struct USB_Controller_Inner_0x7c* fp8;
    
    fp_0xc = &usb_controllers[fp_0x10];

    if (pthread_mutex_lock(&fp_0xc->Data_0x24) != 0)
    {
        usb_slogf(12, 2, 0, "%s(%d):  error acquiring mutex, errno %d",
            "CLASS_ExtractDevice", 1009, errno);
    }
    //loc_10c990
    fp8 = sub_113914(fp_0xc, fp_0x14, fp_0x18);
    if (fp8 == 0)
    {
        if (pthread_mutex_unlock(&fp_0xc->Data_0x24) != 0)
        {
            usb_slogf(12, 2, 0, "%s(%d):  error releasing mutex, errno %d",
                "CLASS_ExtractDevice", 1014, errno);
        }
        //loc_10ca0c
        usb_slogf(12, 2, 1, "CLASS_ExtractDevice:  no parent, bus %d, port %d",
            fp_0x10, fp_0x18);

        //->loc_10cb20
        return 2;
    }
    //loc_10ca3c
    fp8->bData_0xd |= 2;
    fp8->bData_0xd &= ~1;

    if (pthread_mutex_unlock(&fp_0xc->Data_0x24) != 0)
    {
        usb_slogf(12, 2, 0, "%s(%d):  error releasing mutex, errno %d",
            "CLASS_ExtractDevice", 1024, errno);
    }
    //loc_10cac0
    usb_slogf(12, 2, 1, "CLASS_ExtractDevice:  dno %d, vid %x, parent %d, port %d, openings %d",
        fp8->device_address, 
        fp8->device_descriptor.idVendor, 
        fp_0x14, fp_0x18, fp8->Data_0x10);

    return sub_10c748(fp_0xc, fp8);
}


/* 110b48 - complete */
void sub_110b48(int a, int b)
{
#if 0
    fprintf(stderr, "sub_110b48: TODO!!!\n");
#endif

    CLASS_ExtractDevice(a, 0, b);
}


/* 106124 - todo */
void sub_106124(int a, int b, int c, int d, int e)
{
#if 1
    fprintf(stderr, "sub_106124: TODO!!!\n");
#endif

}


/* 10afc4 - todo */
struct USB_Controller_Inner_0x7c* sub_10afc4(struct USB_Controller* fp_0x10)
{
#if 0
    fprintf(stderr, "sub_10afc4: TODO!!!\n");
#endif

    uint32_t fp_0xc;
    struct USB_Controller_Inner_0x7c* fp8;

    //->loc_10b188
    for (fp_0xc = 0; fp_0xc < 20; fp_0xc++)
    {
        //loc_10afe0
        if (fp_0x10->Data_0x78[fp_0xc] == NULL)
        {
            if (fp_0xc > 2)
            {
                usb_slogf(12, 2, 1, "CLASS_MakeNewDeviceEntry");
            }
            //loc_10b028
            fp8 = &fp_0x10->Data_0x7c[fp_0xc];

            memset(fp8, 0, sizeof(struct USB_Controller_Inner_0x7c));

            fp_0x10->Data_0x78[fp_0xc] = fp8;

            fp8->new_device_address = fp_0xc + 1;
            fp8->Data_0x40.Data_0x14 = 0;
            fp8->Data_0x40.Data_0x18 = &fp8->Data_0x40.Data_0x14;
            fp8->Data_0x40.Data_0x1c = 0;
            fp8->Data_0x40.Data_0x20 = &fp8->Data_0x40.Data_0x1c;

            pthread_mutex_init(&fp8->Data_0x70, 0);
            pthread_cond_init(&fp8->Data_0x78, 0);
            pthread_mutex_init(&fp8->Data_0x94, 0);
            pthread_cond_init(&fp8->Data_0x9c, 0);

            usb_slogf(12, 2, 1, "%s(%d): devno %d, dmutexp %p, emutexp %p",
                "CLASS_MakeNewDeviceEntry", 0x162, 
                fp8->new_device_address, 
                &fp8->Data_0x94, &fp8->Data_0x70);

            usb_data_store_init(&fp8->Data_0x8c, 0);

            return fp8;
        }
        //loc_10b17c
    }

    return 0;
}


/* 10d208 - todo */
struct USB_Controller_Inner_0x7c* sub_10d208(struct USB_Controller* fp_0x10, int fp_0x14, int fp_0x18, int fp_0x1c)
{
#if 0
    fprintf(stderr, "sub_10d208: TODO!!!\n");
#endif

    struct USB_Controller_Inner_0x7c* fp8;

    fp8 = sub_10afc4(fp_0x10);
    if (fp8 == NULL)
    {
        usb_slogf(12, 2, 1, "CLASS_EnumerateDevice:  Too many devices");

        return 0;
    }
    //loc_10d260
    fp8->bData_0xc = fp_0x1c;
    fp8->Data_0x1c = (fp_0x14 == 0)? NULL: fp_0x10->Data_0x78[fp_0x14 - 1];
    fp8->Data_0x20 = fp_0x18;
    fp8->Data_0x88 = fp_0x10->Data_8;
    fp8->Data_0x40.bData_3 = 0;
    fp8->Data_0x40.wData_4 = 8;

    return fp8;
}


/* 112b08 - todo */
int USB_EnableEndpoint(struct USB_Controller* fp_0x10, 
    struct USB_Controller_Inner_0x7c* fp_0x14, 
    struct Struct_112b08* fp_0x18)
{
#if 1
    fprintf(stderr, "USB_EnableEndpoint: TODO!!!\n");
#endif

    int fp8 = 0;

    switch (fp_0x18->bData_3 & 0x03)
    {
        case 0:
            //loc_112b50
            fp8 = (fp_0x10->ctrl_pipe_methods->ctrl_endpoint_enable)(fp_0x10, fp_0x14, fp_0x18);
            break;

        case 1:
            //loc_112b78
            fp8 = (fp_0x10->isoch_pipe_methods->isoch_endpoint_enable)(fp_0x10, fp_0x14, fp_0x18);

            fp_0x18->Data_0x28 = 0;
            break;

        case 2:
            //loc_112bac
            fp8 = (fp_0x10->bulk_pipe_methods->bulk_endpoint_enable)(fp_0x10, fp_0x14, fp_0x18);
            break;

        case 3:
            //loc_112bd4
            fp8 = (fp_0x10->int_pipe_methods->int_endpoint_enable)(fp_0x10, fp_0x14, fp_0x18);
            break;
#if 0
        default:
            //loc_112bf8
            break;
#endif
    }
    //loc_112bf8
    return fp8;
}


/* 10cb2c - todo */
int CLASS_CancelDeviceEnumeration(struct USB_Controller_Inner_0x7c* a)
{
#if 1
    fprintf(stderr, "CLASS_CancelDeviceEnumeration: TODO!!!\n");
#endif

    return 0;
}


/* 10bab4 - todo */
void CLASS_CreateUrb(struct Struct_10bab4* fp_0x10, 
    int fp_0x14, 
    int fp_0x18, 
    int fp_0x1c,
    int request_type/*fp4*/, //e.g. USB_GET_DESCRIPTOR 
    int f/*fp8*/, 
    int g/*fp_0xc*/, 
    int h/*fp_0x10*/, 
    int i/*fp_0x14*/, 
    int j/*fp_0x18*/, 
    void* buffer/*fp_0x1c*/, 
    int l/*fp_0x20*/, 
    int o/*fp_0x24*/)
{
#if 1
    fprintf(stderr, "CLASS_CreateUrb: request_type=%d: TODO!!!\n",
        request_type);
#endif

    struct USB_Controller* fp8;

    fp8 = CTRL_HCLookup(fp_0x14);

    fp_0x10->Data_0x10 = 7;
    fp_0x10->Data_0x18 = fp_0x14;
    fp_0x10->Data_0x14 = fp_0x18;
    fp_0x10->Data_0x1c = o; //fp_0x24;
    fp_0x10->Data_8 = 0;
    fp_0x10->Data_0x20 = 0;
    fp_0x10->Data_0x24 = 0;
    fp_0x10->Data_0x28 = 0;
    fp_0x10->Data_0 = 0;
    fp_0x10->Data_0x38 = (fp_0x1c == 1)? 0x80: 0x00;
    fp_0x10->Data_0x3c = request_type; //fp4;
    fp_0x10->Data_0x40 = h; //fp_0x10;
    fp_0x10->Data_0x44 = g; //fp_0xc;
    fp_0x10->Data_0x48 = f; //fp8;
    fp_0x10->Data_0x4c = i; //fp_0x14;
    fp_0x10->Data_0x50 = j; //fp_0x18
    fp_0x10->Data_0x58 = 0;
    fp_0x10->Data_0x30 = l; //fp_0x20

    if (l/*fp_0x20*/ != 0)
    {
        if (fp8->Data_0x6c & 0x40000000)
        {
            fp_0x10->Data_0x2c = buffer/*fp_0x1c*/;
            //->loc_10bc14
        }
        else
        {
            //loc_10bbfc
            fp_0x10->Data_0x2c = sub_117854(buffer/*fp_0x1c*/);
        }
    }
    //loc_10bc14
}


/* 11199c - todo */
void sub_11199c(struct Struct_10bab4* fp8, uint8_t* fp_0xc)
{
#if 1
    fprintf(stderr, "sub_11199c: fp_0xc=0x%x: TODO!!!\n", fp_0xc);
#endif

    fp_0xc[0] = ((uint8_t)(fp8->Data_0x40) << 5) | (fp8->Data_0x38) | (fp8->Data_0x44);
    fp_0xc[1] = fp8->Data_0x3c;
    fp_0xc[2] = fp8->Data_0x4c;
    fp_0xc[3] = fp8->Data_0x48;
    fp_0xc[4] = fp8->Data_0x50;
    fp_0xc[5] = fp8->Data_0x50 >> 8;
    fp_0xc[6] = fp8->Data_0x30;
    fp_0xc[7] = fp8->Data_0x30 >> 8;
}


/* 110e50 - todo */
int sub_110e50(int a, int b)
{
#if 1
    fprintf(stderr, "sub_110e50: TODO!!!\n");
#endif


    return 0;
}


/* 111030 - todo */
int sub_111030(struct USB_Controller* a, void* b, struct Struct_112b08* c)
{
#if 1
    fprintf(stderr, "sub_111030: TODO!!!\n");
#endif

    return 0;
}


/* 111ab0 - todo */
int USB_ControlTransfer(struct Struct_10bab4* fp_0x40, struct Struct_112b08* fp_0x44)
{
#if 1
    fprintf(stderr, "USB_ControlTransfer: TODO!!!\n");
#endif

    int fp_0x3c = 0;
    void* fp_0x38;
    int fp_0x34;
    int fp_0x30 = 0;
    uint32_t fp_0x2c = 0;
    int fp_0x28;
    int fp_0x24;
    int fp_0x20 = 0;
    uint32_t fp_0x1c = 0;
    int fp_0x18;
    int fp_0x14;
    void* fp_0x10 = fp_0x40->Data_0x2c;
    struct USB_Controller* fp_0xc = &usb_controllers[fp_0x40->Data_0x18];
    struct
    {
        int fill_0[3]; //0
        uint8_t bData_0xc; //0xc = 12
    }* fp8;

    // Allocate Setup data
    fp_0x38 = usbd_alloc(8);
    if (fp_0x38 == NULL)
    {
        return 12;
    }
    //loc_111b3c
    fp_0x34 = usb_controllers[fp_0x40->Data_0x18].Data_0x70 + 1;
    fp_0x18 = fp_0xc->Data_0x6c & 0x800;
    //->loc_111f20
    while (fp_0x34--)
    {
        //loc_111b80: Fill Setup Packet
        sub_11199c(fp_0x40, fp_0x38);

        fp_0x40->Data_0x34 = 0;
        fp_0x30 = 0;
        fp_0x2c = fp_0x40->Data_0x30;

        if (fp_0x18 != 0)
        {
            //0x00111bb8
            fp_0x10 = sub_117854(fp_0x38);
            fp_0x14 = 0;
            //->loc_111c0c
        }
        else
        {
            //loc_111bd4
            if ((fp_0xc->Data_0x6c & 0x40000000) == 0)
            {
                //0x00111be8
                fp_0x10 = sub_117854(fp_0x38);
                //->loc_111c04
            }
            else
            {
                //loc_111bfc
                fp_0x10 = fp_0x38;
            }
            //loc_111c04
            fp_0x14 = 0x80000000;
        }
        //loc_111c0c
        fp_0x3c = (fp_0xc->ctrl_pipe_methods->ctrl_transfer)(fp_0xc, 
            fp_0x40, fp_0x44, fp_0x10, 8, fp_0x14 | 1);

        if ((fp_0x3c == 0) && (fp_0x40->Data_0x30 != 0))
        {
            //0x00111c64
            fp_0x10 = fp_0x40->Data_0x2c;
            fp_0x40->Data_0x34 = 0;
            //->loc_111dd4
            while ((fp_0x1c < fp_0x2c) && (fp_0x30 == 0) && (fp_0x3c == 0))
            {
                //loc_111c80
//                uint32_t r3 = ((fp_0xc->Data_0x60 != 0)? fp_0xc->Data_0x60: fp_0x44->wData_4)/*r3*/;
                fp_0x28 = (((fp_0xc->Data_0x60 != 0)? fp_0xc->Data_0x60: fp_0x44->wData_4)/*r3*/ > (fp_0x2c - fp_0x1c)/*r2*/)? (fp_0x2c - fp_0x1c)/*r2*/: 
                    ((fp_0xc->Data_0x60 != 0)? fp_0xc->Data_0x60: fp_0x44->wData_4)/*r3*/;

                fp_0x40->Data_0x30 = fp_0x28;
                fp_0x24 = fp_0x40->Data_0x34;

                fp_0x3c = (fp_0xc->ctrl_pipe_methods->ctrl_transfer/*ip*/)(fp_0xc,
                    fp_0x40, fp_0x44, 
                    ((char*)fp_0x10 + fp_0x1c)/*lr*/,
                    fp_0x28, 
                    ((fp_0x40->Data_0x38 == 0x80)? 4: 8) | fp_0x14);

                fp_0x20 += fp_0x28;

                if (fp_0x18 != 0)
                {
                    //0x00111d54
                    fp_0x1c = fp_0x20;
                    //->loc_111dd4
                }
                else
                {
                    //loc_111d60
#if 0
                    int r2 = fp_0x40->Data_0x34;
                    int r3 = fp_0xc->Data_0x60;

                    if (r3 != 0)
                    {
                        r3 = fp_0xc->Data_0x60;
                        //->loc_111d8c
                    }
                    else
                    {
                        //loc_111d84
                        r3 = fp_0x44->wData_4;
                    }
                    //loc_111d8c
                    if (((r2 % r3) != 0) ||
                        (fp_0x40->Data_0x34 == fp_0x24))
                    {
                        //loc_111db8
                        r3 = 1;
                    }
                    else
                    {
                        //loc_111dc0
                        r3 = 0;
                    }
                    //loc_111dc4
                    fp_0x30 = r3;
#else
                    fp_0x30 = (((fp_0x40->Data_0x34/*r2*/ % 
                        ((fp_0xc->Data_0x60 != 0)? fp_0xc->Data_0x60: fp_0x44->wData_4)/*r3*/) != 0) ||
                        (fp_0x40->Data_0x34 == fp_0x24))? 1: 0;
#endif
                    fp_0x1c = fp_0x40->Data_0x34;
                }
                //loc_111dd4
            } //while ((fp_0x1c < fp_0x2c) && (fp_0x30 == 0) && (fp_0x3c == 0))
            //loc_111dfc
        }
        //loc_111dfc
        if (fp_0x3c == 0)
        {
            //0x00111e08
            fp_0x40->Data_0x30 = 0;

            fp_0x3c = (fp_0xc->ctrl_pipe_methods->ctrl_transfer)(fp_0xc,
                fp_0x40, fp_0x44, 0, 0,
                (fp_0x40->Data_0x38 == 0x80)? 0x8000000a: 0x80000006);
        }
        //loc_111e64
        if (fp_0x3c != 0)
        {
            //0x00111e70
            (fp_0xc->ctrl_pipe_methods->ctrl_transfer_abort)(fp_0xc, fp_0x40, fp_0x44);
        }
        //loc_111e8c
        if ((fp_0x3c != 0) && (fp_0xc->Data_0x6c & 0x40))
        {
            //0x00111eac
            fp8 = sub_110e50(fp_0x40->Data_0x18, fp_0x40->Data_0x14);
            if ((fp8 != NULL) && (fp8->bData_0xc != 2))
            {
                sub_111030(fp_0xc, fp8, fp_0x44);
            }
            //loc_111efc
        }
        //loc_111efc
        if (fp_0x3c == 0)
        {
            //->loc_111f48
            break;
        }

        if (fp_0x3c == 12)
        {
            //->loc_111f48
            break;
        }

        fp_0x40->Data_0x30 = fp_0x2c;
        //loc_111f20
    } //while (fp_0x34--)
    //loc_111f48
    fp_0x40->Data_0x30 = fp_0x2c;

    usbd_free(fp_0x38);

    if (fp_0x3c != 0)
    {
        return 5;
    }
    //loc_111f70
    return 0;
}


/* 10cc08 - todo */
void CLASS_CreateDeviceDescriptor(uint8_t* fp8, usbd_device_descriptor_t* fp_0xc)
{
#if 1
    int i;
    for (i = 0; i < sizeof(usbd_device_descriptor_t); i++)
    {
        fprintf(stderr, "CLASS_CreateDeviceDescriptor: fp8[%d]=0x%02x\n", i, fp8[i]);
    }
#endif

    fp_0xc->bLength = fp8[0];
    fp_0xc->bDescriptorType = fp8[1];
    fp_0xc->bcdUSB = fp8[2] | (fp8[3] << 8);
    fp_0xc->bDeviceClass = fp8[4];
    fp_0xc->bDeviceSubClass = fp8[5];
    fp_0xc->bDeviceProtocol = fp8[6];
    fp_0xc->bMaxPacketSize0 = fp8[7];
    fp_0xc->idVendor = fp8[8] | (fp8[9] << 8);
    fp_0xc->idProduct = fp8[10] | (fp8[11] << 8);
    fp_0xc->bcdDevice = fp8[12] | (fp8[13] << 8);
    fp_0xc->iManufacturer = fp8[14];
    fp_0xc->iProduct = fp8[15];
    fp_0xc->iSerialNumber = fp8[16];
    fp_0xc->bNumConfigurations = fp8[17];
}


/* 10bc1c - todo */
int CLASS_GetDescriptor(struct USB_Controller_Inner_0x7c* fp_0x70, 
    int descr_type/*fp_0x74*/, 
    int fp_0x78, 
    void* buffer/*fp_0x7c*/, 
    int fp4)
{
#if 1
    fprintf(stderr, "CLASS_GetDescriptor: descr_type=%d: TODO!!!\n",
        descr_type);
#endif

    struct Struct_10bab4 fp_0x6c;

    int res/*fp8*/ = 0;

    /* Prepare the Standard Request */
    CLASS_CreateUrb(&fp_0x6c, 
        fp_0x70->Data_0x88, 
        fp_0x70->device_address, 
        1,
        USB_GET_DESCRIPTOR, 
        descr_type, 
        0, 
        0, 
        fp_0x78, 
        0, 
        buffer, 
        fp4, 
        2000);

    res = USB_ControlTransfer(&fp_0x6c, &fp_0x70->Data_0x40);
    if (res != 0)
    {
        usb_slogf(12, 2, 1, "%s:  Get descriptor type %d failed 0x%x",
            "CLASS_GetDescriptor", descr_type, res);
    }
    //loc_10bd10
    return res;
}


/* 10d05c - todo */
int CLASS_SetDeviceAdress(struct USB_Controller_Inner_0x7c* fp_0x78, 
    char* fp_0x7c)
{
#if 1
    fprintf(stderr, "CLASS_SetDeviceAdress: fp_0x78->new_device_address=%d: TODO!!!\n",
        fp_0x78->new_device_address);
#endif

    struct Struct_10bab4 fp_0x70;
    struct USB_Controller* fp_0xc;
    int res; //res;
    
    fp_0xc = &usb_controllers[fp_0x78->Data_0x88];

    usb_slogf(12, 2, 1, "%s:  Set address %d",
        fp_0x7c, fp_0x78->new_device_address);

    /* Prepare the Standard Request */
    CLASS_CreateUrb(&fp_0x70,
        fp_0x78->Data_0x88,
        fp_0x78->device_address,
        2,
        USB_SET_ADDRESS,
        0,
        0,
        0,
        fp_0x78->new_device_address,
        0,
        0,
        0, 
        2000);

    res = USB_ControlTransfer(&fp_0x70, &fp_0x78->Data_0x40);
    if (res != 0)
    {
        usb_slogf(12, 2, 1, "%s:  Set address failed %x",
            fp_0x7c, res);

        return res;
    }
    //loc_10d18c
    fp_0x78->device_address = fp_0x78->new_device_address;

    delay(20);

    res = USB_EnableEndpoint(fp_0xc, fp_0x78, &fp_0x78->Data_0x40);
    if (res != 0)
    {
        usb_slogf(12, 2, 1, "%s:  CTRL_PrepareControlEndpoint failed",
            fp_0x7c);

        return res;
    }
    //loc_10d1f8
    return 0;
}


/* 10bd20 - todo */
int CLASS_validate_device_descriptor(struct USB_Controller_Inner_0x7c* fp8)
{
#if 0
    fprintf(stderr, "CLASS_validate_device_descriptor: TODO!!!\n");
#endif

    if ((fp8->device_descriptor.bLength != sizeof(usbd_device_descriptor_t)) ||
        (fp8->device_descriptor.bNumConfigurations == 0) || 
        (fp8->device_descriptor.bDescriptorType != USB_DESC_DEVICE) ||
        (fp8->device_descriptor.bMaxPacketSize0 == 0))
    {
        usb_slogf(12, 2, 1, 
            "CLASS_EnumerateDevice: Get full device descriptor data corrupted (%x %x %x %x)",
            fp8->device_descriptor.bLength,
            fp8->device_descriptor.bNumConfigurations,
            fp8->device_descriptor.bDescriptorType,
            fp8->device_descriptor.bMaxPacketSize0);

        return 22;
    }
    //loc_10bdcc
    return 0;
}


/* 10b1a4 - complete */
struct UsbConfiguration* CLASS_GetFreeConfiguration(struct USB_Controller_Inner_0x7c* d)
{
#if 0
    fprintf(stderr, "CLASS_GetFreeConfiguration: TODO!!!\n");
#endif

    uint32_t i;
    struct UsbConfiguration* c = &UsbConfigurations[0];

    for (i = 0; i < 40; c++, i++)
    {
        if (c->Data_0x18 == NULL)
        {
            c->Data_0x18 = d;
            return c;
        }
    }

    return NULL;
}


/* 10b2b8 - todo */
void CLASS_CreateConfigurationDescriptor(uint8_t* fp8, usbd_configuration_descriptor_t* fp_0xc)
{
#if 0
    fprintf(stderr, "CLASS_CreateConfigurationDescriptor: TODO!!!\n");
#endif

    fp_0xc->bLength = fp8[0];
    fp_0xc->bDescriptorType = fp8[1];
    fp_0xc->wTotalLength = fp8[2] | (fp8[3] << 8);
    fp_0xc->bNumInterfaces = fp8[4];
    fp_0xc->bConfigurationValue = fp8[5];
    fp_0xc->iConfiguration = fp8[6];
    fp_0xc->bmAttributes = fp8[7];
    fp_0xc->MaxPower = fp8[8];
}


/* 10bddc - complete */
int CLASS_validate_configuration_descriptor(usbd_configuration_descriptor_t* fp8)
{
#if 0
    fprintf(stderr, "CLASS_validate_configuration_descriptor: TODO!!!\n");
#endif

    if ((fp8->wTotalLength < sizeof(usbd_configuration_descriptor_t)) ||
        (fp8->bNumInterfaces == 0) ||
        (fp8->bDescriptorType != USB_DESC_CONFIGURATION))
    {
        //loc_10be1c
        usb_slogf(12, 2, 1, 
            "CLASS_EnumerateDeviceConfiguration:  Invalid data in configuration descriptor ( 0x%x, 0x%x, 0x%x )",
            fp8->wTotalLength, fp8->bNumInterfaces, fp8->bDescriptorType);

        return 22;
    }

    return 0;
}


/* 0x0010b228 - complete */
struct UsbInterface* CLASS_GetFreeInterface(struct UsbConfiguration* fp_0x10)
{
#if 0
    fprintf(stderr, "CLASS_EnumerateDeviceInterface: TODO!!!\n");
#endif

    uint32_t i;
    struct UsbInterface* fp8 = &UsbInterfaces[0];
    //->loc_10b29c
    for (i = 0; i < 80; fp8++, i++)
    {
        //loc_10b250
        if (fp8->Data_0x24 == 0)
        {
            memset(fp8, 0, sizeof(struct UsbInterface));

            fp8->Data_0x24 = fp_0x10;

            return fp8;
        }
        //loc_10b284
    } //for (i = 0; i < 80; i++)

    return NULL;
}


/* 0x0010b3a0 - complete */
void CLASS_CreateInterfaceDescriptor(uint8_t* fp8, usbd_interface_descriptor_t* fp_0xc)
{
#if 0
    fprintf(stderr, "CLASS_CreateInterfaceDescriptor: TODO!!!\n");
#endif

    fp_0xc->bLength = fp8[0];
    fp_0xc->bDescriptorType = fp8[1];
    fp_0xc->bInterfaceNumber = fp8[2];
    fp_0xc->bAlternateSetting = fp8[3];
    fp_0xc->bNumEndpoints = fp8[4];
    fp_0xc->bInterfaceClass = fp8[5];
    fp_0xc->bInterfaceSubClass = fp8[6];
    fp_0xc->bInterfaceProtocol = fp8[7];
    fp_0xc->iInterface = fp8[8];
}


/* 0x0010b470 - complete */
int CLASS_EnumerateDeviceInterface(struct UsbConfiguration* fp_0x10, 
    uint8_t* fp_0x14, struct UsbInterface** fp_0x18)
{
#if 0
    fprintf(stderr, "CLASS_EnumerateDeviceInterface: TODO!!!\n");
#endif

    struct UsbInterface* fp_0xc;
    struct UsbInterface* fp8;

    fp_0xc = CLASS_GetFreeInterface(fp_0x10);
    if (fp_0xc == NULL)
    {
        *fp_0x18 = NULL;

        return 12;
    }
    //loc_10b4b8
    CLASS_CreateInterfaceDescriptor(fp_0x14, &fp_0xc->Data_8);

    if (fp_0x10->interfaces == NULL)
    {
        fp_0x10->interfaces = fp_0xc;
        //->loc_10b524
    }
    else
    {
        //loc_10b4ec
        fp8 = fp_0x10->interfaces;
        //->loc_10b508
        while (fp8->next != NULL)
        {
            //loc_10b4fc
            fp8 = fp8->next;
        }
        //0x0010b518
        fp8->next = fp_0xc;
    }
    //loc_10b524
    *fp_0x18 = fp_0xc;

    return 0;
}


/* 0x0010b540 - todo */
struct UsbEndpoint* CLASS_GetFreeEndpoint(struct UsbInterface* fp_0x10)
{
#if 0
    fprintf(stderr, "CLASS_GetFreeEndpoint: TODO!!!\n");
#endif

    uint32_t i;
    struct UsbEndpoint* fp8 = &UsbEndpoints[0];
    //->loc_10b644
    for (i = 0; i < 320; fp8++, i++)
    {
        //loc_10b568
        if (fp8->interface == NULL)
        {
            fp8->interface = fp_0x10;
            fp8->Data_0x14 = 0;
            fp8->Data_0x18 = &fp8->Data_0x14;
            fp8->Data_0x1c = 0;
            fp8->Data_0x20 = &fp8->Data_0x1c;

            pthread_mutex_init(&fp8->Data_0x30, 0);
            pthread_cond_init(&fp8->Data_0x38, 0);

            usb_slogf(12, 2, 1, "%s(%d): epno %d, emutexp %p",
                "CLASS_GetFreeEndpoint", 0x1d5, i, &fp8->Data_0x30);

            return fp8;
        }
        //loc_10b62c
    }

    return NULL;
}


/* 0x0010b664 - todo */
void CLASS_CreateEndpointDescriptor(uint8_t* fp8, usbd_endpoint_descriptor_t* fp_0xc)
{
#if 0
    fprintf(stderr, "CLASS_CreateEndpointDescriptor: TODO!!!\n");
#endif

    fp_0xc->bLength = fp8[0];
    fp_0xc->bDescriptorType = fp8[1];
    fp_0xc->bEndpointAddress = fp8[2];
    fp_0xc->bmAttributes = fp8[3];
    fp_0xc->wMaxPacketSize = fp8[4] | (fp8[5] << 8);
    fp_0xc->bInterval = fp8[6];
}


/* 0x0010b724 - todo */
int CLASS_EnumerateDeviceEndpoint(struct UsbInterface* fp_0x10, 
        uint8_t* fp_0x14, struct UsbEndpoint** fp_0x18)
{
#if 0
    fprintf(stderr, "CLASS_EnumerateDeviceEndpoint: TODO!!!\n");
#endif

    struct UsbEndpoint* fp_0xc;
    struct UsbEndpoint* fp8;

    fp_0xc = CLASS_GetFreeEndpoint(fp_0x10);
    if (fp_0xc == NULL)
    {
        *fp_0x18 = NULL;

        return 12;
    }
    //loc_10b76c
    CLASS_CreateEndpointDescriptor(fp_0x14, &fp_0xc->endpoint_descriptor);

    if (fp_0x10->endpoints == NULL)
    {
        fp_0x10->endpoints = fp_0xc;
        //->loc_10b7d4
    }
    else
    {
        //loc_10b79c
        fp8 = fp_0x10->endpoints;
        //->loc_10b7b8
        while (fp8->next != NULL)
        {
            //loc_10b7ac
            fp8 = fp8->next;
        }
        //0x0010b7c8
        fp8->next = fp_0xc;
    }
    //loc_10b7d4
    *fp_0x18 = fp_0xc;

    return 0;
}


/* 10b7f0 - todo */
int CLASS_ResolveConfiguration(struct UsbConfiguration* fp_0x28, uint8_t* fp_0x2c)
{
#if 0
    fprintf(stderr, "CLASS_SelectDefaultConfiguration: TODO!!!\n");
#endif

    struct UsbEndpoint* fp_0x24;
    struct UsbInterface* fp_0x20;
    usbd_configuration_descriptor_t* fp_0x1c;
    int fp_0x18;
    int fp_0x14;
    int fp_0x10 = 0;
    int fp_0xc;
    int fp8;

    fp_0x1c = &fp_0x28->configuration_descriptor;
    fp_0x18 = fp_0x1c->wTotalLength;
    fp_0x2c += fp_0x1c->bLength;
    fp_0x18 -= fp_0x1c->bLength;
    fp_0x20 = NULL;
    fp_0x24 = NULL;
    //->loc_10b954
    while (fp_0x18 > 0)
    {
        //loc_10b860
        switch (fp_0x2c[1]) //bDescriptorType
        {
            case USB_DESC_INTERFACE:
                //loc_10b880
                fp_0x14 = CLASS_EnumerateDeviceInterface(fp_0x28, fp_0x2c, &fp_0x20);
                if (fp_0x14 != 0)
                {
                    //0x0010b8a8
                    return fp_0x14;
                }
                //->loc_10b910
                break;

            case USB_DESC_ENDPOINT:
                //loc_10b8b0
                if (fp_0x20 == 0)
                {
                    //0x0010b8bc
                    usb_slogf(12, 2, 1, 
                        "CLASS_ResolveConfiguration: No interface found for this endpoint");

                    return -1;
                }
                //loc_10b8dc
                fp_0x14 = CLASS_EnumerateDeviceEndpoint(fp_0x20, fp_0x2c, &fp_0x24);
                if (fp_0x14 != 0)
                {
                    return fp_0x14;
                }
                //loc_10b914
                break;

            default:
                //loc_10b914
                break;
        }
        //loc_10b914
        if (fp_0x2c[0] == 0)
        {
            return -1;
        }
        //loc_10b92c
        fp_0x18 -= fp_0x2c[0]; //bLength
        fp_0x2c += fp_0x2c[0]; //bLength
        //loc_10b954
    } //while (fp_0x18 > 0)
    //0x0010b960
    fp_0x20 = fp_0x28->interfaces;
    //->loc_10ba50
    while (fp_0x20 != 0)
    {
        //loc_10b970
        fp_0xc = 0;
        fp8 = fp_0x20->Data_8.bNumEndpoints;

        if (fp_0x20->Data_8.bAlternateSetting == 0)
        {
            fp_0x10++;
        }
        //loc_10b9a0
        fp_0x24 = fp_0x20->endpoints;
        //->loc_10b9f8
        while (fp_0x24 != NULL)
        {
            //loc_10b9b0
            if (fp_0x24->endpoint_descriptor.wMaxPacketSize == 0)
            {
                usb_slogf(12, 2, 1, 
                    "CLASS_ResolveConfiguration: Endpoint has wMaxPacketSize of zero");
                
                return -1;
            }
            //loc_10b9e0
            fp_0xc++;
            fp_0x24 = fp_0x24->next;
        } //while (fp_0x24 != NULL)
        //0x0010ba04
        if (fp_0xc != fp8)
        {
            usb_slogf(12, 2, 1, 
                "CLASS_ResolveConfiguration: num endpoints are not consistent (expect %d parsed %d)",
                fp8, fp_0xc);

            return -1;
        }
        //loc_10ba44
        fp_0x20 = fp_0x20->next;
    } //while (fp_0x20 != 0)
    //0x0010ba5c
    if (fp_0x10 != fp_0x28->configuration_descriptor.bNumInterfaces)
    {
        //0x0010ba70
        usb_slogf(12, 2, 1, 
            "CLASS_ResolveConfiguration: num interfaces are not consistent (%d %d)",
            fp_0x28->configuration_descriptor.bNumInterfaces, fp_0x10);
        
        return -1;
    }
    //loc_10baa4
    return 0;
}


/* 10c1e0 - todo */
int CLASS_EnumerateDeviceConfiguration(int fp_0x28, struct USB_Controller_Inner_0x7c* fp_0x2c)
{
#if 0
    fprintf(stderr, "CLASS_EnumerateDeviceConfiguration: TODO!!!\n");
#endif

    void* fp_0x24;
    struct UsbConfiguration* fp_0x20;
    struct UsbConfiguration* fp_0x1c;
    usbd_configuration_descriptor_t* fp_0x18;
    void* fp_0x14;
    int fp_0x10;
    uint32_t fp_0xc;
    int fp8 = 0;

    fp_0x10 = fp_0x2c->device_descriptor.bNumConfigurations;
    if (fp_0x10 == 0)
    {
        return 22;
    }
    //loc_10c21c
    fp_0x24 = usbd_alloc(sizeof(usbd_configuration_descriptor_t));
    if (fp_0x24 == NULL)
    {
        usb_slogf(12, 2, 1, 
            "CLASS_EnumerateDeviceConfiguration:  config descriptor ENOMEM");

        return 0x9000;
    }
    //loc_10c258
    //->loc_10c4b0
    for (fp_0xc = 0; (fp_0xc < fp_0x10) && (fp8 == 0); fp_0xc++)
    {
        //loc_10c264
        fp8 = CLASS_GetDescriptor(fp_0x2c, 
                USB_DESC_CONFIGURATION, 
                fp_0xc, 
                fp_0x24, 
                sizeof(usbd_configuration_descriptor_t));
        if (fp8 != 0)
        {
            usb_slogf(12, 2, 1, 
                "CLASS_EnumerateDeviceConfiguration:  Get config descriptor failed %x",
                fp8);

            usbd_free(fp_0x24);

            return 0x8300;
        }
        //loc_10c2c4
        fp_0x20 = CLASS_GetFreeConfiguration(fp_0x2c);
        if (fp_0x20 == NULL)
        {
            usbd_free(fp_0x24);

            return 0x9000;
        }
        //loc_10c2f0
        if (fp_0x2c->Data_0x84 == NULL)
        {
            fp_0x2c->Data_0x84 = fp_0x20;
            //->loc_10c348
        }
        else
        {
            //loc_10c310
            fp_0x1c = fp_0x2c->Data_0x84;
            //->loc_10c32c
            while (fp_0x1c->next != NULL)
            {
                //loc_10c320
                fp_0x1c = fp_0x1c->next;
            }
            //0x0010c33c
            fp_0x1c->next = fp_0x20;
        }
        //loc_10c348
        fp_0x18 = &fp_0x20->configuration_descriptor;

        CLASS_CreateConfigurationDescriptor(fp_0x24, fp_0x18);

        if (CLASS_validate_configuration_descriptor(fp_0x18) != 0)
        {
            usbd_free(fp_0x24);

            return 0x8300;
        }
        //loc_10c388
        fp_0x14 = usbd_alloc(fp_0x18->wTotalLength);
        if (fp_0x14 == NULL)
        {
            usbd_free(fp_0x24);

            return 0x9000;
        }
        //loc_10c3bc
        usb_slogf(12, 2, 1, 
            "CLASS_EnumerateDeviceConfiguration:  Get full config descriptor");

        fp8 = CLASS_GetDescriptor(fp_0x2c, USB_DESC_CONFIGURATION, 
                fp_0xc, fp_0x14, fp_0x18->wTotalLength);
        if (fp8 != 0)
        {
            usb_slogf(12, 2, 1, 
                "CLASS_EnumerateDeviceConfiguration:  Get full config descriptor failed %x",
                fp8);

            usbd_free(fp_0x14);
            usbd_free(fp_0x24);

            return 0x8300;
        }
        //loc_10c440
        usb_store_data_key(fp_0x2c->Data_0x8c, 
            0, 1, fp_0xc | 0x200, 0, 0, fp_0x14, fp_0x18->wTotalLength);

        fp8 = CLASS_ResolveConfiguration(fp_0x20, fp_0x14);

        usbd_free(fp_0x14);

    } //for (fp_0xc = 0; (fp_0xc < fp_0x10) && (fp8 == 0); fp_0xc++)
    //loc_10c4cc
    usbd_free(fp_0x24);
    
    if (fp8 != 0)
    {
        return 0x8400;
    }

    return 0;
}


/* 10cdec - todo */
int CLASS_SelectDefaultConfiguration(struct USB_Controller* a, struct USB_Controller_Inner_0x7c* b)
{
#if 1
    fprintf(stderr, "CLASS_SelectDefaultConfiguration: TODO!!!\n");
#endif


    return 0;
}


struct Struct_10ae08
{
    uint8_t bDeviceClass; //0
    uint8_t bDeviceSubClass; //1
    uint8_t bDeviceProtocol; //2
    uint16_t idProduct; //4
    uint16_t idVendor; //6
    //8???
};


/* 10ae08 - complete */
struct ArrayClass* sub_10ae08(struct Struct_10ae08* fp_0x10)
{
#if 0
    fprintf(stderr, "sub_10ae08: TODO!!!\n");
#endif

    uint32_t i = 0;
    struct ArrayClass* fp8 = &ArrayClass[0];

    for (; i < 8; i++, fp8++)
    {
#if 1
        fprintf(stderr, "sub_10ae08[%d]: fp8->bData_0x2c=%d, fp8->Data_0=%d(%d), fp8->Data_0x14=0x%x\n",
            i,
            fp8->bData_0x2c, 
            fp8->Data_0, fp_0x10->bDeviceClass, 
            fp8->Data_0x14);
#endif
        if ((fp8->bData_0x2c != 0) &&
            (fp8->Data_0 == fp_0x10->bDeviceClass) &&
            (fp8->Data_0x14 == 0x10))
        {
            return fp8;
        }
    } //for (i = 0; i < 8; i++, fp8++)

    i = 0;
    fp8 = &ArrayClass[0];

    for (; i < 8; i++, fp8++)
    {
#if 1
        fprintf(stderr, "sub_10ae08[%d]: fp8->bData_0x2c=%d, fp8->Data_0=%d\n",
            i,
            fp8->bData_0x2c, fp8->Data_0);
#endif
        if ((fp8->bData_0x2c != 0) && 
            (fp8->Data_0 == -1))
        {
            return fp8;
        }
    }

    return NULL;
}


/* 10af0c - todo */
void sub_10af0c(int a, int b, int c, int d)
{
#if 1
    fprintf(stderr, "sub_10af0c: TODO!!!\n");
#endif

}


/* 10ceb4 - todo */
int CLASS_StartDriver(struct USB_Controller_Inner_0x7c* fp_0x28)
{
#if 1
    fprintf(stderr, "CLASS_StartDriver: TODO!!!\n");
#endif

    struct Struct_10ae08 fp_0x24;

    struct ArrayClass* fp_0x1c;
    usbd_device_descriptor_t* fp_0x18;
    struct
    {
        int fill_0[2]; //0
        uint8_t fill_8; //8
        uint8_t bData_9; //9
        int fill_0xc[2]; //12 = 0xc
        int Data_0x14; //0x14
        //???
    }* fp_0x14;

    struct fp_0x10
    {
        int fill_0[2]; //0
        int Data_8; //8
        int fill_0xc[4]; //12 = 0xc
        struct fp_0x10* Data_0x1c; //0x1c = 28
        //???
    }* fp_0x10;

    struct
    {
        uint16_t fill_0; //0
        uint8_t fill_2; //2
        uint8_t bData_3; //3
        //???
    }* fp_0xc;
    
    int fp8;
    
    fp_0x18 = &fp_0x28->device_descriptor;

    fp_0x24.idProduct = fp_0x18->idProduct;
    fp_0x24.idVendor = fp_0x18->idVendor;
    fp_0x24.bDeviceClass = fp_0x18->bDeviceClass;
    fp_0x24.bDeviceSubClass = fp_0x18->bDeviceSubClass;
    fp_0x24.bDeviceProtocol = fp_0x18->bDeviceProtocol;

    fp_0x1c = sub_10ae08(&fp_0x24);
    if (fp_0x1c != NULL)
    {
        //0x0010cf2c
        fp_0x28->Data_0x18 = fp_0x1c;

        if (fp_0x18->bNumConfigurations == 1)
        {
            //0x0010cf48
            fp_0x14 = fp_0x28->Data_0x84;
            fp8 = fp_0x14->bData_9;
            //->loc_10cf6c
        }
        else
        {
            //loc_10cf64
            fp8 = -1;
        }
        //loc_10cf6c
        (fp_0x1c->on_insertion)(fp_0x28->Data_0x88, 
            fp_0x28->device_address, fp8, -1);
        //->loc_10d04c
    }
    else
    {
        //loc_10cf9c
        fp_0x24.bDeviceClass = fp_0x18->bDeviceClass;
        fp_0x24.bDeviceSubClass = fp_0x18->bDeviceSubClass;
        fp_0x24.bDeviceProtocol = fp_0x18->bDeviceProtocol;

        if (fp_0x18->bNumConfigurations == 1)
        {
            //0x0010cfd0
            fp_0x14 = fp_0x28->Data_0x84;
            fp_0x10 = fp_0x14->Data_0x14;
            //->loc_10d040
            while (fp_0x10 != NULL)
            {
                //->loc_10cfec
                fp_0xc = &fp_0x10->Data_8;

                if (fp_0xc->bData_3 == 0)
                {
                    //0x0010d008
                    sub_10af0c(fp_0x28->Data_0x88,
                        fp_0x28->device_address, fp_0x14->bData_9, fp_0x10);
                }
                //loc_10d034
                fp_0x10 = fp_0x10->Data_0x1c;
                //loc_10d040
            } //while (fp_0x10 != 0)
            //loc_10d04c
        }
        //loc_10d04c
    }
    //loc_10d04c
    return 0;
}


/* 10d2f0 - todo */
int CLASS_EnumerateDevice(int fp_0x20, int fp_0x24, int fp_0x28, int fp_0x2c)
{
#if 1
    fprintf(stderr, "CLASS_EnumerateDevice: TODO!!!\n");
#endif

    struct USB_Controller_Inner_0x7c* fp_0x18;
    void* fp_0x14;
    int fp_0x10; 
    void* fp_0xc;
    struct USB_Controller* fp8;

    fp8 = &usb_controllers[fp_0x20];

    usb_slogf(12, 2, 1, 
        "CLASS_EnumerateDevice: bus %d, parent %d, port %d, speed %d",
        fp_0x20, fp_0x24, fp_0x28, fp_0x2c);

    fp_0x18 = sub_10d208(fp8, fp_0x24, fp_0x28, fp_0x2c);
    if (fp_0x18 == NULL)
    {
        return 0x8203;
        //->loc_10d770
    }
    //loc_10d390
    fp_0x10 = USB_EnableEndpoint(fp8, fp_0x18, &fp_0x18->Data_0x40);
    if (fp_0x10 != 0)
    {
        usb_slogf(12, 2, 1, "CLASS_EnumerateDevice: USB_EnableEndpoint failed");

        CLASS_CancelDeviceEnumeration(fp_0x18);

        return 0x8202;
        //->loc_10d770
    }
    //loc_10d3e4
    fp_0xc = usbd_alloc(sizeof(usbd_device_descriptor_t));
    if (fp_0xc == NULL)
    {
        usb_slogf(12, 2, 1, "CLASS_EnumerateDevice:  device descriptor ENOMEM");

        CLASS_CancelDeviceEnumeration(fp_0x18);

        return 0x9000;
        //->loc_10d770
    }
    //loc_10d428
    usb_slogf(12, 2, 1, "CLASS_EnumerateDevice:  Get device descriptor");

    fp_0x10 = CLASS_GetDescriptor(fp_0x18, USB_DESC_DEVICE, 0, fp_0xc, 8);
    if (fp_0x10 != 0)
    {
        usb_slogf(12, 2, 1, 
            "CLASS_EnumerateDevice:  Get device descriptor failed %x", fp_0x10);

        usbd_free(fp_0xc);
        CLASS_CancelDeviceEnumeration(fp_0x18);

        return 0x8403;
    }
    //loc_10d4a8: Extract Device Descriptor data (max packet size)
    CLASS_CreateDeviceDescriptor(fp_0xc, &fp_0x18->device_descriptor);
    //0x0010d4c0
    fp_0x18->Data_0x40.wData_4 = fp_0x18->device_descriptor.bMaxPacketSize0;

    if (fp_0x18->Data_0x40.wData_4 == 0)
    {
        //0x0010d4e4
        usb_slogf(12, 2, 1, "CLASS_EnumerateDevice: Control Endpoint MPS is zero");

        usbd_free(fp_0xc);
        CLASS_CancelDeviceEnumeration(fp_0x18);

        return 0x8403;
    }
    //loc_10d514
    fp_0x14 = fp_0xc;

    if (CLASS_SetDeviceAdress(fp_0x18, "CLASS_EnumerateDevice") != 0)
    {
        //0x0010d538
        usbd_free(fp_0xc);
        CLASS_CancelDeviceEnumeration(fp_0x18);

        return 0x8300;
    }
    //loc_10d550
    usb_slogf(12, 2, 1, "CLASS_EnumerateDevice:  Get full device descriptor");

    if (CLASS_GetDescriptor(fp_0x18, USB_DESC_DEVICE, 0, fp_0xc, 
            sizeof(usbd_device_descriptor_t)) != 0)
    {
        usb_slogf(12, 2, 1, "CLASS_EnumerateDevice:  Get full device descriptor failed %x",
            fp_0x10);

        usbd_free(fp_0xc);
        CLASS_CancelDeviceEnumeration(fp_0x18);

        return 0x8300;
    }
    //loc_10d5c8
    CLASS_CreateDeviceDescriptor(fp_0xc, &fp_0x18->device_descriptor);

    if (CLASS_validate_device_descriptor(fp_0x18) != 0)
    {
        usbd_free(fp_0xc);
        CLASS_CancelDeviceEnumeration(fp_0x18);

        return 0x8300;
    }
    //loc_10d60c
    usb_store_data_key(fp_0x18->Data_0x8c, 
        0, 1, 0x100, 0, 0, fp_0xc, sizeof(usbd_device_descriptor_t));

    usbd_free(fp_0xc);

    fp_0x10 = CLASS_EnumerateDeviceConfiguration(fp_0x20, fp_0x18);
    if (fp_0x10 != 0)
    {
        CLASS_CancelDeviceEnumeration(fp_0x18);

        return fp_0x10;
    }
    //loc_10d680
    if ((fp_0x18->device_descriptor.bDeviceClass == 9/*Hub???*/) ||
        (((UsbdiGlobals.Data_0x10 & 0x40000000) == 0) && 
            ((fp_0x18->device_descriptor.bNumConfigurations < 2) ||
            ((UsbdiGlobals.Data_0x10 & 1) == 0))))
    {
        //loc_10d6d0
        fp_0x10 = CLASS_SelectDefaultConfiguration(fp8, fp_0x18);
        if (fp_0x10 != 0)
        {
            CLASS_CancelDeviceEnumeration(fp_0x18);

            return fp_0x10;
        }
    }
    //loc_10d700
    fp_0x18->bData_0xd = 1;

    fp_0x10 = CLASS_StartDriver(fp_0x18);
    if (fp_0x10 != 0)
    {
        return 0x8402;
    }
    //loc_10d730
    usb_slogf(12, 2, 1, "CLASS_EnumerateDevice: bus %d dno %d, vid %x",
        fp8->Data_8, 
        fp_0x18->device_address, 
        fp_0x18->device_descriptor.idVendor);

    return 0;
}


/* 1109a0 - todo */
int sub_1109a0(int fp_0x18, int fp_0x1c)
{
#if 0
    fprintf(stderr, "sub_1109a0: TODO!!!\n");
#endif

    int fp_0x10 = 0;
    int fp_0xc;
    struct USB_Controller* fp8;

    fp8 = &usb_controllers[fp_0x18];

    if ((fp8->controller_methods->check_device_connected)(fp8, fp_0x1c) == 0)
    {
        //0x001109fc
        delay(100);

        fp_0xc = UsbdiGlobals.Data_0x180;
        //->loc_110ae0
        while (fp_0xc--)
        {
            //->loc_110a18
            fp_0x10 = (fp8->controller_methods->set_port_feature)(fp8, fp_0x1c, 2);
            if (fp_0x10 != 0x13)
            {
                delay(100);

                fp_0x10 = CLASS_EnumerateDevice(fp_0x18, 0, fp_0x1c, 
                    (fp8->controller_methods->get_root_device_speed)(fp8, fp_0x1c));

                if (fp_0x10 != 0)
                {
                    //0x00110a90
                    if ((fp8->controller_methods->check_device_connected)(fp8, fp_0x1c) != 0)
                    {
                        //0x00110ab4
                        fp_0x10 = 0x13;
                        //->loc_110b10
                        break;
                    }
                    //loc_110ac0
                }
                //loc_110ac0
                if (fp_0x10 == 0)
                {
                    //->loc_110b10
                    break;
                }

                if (fp_0x10 == 12)
                {
                    //->loc_110b10
                    break;
                }
                //0x00110ad8
                delay(1000);
                //loc_110ae0
            }
            //loc_110b0c
        } //while (fp_0xc--)
        //loc_110b10
    }
    //loc_110b10
    if (fp_0x10 != 0)
    {
        (fp8->controller_methods->clear_port_feature)(fp8, fp_0x1c, 1);
    }
    //loc_110b38
    return fp_0x10;
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
    } //for (fp_0x18 = 0; fp_0x18 < 16; fp_0x18++)
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

    delay(20);

    fp_0x2c.it_value.tv_sec = 5;
    fp_0x2c.it_value.tv_nsec = 0; //1000000000; //100000000;
    fp_0x2c.it_interval.tv_sec = 5;
    fp_0x2c.it_interval.tv_nsec = 0; //1000000000; //100000000;

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
#if 1
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
#endif
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
            p->on_insertion = a->on_insertion;
            p->Data_0x28 = a->Data_0x20;
            p->bData_0x2c = 1;

            return p;
        }
    }

    return 0;
}


