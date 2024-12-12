

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/slog.h>
#include <sys/usbdi.h>

// CAM specific includes
#include <module.h>
#include <ntocam.h>
#include <sim.h>

#include "sim_umass.h"


static int umass_sim_args(char* options);
static int umass_sim_attach(CAM_ENTRY *centry);
static int umass_sim_detach(void);
static long umass_sim_init(SIM_HBA *hba, long path);
static long umass_sim_action(SIM_HBA *hba, CCB *ccb_ptr);
static void umass_command_scsi(SIM_UMASS_EXT*, CCB_SCSIIO*);
static int umass_bulk_cbw(SIM_UMASS_EXT*, CCB_SCSIIO*);
static void umass_command_qnx_rbc(void);
static void umass_command_ufi(void);
static void umass_command_sff8020(void);
static void umass_cb_adsc(void);
static void umass_command_rbc(void);
static void umass_command_sff8070(void);


extern int cam_configure( const MODULE_ENTRY *sim_entry, int nsims, int argc, char *argv[] );


static const MODULE_ENTRY sim_module =  //0x001067ac
{
    "umass",
    umass_sim_args,
    umass_sim_attach,
    umass_sim_detach,
};


CAM_SIM_ENTRY umass_sim_entry = //0x00108100
{
	&umass_sim_init,
	&umass_sim_action
};


static char* const cam_opts[] = //0x00107ec8
{
    "pnp",
    0
};


struct Struct_1034dc
{
    int fill_0[116]; //0
    int Data_0x1d0; //0x1d0;
};


struct
{
#if 0
    int Data_0; //0
    SIM_HBA* Data_4; //4
#else
    TAILQ_HEAD(,_sim_hba) hlist; // linked list of hba's
#endif
    int Data_8; //8
    int Data_0xc; //0xc
    int fill_0x10; //0x10
    char* Data_0x14; //0x14
    int Data_0x18; //0x18
    int Data_0x1c; //0x1c
    uint32_t Data_0x20; //0x20
    int Data_0x24; //0x24
    int Data_0x28; //0x28
    uint32_t Data_0x2c; //0x2c
    struct usbd_connection* Data_0x30; //0x30 = 1081f4

} umass_ctrl; //0x001081c4



/* 0x001034dc - todo */
int umass_slogf(struct Struct_1034dc* r0, int opcode, int severity, int verbosity, 
        const char* fmt, ...)
{
    va_list arglist;
    int r2 = (r0 != NULL)? r0->Data_0x1d0: umass_ctrl.Data_0xc;

    if (verbosity <= r2)
    {
        va_start(arglist, fmt);

        vfprintf(stderr, fmt, arglist);
        fputc(0x0a, stderr);
    }
    else if (verbosity > 4)
    {
        return 0;
    }

    va_start(arglist, fmt);
    
    return vslogf(opcode, severity, fmt, arglist);
}


char* umass_module_args(int argc/**/, char *argv/**/[], char* c)
{
#if 1
    fprintf(stderr, "umass_module_args: TODO!!!\n");
#endif

    return NULL;
}


/* 0x00103678 - todo */
int umass_check_module_args(int argc/**/, char *argv/**/[])
{
#if 1
    fprintf(stderr, "umass_check_module_args: TODO!!!\n");
#endif

    char* fp_0x24;
    char* fp_0x28;
    void* r8;

    fp_0x24 = r8 = umass_module_args(argc, argv, "cam");

    //->loc_1036d4
    while ((fp_0x24 != NULL) && (fp_0x24[0] != 0))
    {
        //loc_1036ac
        int r0 = getsubopt(&fp_0x24, cam_opts, &fp_0x28);
        if (r0 != -1)
        {
            if (r0 == 0)
            {
                umass_ctrl.Data_8 |= 0x100;
            }
        }
        //loc_1036d4
    }
    //loc_1036ec
    if (r8 != NULL)
    {
        free(r8);
    }    

    return 0;
}



/* 0x00103710 - todo */
int main(int argc/*r6*/, char *argv/*r7*/[])
{
    umass_slogf(NULL, 0x38400013, 2, 1, "%s %d.%02d%c (%s %s)",
        "devb-umass", 1, 0, 'A', "Jul  9 2010", "13:54:46");

#if 0
    umass_ctrl.Data_0 = 0;
    umass_ctrl.Data_4 = &umass_ctrl;
#else
    TAILQ_INIT(&umass_ctrl.hlist);
#endif

    umass_ctrl.Data_0x1c = 60;
    umass_ctrl.Data_0x18 = 0x15;
    umass_ctrl.Data_8 = 0x204;
    umass_ctrl.Data_0x20 = 0x80;
    umass_ctrl.Data_0x24 = 0;

    umass_check_module_args(argc, argv);

    return cam_configure(&sim_module, 1, argc, argv);
}


/* 0x00104918 - todo */
SIM_HBA* umass_alloc_hba(void)
{
#if 0
    fprintf(stderr, "umass_alloc_hba: TODO!!!\n");
#endif

    SIM_HBA* hba; //r4
    SIM_UMASS_EXT* ext; //r5;

    if ((hba = sim_alloc_hba(sizeof(SIM_UMASS_EXT))) == NULL)
    {
        return NULL;
    }

    ext = (SIM_UMASS_EXT*) hba->ext; 
    hba->verbosity = umass_ctrl.Data_0xc;
    hba->rst_settle = 0;
    hba->timeout = 10;
    ext->Data_0x14 = 0;
    ext->Data_0x18 = 0;

    memset(&ext->Data_0x1c.Data_4, 0xffffffff, 0x24);

    if (umass_ctrl.Data_8 & 0x08)
    {
        ext->Data_0x1c.Data_0x2c |= 0x800;
    }

    if (pthread_mutex_init(&ext->Data_8, 0) == -1)
    {
        free(hba->ext);
        free(hba);
        return NULL;
    }

    pthread_sleepon_lock();

#if 0
    hba->hlink.tqe_next = NULL;
    hba->hlink.tqe_prev = umass_ctrl.Data_4;
    umass_ctrl.Data_4->hlink.tqe_next = hba;
    umass_ctrl.Data_4 = hba;
#else
    // add hba to drivers hba list
    TAILQ_INSERT_TAIL(&umass_ctrl.hlist, hba, hlink);
#endif
    umass_ctrl.Data_0x28++;

    pthread_sleepon_unlock();

    return hba;
}


int umass_free_hba(SIM_HBA* hba)
{
#if 1
    fprintf(stderr, "umass_free_hba: TODO!!!\n");
#endif

    return 0;
}



/* 0x00104dd0 - todo */
static int umass_sim_args(char *options/*fp_0x30*/)
{
#if 1
    fprintf(stderr, "umass_sim_args: TODO!!!\n");
#endif

    static char* const opts[] = //0x00108108
    {
        "debug",
        "path",
        "wait",
        "busno",
        "devno",
        "maxio",
        "priority",
        "cmdset",
        "csw_ignore",
        "iface",
        "ign_remove",
        "config",
        "maxsg",
        "verbose",
        "chain", 
        0
    };

    char* fp_0x2c;

    if (options[0] == 0)
    {
        //0x00104df0
        if (umass_ctrl.Data_0x28 == 0)
        {
            //0x00104e00
            umass_ctrl.Data_8 |= 0x01;

            return 0; //->loc_105314
        }
        //loc_105310
    }
    else
    {
        //loc_104e18
        SIM_HBA* r7;

        if (((umass_ctrl.Data_8 & 0x01) == 0) &&
            ((r7 = umass_alloc_hba()) != NULL))
        {
            //0x00104e34
            SIM_UMASS_EXT* r8 = (SIM_UMASS_EXT*) r7->ext;
            int sl = 0;
            //r5 = opts;
            //r6 = umass_ctrl;
            //sb = "device";
            //->loc_10524c
            while (options[0] != '\0')
            {
                //loc_104e4c
                int r0 = getsubopt(&options, opts, &fp_0x2c);
                if (r0 == -1)
                {
                    //0x00104e64
                    sim_drvr_options(r7, fp_0x2c);
                    //->loc_10524c
                    continue;
                }
                //loc_104e74
                switch (r0)
                {
                    case 0: //"debug"
                        //loc_104ebc

                        break;

                    //TODO!!!

                    case 7: //"cmdset"
                        //loc_1050a0

                        break;

                    case 13: //"verbose"
                        //loc_1051d0
                        if ((fp_0x2c != NULL) && (fp_0x2c[0] != 0))
                        {
                            umass_ctrl.Data_0xc = strtoul(fp_0x2c, 0, 0);
                        }
                        //->loc_10524c
                        break;

                    default:
                        //->loc_10524c
                        break;
                } //switch (r0)
            } //while (options[0] != 0)
            //0x0010525c
            if (umass_ctrl.Data_8 & 0x100)
            {
                //0x0010526c
#if 1
                fprintf(stderr, "umass_sim_attach: 0x0010526c: TODO!!!\n");
#endif
                //TODO!!!
            }
            //loc_1052a0
            if ((r7->cfg.Device_ID.DevID == 0) || 
                (r8->Data_0x1c.Data_4.devno == 0))
            {
                //loc_1052b8
                if (umass_ctrl.Data_0x28 == 1)
                {
                    //0x001052c8
                    umass_ctrl.Data_8 |= 0x01;
                    if (r8->Data_0x1c.Data_0x2c & 0x800)
                    {
                        umass_ctrl.Data_8 |= 0x08;
                    }
                    if (sl != 0)
                    {
                        umass_ctrl.Data_0x24 = r8->Data_0x14;
                    }

                    umass_free_hba(r7);

                    return 0;
                }
                //loc_105310
            }
            //loc_105310
        }
        else
        {
            //loc_105308
            return 1;
        }
    }
    //loc_105310
    return 0;
}


static void umass_removal(struct usbd_connection* a, usbd_device_instance_t* instance)
{
#if 1
    fprintf(stderr, "umass_removal: TODO!!!\n");
#endif


}


static void umass_insertion(struct usbd_connection* a, usbd_device_instance_t* instance)
{
#if 1
    fprintf(stderr, "umass_insertion: TODO!!!\n");
#endif


}



int umass_preverify(usbd_device_ident_t* a)
{
#if 1
    fprintf(stderr, "umass_preverify: TODO!!!\n");
#endif


    return 0;
}


static const struct _devices
{
    usbd_device_ident_t ident; //0
    int Data_0x14; //0x14
    int Data_0x18; //0x18
    int Data_0x1c; //0x1c
    void (*Data_0x20)(); //0x20
    void (*Data_0x24)(); //0x24
    //0x28
} 
umass_devices[] = 
{
    /*vendor,device,dclass,subclass,protocol*/
    {{0xf19, 0x105,  0x8,   0x6,     0x50}, 0x6, 0x50, 0x800, umass_command_scsi, umass_bulk_cbw},
    {{0x4e6, 0x325,  0x8,   0x6,     0x50}, 0x6, 0x50, 0x200, umass_command_scsi, umass_bulk_cbw},
    {{0x781, 0x7112, 0x8,   0x6,     0x50}, 0x6, 0x50, 0x800, umass_command_scsi, umass_bulk_cbw},
    {{0x781, 0x7113, 0x8,   0x6,     0x50}, 0x6, 0x50, 0x800, umass_command_scsi, umass_bulk_cbw},
    {{0x781, 0x7114, 0x8,   0x6,     0x50}, 0x6, 0x50, 0x800, umass_command_scsi, umass_bulk_cbw},
    {{0x781, 0x7103, 0x8,   0x6,     0x50}, 0x6, 0x50, 0x800, umass_command_scsi, umass_bulk_cbw},
    {{0x781, 0x8181, 0x8,   0x6,     0x50}, 0x6, 0x50, 0x800, umass_command_scsi, umass_bulk_cbw},
    {{0x8ec, 0x12,   0x8,   0x6,     0x50}, 0x6, 0x50, 0x0, umass_command_qnx_rbc, umass_bulk_cbw},
    {{0x90c, 0x1000, 0x8,   0x6,     0x50}, 0x6, 0x50, 0x0, umass_command_qnx_rbc, umass_bulk_cbw},
    {{0x54c, 0x2e,   0x8,   0xff,    0x1 }, 0x4, 0x1, 0x0, umass_command_ufi, umass_cb_adsc},
    {{0x54c, 0x10,   0x8,   0xff,    0x1 }, 0x4, 0x1, 0x0, umass_command_ufi, umass_cb_adsc},
    {{0x4e6, 0x1,    0xff,  0x0,     0x0 }, 0x4, 0x1, 0x0, umass_command_ufi, umass_cb_adsc},
    {{0x644, 0x1000, 0x8,   0x2,     0x50}, 0x5, 0x1, 0x400, umass_command_sff8020, umass_bulk_cbw},
    {{0                                  }, 0, 0, 0, NULL, NULL}
};



/* 0x00103a18 - todo */
int umass_verify(SIM_HBA* sl, usbd_device_ident_t* r6)
{
#if 0
    fprintf(stderr, "umass_verify: TODO!!!\n");
#endif

    SIM_UMASS_EXT* r8 = (SIM_UMASS_EXT*) sl->ext;

    struct _devices* r4 = &umass_devices[0];
    while (r4->ident.vendor != 0)
    {
        //loc_103a48
        struct _devices* r5 = r4;

        if (memcmp(r6, &r4->ident, sizeof(usbd_device_ident_t)) == 0)
        {
            //0x00103a64
            r8->Data_0x1c.Data_0x2c |= r4->Data_0x1c;
            r8->Data_0x1c.Data_4.ident.subclass = r4->Data_0x14;
            r8->Data_0x1c.Data_4.ident.protocol = r4->Data_0x18;
            r8->Data_0x124 = r4->Data_0x20;
            r8->Data_0x128 = r4->Data_0x24;

            return 0;
        }
        //loc_103a98
        r4++;
    }
    //loc_103aa4
    if (sl->rst_settle != 0)
    {
        delay(sl->rst_settle);
    }

#if 1
    fprintf(stderr, "umass_verify: r6->dclass=%d, r6->subclass=%d, r6->protocol=0x%x\n",
        r6->dclass, r6->subclass, r6->protocol);
#endif

    if (r6->dclass == 8)
    {
        //0x00103abc
        if ((r6->subclass == 4) ||
            (r6->subclass == 2) ||
            (r6->subclass == 1) ||
            (r6->subclass == 5) ||
            (r6->subclass == 6))
        {
            //loc_103ae4
            if ((r6->protocol == 0x01) ||
                (r6->protocol == 0x50) ||
                (r6->protocol == 0x00))
            {
                //loc_103b00
                switch (r6->protocol)
                {
                    case 0x50:
                        //0x00103b10
                        r8->Data_0x128 = umass_bulk_cbw;
                        //loc_103b24
                        break;
                    
                    case 0x00:
                    case 0x01:
                        //loc_103b1c
                        r8->Data_0x128 = umass_cb_adsc;
                        //loc_103b24
                        break;

                    default:
                        return 1;
                }
                //loc_103b24
                switch (r6->subclass)
                {
                    case 1:
                        //loc_103b50
                        r8->Data_0x124 = umass_command_rbc;
                        return 0;
                        break;

                    case 2:
                        //loc_103b60
                        r8->Data_0x124 = umass_command_sff8020;
                        return 0;
                        break;

                    case 4:
                        //loc_103b70
                        r8->Data_0x124 = umass_command_ufi;
                        return 0;
                        break;

                    case 5:
                        //loc_103b80
                        r8->Data_0x124 = umass_command_sff8070;
                        return 0;
                        break;

                    case 6:
                        //loc_103b90
                        r8->Data_0x124 = umass_command_scsi;
                        return 0;
                        break;
                }
            }
            //loc_103ba0
        }
        //loc_103ba0
    }
    //loc_103ba0
    return 1;
}


/* 0x0010416c - todo */
int umass_parse_descriptors(struct Struct_10416c* r4_)
{
#if 0
    fprintf(stderr, "umass_parse_descriptors: TODO!!!\n");
#endif

    struct usbd_desc_node* fp_0x2c; //fp_0x2c
    struct usbd_desc_node* fp_0x30; //fp_0x30

    usbd_interface_descriptor_t* r0;

    r0 = usbd_interface_descriptor(r4_->Data_0x28,
        r4_->Data_4.config, r4_->Data_4.iface, r4_->Data_4.alternate, &fp_0x2c);
    if (r0 != NULL)
    {
        //0x001041a4
        int sb = (r0->bInterfaceProtocol > 1)? 0x07: 0x0f;
        //fp_0x34 = &r4_->Data_0xd4;
        //fp_0x38 = &r4_->Data_0xd8;
        //fp_0x44 = &r4_->Data_0xdc;
        //fp_0x48 = &r4_->Data_0xe0;
        int sl = 0;
        int r5 = 0;
        //r7 = &fp_0x30
        //r8 = 5;
        //fp_0x3c = sb & 0x02;
        //fp_0x40 = sb & 0x08;
        //r6 = r4_;
        //->loc_1042d8
        usbd_descriptors_t* r4;
        while ((r4 = usbd_parse_descriptors(r4_->Data_0x28,
                fp_0x2c, USB_DESC_ENDPOINT/*r8*/, 
                r5, &fp_0x30/*r7*/)) != 0)
        {
            //loc_1041fc
#if 1
            fprintf(stderr, "umass_parse_descriptors: r5=%d, bmAttributes=0x%x, bEndpointAddress=0x%x, wMaxPacketSize=%d\n",
                r5, r4->endpoint.bmAttributes,
                r4->endpoint.bEndpointAddress,
                r4->endpoint.wMaxPacketSize);
#endif

            switch (r4->endpoint.bmAttributes)
            {
                case 0:
                    //0x00104218: Control
                    if (usbd_open_pipe(r4_->Data_0x28, r4, 
                            &r4_->Data_0xd4/*fp_0x34*/) == 0)
                    {
                        sl |= 0x01;
                    }
                    //->loc_1042d4
                    break;

                case 2:
                    //loc_104234: Bulk
                    {
                        int r3 = r4->endpoint.bEndpointAddress & 0x80;
                        switch (r3)
                        {
                            case 0:
                                //loc_10424c
                                if (usbd_open_pipe(r4_->Data_0x28, r4, 
                                        &r4_->Data_0xd8/*fp_0x38*/) == 0)
                                {
                                    r4_->Data_0xe8 = r4->endpoint.wMaxPacketSize;
                                    sl |= 0x04;
                                }
                                //->loc_1042d4
                                break;

                            case 0x80:
                                //loc_104274
                                if (/*fp_0x3c*/(sb & 0x02) != 0)
                                {
                                    if (usbd_open_pipe(r4_->Data_0x28, r4, 
                                            &r4_->Data_0xdc/*fp_0x44*/) == 0)
                                    {
                                        sl |= 0x02;
                                    }
                                }
                                //loc_1042d4
                                break;

                            default:
                                //loc_1042d4
                                break;
                        }
                    }
                    break;

                case 3:
                    //loc_10429c
                    if ((r4->endpoint.bEndpointAddress & 0x80) && 
                        ((sb & 0x08) != 0))
                    {
                        //0x001042b4
                        if (usbd_open_pipe(r4_->Data_0x28, r4, 
                                &r4_->Data_0xe0/*fp_0x48*/) == 0)
                        {
                            sl |= 0x08;
                            r4_->Data_0xec = r4->endpoint.wMaxPacketSize;
                        }
                    }
                    //loc_1042d4
                    break;

                default:
                    //loc_1042d4
                    break;
            }
            r5++;
            //loc_1042d8
        } //while ((r4 = usbd_parse_descriptors...
        //0x001042f8
        if (sb == sl)
        {
            //->loc_104304
            return 0;
        }
    }
    //loc_104300
    return 0x13;
}


/* 0x0010430c - todo */
int umass_init_mem(struct Struct_10416c* r4)
{
#if 1
    fprintf(stderr, "umass_init_mem: r4->Data_0x2c=0x%x\n", r4->Data_0x2c);
#endif

    r4->Data_0xe4 = usbd_alloc(0x10);
    if (r4->Data_0xe4 == NULL)
    {
        return 12;
    }
    //loc_104338
    r4->Data_0xf4 = usbd_alloc_urb(NULL/*link*/);
    if (r4->Data_0xf4 == NULL)
    {
        goto loc_104460;
    }

    r4->Data_0xf0 = usbd_alloc_urb(NULL);
    if (r4->Data_0xf0 == NULL)
    {
        goto loc_104458;
    }

    r4->Data_0xf8 = usbd_alloc_urb(NULL);
    if (r4->Data_0xf8 == NULL)
    {
        goto loc_104450;
    }

    r4->Data_0xfc = usbd_alloc_urb((r4->Data_0x2c & 0x2000)? 
        r4->Data_0xf8: NULL);
    if (r4->Data_0xfc == NULL)
    {
        goto loc_104448;
    }

    r4->Data_0x100 = usbd_alloc_urb((r4->Data_0x2c & 0x2000)? 
        r4->Data_0xfc: NULL);
    if (r4->Data_0x100 == NULL)
    {
        goto loc_104440;
    }

    r4->Data_0xcc = usbd_alloc(0x10);
    if (r4->Data_0xcc == NULL)
    {
        goto loc_104438;
    }

    r4->Data_0xd0 = usbd_alloc(0x20);
    if (r4->Data_0xd0 == NULL)
    {
        goto loc_104430;
    }

    r4->Data_0xc8 = usbd_alloc(0x14);
    if (r4->Data_0xc8 == NULL)
    {
        goto loc_104428;
    }

    if (r4->Data_0x2c & 0x1000)
    {
        //0x001043fc
        if (usbd_alloc_sg_list(umass_ctrl.Data_0x20, &r4->Data_0x104) != 0)
        {
            //0x00104414
            r4->Data_0x2c &= ~0x1000;

            return 0;
        }
        //loc_104470
    }
    //loc_104470
    goto loc_104470;

loc_104428:
    usbd_free(r4->Data_0xd0);

loc_104430:
    usbd_free(r4->Data_0xcc);

loc_104438:
    usbd_free_urb(r4->Data_0x100);

loc_104440:
    usbd_free_urb(r4->Data_0xfc);

loc_104448:
    usbd_free_urb(r4->Data_0xf8);

loc_104450:
    usbd_free_urb(r4->Data_0xf0);

loc_104458:
    usbd_free_urb(r4->Data_0xf4);

loc_104460:
    usbd_free(r4->Data_0xe4);
    return 12;

loc_104470:
    return 0;
}


/* 0x001034a4 - complete */
int umass_io(struct usbd_urb* urb, struct usbd_pipe* pipe, 
        void (*func)(struct usbd_urb *, struct usbd_pipe *, void *), 
        struct Struct_10416c* d, uint32_t timeout)
{
#if 0
    fprintf(stderr, "umass_io: TODO!!!\n");
#endif

    if (usbd_io(urb, pipe, func, d/*handle*/, timeout) != 0)
    {
        d->Data_0x2c &= ~0x01;
        return 0x11;
    }

    return 0;
}


/* 0x00104024 - complete */
int umass_get_max_luns(struct Struct_10416c* r4)
{
#if 0
    fprintf(stderr, "umass_get_max_luns: TODO!!!\n");
#endif

    SIM_HBA* r3 = r4->Data_0;
    SIM_UMASS_EXT* r7 = (SIM_UMASS_EXT*) r3->ext;

    uint8_t* buf/*r5*/ = usbd_alloc(1);
    if (buf == NULL)
    {
        return 12;
    }

    usbd_setup_vendor(r4->Data_0xf4, 0x1/*flags*/, 
        0xfe/*request*/, 0x21/*rtype*/, 
        0/*r6*//*value*/, 
        r4->Data_4.iface/*index*/, buf/*addr*/, 1/*len*/);

    int r6 = umass_io(r4->Data_0xf4, r4->Data_0xd4, 0/*r6*/, r4, 4000);
    if (r6 == 0)
    {
        //0x001040a0
        uint32_t fp_0x20; //fp_0x20
        uint32_t fp_0x24; //fp_0x24

        usbd_urb_status(r4->Data_0xf4, &fp_0x24/*status*/, &fp_0x20/*length*/);

#if 1
        fprintf(stderr, "umass_get_max_luns: fp_0x24=0x%x, fp_0x20=%d, buf[0]=%d\n",
            fp_0x24, fp_0x20, buf[0]);
#endif

        if ((fp_0x24 & 0xff000000) == 0x1000000)
        {
            //0x001040c0
            if (fp_0x20 != 0)
            {
                r7->Data_0x18 = buf[0] & 0x0f;
            }
        }
        //loc_1040d4
    }
    //loc_1040d4
    usbd_free(buf);
    //loc_1040dc
    return r6;
}



/* 0x001040e8 - complete */
int umass_configure(struct Struct_10416c* r4)
{
#if 0
    fprintf(stderr, "umass_configure: TODO!!!\n");
#endif

    SIM_HBA* r3 = r4->Data_0;
    SIM_UMASS_EXT* r5 = (SIM_UMASS_EXT*) r3->ext;

    r4->bData_0x3e = 1;
    r4->bData_0x42 = 0;
    r4->Data_0x44 = 0x200460;
    r4->Data_0x5c = 0x12;
    r4->Data_0x84 = 0;
    r4->bData_0x65 = 6;
    r4->bData_0x74 = 3;
    r4->bData_0x78 = 0x12;
    r4->Data_0x58 = usbd_mphys(r4->Data_0xc8);

    if (r5->Data_0x1c.Data_4.ident.protocol == 0x50)
    {
        if ((r4->Data_0x2c & 0x100) == 0)
        {
            umass_get_max_luns(r4);
        }
    }
    //loc_104160
    return 0;
}


int umass_free_mem(SIM_HBA** a)
{
#if 1
    fprintf(stderr, "umass_free_mem: TODO!!!\n");
#endif

    return 0;
}


/* 0x00104548 - todo */
int umass_attach(SIM_HBA* r4, struct usbd_connection* r7, usbd_device_instance_t* r5)
{
#if 0
    fprintf(stderr, "umass_attach: TODO!!!\n");
#endif

    struct usbd_device* fp_0x20; //fp_0x20
    usbd_hcd_info_t fp_0x44; //fp_0x44 -0x24 = 0x20

    SIM_UMASS_EXT* r6 = (SIM_UMASS_EXT*) r4->ext;

    if (usbd_attach(r7, r5, 4, &fp_0x20) != 0)
    {
        return 1;
    }

    SIM_HBA** r0 = usbd_device_extra(fp_0x20);
    *r0 = r4;
    r6->Data_0x1c.Data_0 = r4;
    r6->Data_0x1c.Data_0x28 = fp_0x20;
    r6->Data_0x1c.Data_4 = *r5;

    if (umass_verify(r4, &r5->ident) != 0)
    {
        usbd_detach(fp_0x20);
        return 1; //->loc_104708
    }
    //loc_1045e4
    struct Struct_10416c* r4_ = &r6->Data_0x1c;
    if (umass_parse_descriptors(r4_) == 0)
    {
        //0x001045f8
        usbd_hcd_ext_info(r7, r5->path, &fp_0x44);

#if 1
        fprintf(stderr, "umass_attach: fp_0x44.cap=0x%x, USBD_HCD_CAP_BULK_SG=%d, fp_0x44.max_td_io=%d\n",
            fp_0x44.capabilities,
            (fp_0x44.capabilities & USBD_HCD_CAP_BULK_SG)? 1: 0, 
            fp_0x44.max_td_io);
#endif

        if (fp_0x44.capabilities & USBD_HCD_CAP_BULK_SG/*0x200*/)
        {
            //0x00104614
            r6->Data_0x1c.Data_0x2c |= 0x1000;

            if (r6->Data_0x14 == 0)
            {
                //0x0010462c
                if (umass_ctrl.Data_0x24 != 0)
                {
                    r6->Data_0x14 = umass_ctrl.Data_0x24;
                    //->loc_1046a0
                }
                else
                {
                    //0x00104640
                    if ((fp_0x44.max_td_io != 0) && 
                        (umass_ctrl.Data_0x20 > 1))
                    {
                        r6->Data_0x14 = 0x20000;
                        //->loc_1046a0
                    }
                    else
                    {
                        //loc_104664
                        r6->Data_0x14 = 0x1000;
                        //->loc_1046a0
                    }
                }
            } //if (r6->Data_0x14 == 0)
            //loc_1046a0
        } //if (fp_0x44.capabilities & USBD_HCD_CAP_BULK_SG)
        else
        {
            //loc_104670
            if (r6->Data_0x14 == 0)
            {
                //0x0010467c
                if (umass_ctrl.Data_0x24 != 0)
                {
                    r6->Data_0x14 = umass_ctrl.Data_0x24;
                    //->loc_1046a0
                }
                else
                {
                    //0x00104690
                    r6->Data_0x14 = (fp_0x44.max_td_io != 0)?
                        fp_0x44.max_td_io: 0x1000;
                }
            } //if (r6->Data_0x14 == 0)
            //loc_1046a0
        }
        //loc_1046a0
#if 0
        fprintf(stderr, "umass_attach: r6->Data_0x14=%d\n",
            r6->Data_0x14);
#endif

#if 1
        fprintf(stderr, "umass_attach: USBD_HCD_CAP_CHAINED_URB=%d, umass_ctrl.Data_8=0x%x\n",
            (fp_0x44.capabilities & USBD_HCD_CAP_CHAINED_URB)? 1: 0, 
            umass_ctrl.Data_8);
#endif

        if (fp_0x44.capabilities & USBD_HCD_CAP_CHAINED_URB) //0x1000)
        {
            //0x001046ac
            if (umass_ctrl.Data_8 & 0x200)
            {
#if 0
                r6->Data_0x1c.Data_0x2c |= 0x2000;   
#endif
            }
        }
        //loc_1046c4
        if (umass_init_mem(r4_) == 0)
        {
            if (umass_configure(r4_) == 0)
            {
                //0x001046e4
                r6->Data_0x1c.Data_0x2c |= 0x01;
                //->loc_104708
                return 0;
            }
            //loc_1046f4
            umass_free_mem(r4_);
        }
        //loc_1046fc
    } //if (umass_parse_descriptors(r4_) == 0)
    //loc_1046fc
    usbd_detach(fp_0x20);

    return 1;
}


int umass_detach(int* a)
{
#if 1
    fprintf(stderr, "umass_detach: TODO!!!\n");
#endif

    return 0;
}


int umass_validate_cmd(SIM_UMASS_EXT* a)
{
#if 1
    fprintf(stderr, "umass_validate_cmd: TODO!!!\n");
#endif

    return 0;
}


/* 0x001033a4 - complete */
int umass_scsi_io(SIM_HBA* r0, CCB_SCSIIO* r5)
{
#if 0
    fprintf(stderr, "umass_scsi_io\n");
#endif

    SIM_UMASS_EXT* r4 = (SIM_UMASS_EXT*) r0->ext;

    if (umass_validate_cmd(r4) == 0)
    {
        (r4->Data_0x124)(r4, r5);
    }

    return 0;
}


int umass_reset_bus(SIM_HBA* a, CCB_SCSIIO* b)
{
#if 1
    fprintf(stderr, "umass_reset_bus: TODO!!!\n");
#endif

    return 0;
}


int umass_reset_dev(SIM_HBA* a, CCB_SCSIIO* b)
{
#if 1
    fprintf(stderr, "umass_reset_dev: TODO!!!\n");
#endif

    return 0;
}


int umass_ccb_abort(SIM_HBA* a, CCB_SCSIIO* b)
{
#if 1
    fprintf(stderr, "umass_ccb_abort: TODO!!!\n");
#endif

    return 0;
}


int umass_term_io(SIM_HBA* a, CCB_SCSIIO* b)
{
#if 1
    fprintf(stderr, "umass_term_io: TODO!!!\n");
#endif

    return 0;
}


int umass_devctl(SIM_HBA* a, CCB_SCSIIO* b)
{
#if 1
    fprintf(stderr, "umass_devctl: TODO!!!\n");
#endif

    return 0;
}


/* 0x00102f40 - todo */
void umass_start_ccb(SIM_HBA* r7)
{
#if 0
    fprintf(stderr, "umass_start_ccb\n");
#endif

    SIM_UMASS_EXT* r4 = (SIM_UMASS_EXT*) r7->ext;
//    int r8 = &r4->Data_0xc;

//    void* sl = __tls();
    //fp_0x2c = &r4->Data_8;
    //r6 = 0;
    //sb = 0xffff;
    while (1)
    {
        //loc_102f74
#if 0
        if (cmpxchg(r8, 0/*r6*/, sl->Data_0x1c) != 0)
        {
            SyncMutexLock_r(&r4->Data_8);
        }
#endif
        __mutex_lock(&r4->Data_8);

        if ((r4->Data_0x10 != NULL) && 
            ((simq_ccb_state(r4->Data_0x10, 0xffff/*sb*/) & 0x8000) == 0))
        {
            //0x00102fac
            __mutex_unlock(&r4->Data_8);
            return;
        }
        //loc_102fec
        CCB_SCSIIO* r5 = r4->Data_0x10 = simq_ccb_dequeue(r7->simq);
        if (r4->Data_0x10 == NULL)
        {
            //0x00103004
            __mutex_unlock(&r4->Data_8);
            return;
        }
        //loc_103044
        __mutex_unlock(&r4->Data_8);
        //loc_10307c
        if ((r4->Data_0x1c.Data_0x2c & 0x01) == 0)
        {
            //0x00103088
            r4->Data_0x10 = 0;
            r5->cam_ch.cam_status = 0x11;

            simq_post_ccb(r7->simq, r5);
            return;
        }
        //loc_1030a8
#if 1
        fprintf(stderr, "umass_start_ccb: r5->cam_ch.cam_func_code=0x%x\n",
                r5->cam_ch.cam_func_code);
#endif
        int r0;
        switch (r5->cam_ch.cam_func_code)
        {
            case XPT_SCSI_IO: //0x01:
                //loc_1030e8
                r0 = umass_scsi_io(r7, r5);
                break;

            case XPT_RESET_BUS: //0x11:
                //loc_1030f8
                r0 = umass_reset_bus(r7, r5);
                break;

            case XPT_RESET_DEV: //0x12:
                //loc_103108
                r0 = umass_reset_dev(r7, r5);
                break;

            case XPT_ABORT: //0x10:
                //loc_103118
                r0 = umass_ccb_abort(r7, r5);
                break;

            case XPT_TERM_IO: //0x13:
                //loc_103128
                r0 = umass_term_io(r7, r5);
                break;

            case XPT_DEVCTL: //0x81:
                //loc_103138
                r0 = umass_devctl(r7, r5);
                break;

            default:
                //loc_1030e0
                r0 = 1;
                //->loc_103144
                break;
        }
        //loc_103144
        if (r0 != 0)
        {
            //0x0010314c
            r4->Data_0x10 = NULL/*r6*/;
            r5->cam_ch.cam_status = r0 & 0xff;

            simq_post_ccb(r7->simq, r5);
        }
        //loc_103164
        if (r4->Data_0x10 != NULL)
        {
            break;
        }
    } //while (1)
    //loc_103170
}



/* 0x0010317c - todo */
void umass_event_handler(SIM_HBA* r5)
{
#if 0
    fprintf(stderr, "umass_event_handler: TODO!!!\n");
#endif

    SIM_UMASS_EXT* r4 = (SIM_UMASS_EXT*) r5->ext;

    struct
    {
        int fill_0; //0
        int8_t bData_4; //4
        int fill_8[2]; //8
        //16?
    } fp_0x34;
    iov_t fp_0x3c; 

    SETIOV(&fp_0x3c, &fp_0x34, 16);

    //r6 = &fp_0x3c;
    //r7 = 1;
    //r8 = 0;
    //sl = 0x30;

    while (1)
    {
        //loc_1031b4
        int r0 = MsgReceivev(r5->chid, &fp_0x3c, 1, 0);
        if (r0 == -1)
        {
            //->loc_1031b4
            continue;
        }
        //0x001031d0
        switch (fp_0x34.bData_4)
        {
            case 1:
                //loc_1031ec
                umass_start_ccb(r5);
                //->loc_103210
                break;

            case 3:
                //loc_103210
                break;

            default:
                //loc_1031f8
                if (r0 != 0)
                {
                    MsgReplyv(r0, 0x30, &fp_0x3c, 1);
                }
                //loc_103210
                break;
        }
        //loc_103210
        if (r4->Data_0x10 == 0)
        {
            umass_start_ccb(r5);
        }
        //->loc_1031b4
    }
}


/* 0x00103228 - todo */
void* umass_driver_thread(void* a)
{
#if 0
    fprintf(stderr, "umass_driver_thread: TODO!!!\n");
#endif

    umass_event_handler(a);

    return NULL;
}


void umass_internal_cbf()
{
#if 1
    fprintf(stderr, "umass_internal_cbf: TODO!!!\n");
#endif

}


/* 0x00103bcc - todo */
int umass_inquiry(SIM_HBA* r5)
{
#if 1
    fprintf(stderr, "umass_inquiry: TODO!!!\n");
#endif

    SIM_UMASS_EXT* sl = (SIM_UMASS_EXT*) r5->ext;

    CCB_SCSIIO* r4 = xpt_ccb_alloc();
    if (r4 == NULL)
    {
        return 1; //loc_103d80
    }

    void* r8 = mmap(NULL, 0x60, 0xb00, 0xb0002, -1, 0);
    if (r8 == -1)
    {
        xpt_ccb_free(r4);

        return 1;
    }
    //loc_103c30
    memset(r4, 0, sizeof(CCB_SCSIIO));

    r4->cam_cbfcnp = umass_internal_cbf;
    r4->cam_pdrv_ptr = r5;
    r4->cam_ch.cam_func_code = 1;
    r4->cam_timeout = r5->timeout;
    r4->cam_dxfer_len = 0x60;
    r4->cam_ch.cam_flags = 0x200440;
    r4->cam_data.cam_data_ptr = mphys(r8);
    r4->cam_sense_ptr = sl->Data_0x1c.Data_0xc8;
    r4->cam_sense_len = 0x14;
    r4->cam_cdb_len = 6;
    r4->cam_cdb_io.cam_cdb_bytes[0] = 0x12;
    r4->cam_cdb_io.cam_cdb_bytes[4] = 0x60; //TODO!!!
    int r6; // = 0;
    //r7 = 0;
    //sb = 0x64;
    for (r6 = 0; r6 < 5; r6++)
    {
        //loc_103cac
        r4->cam_scsi_status = 0; //r7
        r4->cam_ch.cam_status = 0; //r7

        simq_ccb_enqueue(r5->simq, r4);
        umass_start_ccb(r5);

        pthread_sleepon_lock();

        while ((r4->cam_ch.cam_status & 0x3f) == 0)
        {
            //loc_103cd8
            pthread_sleepon_wait(r4);
        }
        //loc_103cec
        pthread_sleepon_unlock();

        if ((r4->cam_ch.cam_status & 0x3f) == 1)
        {
            //->loc_103d2c
            break;
        }
        //0x00103d00
        if (r4->cam_ch.cam_status & 0x80)
        {
            //0x00103d0c
            delay(100/*sb*/);
            //->loc_103d20
        }
        else
        {
            //loc_103d18
            if (r6 > 1)
            {
                //->loc_103d2c
                break;
            }
        }
        //loc_103d20
    } //for (r6 = 0; r6 < 5; r6++)
    //loc_103d2c
    int res;
    if ((r4->cam_ch.cam_status & 0x3f) != 1)
    {
        res = 1;
        //->loc_103d6c
    }
    else
    {
        //0x00103d40
        if ((((uint8_t*)r8)[0] == 0) &&
            (sl->Data_0x1c.Data_4.ident.subclass == 6))
        {
            sl->Data_0x124 = umass_command_qnx_rbc;
            res = 0;
            //->loc_103d6c
        }
        else
        {
            //loc_103d68
            res = 0;
        }
    }
    //loc_103d6c
    xpt_ccb_free(r4);
    munmap(r8, 0x60);

    return res;
}



/* 0x00103d9c - todo */
int umass_reg(SIM_HBA* hba/*r5*/)
{
#if 0
    fprintf(stderr, "umass_reg: TODO!!!\n");
#endif

    pthread_attr_t attr; //fp_0x64 -8 = 0x5c
    struct sched_param param; //fp_0x5c

    SIM_UMASS_EXT* ext/*r4*/ = (SIM_UMASS_EXT*) hba->ext;

    ext->Data_0x1c.Data_0x2c |= 0x02;

    pthread_attr_init(&attr/*r6*/);
    pthread_attr_setschedpolicy(&attr, 2);
    param.sched_priority = umass_ctrl.Data_0x18; 
    pthread_attr_setschedparam(&attr, &param);
    pthread_attr_setinheritsched(&attr, 2);
    pthread_attr_setdetachstate(&attr, 1);
    pthread_attr_setstacksize(&attr, 0x3000);
    hba->chid = ChannelCreate(0x0a);
    if (hba->chid == -1)
    {
        //->loc_103f94
        goto loc_103f94;
    }

    hba->coid = ConnectAttach(0, 0, hba->chid, 0x40000000, 0);
    if (hba->coid == -1)
    {
        //->loc_103f74
        goto loc_103f74;
    }
    //0x00103e4c

    hba->simq = simq_init(hba->coid, hba, 1, ext->Data_0x18 + 1, 2, 1, 2, 0);
    if (hba->simq == NULL)
    {
        //->loc_103f54
        goto loc_103f54;
    }
    //0x00103e84
    if (umass_ctrl.Data_8 & 0x04)
    {
        //0x00103e94
        if (umass_inquiry(hba) != 0)
        {
            ext->Data_0x1c.Data_0x2c &= ~0x02;

            return 1; //->loc_103fc0
        }
        //loc_103eb8
    }
    //loc_103eb8
    if (pthread_create(&hba->tid, &attr, umass_driver_thread, hba) != 0)
    {
        //->loc_103f2c
        goto loc_103f2c;
    }
    //0x00103ed4
    ext->Data_0x1c.Data_0x2c &= ~0x02;

    hba->pathid = xpt_bus_register(&umass_sim_entry, hba);
    if (hba->pathid > umass_ctrl.Data_0x2c)
    {
        umass_ctrl.Data_0x2c = hba->pathid;
    }

    xpt_async(0x20, hba->pathid, 0xffffffff, 0xffffffff, NULL, 0);

    return 0;

loc_103f2c:
    umass_slogf(hba, 0x38400013, 2, 4, "umass_init:  Unable to create driver thread");
    simq_dinit(hba->simq);
    //->loc_103fb0
    goto loc_103fb0;

loc_103f54:
    umass_slogf(hba, 0x38400013, 2, 4, "umass_init:  simq_init failure");
    //->loc_103fb0
    goto loc_103fb0;

loc_103f74:
    umass_slogf(hba, 0x38400013, 2, 4, "umass_init:  Unable to attach channel");
    //->loc_103fb0
    goto loc_103fb0;

loc_103f94:
    umass_slogf(hba, 0x38400013, 2, 4, "umass_init:  Unable to create channel");
    //->loc_103fb0
    goto loc_103fb0;

loc_103fb0:
    ext->Data_0x1c.Data_0x2c &= ~0x02;

    return 1;
}



/* 0x001049ec - todo */
static int umass_sim_attach(CAM_ENTRY *centry)
{
#if 1
    fprintf(stderr, "umass_sim_attach: TODO!!!\n");
#endif

    usbd_funcs_t fp_0x38 = //fp_0x38 -0x10 = 0x28
    {
        _USBDI_NFUNCS, NULL, umass_removal, NULL
    };
    usbd_device_ident_t fp_0x4c = //fp_0x4c -0x14 = 0x38
    {
        0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
    };
    usbd_connect_parm_t fp_0x7c; //fp_0x7c -0x30 = 0x4c
    struct usbd_connection* fp_0x80; //fp_0x80
    struct usbd_device* fp_0x84; //fp_0x84
    usbd_hcd_info_t fp_0xa8; //fp_0xa8 -0x24 = 0x84
    usbd_bus_topology_t fp_0x2a8; //fp_0x2a8 -0x200 = 0xa8
    int fp_0x2ac; //fp_0x2ac
    int fp_0x2b0; //fp_0x2b0

    memset(&fp_0x7c, 0, sizeof(usbd_connect_parm_t));
    fp_0x7c.vusb = 0x110;
    fp_0x7c.vusbd = USBD_VERSION; //0x101;
    fp_0x7c.funcs = &fp_0x38; //r4;
    fp_0x7c.ident = &fp_0x4c; 
    fp_0x7c.path = umass_ctrl.Data_0x14;
    fp_0x7c.connect_wait = umass_ctrl.Data_0x1c;
    fp_0x7c.evtprio = umass_ctrl.Data_0x18;

    if (fp_0x7c.path == NULL)
    {
        //0x00104a98
        fp_0x7c.path = strdup("/dev/io-usb/io-usb");
    }
    //loc_104aa4
    if (umass_ctrl.Data_8 & 0x100)
    {
        //0x00104ab4
        fp_0x38.insertion = umass_insertion;

        int r0;
        if ((r0 = usbd_connect(&fp_0x7c, &umass_ctrl.Data_0x30)) != 0)
        {
            //0x00104ad0
            umass_slogf(0, 0x38400013, 2, 4, "umass_sim_attach:  usbd_connect - %s",
                strerror(r0));
            return CAM_FAILURE;
        }
        //loc_104d9c
#if 1
        fprintf(stderr, "umass_sim_attach: loc_104d9c: TODO!!!\n");
#endif

        //TODO!!!
    }
    else
    {
        //loc_104afc
        if (umass_ctrl.Data_8 & 0x01)
        {
            umass_ctrl.Data_8 |= 0x02;
        }

        int r0;
        if ((r0 = usbd_connect(&fp_0x7c, &umass_ctrl.Data_0x30)) != 0)
        {
            //0x00104b28
            umass_slogf(0, 0x38400013, 2, 4, "umass_sim_attach:  usbd_connect - %s",
                strerror(r0));
            return 1;
        }
        //loc_104b54
        if (umass_ctrl.Data_8 & 0x01)
        {
            //0x00104b64
            fp_0x7c.funcs = NULL;

            if ((r0 = usbd_connect(&fp_0x7c, &fp_0x80)) != 0)
            {
                //0x00104b80
                umass_slogf(0, 0x38400013, 2, 4, "umass_sim_attach:  read-only usbd_connect - %s",
                    strerror(r0));
                return 1;
            }
            //loc_104bac
            SIM_HBA* r6 = umass_ctrl.hlist.tqh_first;
            
            for (fp_0x2b0 = 0; fp_0x2b0 < 10; fp_0x2b0++)
            {
                //loc_104bbc
                if (usbd_hcd_ext_info(fp_0x80, fp_0x2b0, &fp_0xa8) == 0)
                {
                    //0x00104bd4
                    fp_0x2ac = fp_0x2b0 & 0xff;
                    if (usbd_topology_ext(fp_0x80, fp_0x2b0, &fp_0x2a8) == 0)
                    {
                        //0x00104bf8
                        int sb;
                        //sb = 1;
                        //sl = 0;
                        for (sb = 1; sb < 64; sb++)
                        {
                            //loc_104c00
                            if (fp_0x2a8.ports[sb].upstream_port != 0xff)
                            {
                                int r7;
                                for (r7 = 0; r7 < 10; r7++)
                                {
                                    //loc_104c18
                                    if (r6 == NULL)
                                    {
                                        //0x00104c20
                                        r6 = umass_alloc_hba();
                                        if (r6 == NULL)
                                        {
                                            //->loc_104ce4
                                            break;
                                        }
                                    }
                                    //loc_104c2c
                                    SIM_UMASS_EXT* r5 = (SIM_UMASS_EXT*) r6->ext;

                                    memset(&r5->Data_0x1c.Data_4/*r8*/, 0xffffffff, 0x24);

                                    r5->Data_0x1c.Data_4.path = fp_0x2ac;
                                    r5->Data_0x1c.Data_4.devno = sb;
                                    r5->Data_0x1c.Data_4.iface = r7;
                                    r5->Data_0x1c.Data_4.alternate = 0;

                                    if (usbd_attach(fp_0x80, 
                                            &r5->Data_0x1c.Data_4/*r8*/,
                                            0/*sl*/,
                                            &fp_0x84) == 0)
                                    {
                                        //0x00104c78
                                        int r4 = umass_preverify(&r5->Data_0x1c.Data_4.ident);
                                        usbd_detach(fp_0x84);
                                        if (r4 == 0)
                                        {
                                            //0x00104c94
                                            if (umass_attach(r6, 
                                                    umass_ctrl.Data_0x30, 
                                                    &r5->Data_0x1c.Data_4) == 0)
                                            {
                                                //0x00104cb0
                                                if (umass_reg(r6) == 0)
                                                {
                                                    //->loc_104cd0
                                                    break;
                                                }
                                                //0x00104cc0
                                                umass_detach(&r5->Data_0x1c);
                                            }
                                            //loc_104cc8
                                        }
                                        //loc_104cc8
                                    }
                                    //loc_104cc8
                                    umass_free_hba(r6);
                                    //loc_104cd0
                                    r6 = NULL; //sl;
                                } //for (r7 = 0; r7 < 10; r7++)
                                //0x00104ce0
                            } //if (fp_0x2a8.ports[sb].upstream_port != 0xff)
                            //loc_104ce4
                        } //for (sb = 1; sb < 64; sb++)
                        //loc_104cf0
                    }
                    //loc_104cf0
                }
                //loc_104cf0
            } //for (fp_0x2b0 = 0; fp_0x2b0 < 10; fp_0x2b0++)
            //0x00104d04
            umass_ctrl.Data_8 &= ~0x02;

            usbd_disconnect(fp_0x80);

            return CAM_SUCCESS; //->loc_104da0
        }
        //loc_104d24
        if (umass_ctrl.hlist.tqh_first != NULL)
        {
            //0x00104d34
            //int r7 = 0xffff;
            //void* r8 = umass_ctrl;

//            while (1)
            {
                //loc_104d3c
#if 1
                fprintf(stderr, "umass_sim_attach: loc_104d3c: TODO!!!\n");
#endif
            }
            //loc_104d9c
        }
        //loc_104d9c
    }
    //loc_104d9c
    return CAM_SUCCESS;
}


static int umass_sim_detach(void)
{
#if 1
    fprintf(stderr, "umass_sim_detach: TODO!!!\n");
#endif

    return 0;
}


static long umass_sim_init(SIM_HBA *hba, long path)
{
#if 1
    fprintf(stderr, "umass_sim_init: TODO!!!\n");
#endif

    return 0;
}


static long umass_sim_action(SIM_HBA *hba, CCB *ccb_ptr)
{
#if 1
    fprintf(stderr, "umass_sim_action: TODO!!!\n");
#endif

    return 0;
}


/* 0x00101e78 - complete */
static void umass_command_scsi(SIM_UMASS_EXT* r3, CCB_SCSIIO* r1)
{
#if 0
    fprintf(stderr, "umass_command_scsi: TODO!!!\n");
#endif

    if (r1->cam_cdb_io.cam_cdb_bytes[0] == 0x12)
    {
        r1->cam_dxfer_len = 0x24;
        r1->cam_cdb_io.cam_cdb_bytes[4] = 0x24;
    }

    (r3->Data_0x128)(r3, r1);
}


void umass_bulk_partial_link_cbf()
{
#if 1
    fprintf(stderr, "umass_bulk_partial_link_cbf: TODO!!!\n");
#endif

}


void umass_bulk_full_link_cbf()
{
#if 1
    fprintf(stderr, "umass_bulk_full_link_cbf: TODO!!!\n");
#endif

}


void umass_bulk_data_cbf()
{
#if 1
    fprintf(stderr, "umass_bulk_data_cbf: TODO!!!\n");
#endif

}


int umass_handle_urb_error(struct Struct_10416c* a,
        CCB_SCSIIO* b, struct usbd_pipe* c, uint32_t d, uint32_t e)
{
#if 1
    fprintf(stderr, "umass_handle_urb_error: TODO!!!\n");
#endif

}


int umass_bulk_csw(struct Struct_10416c* a)
{
#if 1
    fprintf(stderr, "umass_bulk_csw: TODO!!!\n");
#endif

    return 0;
}


/* 0x00105adc - complete */
void umass_bulk_cbw_cbf(struct usbd_urb* r0, 
        struct usbd_pipe* r7, struct Struct_10416c* r4)
{
#if 1
    fprintf(stderr, "umass_bulk_cbw_cbf: TODO!!!\n");
#endif

    uint32_t fp_0x20;
    uint32_t fp_0x24;

    SIM_UMASS_EXT* r6 = (SIM_UMASS_EXT*) r4->Data_0->ext;
    CCB_SCSIIO* r5 = r6->Data_0x10;

    usbd_urb_status(r0, &fp_0x24, &fp_0x20);

    if ((fp_0x24 & 0xff000000) != 0x1000000)
    {
        umass_handle_urb_error(r4, r5, r7, fp_0x24, fp_0x20);
    }
    else
    {
        if ((r5->cam_ch.cam_flags & 0xc0) != 0xc0)
        {
            int r2 = umass_bulk_data_phase(r6, r4, r5, r4->Data_0xfc);
            if (r2 != 0)
            {
                umass_post_ccb(r4, r5, r2, 0);
            }
        }
        else
        {
            umass_bulk_csw(r4);
        }
    }

}


int umass_post_ccb(struct Struct_10416c* a, 
        CCB_SCSIIO* b, int c, int d)
{
#if 1
    fprintf(stderr, "umass_post_ccb: TODO!!!\n");
#endif

    return 0;
}


int umass_padvance(struct Struct_10416c* a)
{
#if 1
    fprintf(stderr, "umass_padvance: TODO!!!\n");
#endif

    return 0;
}


/* 0x00105430 - todo */
int umass_bulk_data_phase(SIM_UMASS_EXT * r7, 
    struct Struct_10416c* r5, 
    CCB_SCSIIO* r6, 
    struct usbd_urb* fp_0x2c)
{
#if 0
    fprintf(stderr, "umass_bulk_data_phase: TODO!!!\n");
#endif

    usbd_urb_sg_elem_t* r8 = r5->Data_0x104;
    struct
    {
        int fill_0[4]; //0
        char* Data_0x10; //0x10
        uint32_t Data_0x14; //0x14
        //???
    }* r4 = (void*) &r6->cam_sim_priv[0];

#if 1
    fprintf(stderr, "umass_bulk_data_phase: r5->Data_0x2c=0x%x, r4->Data_0x10=%p, r4->Data_0x14=%d\n", 
        r5->Data_0x2c, r4->Data_0x10, r4->Data_0x14);
#endif

    if (r5->Data_0x2c & 0x1000)
    { 
        //0x00105464
        if ((umass_padvance(r5) == 0) &&
            (r4->Data_0x14 != 0))
        {
            int sl = 0;
            int sb = 0;
            while (1)
            {
                //loc_105488
                sb++;
                r8->urb_sg_address = r4->Data_0x10;

                int r3 = (r4->Data_0x14 < r7->Data_0x14)?
                    r4->Data_0x14: r7->Data_0x14;

                r8->urb_sg_count = r3;
                
                sl += r3;
                r4->Data_0x14 -= r3;
                r4->Data_0x10 += r3;

                r8++;

                if ((sl >= r7->Data_0x14) ||
                    (sb >= umass_ctrl.Data_0x20) ||
                    (umass_padvance(r5) != 0))
                {
                    //loc_1054f4
                    usbd_setup_sg_bulk(r5->Data_0xfc, 
                        ((r6->cam_ch.cam_flags & 0x40) != 0)? 0x20005: 0x20006,
                        r5->Data_0x104, sb);

                    if ((r5->Data_0x2c & 0x2000) == 0)
                    {
                        //0x00105524
                        return umass_io(r5->Data_0xfc,
                            (r6->cam_ch.cam_flags & 0x40)?
                                r5->Data_0xdc: r5->Data_0xd8,
                            umass_bulk_data_cbf, r5,
                            r6->cam_timeout * 1000);
                        //->loc_1057c8
                    }
                    //loc_105560
                    if ((r4->Data_0x14 == 0) &&
                        (umass_padvance(r5) == 1))
                    {
                        //0x0010557c   
                        if (usbd_chain_io(r5->Data_0xfc,
                                r5->Data_0xf8,
                                (r6->cam_ch.cam_flags & 0x40)?
                                    r5->Data_0xdc: r5->Data_0xd8,
                                NULL/*func*/,
                                r5/*handle*/,
                                r6->cam_timeout * 1000) != 0)
                        {
                            //->loc_1057c4
                            return 4;
                        }
                        //->loc_105608
                        break;
                    }
                    else
                    {
                        //loc_1055c4
                        if (usbd_chain_io(r5->Data_0xfc,
                                r5->Data_0xf8,
                                (r6->cam_ch.cam_flags & 0x40)?
                                    r5->Data_0xdc: r5->Data_0xd8,
                                umass_bulk_partial_link_cbf/*func*/,
                                r5/*handle*/,
                                r6->cam_timeout * 1000) != 0)
                        {
                            //->loc_1057c4
                            return 4;
                        }
                        //loc_105608
                        break;
                    }
                }
                //->loc_105488
            } //while (1)
        }
        //loc_105608
        if (((r6->cam_ch.cam_flags & 0xc0) == 0xc0) ||
            ((r4->Data_0x14 == 0) && (umass_padvance(r5) == 1)))
        {
            //loc_105634
            usbd_setup_bulk(r5->Data_0x100, 5, r5->Data_0xcc, 0x0d);

            if (usbd_chain_io(r5->Data_0x100,
                    ((r6->cam_ch.cam_flags & 0xc0) == 0xc0)?
                        r5->Data_0xf8: r5->Data_0xfc,
                    r5->Data_0xdc,
                    umass_bulk_full_link_cbf, r5,
                    4000) != 0)
            {
                //->loc_1057c4
                return 4;
            }
            //0x00105680
            struct usbd_pipe* r1;
            if (((r6->cam_ch.cam_flags & 0x80) == 0) &&
                (r5->Data_0xf8 != fp_0x2c))
            {
                r1 = r5->Data_0xdc;
            }
            else
            {
                //loc_1056a0
                r1 = r5->Data_0xd8;
            }
            //loc_1056a4
            return umass_io(fp_0x2c, r1, 
                NULL, r5, r6->cam_timeout * 1000);
        }
        //loc_1056d0
        if (r5->Data_0xfc == fp_0x2c)
        {
            //0x001056e0
            return umass_io(r5->Data_0xfc,
                (r6->cam_ch.cam_flags & 0x80)?
                    r5->Data_0xd8: r5->Data_0xdc,
                umass_bulk_partial_link_cbf, r5,
                r6->cam_timeout * 1000);
        }
        //loc_105718
        return umass_io(fp_0x2c,
            r5->Data_0xd8,
            NULL, r5,
            r6->cam_timeout * 1000);
    }
    //loc_105748
    umass_padvance(r5);

    int r3 = (r4->Data_0x14 < r7->Data_0x14)? 
        r4->Data_0x14: r7->Data_0x14;
    r4->Data_0x14 -= r3;

    usbd_setup_bulk(r5->Data_0xfc, 
        ((r6->cam_ch.cam_flags & 0x40) != 0)? 0x20005: 0x20006,
        r4->Data_0x10, r3);

    return umass_io(r5->Data_0xfc,
        (r6->cam_ch.cam_flags & 0x40)?
            r5->Data_0xdc: r5->Data_0xd8,
        umass_bulk_data_cbf, r5,
        r6->cam_timeout * 1000);

    return 4;
}



/* 0x001057e8 - complete */
static int umass_bulk_cbw(SIM_UMASS_EXT* r6, CCB_SCSIIO* r4)
{
#if 1
    fprintf(stderr, "umass_bulk_cbw\n");
#endif

    struct Struct_10416c* r7 = &r6->Data_0x1c;
    struct 
    {
        int Data_0; //0
        CCB_SCSIIO* Data_4; //4
        int Data_8; //8
        uint8_t bData_0xc; //0xc
        uint8_t bData_0xd; //0xd
        uint8_t bData_0xe; //0xe
        uint8_t bData_0xf[IOCDBLEN]; //0xf +0x10 = 0x1f
        //0x1f???
    }* r5 = r6->Data_0x1c.Data_0xd0;

    r6->Data_0x1c.Data_0x34 = 0;

    r5->Data_0 = 0x43425355;
    r5->Data_4 = r4;
    r5->Data_8 = r4->cam_dxfer_len;
    r5->bData_0xc = ((r4->cam_ch.cam_flags & 0xc0) == 0x40)? 0x80: 0x00;
    r5->bData_0xd = r4->cam_ch.cam_target_lun;
    r5->bData_0xe = r4->cam_cdb_len;

    memcpy(&r5->bData_0xf[0], &r4->cam_cdb_io.cam_cdb_bytes[0], IOCDBLEN);

    usbd_setup_bulk(r6->Data_0x1c.Data_0xf8, 
        0x02, r5, 0x1f);

    if ((r6->Data_0x1c.Data_0x2c & 0x2000) == 0)
    {
        //0x0010587c
        int r2 = umass_io(r6->Data_0x1c.Data_0xf8, 
                r6->Data_0x1c.Data_0xd8, 
                umass_bulk_cbw_cbf, r7, 4000);
        if (r2 != 0)
        {
            //0x001058a0
            umass_post_ccb(r7, r4, r2, 0);
        }
        //loc_1058e0
    }
    else
    {
        //loc_1058b4
        int r2 = umass_bulk_data_phase(r6, r7, r4, r6->Data_0x1c.Data_0xf8);
        if (r2 != 0)
        {
            //0x001058d0
            umass_post_ccb(r7, r4, r2, 0);
        }
    }
    //loc_1058e0
    return 0;
}


static void umass_command_qnx_rbc(void)
{
#if 1
    fprintf(stderr, "umass_command_qnx_rbc: TODO!!!\n");
#endif

}



static void umass_command_ufi(void)
{
#if 1
    fprintf(stderr, "umass_command_ufi: TODO!!!\n");
#endif

}



static void umass_command_sff8020(void)
{
#if 1
    fprintf(stderr, "umass_command_sff8020: TODO!!!\n");
#endif

}


static void umass_cb_adsc(void)
{
#if 1
    fprintf(stderr, "umass_cb_adsc: TODO!!!\n");
#endif

}


static void umass_command_rbc(void)
{
#if 1
    fprintf(stderr, "umass_command_rbc: TODO!!!\n");
#endif

}


static void umass_command_sff8070(void)
{
#if 1
    fprintf(stderr, "umass_command_sff8070: TODO!!!\n");
#endif

}
