

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


static int umass_sim_args(char* options);
static int umass_sim_attach(CAM_ENTRY *centry);
static int umass_sim_detach(void);

extern int cam_configure( const MODULE_ENTRY *sim_entry, int nsims, int argc, char *argv[] );


static const MODULE_ENTRY sim_module =  //0x001067ac
{
    "umass",
    umass_sim_args,
    umass_sim_attach,
    umass_sim_detach,
};


struct Struct_1034dc
{
    int fill_0[116]; //0
    int Data_0x1d0; //0x1d0;
};


struct
{
    int Data_0; //0
    void* Data_4; //4
    int Data_8; //8
    int Data_0xc; //0xc
    int fill_0x10; //0x10
    char* Data_0x14; //0x14
    int Data_0x18; //0x18
    int Data_0x1c; //0x1c
    int Data_0x20; //0x20
    int Data_0x24; //0x24

} umass_ctrl;


struct usbd_connection *Data_1081f4; //connection; //1081f4



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



/* 0x00103678 - todo */
int umass_check_module_args(int argc/**/, char *argv/**/[])
{
#if 1
    fprintf(stderr, "umass_check_module_args: TODO!!!\n");
#endif

    return 0;
}



/* 0x00103710 - todo */
int main(int argc/*r6*/, char *argv/*r7*/[])
{
    umass_slogf(NULL, 0x38400013, 2, 1, "%s %d.%02d%c (%s %s)",
        "devb-umass", 1, 0, 'A', "Jul  9 2010", "13:54:46");

    umass_ctrl.Data_0 = 0;
    umass_ctrl.Data_4 = &umass_ctrl;
    umass_ctrl.Data_0x1c = 60;
    umass_ctrl.Data_0x18 = 0x15;
    umass_ctrl.Data_8 = 0x204;
    umass_ctrl.Data_0x20 = 0x80;
    umass_ctrl.Data_0x24 = 0;

    umass_check_module_args(argc, argv);

    return cam_configure(&sim_module, 1, argc, argv);
}



/* 0x00104dd0 - todo */
static int umass_sim_args(char *options)
{
#if 1
    fprintf(stderr, "umass_sim_args: TODO!!!\n");
#endif

    return 0;
}


static void umass_removal(struct usbd_connection* a, usbd_device_instance_t* instance)
{
#if 1
    fprintf(stderr, "umass_removal: TODO!!!\n");
#endif


}



/* 0x001049ec - todo */
static int umass_sim_attach(CAM_ENTRY *centry)
{
#if 0
    fprintf(stderr, "umass_sim_attach: TODO!!!\n");
#endif

    usbd_funcs_t fp_0x38 = //fp_0x38
    {
        _USBDI_NFUNCS, NULL, umass_removal, NULL
    };
    usbd_device_ident_t fp_0x4c = //fp_0x4c
    {
        0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
    };
    usbd_connect_parm_t fp_0x7c; //fp_0x7c

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
#if 0 //TODO!!!
        fp_0x38.Data_0x10 = umass_insertion;
#endif

        int r0;
        if ((r0 = usbd_connect(&fp_0x7c, &Data_1081f4)) != 0)
        {
            //0x00104ad0
            umass_slogf(0, 0x38400013, 2, 4, "umass_sim_attach:  usbd_connect - %s",
                strerror(r0));
            return CAM_FAILURE;
        }
        //loc_104d9c
    }
    else
    {
        //loc_104afc
        if (umass_ctrl.Data_8 & 0x01)
        {
            umass_ctrl.Data_8 |= 0x02;
        }

        int r0;
        if ((r0 = usbd_connect(&fp_0x7c, &Data_1081f4)) != 0)
        {
            //0x00104b28
            umass_slogf(0, 0x38400013, 2, 4, "umass_sim_attach:  usbd_connect - %s",
                strerror(r0));
            return 1;
        }
        //loc_104b54
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


