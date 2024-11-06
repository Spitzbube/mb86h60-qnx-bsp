
#include <stdio.h>
#include <sys/dispatch.h>
#include <sys/iofunc.h>
#include "externs.h"


int USBDRIV_Main(int a, int b)
{
    fprintf(stderr, "USBDRIV_Main: TODO\n");
    return 0;
}


void usb_slogf()
{
    fprintf(stderr, "usb_slogf\n");

}


void CTRL_RegisterControllerType()
{
    fprintf(stderr, "CTRL_RegisterControllerType\n");

}


void stop_controllers(void)
{
    fprintf(stderr, "stop_controllers\n");

}


void udi_memory_info()
{
    fprintf(stderr, "udi_memory_info\n");

}


void usb_port_monitor_start()
{
    fprintf(stderr, "usb_port_monitor_start\n");

}


void usb_signal_handler()
{
    fprintf(stderr, "usb_signal_handler\n");

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


void usbdi_memchunk_init()
{
    fprintf(stderr, "usbdi_memchunk_init\n");

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

}




