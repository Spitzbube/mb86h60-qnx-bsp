

#include "externs.h"


extern int usbdi_memchunk_init();
extern void usbdi_memchunk_free(int, void*);

extern void usbdi_client_destroy();

const uint32_t Data_11ddf4[8] = //11ddf4
{
    20, 44, 112, 246, 502, 1010, 2032, 8192
};

extern const resmgr_io_funcs_t ResmgrIOFuncs; //0x11f404
extern const iofunc_funcs_t ResmgrOCBFuncs; //0x0011f470
extern const resmgr_connect_funcs_t ResmgrCFuncs; //0x0011f488


/* 0x001155f4 - complete */
void usbdi_ocb_free(IOFUNC_OCB_T *ocb)
{
#if 0
    fprintf(stderr, "usbdi_ocb_free\n");
#endif

    usbdi_memchunk_free(UsbdiGlobals.Data_0xc, ocb);
}


/* 0x00115610 - todo */
IOFUNC_OCB_T* usbdi_ocb_calloc(resmgr_context_t* ctp,
                     iofunc_attr_t* attr)
{
#if 1
    fprintf(stderr, "usbdi_ocb_calloc: sizeof(iofunc_ocb_t)=%d / %d TODO!!!\n",
        sizeof(IOFUNC_OCB_T), 28);
#endif

    IOFUNC_OCB_T* ocb = usbdi_memchunk_calloc(UsbdiGlobals.Data_0xc, 1, 
                    sizeof(*ocb)/*28*/);

    if (ocb == 0)
    {
        errno = 23;
    }

    return ocb;
}


/* 108dd0 - todo */
int udi_enumerate(int a)
{
    fprintf(stderr, "udi_enumerate: TODO!!!\n");

    return 0;
}



/* 106bac - complete */
int udi_hcd_info(int a, usbd_hcd_info_t* b)
{
#if 0
    fprintf(stderr, "udi_hcd_info: TODO!!!\n");
#endif

    struct USB_Controller* cntrl;

    if (ausb_controllers[a] == NULL)
    {
        return 2;
    }

    b->vusb = 0x110;
    b->vusbd = 0x101;
    b->vhcd = 0x101;

    cntrl = &usb_controllers[a];

    b->capabilities = cntrl->capabilities | 0x1000;
    b->cindex = cntrl->Data_8;
    b->max_td_io = cntrl->Data_0x60;
    strcpy(&b->controller[0], cntrl->Data_0);

    return 0;
}


/* 105ed8 - todo */
int udi_topology(int r6, usbd_bus_topology_t* b)
{
#if 0
    fprintf(stderr, "udi_topology: TODO!!!\n");
#endif

    uint32_t i;
    usbd_port_attachment_t* r5 = &b->ports[0];

    struct USB_Controller* cntrl = CTRL_HCLookup(r6);
    if (cntrl == NULL)
    {
        return 0x13;
    }

    if (pthread_mutex_lock(&cntrl->Data_0x24) != 0)
    {
        usb_slogf(12, 2, 0, "udi_topology:  error acquiring mutex, %d", errno);
    }

    for (i = 1; i < 21; i++)
    {
        //loc_105f38
        struct USB_Controller_Inner_0x7c* r0 = USB_CheckDevice(r6, i);
        if ((r0 != NULL) && (r0->bData_0xd & 1))
        {
            r5[1].upstream_hc = r0->Data_0x88;
            r5[1].upstream_devno = 
                (r0->Data_0x1c != NULL)? ((uint8_t*)r0->Data_0x1c)[0]: 0;
            r5[1].upstream_port = r0->Data_0x20;
            r5[1].upstream_port_speed = r0->bData_0xc;
#if 1
        fprintf(stderr, "udi_topology[%d]: hc=%d, devno=%d, port=%d, port_speed=%d\n",
            i, r5[1].upstream_hc, r5[1].upstream_devno, 
            r5[1].upstream_port, r5[1].upstream_port_speed);
#endif
        }
        //loc_105f84
        r5++;
    } //for (i = 1; i < 21; i++)
    //0x00105f94
    if (pthread_mutex_unlock(&cntrl->Data_0x24) != 0)
    {
        usb_slogf(12, 2, 0, "udi_topology:  error releasing mutex, %d", errno);
    }

    return 0;
}


/* 1113ec - todo */
int sub_1113ec(int a, int b, int c, int d)
{
#if 1
    fprintf(stderr, "sub_1113ec: TODO!!!\n");
#endif

    return 0;
}


/* 0x00106300 - todo */
int udi_attach(usbd_device_instance_t* r4, int r8)
{
#if 1
    fprintf(stderr, "udi_attach: r8=0x%x: TODO!!!\n", r8);
#endif

    struct UsbInterface* r0;
    struct UsbConfiguration* r7_;
    struct USB_Controller_Inner_0x7c* r6;
    struct USB_Controller* r7 = CTRL_HCLookup(r4->path);
    if (r7 == NULL)
    {
        //->loc_106858
        return 0x13;
    }

    usb_slogf(12, 2, 5, "%s(%d): devno %d",
        "udi_attach", 0x6c1, r4->devno);

    if (pthread_mutex_lock(&r7->Data_0x24/*r5*/) != 0)
    {
        //0x00106364
        usb_slogf(12, 2, 0, "%s(%d):  error acquiring mutex, %d",
            "udi_attach", 0x6c4, errno);
    }
    //loc_106398
    r6 = USB_CheckDevice(r4->path, r4->devno);
    if ((r6 == NULL) || ((r6->bData_0xd & 1) == 0))
    {
        //loc_1063b8
        if (pthread_mutex_unlock(&r7->Data_0x24/*r5*/) != 0)
        {
            //0x001063c8
            usb_slogf(12, 2, 0, "%s(%d):  error releasing mutex, %d",
                "udi_attach", 0x6c4, errno);

            //->loc_10685c
        }
        //loc_106858
        return 0x13;
    }
    //loc_106404
    if (r8 & 0x02)
    {
        //0x0010640c
        fprintf(stderr, "udi_attach: 0x0010640c: TODO!!!\n");

        //TODO!!!
    }
    //loc_106560
#if 1
    fprintf(stderr, "udi_attach: r4->config=%d, r6->Data_0x14=%d, x=%d\n", 
        r4->config, r6->Data_0x14,
        r6->Data_0x84->configuration_descriptor.bConfigurationValue);
#endif
    if ((r4->config == -1) && (r6->Data_0x14 != 0))
    {
        r4->config = r6->Data_0x14;
        //->loc_106590
    }
    //loc_10657c
    else if (r4->config != r6->Data_0x14)
    {
        r4->config = r6->Data_0x84->configuration_descriptor.bConfigurationValue;
    }
    //loc_106590
    r7_ = USB_GetConfiguration(r7, r4->devno, r4->config);
    if (r7_ == NULL)
    {
        //0x001065a8
        if (pthread_mutex_unlock(&r7->Data_0x24/*r5*/) != 0)
        {
            //0x001065b8
            usb_slogf(12, 2, 0, "%s(%d):  error releasing mutex, %d",
                "udi_attach", 0x704, errno);

            //->loc_10685c
        }
        //loc_106858
        return 0x13;
    }
    //loc_1065f4
    if ((r4->iface != -1) && (r6->Data_0x14 != 0))
    {
        r0 = sub_1113ec(r4->path, r4->devno, r4->config, r4->iface);
        if (r0 == NULL)
        {
            //0x00106624
            if (pthread_mutex_unlock(&r7->Data_0x24/*r5*/) != 0)
            {
                //0x00106634
                usb_slogf(12, 2, 0, "%s(%d):  error releasing mutex, %d",
                    "udi_attach", 0x70c, errno);
            }
            //loc_106664
            usb_slogf(12, 2, 4, 
                "%s(%d):  unable to find matching interface, path %d, devno %d, cfg %d, iface %d, ",
                "udi_attach", 0x70f, 
                r4->path, r4->devno, r4->config, r4->iface);
            return 0x13;
        }
        //loc_1066b8
    }
    else
    {
        //loc_1066b4
        r0 = r7_->interfaces;
    }
    //loc_1066b8
    if (((r4->ident.dclass != -1) &&  (r4->ident.dclass != r0->Data_8.bInterfaceClass)) ||
        ((r4->ident.subclass != -1) && (r4->ident.subclass != r0->Data_8.bInterfaceSubClass)) ||
        ((r4->ident.protocol != -1) && (r4->ident.protocol != r0->Data_8.bInterfaceProtocol)))
    {
        //loc_106700
        if (pthread_mutex_unlock(&r7->Data_0x24/*r5*/) != 0)
        {
            //0x00106710
            usb_slogf(12, 2, 0, "%s(%d):  error releasing mutex, %d",
                "udi_attach", 0x71f, errno);
        }
        //loc_106744
        usb_slogf(12, 2, 4, 
            "%s(%d):  unable to find matching class, path %d, devno %d, cfg %d, iface %d (%x %x %x) ",
            "udi_attach", 0x722, 
            r4->path, r4->devno, r4->config, r4->iface,
            r4->ident.dclass, r4->ident.subclass, r4->ident.protocol);
        return 0x13;
    }
    //loc_1067ac
    r4->generation = r6->wData_0xe;
    r4->ident.vendor = r6->device_descriptor.idVendor; //wData_0x34;
    r4->ident.device = r6->device_descriptor.idProduct; //wData_0x36;

#if 1
    fprintf(stderr, "udi_attach: r4->generation=%d, r4->ident.vendor=0x%x, r4->ident.device=0x%x\n", 
        r4->generation, r4->ident.vendor, r4->ident.device);
#endif

    if (r0->Data_8.bAlternateSetting == 0)
    {
        //0x001067d0
        r4->ident.dclass = r0->Data_8.bInterfaceClass;
        r4->ident.subclass = r0->Data_8.bInterfaceSubClass;
        r4->ident.protocol = r0->Data_8.bInterfaceProtocol;
        r4->config = r7_->configuration_descriptor.bConfigurationValue;
        r4->iface = r0->Data_8.bInterfaceNumber;
        r4->alternate = r0->Data_0x14;
#if 1
        fprintf(stderr, "udi_attach: r4->ident.dclass=0x%x, r4->ident.subclass=0x%x, r4->ident.protocol=0x%x\n", 
            r4->ident.dclass, r4->ident.subclass, r4->ident.protocol);
        fprintf(stderr, "udi_attach: r4->config=%d, r4->iface=%d, r4->alternate=%d\n", 
            r4->config, r4->iface, r4->alternate);
#endif
    }
    //loc_106800
    if (pthread_mutex_unlock(&r7->Data_0x24/*r5*/) != 0)
    {
        usb_slogf(12, 2, 0, "%s(%d):  error releasing mutex, %d",
            "udi_attach", 0x737, errno);

        //->loc_10685c
    }

    return 0;
}


/* 114194 - todo */
int conflict(struct Struct_114194* r4, struct USB_Client* r7)
{
#if 0
    fprintf(stderr, "conflict: TODO!!!\n");
#endif

    if (r7->Data_0x10 & 0x02)
    {
        //0x001141ac
        pthread_mutex_lock(&UsbdiGlobals.Data_0);

        struct UsbdiGlobals_Inner_0x24* r5 = UsbdiGlobals.Data_0x24;
        while (r5 != NULL)
        {
            //loc_1141c8
            pthread_mutex_lock(&r5->Data_8/*r6*/);

            struct
            {
                void* Data_0; //0
                int fill_4; //4
                int Data_8; //8
                int fill_0xc[6]; //0xc
                int Data_0x24; //0x24
                //???
            }* r3 = r5->Data_0x1c;
            //0x001141e0
            while (r3 != NULL)
            {
                //loc_1141e8
#if 1
                fprintf(stderr, "conflict: loc_1141e8: TODO!!!\n");
#endif
                if (((r5->Data_0x10 & 0x02) != 0) && 
                    (r3->Data_8 == *((int*)&r4->Data_8) /*TODO!!!*/) &&
                    (r3->Data_0x24 == r4->Data_8.iface /*0x24*/))
                {
                    pthread_mutex_unlock(&r5->Data_8/*r6*/);
                    pthread_mutex_unlock(&UsbdiGlobals.Data_0);

                    return 0x10;
                }
                //loc_11422c
                r3 = r3->Data_0;
                //->loc_1141e8
            }
            //loc_114238
            pthread_mutex_unlock(&r5->Data_8/*r6*/);

            r5 = r5->Data_0;
        }
        //loc_11424c
        pthread_mutex_lock(&r7->Data_8);

        if ((r4->Data_0 = r7->Data_0x1c) != 0)
        {
            r7->Data_0x1c->Data_4 = &r4->Data_0;
        }
        else
        {
            r7->Data_0x20 = r4;
        }

        r7->Data_0x1c = r4;
        r4->Data_4 = &r7->Data_0x1c;

        pthread_mutex_unlock(&r7->Data_8);

        pthread_mutex_unlock(&UsbdiGlobals.Data_0);

        return 0;
    }
    else
    {
        //loc_114294
        pthread_mutex_lock(&r7->Data_8);

        if ((r4->Data_0 = r7->Data_0x1c) != 0)
        {
            r7->Data_0x1c->Data_4 = &r4->Data_0;
        }
        else
        {
            r7->Data_0x20 = r4;
        }

        r7->Data_0x1c = r4;
        r4->Data_4 = &r7->Data_0x1c;

        pthread_mutex_unlock(&r7->Data_8);
    }

    return 0;
}


/* 1143a4 - complete */
int usbdi_client_attach(struct USB_Client* a, usbd_device_instance_t* b)
{
#if 0
    fprintf(stderr, "usbdi_client_attach: TODO!!!\n");
#endif

    int res;
    struct Struct_114194* r5;
    
    r5 = usbdi_memchunk_malloc(UsbdiGlobals.Data_0xc, sizeof(struct Struct_114194));
    if (r5 == NULL)
    {
        return 12;
    }

    memcpy(&r5->Data_8, b, sizeof(usbd_device_instance_t));

    res = conflict(r5, a);
    if (res != 0)
    {
        usbdi_memchunk_free(UsbdiGlobals.Data_0xc, r5);
    }

    return res;
}


/* 1115b4 - todo */
int sub_1115b4(int a, int b)
{
#if 1
    fprintf(stderr, "sub_1115b4: TODO!!!\n");
#endif

    return 0;
}



/* 0x001071c8 - todo */
int udi_endpoint_descriptor(struct usbd_urb* r4, 
        struct Struct_112b08** r6, 
        struct USB_Controller_Inner_0x7c** r5, 
        int r7)
{
#if 0
    fprintf(stderr, "udi_endpoint_descriptor: TODO!!!\n");
#endif

    struct USB_Controller_Inner_0x7c* r0;

    *r6 = 0;
    if (r5 != NULL)
    {
        *r5 = 0;
    }

    r0 = USB_CheckDevice(r4->bData_0x28, r4->bData_0x29);
    if (r0 == NULL)
    {
        //->loc_107278
        return 0x13;
    }

    if (r7 != 0)
    {
        if (r0->wData_0xe != r4->wData_0x2a)
        {
            //->loc_107278
            return 0x13;
        }
        //0x00107214
        if ((r0->bData_0xd & 1) == 0)
        {
            //->loc_107278
            return 0x13;
        }
    }
    //loc_107220
    if (r5 != 0)
    {
        *r5 = r0;
    }

    if ((r4->Data_0x38 & 0x0f) == 0)
    {
        *r6 = &r0->Data_0x40;

        return 0;
    }

    int r0_ = sub_1113ec(r4->bData_0x28, r4->bData_0x29,
            r4->Data_0x2c, r4->Data_0x30);
    if (r0_ != 0)
    {
        //0x0010725c
        *r6 = sub_1115b4(r0_, r4->Data_0x38);
        if (*r6 != 0)
        {
            return 0;
        }
    }
    //loc_107280
    return 2;
}


/* 11779c - todo */
void usbd_free_cached(void* a)
{
 #if 1
    fprintf(stderr, "usbd_free_cached: TODO!!!\n");
#endif
   
}


/* 117af8 - todo */
void* usbd_alloc_cached(size_t size)
{
#if 0
    fprintf(stderr, "usbd_alloc_cached: TODO!!!\n");
#endif

    return usbdi_memchunk_malloc(UsbdiGlobals.Data_0xc, size);
}


/* 107eac - todo */
void sub_107eac()
{
#if 1
    fprintf(stderr, "sub_107eac: TODO!!!\n");
#endif

}


/* 108340 - todo */
void sub_108340()
{
#if 1
    fprintf(stderr, "sub_108340: TODO!!!\n");
#endif

}


/* 0x00107288 - todo */
int udi_alloc_surb(struct USB_Controller* sb,
        struct USB_Client* sp_0x1c, 
        struct usbd_urb* r8,
        struct Struct_10bab4** sp_0x2c)
{
#if 0
    fprintf(stderr, "udi_alloc_surb: TODO!!!\n");
#endif

    int r5_res;
    int r7_;
    int r0;
    struct usbd_urb* r3;
    struct Struct_112b08* sp_0x34;
    int sp_0x28;
    struct Struct_10bab4* sp_0x18;
    int sp_0x14;

    *sp_0x2c = 0;

    if ((r8->Data_0x38 & 0x0f) &&
        ((r8->Data_0x24 & 0x80000) == 0))
    {
        sp_0x14 = 0x70;
        //->loc_1072d4
    }
    else
    {
        //loc_1072cc
        sp_0x14 = 0;
    }
    //loc_1072d4
#if 1
    if (r8 == NULL)
    {
        r0 = 0; 
        r7_ = 0;
        //->loc_107324
    }
    else
    {
        r3 = r8;
        r0 = 0;
        r7_ = 0;
#else
    {
        r0 = r7_ = 0;
        r3 = r8;
#endif
        while (r3 != NULL)
        {
            //loc_1072f0
            r7_++;
            int r2 = r3->Data_0x24;
            if (r2 & 0x200000)
            {
                r0 = r0 + r3->wData_0x5e;
            }
            if (r3->Data_4 == NULL)
            {
                //->loc_107324
                break;
            }
            if ((r2 & 0x100000) == 0)
            {
                //->loc_107324
                break;
            }

            r3 = ((uint8_t*)r8) + r3->wData_0x68;
        }
    }
    //loc_107324
    sp_0x28 = sp_0x14;
    sp_0x18 = usbd_alloc_cached((sp_0x28 + 0x64) * r7_ + r0);
    if (sp_0x18 == NULL)
    {
        return 0/*r5_res*/; //->loc_107620
    }
    //0x00107348
    if (r8 != 0)
    {
        //0x00107350
        struct usbd_urb* r4 = r8;
        //r6 = sp_0x18;
        struct
        {
            int fill_0; //0
            int Data_4; //4
            //???
        }* sl = 0;
        //fp = 0;
        //sp_0x20 = sub_108340;
        //sp_0x24 = sub_107eac;
        //struct USB_Controller* r5 = sb;
        //struct usbd_urb* sb = r8;
        //r8 = r7_;
        //r7 = r6;
        //r6 = r4;

        struct Struct_10bab4* r7 = sp_0x18; //r6;
        struct usbd_urb* r6 = r8; //r4;

        while (1)
        {
            //loc_10738c
            r7->Data_0x10 = 7;
            r7->Data_0x18 = r6->bData_0x28;
            r7->Data_0x14 = r6->bData_0x29;
            r7->Data_0x1c = (r6->Data_0x40 == 0)? 2000: r8/*sb*/->Data_0x40;
            r7->Data_8 = r6->Data_0x3c;
            r7->Data_0x20 = r6->Data_0x2c;
            r7->Data_0x24 = r6->Data_0x30;
            r7->Data_0x28 = r6->Data_0x38 & 0x0f;
            r7->Data_0 = r6->Data_0x24 | 0x20000;
            r7->Data_0x34 = 0; //fp;
            r7->pData = r6->pData;
            r7->dwLength = r6->dwLength;
            r7->direction = ((r6->Data_0x24 & 0x03) == 0x01)? 
                USB_DIRECTION_HOST: //Device to Host
                USB_DIRECTION_DEVICE; //Host to Device
            r7->Data_0x54 = r6->Data_0x54;
            r7->request = r6->request; //e.g. USB_GET_DESCRIPTOR
            r7->request_type = r6->request_type >> 5; //e.g. USB_TYPE_STANDARD
            r7->request_recipient = r6->request_type & 0x07; //e.g. USB_RECIPIENT_DEVICE
            r7->value_high = r6->wValue >> 8; //e.g. Descriptor Type 
            r7->value_low = r6->wValue & 0xff; //e.g. Index
            r7->Data_0x50 = r6->wData_0x5a;
            r7->Func_0x58 = (r7_/*r8*/ == 1)? 
                sub_108340/*sp_0x20*/: sub_107eac/*sp_0x24*/;
            r7->Data_0x60 = sp_0x1c;

            if (/*r5*/sb->capabilities & 0x40000000)
            {
                //0x00107480
                int r0 = udi_endpoint_descriptor(r6, &sp_0x34, NULL/*fp*/, 1);
                if (r0 == 0)
                {
                    //0x0010749c
                    if ((r7->pData != NULL) &&
                        (r7->dwLength != 0))
                    {
                        //0x001074b4
                        r7->pData = ccache_get_addr_cache(sp_0x34, r7, 
                                r7->pData, r7->dwLength, sp_0x1c);

                        if (r7->pData == NULL)
                        {
                            //0x001074d4
                            //r6 = r7; //TODO!!!

                            usb_slogf(12, 2, 0, "%s(%d): %p, len %d",
                                "udi_alloc_surb", 0x5fd, NULL, r7->dwLength);

                            r5_res = 12;
                            //->loc_107518
                            goto loc_107518;
                        }
                        //loc_107524
                    }
                    //loc_107524
                }
                else
                {
                    //loc_107514
                    r5_res = r0;
loc_107518:                    
                    //loc_107518
                    usbd_free_cached(sp_0x18);
                    //->loc_107620
                    return r5_res;
                }
            } //if (/*r5*/sb->capabilities & 0x40000000)
            //loc_107524
            if (sp_0x14 == 0)
            {
                r7->Data_0x5c = r6;
                r4 = r8/*sb*/;
                //->loc_107594
            }
            else
            {
                //0x00107538
                if (r6->Data_0x24 & 0x200000)
                {
                    //0x00107544
                    r6->Data_0x60 = r7 + 1; //&r7->Data_0x64;

                    memcpy(r6->Data_0x60, r6 + 1, r6->wData_0x5e);

                    r7->Data_0x5c = ((uint8_t*)r6->Data_0x60) + r6->wData_0x5e;

                    memcpy(r7->Data_0x5c, r6, sizeof(struct usbd_urb)/*0x70*/);

                    r4 = r7->Data_0x5c;
                    //->loc_107594
                }
                else
                {
                    //loc_10757c
                    r4 = r7 + 1; //&r7->Data_0x64;

                    memcpy(r4, r6, sp_0x28);

                    r7->Data_0x5c = r4;
                }
            }
            //loc_107594
            r4->Data_0x14 = r7;
            r4->Data_0x64 = (r7_/*r8*/ <= 1)? 0/*fp*/: sp_0x18->Data_0x5c;

            if (sl != 0)
            {
                sl->Data_4 = r4;
            }

            int r2 = r6->wData_0x5e;
            if ((r6->Data_0x24 & 0x100000) == 0)
            {
                //->loc_1075ec
                //r8 = sb;
                break;
            }

            if (r6->Data_4 == 0)
            {
                //->loc_1075f4
                //r8 = sb;
                break;
            }

            r6 = ((uint8_t*)r8/*sb*/) + r6->wData_0x68;
            if (r6 == 0)
            {
                //->loc_1075fc
                //r8 = sb;
                break;
            }
            //0x001075dc
            r2 = r2 + 0xd4;
            r7 = ((uint8_t*)r7) + r2;
            sl = r4;
            //->loc_10738c
        } //while (1)
        //loc_1075ec
        //loc_1075f4
        //loc_1075fc
    } //if (r8 != 0)
    //loc_107600
    if (r8->Data_4 != NULL)
    {
        sp_0x18->Data_0x50 = sp_0x18;
    }

    *sp_0x2c = sp_0x18;

    return 0;
}


/* 107a0c - todo */
void sub_107a0c(struct Struct_112b08* a)
{
#if 1
    fprintf(stderr, "sub_107a0c: TODO!!!\n");
#endif

}


/* 1099a8 - todo */
void sub_1099a8()
{
#if 1
    fprintf(stderr, "sub_1099a8: TODO!!!\n");
#endif

}


/* 117148 - todo */
void usbdi_timeout(int a, void (*b)(), struct usbd_urb* c)
{
#if 1
    fprintf(stderr, "usbdi_timeout: TODO!!!\n");
#endif

}


/* 11266c - todo */
int sub_11266c(struct Struct_10bab4* a)
{
#if 1
    fprintf(stderr, "sub_11266c: TODO!!!\n");
#endif

    return 0;
}


int usb_find_data_key(struct Struct_1047a8* a, 
        int b, int c, int d, int e, void* f, int* g)
{
#if 1
    fprintf(stderr, "usb_find_data_key: f=%p, *g=%d: TODO!!!\n",
        f, *g);
#endif


    return 0;
}


/* 106c90 - todo */
int udi_descriptor(struct usbd_urb* r4)
{
#if 1
    fprintf(stderr, "udi_descriptor: TODO!!!\n");
#endif

    int r6;
    struct USB_Client* r2;
    struct Struct_10bab4* r5;
    struct USB_Controller_Inner_0x7c* r7;

    r7 = USB_CheckDevice(r4->bData_0x28, r4->bData_0x29);
    if (r7 == NULL)
    {
        return 0x13; //->loc_106e34
    }

    r5 = r4->Data_0x14;
    r2 = r5->Data_0x60;

    if (((r4->Data_0x24 & 0x3) == 0) || 
        (r4->request_type != 0) ||
        (r2->Data_0x10 & 0x08))
    {
        //loc_106ce0
        r6 = USB_SendCommand(r5);
        //->loc_106e34
    }
    else
    {
        //loc_106cf0
        if (r4->request == USB_GET_DESCRIPTOR)
        {
            //0x00106cfc
            void* r8 = mmap(NULL, r4->dwLength, 
                        PROT_NOCACHE|PROT_READ|PROT_WRITE, //0xb00, 
                        MAP_PHYS|MAP_SHARED, //0x10001, 
                        -1, 
                        (off_t)(r4->pData));
#if 1
            fprintf(stderr, "udi_descriptor: r4->pData=%p -> r8=%p\n", 
                    r4->pData, r8);
#endif
            if (r8 != NULL)
            {
                //0x00106d2c
                int sp_0x14 = r4->dwLength;

                struct
                {
                    int fill_0[2]; //0
                    int Data_8; //8
                    //???
                }* r0;

                r0 = usb_find_data_key(r7->Data_0x8c,
                        1, 
                        r4->wValue,
                        r4->wData_0x5a,
                        0, //sp
                        r8, //sp4
                        &sp_0x14);

                if ((r0 != NULL) &&
                    //0x00106d64
                    ((r4->dwLength == sp_0x14) ||
                        ((r0->Data_8 & 0x01) != 0)))
                {
                    //loc_106d80
                    r6 = 0;
                    r5->Data_8 = r6; //0
                    r5->Data_0x34 = sp_0x14;
                    //->loc_106e04
                }
                else
                {
                    //loc_106d94
                    r6 = USB_SendCommand(r4->Data_0x14);
                    if (r6 == 0)
                    {
                        //0x00106da4
#if 1
                        fprintf(stderr, "udi_descriptor: 0x00106da4: TODO!!!\n");
                        int i;
                        for (i = 0; i < r4->dwLength; i++)
                        {
                            fprintf(stderr, "r4->Data_0x14->pData[%d] = 0x%02x\n",
                                i, ((uint8_t*)(r4->Data_0x14->pData))[i]);
                        }
#endif
                        //TODO!!!
                    }
                }
                //loc_106e04
                munmap(r8, r4->dwLength);
                //->loc_106e34
            } //if (r8 != NULL)
            else
            {
                //loc_106e14
                r6 = 12;
                r5->Data_8 = r6; //12
                r5->Data_0x34 = 0;
                //->loc_106e34
            }
        } //if (r4->request == USB_GET_DESCRIPTOR)
        else
        {
            //loc_106e28
            r6 = USB_SendCommand(r5);
        }
    }
    //loc_106e34
    return r6;
}


/* 106f6c - todo */
int udi_control_transfer(struct usbd_urb* r0)
{
#if 1
    fprintf(stderr, "udi_control_transfer: TODO!!!\n");
#endif

    switch (r0->wData_0x22)
    {
#if 0 //TODO!!!
        case 8:
            //loc_106f98
            break;

        case 9:
            //loc_106fa0
            break;

        case 6:
            //loc_106fa8
            break;
#endif

        case 5:
            //loc_106fc8
            return udi_descriptor(r0);
            //break;

#if 0
        case 7:
        default:
            //loc_106fd0
            break;
#else
        default:
            fprintf(stderr, "udi_control_transfer: r0->wData_0x22=%d: TODO!!!\n",
                    r0->wData_0x22);
            break;
#endif
    }

    return 0;
}


/* 105c64 - todo */
int udi_xlat_status(int a)
{
#if 1
    fprintf(stderr, "udi_xlat_status: TODO!!!\n");
#endif

    return 0;
}


/* 107758 - todo */
int udi_transfer(struct usbd_urb* r4, struct Struct_112b08* r5)
{
#if 1
    fprintf(stderr, "udi_transfer: TODO!!!\n");
#endif

    struct Struct_10bab4* r8 = r4->Data_0x14;
    int r7 = r4->Data_0x38 & 0x0f;
    int r6;
    int r0;

    if (r4->Data_0x3c != 0)
    {
        r6 = 0x16;
        //->loc_1078b8
    }
    else
    {
        //0x00107784
        r5->Data_0x24 |= 0x02;

        if (r7 != 0)
        {
            //0x00107798
            if (r4->Data_0x40 == 0)
            {
                r4->Data_0x40 = 2000;
                //->loc_1077b4
            }
            if (r4->Data_0x40 != -1)
            {
                usbdi_timeout(r4->Data_0x40, sub_1099a8, r4);
            }
            //loc_1077c4
            r0 = pthread_mutex_unlock(&r5->Data_0x30);
            if (r0 != 0)
            {
                //0x001077d4
                usb_slogf(12, 2, 0, "%s(%d):  error releasing mutex, %d",
                    "udi_transfer", 0x555, r0);
            }
            //loc_107800
            r6 = sub_11266c(r8);
            //->loc_107858
        }
        else
        {
            //loc_107810
            r0 = pthread_mutex_unlock(&r5->Data_0x30);
            if (r0 != 0)
            {
                //0x00107820
                usb_slogf(12, 2, 0, "%s(%d):  error releasing mutex, %d",
                    "udi_transfer", 0x55c, r0);
            }
            //loc_10784c
            r6 = udi_control_transfer(r4);
        }
        //loc_107858
        r0 = pthread_mutex_lock(&r5->Data_0x30);
        if (r0 != 0)
        {
            //0x00107868
            usb_slogf(12, 2, 0, "%s(%d):  error acquiring mutex, %d",
                "udi_transfer", 0x564, r0);
        }
        //loc_107894
        int r3 = r5->Data_0x24;
        r5->Data_0x24 = r3 & ~0x02;

        if (r3 & 0x01)
        {
            //0x001078a8
            pthread_cond_signal(&r5->Data_0x38);
        }
        //loc_1078b0
    }
    //loc_1078b0
    if (r6 != 0)
    {
        //loc_1078b8

        fprintf(stderr, "udi_transfer: loc_1078b8: TODO!!!\n");

        //TODO!!!
    }
    //loc_1079e0
    if (r7 == 0)
    {
        //0x001079e8
        r4->Data_0x3c = udi_xlat_status(r8->Data_8);

        r4->Data_0x50 = r8->Data_0x34;
    }
    //loc_1079fc
    return r6;
}


/* 107a90 - todo */
int udi_io(struct USB_Client* r8, struct usbd_urb* r4)
{
#if 1
    fprintf(stderr, "udi_io: TODO!!!\n");
#endif

    struct Struct_10bab4* sp_0x1c;
    struct Struct_112b08* sp_0x18;
    struct USB_Controller_Inner_0x7c* sp_0x14;
    int r5;
    struct USB_Controller* r7;

    r7 = CTRL_HCLookup(r4->bData_0x28);
    if (r7 == NULL)
    {
        return 0x13; //->loc_107e9c
    }

    int r0 = pthread_mutex_lock(&r7->Data_0x24/*r6*/);
    if (r0 != 0)
    {
        usb_slogf(12, 2, 0, "%s(%d):  error acquiring mutex, %d",
            "udi_io", 0x647, r0);
    }
    //loc_107af4
    r5 = udi_endpoint_descriptor(r4, &sp_0x18, &sp_0x14, 1);
    if (r5 != 0)
    {
        //0x00107b10
        usb_slogf(12, 2, 4, "%s(%d): devno %d status %d ",
            "udi_io", 0x64b, r4->bData_0x29, r5);

        r0 = pthread_mutex_unlock(&r7->Data_0x24/*r6*/);
        if (r0 != 0)
        {
            //0x00107b54
            usb_slogf(12, 2, 0, "%s(%d):  error releasing mutex, %d",
                "udi_io", 0x64d, r0);
        }
        //loc_107e9c
        return r5;
    }
    //loc_107b84
    atomic_add(&sp_0x14->Data_0xa8, 1);

    r5 = udi_alloc_surb(r7, r8, r4, &sp_0x1c);
    if (r5 != 0)
    {
        //0x00107bb0
        atomic_sub(&sp_0x14->Data_0xa8, 1);

        r0 = pthread_mutex_unlock(&r7->Data_0x24/*r6*/);
        if (r0 != 0)
        {
            //0x00107bd0
            usb_slogf(12, 2, 0, "%s(%d):  error releasing mutex, %d",
                "udi_io", 0x657, r0);
        }
        //loc_107bfc
        usb_slogf(12, 2, 0, "%s(%d): devno %d status %d ",
            "udi_io", 0x659, r4->bData_0x29, r5);
        //loc_107e9c
        return r5;
    }
    //loc_107c34
    struct usbd_urb* r4_ = sp_0x1c->Data_0x5c;
    sp_0x1c->Data_0x60 = r8;
    int r7_ = r4_->Data_0x38;

    r0 = pthread_mutex_unlock(&r7->Data_0x24/*r6*/);
    if (r0 != 0)
    {
        //0x00107c54
        usb_slogf(12, 2, 0, "%s(%d):  error releasing mutex, %d",
            "udi_io", 0x663, r0);
    }
    //loc_107c80
    pthread_mutex_lock(&sp_0x14->Data_0x94);

    while (sp_0x14->bData_0xd & 0x08)
    {
        //loc_107c9c
        pthread_cond_wait(&sp_0x14->Data_0x9c, &sp_0x14->Data_0x94);
    }
    //loc_107cb8
    pthread_mutex_unlock(&sp_0x14->Data_0x94);

    r0 = pthread_mutex_lock(&sp_0x18->Data_0x30);
    if (r0 != 0)
    {
        //0x00107cd4
        usb_slogf(12, 2, 0, "%s(%d):  error acquiring mutex, %d",
            "udi_io", 0x66e, r0);
    }
    //loc_107d00
    if (r7_ & 0xf)
    {
        //0x00107d08
        while (sp_0x18->Data_0x24 & 0x01)
        {
            //loc_107d18
            pthread_cond_wait(&sp_0x18->Data_0x38, &sp_0x18->Data_0x30);
        }
        //loc_107d34
        r4_->Data_8 = 0;
        r4_->Data_0xc = sp_0x18->Data_0x18;
        sp_0x18->Data_0x18->Data_0 = r4_;
        r4_ = &r4_->Data_8;
        sp_0x18->Data_0x18 = r4_;

        sub_107a0c(sp_0x18);

        r0 = pthread_mutex_unlock(&sp_0x18->Data_0x30);
        if (r0 != 0)
        {
            //0x00107d7c
            usb_slogf(12, 2, 0, "%s(%d):  error releasing mutex, %d",
                "udi_io", 0x679, r0);
        }
        //->loc_107e9c
    }
    else
    {
        //loc_107db8
        while ((sp_0x18->Data_0x1c != 0) ||
            (sp_0x18->Data_0x24 & 1))
        {
            //loc_107dac
            pthread_cond_wait(&sp_0x18->Data_0x38, &sp_0x18->Data_0x30);
        }
        //0x00107dd4
        r4_->Data_8 = NULL;
        r4_->Data_0xc = sp_0x18->Data_0x20;
        sp_0x18->Data_0x20->Data_0 = r4_;
        sp_0x18->Data_0x20 = &r4_->Data_8;

        r5 = udi_transfer(r4_, sp_0x18);

        if (r4_->Data_8 != NULL)
        {
            r4_->Data_8->Data_0xc = r4_->Data_0xc;
        }
        else
        {
            sp_0x18->Data_0x20 = r4_->Data_0xc;
        }

        r4_->Data_0xc->Data_0 = r4_->Data_8;

        pthread_cond_signal(&sp_0x18->Data_0x38);
        r0 = pthread_mutex_unlock(&sp_0x18->Data_0x30);
        if (r0 != 0)
        {
            usb_slogf(12, 2, 0, "%s(%d):  error releasing mutex, %d",
                "udi_io", 0x68a, r0);
        }
        //loc_107e84
        atomic_sub(&sp_0x14->Data_0xa8, 1);

        usbd_free_cached(sp_0x1c);
    }
    //loc_107e9c
    return r5;
}


/* 0x00115648 - todo */
int usbdi_resmgr_msg(resmgr_context_t* ctp/*r7*/, 
                    io_msg_t* msg/*r1*/,
                     RESMGR_OCB_T* ocb/*r5*/)
{
    int r4;

    struct
    {
        uint16_t wData_0; //0
        uint16_t wData_2; //2
        union
        {
            usbd_device_instance_t device_instance; //4
            struct
            {
                int fill_4; //0
                usbd_hcd_info_t hcd_info; //4
            } hcd_info; //4
            struct 
            {
                uint32_t Data_0; //0
                char bData_4[100]; //4
            } udi_memory_info; //4
            struct 
            {
                int Data_0; //0
                int Data_4; //4
                int Data_8; //8
            } type_5; //4
                                    
        } u;
        
    } sp_0x26c;

    struct
    {
        struct 
        {
            uint16_t wData_0; //0
            uint16_t wData_2; //2
            int fill_4; //4
            //8
        } Data_0;                        
        int fill_8[25]; //8
        usbd_bus_topology_t Data_0x6c; //0x6c
        //0x26c
    } sp;                    

    struct
    {
        int Data_0; //0
        uint16_t wData_4; //4
        uint16_t wData_6; //6

    }* r8;
    struct USB_Client* r6 = ocb->Data_0x18;

#if 1
    fprintf(stderr, "usbdi_resmgr_msg: r6=%p, msg->i.mgrid=%d, msg->i.subtype=%d\n",
        r6, msg->i.mgrid, msg->i.subtype);
#endif

    if (msg->i.mgrid != _IOMGR_USB)
    {
        //->loc_115b34
        return 0x59;
    }

    if (r6 == NULL)
    {
        //0x00115670
        if (msg->i.subtype != 1)
        {
            //->loc_115b3c
            return 0x09;
        }
        else
        {
            //->loc_115b68
            r8 = msg + 1;
            //->loc_1156d8
            if (((r8->wData_4 != 0) && (r8->wData_4 != 0x110)) ||
                ((r8->wData_6 != 0) && (r8->wData_6 != 0x101)))
            {
                //->loc_115b44
                return 0x113;
            }
            //0x001156fc
            pthread_mutex_lock(&UsbdiGlobals.Data_0);

            r4 = usbdi_client_create(r8->Data_0, &ocb->Data_0x18);

            pthread_mutex_unlock(&UsbdiGlobals.Data_0);

            if (r4 != 0)
            {
                //->loc_115b48
                return r4;
            }

            if ((r8->Data_0 & 0x04) == 0)
            {
                //->loc_115b48
                return r4;
            }
            //0x00115738
            udi_enumerate(ocb->Data_0x18);
            //->loc_115b48
            return r4;
        }
    }
    else
    {
        //loc_115680
        if (msg->i.subtype == 1)
        {
            //->loc_115b3c
            return 0x09;
        }
        //0x0011568c
        r8 = msg + 1;

        switch (msg->i.subtype)
        {
            case 1:
                //loc_1156d8
                if (((r8->wData_4 != 0) && (r8->wData_4 != 0x110)) ||
                    ((r8->wData_6 != 0) && (r8->wData_6 != 0x101)))
                {
                    //->loc_115b44
                    return 0x113;
                }
                //0x001156fc
                pthread_mutex_lock(&UsbdiGlobals.Data_0);

                r4 = usbdi_client_create(r8->Data_0, &ocb->Data_0x18);

                pthread_mutex_unlock(&UsbdiGlobals.Data_0);

                if (r4 != 0)
                {
                    //->loc_115b48
                    return r4;
                }

                if ((r8->Data_0 & 0x04) == 0)
                {
                    //->loc_115b48
                    return r4;
                }
                //0x00115738
                udi_enumerate(ocb->Data_0x18);
                //->loc_115b48
                break;

#if 0
            case 2:
                //loc_115744
                break;
#endif
                
            case 3:
                //loc_11575c: Attach
                {
                    sp_0x26c.wData_0 = 1;
                    sp_0x26c.wData_2 = 0x6c;
                    memcpy(&sp_0x26c.u.device_instance, r8, sizeof(usbd_device_instance_t));

                    r4 = udi_attach(&sp_0x26c.u.device_instance, r6->Data_0x10);
                    if (r4 == 0)
                    {
                        //0x001157a0
                        r4 = usbdi_client_attach(r6, &sp_0x26c.u.device_instance);
                        if (r4 == 0)
                        {
                            //0x001157b4
                            int r0 = MsgReply_r(ctp->rcvid, 0, 
                                        &sp_0x26c, sp_0x26c.wData_2);
                            if (r0 != 0)
                            {
                                r4 = -r0;
                            }
                            else
                            {
                                r4 |= 0x80000000;
                            }
                        }
                        else
                        {
                            //loc_1157dc
                            udi_detach(r6, &sp_0x26c.u.device_instance, 0);
                        }
                    }
                    //loc_115b48
                }
                break;

#if 0          
            case 4:
                //loc_1157f0
                break;
#endif
                
            case 5:
                //loc_11581c
                {
                    if ((((struct usbd_urb*)r8)->Data_0x24 & 0x80000) == 0)
                    {
                        //0x00115828
                        if ((r6->Data_0x10 & 0x01) == 0)
                        {
                            r4 = 0x16;
                            //->loc_115b48
                        }
                        else
                        {
                            //loc_115b54
                            r4 = udi_io(r6, r8);
                        }
                    }
                    else
                    {
                        //loc_11583c
                        r4 = udi_io(r6, r8);
                        if ((r4 == 5) || (r4 == 0))
                        {
                            //0x00115858
                            sp_0x26c.wData_0 = 3;
                            sp_0x26c.wData_2 = 0x6c;

                            sp_0x26c.u.type_5.Data_0 = ((struct usbd_urb*)r8)->Data_0x3c;
                            sp_0x26c.u.type_5.Data_4 = ((struct usbd_urb*)r8)->Data_0x50;
                            sp_0x26c.u.type_5.Data_8 = ((struct usbd_urb*)r8)->Data_0;

                            int r0 = MsgReply_r(ctp->rcvid, 0, &sp_0x26c, sp_0x26c.wData_2);
                            if (r0 != 0)
                            {
                                r4 = -r0;
                            }
                            else
                            {
                                r4 |= 0x80000000;
                            }
                        }
                        //loc_115b48
                    }
                }
                break;

#if 0          
            case 6:
                //loc_1158a4
                break;
                
            case 14:
                //loc_1158b8
                break;
#endif
                
            case 7:
                {
                    //loc_1158cc
                    struct Struct_1158cc
                    {
                        uint8_t bData_0;
                    };

                    r4 = udi_hcd_info(((struct Struct_1158cc*)r8)->bData_0,
                            &sp_0x26c.u.hcd_info.hcd_info);
                    if (r4 == 0)
                    {
                        sp_0x26c.wData_0 = 4;
                        sp_0x26c.wData_2 = 0x6c;

                        int r0 = MsgReply_r(ctp->rcvid, 0, &sp_0x26c, 0x6c);
                        if (r0 != 0)
                        {
                            r4 = -r0;
                        }
                        else
                        {
                            r4 |= 0x80000000;
                        }
                    }
                }
                //->loc_115b48
                break;

#if 0          
            case 8:
                //loc_115914
                break;
                
            case 9:
                //loc_11597c
                break;
#endif
                
            case 10:
                //loc_115990
                {
                    struct Struct_115990
                    {
                        uint32_t Data_0;
                    };

                    memset(&sp/*r5*/, 0xff, 0x26c);

                    sp.Data_0.wData_0 = 7;
                    sp.Data_0.wData_2 = 0x26c;

                    r4 = udi_topology(((struct Struct_115990*)r8)->Data_0,
                            &sp.Data_0x6c);
                    if (r4 == 0)
                    {
                        //0x001159e4
                        int r0 = MsgReply_r(ctp->rcvid, 0, &sp, sp.Data_0.wData_2);
                        if (r0 != 0)
                        {
                            r4 = -r0;
                        }
                        else
                        {
                            r4 |= 0x80000000;
                        }
                    }
                }
                //loc_115b48
                break;

            case 11:
                //loc_115a14: Memory Info
                {
                    sp_0x26c.u.udi_memory_info.bData_4[0] = 0;
                    sp_0x26c.u.udi_memory_info.Data_0 = 0;

                    udi_memory_info(&sp_0x26c.u.udi_memory_info.Data_0);

                    if (UsbdiGlobals.Data_0x48 != NULL)
                    {
                        strcpy(&sp_0x26c.u.udi_memory_info.bData_4[0], 
                            UsbdiGlobals.Data_0x48);
                    }
                    //loc_115a4c
                    if (UsbdiGlobals.typed_mem_fd != -1)
                    {
                        //0x00115a60
                        strcpy(&sp_0x26c.u.udi_memory_info.bData_4[0], 
                            UsbdiGlobals.typed_memory_name);

                        sp_0x26c.u.udi_memory_info.Data_0 |= 0x04;
                    }
                    //loc_115a80
                    sp_0x26c.wData_0 = 8;
                    sp_0x26c.wData_2 = 0x6c;

                    int r0 = MsgReply_r(ctp->rcvid, 0, &sp_0x26c, sp_0x26c.wData_2);
                    if (r0 != 0)
                    {
                        r4 = -r0;
                    }
                    else
                    {
                        r4 |= 0x80000000;
                    }
                }   //loc_115b48
                break;
                
#if 0          
            case 12:
                //loc_115ab4
                break;
                
            case 13:
                //loc_115afc
                break;
#endif

            default:
                //loc_115b34
#if 1
                fprintf(stderr, "usbdi_resmgr_msg: msg->i.subtype=%d: TODO!!!\n",
                    msg->i.subtype);
#endif
                return 0x59;
                //break;
        }
    }
    //loc_115b48
    return r4;
}


/* 0x00115b70 - complete */
int _iofunc_callout(int (*func)(), 
        resmgr_context_t *ctp, io_stat_t *msg, iofunc_ocb_t *ocb)
{
#if 0
    fprintf(stderr, "_iofunc_callout\n");
#endif

    int res = iofunc_attr_lock(ocb->attr);
    if (res == 0)
    {
        res = (func)(ctp, msg, ocb);

        iofunc_attr_unlock(ocb->attr);
    }

    return res;
}



/* 0x00115c80 - complete */
int usbdi_resmgr_stat(resmgr_context_t *ctp, io_stat_t *msg, iofunc_ocb_t *ocb)
{
#if 1
    fprintf(stderr, "usbdi_resmgr_stat\n");
#endif

    return _iofunc_callout(iofunc_stat_default, ctp, msg, ocb);
}



/* 0x00115d34 - todo */
int usbdi_resmgr_open(resmgr_context_t *ctp, io_open_t *msg,
                      RESMGR_HANDLE_T *handle, void *extra)
{
#if 1
    fprintf(stderr, "usbdi_resmgr_open\n");
#endif

    int r4;
    IOFUNC_OCB_T* ocb;

    if (msg->connect.extra_type != 0)
    {
        return 0x59;
    }

    r4 = iofunc_attr_lock(&UsbdiGlobals.iofunc_attr);
    if (r4 == 0)
    {
        r4 = iofunc_open(ctp, msg, &UsbdiGlobals.iofunc_attr, 0, 0);
        if (r4 == 0)
        {
            ocb = usbdi_ocb_calloc(ctp, &UsbdiGlobals.iofunc_attr);
            if (ocb != NULL)
            {
                r4 = iofunc_ocb_attach(ctp, msg, &ocb->hdr, 
                        &UsbdiGlobals.iofunc_attr, &ResmgrIOFuncs);

                if (r4 == 0)
                {
                    iofunc_attr_unlock(&UsbdiGlobals.iofunc_attr);

                    return r4;
                }

                usbdi_ocb_free(ocb);
            }

        }

        iofunc_attr_unlock(&UsbdiGlobals.iofunc_attr);
    }

    return r4;
}


/* 0x00115ce8 - complete */
int usbdi_resmgr_close(resmgr_context_t *ctp, void *reserved, IOFUNC_OCB_T *ocb)
{
#if 1
    fprintf(stderr, "usbdi_resmgr_close\n");
#endif

    iofunc_attr_t* r5 = ocb->hdr.attr;

    iofunc_attr_lock(r5);

    iofunc_ocb_detach(ctp, &ocb->hdr);

    if (ocb->Data_0x18 != 0)
    {
        usbdi_client_destroy(ocb->Data_0x18);
    }

    usbdi_ocb_free(ocb);
    iofunc_attr_unlock(r5);

    return 0;
}



static int nonblockevent(message_context_t *ctp, int code, unsigned flags, void *handle);


/* 0x00115dec - todo */
int usbdi_init_server_globals(char* r5, struct USB_Timer* r6)
{
#if 0
    fprintf(stderr, "usbdi_init_server_globals\n");
#endif

    int r4;
    ino64_t inode; //sp_0x98; //TODO
    resmgr_attr_t sp_0x78;
    struct stat sp_0x30;
    pthread_mutexattr_t sp_0x10;

    if (stat(r5, &sp_0x30) != -1)
    {
        fprintf(stderr, "io-usb already attached to %s\n", r5);
        //->loc_1160f8
        r4 = 16;
        return r4;
    }
    //loc_115e2c
    pthread_mutexattr_init(&sp_0x10);
    pthread_mutexattr_setrecursive(&sp_0x10, 2);
    r4 = pthread_mutex_init(&UsbdiGlobals.Data_0, &sp_0x10);

    if (r4 != 0)
    {
        if (r4 == 16)
        {
            r4 = 0;
        }
        return r4;
    }
    //loc_115e68
    r4 = usbdi_memchunk_init(&Data_11ddf4[0], 8, &UsbdiGlobals.Data_8, 0);
    if (r4 != 0)
    {
        return r4;
    }

    r4 = usbdi_memchunk_init(&Data_11ddf4[0], 8, &UsbdiGlobals.Data_0xc, 1);
    if (r4 != 0)
    {
        return r4;
    }

    UsbdiGlobals.Data_0x24 = 0;
    UsbdiGlobals.Data_0x28 = &UsbdiGlobals.Data_0x24;

    iofunc_attr_init(&UsbdiGlobals.iofunc_attr, 0x21a4, 0, 0);

    UsbdiGlobals.Data_0x4c.flags = 0x100;
    UsbdiGlobals.Data_0x4c.conf = 3;
    UsbdiGlobals.Data_0x4c.blocksize = 1;
    UsbdiGlobals.Data_0x4c.funcs = &ResmgrOCBFuncs;
    UsbdiGlobals.iofunc_attr.mount = &UsbdiGlobals.Data_0x4c;

    UsbdiGlobals.dpp = dispatch_create();

    if (UsbdiGlobals.dpp == 0)
    {
        r4 = errno;
        return r4;
    }
    //loc_115f14
#if 1
    memset(&sp_0x78, 0, sizeof(sp_0x78));
#else
    sp_0x78.flags = 0;
    sp_0x78.other_func = 0;
    sp_0x78.reserved[0] = 0;
    sp_0x78.reserved[1] = 0;
    sp_0x78.reserved[2] = 0;
    sp_0x78.reserved[3] = 0;
#endif

    sp_0x78.nparts_max = 0x41;
    sp_0x78.msg_max_size = 0x2214;

    resmgr_attach(UsbdiGlobals.dpp,
        &sp_0x78,
        0,
        0x0b,
        0x100,
        &ResmgrCFuncs,
        0,
        0);

    UsbdiGlobals.resmgr_attr.nparts_max = 0x41;

    UsbdiGlobals.Data_0xdc.handle = UsbdiGlobals.dpp;
    UsbdiGlobals.Data_0xdc.context_alloc = dispatch_context_alloc;
    UsbdiGlobals.Data_0xdc.context_free = dispatch_context_free;
    UsbdiGlobals.Data_0xdc.block_func = dispatch_block;
    UsbdiGlobals.Data_0xdc.handler_func = dispatch_handler;
    UsbdiGlobals.Data_0xdc.tid_name = "usb_resmgr";
    UsbdiGlobals.Data_0xdc.attr = &UsbdiGlobals.Data_0x120;

    pthread_attr_init(&UsbdiGlobals.Data_0x120);
    pthread_attr_setdetachstate(&UsbdiGlobals.Data_0x120, 1);
    pthread_attr_setstacksize(&UsbdiGlobals.Data_0x120, 0x4000);

    UsbdiGlobals.Data_0x30 = resmgr_attach(UsbdiGlobals.dpp,
        &UsbdiGlobals.resmgr_attr,
        r5,
        0x0b,
        0x300,
        &ResmgrCFuncs,
        &ResmgrIOFuncs,
        &UsbdiGlobals.iofunc_attr);

    if (UsbdiGlobals.Data_0x30 == -1)
    {
        r4 = errno;
        return r4;
    }
    //loc_116030
    resmgr_devino(UsbdiGlobals.Data_0x30, &UsbdiGlobals.Data_0x4c.dev, &inode);

    UsbdiGlobals.Data_0xb8 = UsbdiGlobals.Data_0x4c.dev;
    UsbdiGlobals.iofunc_attr.inode = inode; //TODO: only 32bit

    UsbdiGlobals.Data_0x2c = message_connect(UsbdiGlobals.dpp, 0x200);

    if (UsbdiGlobals.Data_0x2c == -1)
    {
        r4 = errno;
        return r4;
    }
    //loc_116078
    r4 = usbdi_timeout_init(r6);
    if (r4 != 0)
    {
        return r4;
    }

    UsbdiGlobals.Data_0x34 = pulse_attach(UsbdiGlobals.dpp, 
        2, 0, nonblockevent, 0);

    if (UsbdiGlobals.Data_0x34 == -1)
    {
        r4 = errno;
        return r4;
    }
    //loc_1160bc
    UsbdiGlobals.Data_0x20 = thread_pool_create(&UsbdiGlobals.Data_0xdc, 0);
    
    if (UsbdiGlobals.Data_0x20 == 0)
    {
        r4 = errno;
        return r4;
    }
    //loc_1160e4
    if (thread_pool_start(UsbdiGlobals.Data_0x20) == -1)
    {
        r4 = errno;
        return r4;
    }
    //loc_1160f8
    return 0;
}


/* 116120 - todo */
static int nonblockevent(message_context_t *ctp, int code, unsigned flags, void *handle)
{
#if 1
    fprintf(stderr, "nonblockevent\n");
#endif

}


