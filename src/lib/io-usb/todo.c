
#include <stdio.h>
#include <sys/dispatch.h>
#include <sys/iofunc.h>
#include "externs.h"


void usb_slogf()
{
    fprintf(stderr, "usb_slogf\n");

}


void sub_10a498()
{
    fprintf(stderr, "sub_10a498\n");

}


int CTRL_GetHCEntry()
{
    fprintf(stderr, "CTRL_GetHCEntry\n");

}


void CTRL_GetOptions()
{
    fprintf(stderr, "CTRL_GetOptions\n");

}


int CTRL_IsPCIDevice()
{
    fprintf(stderr, "CTRL_IsPCIDevice\n");

    return 0;
}


int CTRL_ProcessArgs()
{
    fprintf(stderr, "CTRL_ProcessArgs\n");


    return 0;
}


void stop_controllers(void)
{
    fprintf(stderr, "stop_controllers\n");

}


void usbdi_timeout_tick()
{
    fprintf(stderr, "usbdi_timeout_tick\n");

}


int usbdi_resmgr_open(resmgr_context_t *ctp, io_open_t *msg,
                      RESMGR_HANDLE_T *handle, void *extra)
{
    fprintf(stderr, "usbdi_resmgr_open\n");

}


int usbdi_io_mount(resmgr_context_t *ctp, io_mount_t *msg,
                      RESMGR_HANDLE_T *handle,
                      io_mount_extra_t *extra)
{
    fprintf(stderr, "usbdi_io_mount\n");

}


int usbdi_memchunk_init()
{
    fprintf(stderr, "usbdi_memchunk_init\n");

    return 0;
}


iofunc_ocb_t* usbdi_ocb_calloc(resmgr_context_t *ctp,
                     iofunc_attr_t *attr)
{
    fprintf(stderr, "usbdi_ocb_calloc\n");

}


void usbdi_ocb_free(iofunc_ocb_t *ocb)
{
    fprintf(stderr, "usbdi_ocb_free\n");

}


int usbdi_timeout_init(struct USB_Timer* a)
{
    fprintf(stderr, "usbdi_timeout_init\n");

    return 0;
}

int usbdi_resmgr_close()
{
    fprintf(stderr, "usbdi_resmgr_close\n");

}


int usbdi_resmgr_stat()
{
    fprintf(stderr, "usbdi_resmgr_stat\n");

}


int usbdi_resmgr_devctl()
{
    fprintf(stderr, "usbdi_resmgr_devctl\n");

}


int usbdi_resmgr_unblock()
{
    fprintf(stderr, "usbdi_resmgr_unblock\n");

}


int usbdi_resmgr_pathconf()
{
    fprintf(stderr, "usbdi_resmgr_pathconf\n");

}


int usbdi_resmgr_chmod()
{
    fprintf(stderr, "usbdi_resmgr_chmod\n");

}


int usbdi_resmgr_chown()
{
    fprintf(stderr, "usbdi_resmgr_chown\n");

}


int usbdi_resmgr_utime()
{
    fprintf(stderr, "usbdi_resmgr_utime\n");

}


int usbdi_resmgr_msg()
{
    fprintf(stderr, "usbdi_resmgr_msg\n");

}


void hub_start_driver(int a, int b)
{
    fprintf(stderr, "hub_start_driver\n");

}


void udi_transfer_done()
{
    fprintf(stderr, "udi_transfer_done\n");

}


void udi_insertion()
{
    fprintf(stderr, "udi_insertion\n");

}


void udi_removal()
{
    fprintf(stderr, "udi_removal\n");

}

