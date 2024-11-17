

#include "externs.h"



void CTRL_FreeHCEntry(int a)
{
    fprintf(stderr, "CTRL_FreeHCEntry\n");

}


void CTRL_StripArgs(char* a)
{
    fprintf(stderr, "CTRL_StripArgs\n");

}


int CTRL_IsPCIDevice()
{
    fprintf(stderr, "CTRL_IsPCIDevice\n");

    return 0;
}


void usbdi_timeout_tick()
{
    fprintf(stderr, "usbdi_timeout_tick\n");

}


int usbdi_io_mount(resmgr_context_t *ctp, io_mount_t *msg,
                      RESMGR_HANDLE_T *handle,
                      io_mount_extra_t *extra)
{
    fprintf(stderr, "usbdi_io_mount\n");

}


int usbdi_timeout_init(struct USB_Timer* a)
{
    fprintf(stderr, "usbdi_timeout_init\n");

    return 0;
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

