

#include "externs.h"

extern int usbdi_memchunk_init();
extern void* usbdi_memchunk_calloc(int a, int b, int c);
extern void usbdi_memchunk_free(int, void*);

extern void usbdi_client_destroy();

extern int Data_11ddf4; //11ddf4

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

    b->capabilities = cntrl->Data_0x6c | 0x1000;
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
int sub_1113ec(int a, int b, int c)
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
        r0 = sub_1113ec(r4->path, r4->devno, r4->config);
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
        fprintf(stderr, "udi_attach: 0x001067d0: TODO!!!\n");

        //TODO!!!

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


/* 1143a4 - todo */
int sub_1143a4(struct USB_Client* a, void* b)
{
#if 1
    fprintf(stderr, "sub_1143a4: TODO!!!\n");
#endif

    return 0;
}


/* 0x00115648 - todo */
int usbdi_resmgr_msg(resmgr_context_t* ctp/*r7*/, 
                    io_msg_t* msg/*r1*/,
                     RESMGR_OCB_T* ocb/*r5*/)
{
    int r4;

    usbd_hcd_info_t sp_0x274;
    struct
    {
        uint16_t wData_0; //0
        uint16_t wData_2; //2
        int fill_4; //4
        //8???
    } sp_0x26c;

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
                    usbd_device_instance_t sp_0x270;

                    sp_0x26c.wData_0 = 1;
                    sp_0x26c.wData_2 = 0x6c;

                    memcpy(&sp_0x270, r8, sizeof(usbd_device_instance_t));

                    r4 = udi_attach(&sp_0x270, r6->Data_0x10);
                    if (r4 == 0)
                    {
                        //0x001157a0
                        r4 = sub_1143a4(r6, &sp_0x270);
                        if (r4 == 0)
                        {
                            //0x001157b4
                            int r0 = MsgReply_r(ctp->rcvid, 0, 
                                        &sp_0x26c, sp_0x26c.wData_0);
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
                            udi_detach(r6, &sp_0x270, 0);
                        }
                    }
                    //loc_115b48
                }
                break;

#if 0          
            case 4:
                //loc_1157f0
                break;
                
            case 5:
                //loc_11581c
                break;
                
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
                            &sp_0x274);
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

#if 0          
            case 11:
                //loc_115a14
                break;
                
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
    r4 = usbdi_memchunk_init(&Data_11ddf4, 8, &UsbdiGlobals.Data_8, 0);
    if (r4 != 0)
    {
        return r4;
    }

    r4 = usbdi_memchunk_init(&Data_11ddf4, 8, &UsbdiGlobals.Data_0xc, 1);
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


