
#include <stdio.h>
#include "io-usb.h"


/* 0x00004f3c - complete */
int mentor_init()
{
    fprintf(stderr, "mentor_init\n");

    return 0;
}


/* 0x00004f44 - complete */
int mentor_shutdown()
{
    fprintf(stderr, "mentor_shutdown\n");

    return 0;
}


/* 0x00004fa8 - todo */
int mentor_controller_shutdown()
{
    fprintf(stderr, "mentor_controller_shutdown\n");

    return 0;
}


/* 0x0000615c - todo */
int mentor_controller_init()
{
    fprintf(stderr, "mentor_controller_init\n");

    return 0;
}


static struct io_usb_controller_methods_t mentor_controller_methods; //0x0000bf64

struct io_usb_dll_entry_t io_usb_dll_entry = //0x0000bf40
{
    "devu-mb86h60-mg.so",
    0xffffffff,
    mentor_init,
    mentor_shutdown,
    &mentor_controller_methods,
#if 0 //TODO
    &mentor_ctrl_pipe_methods,
    &mentor_int_pipe_methods,
    &mentor_bulk_pipe_methods,
    &mentor_isoch_pipe_methods,
#endif
};


static struct io_usb_controller_methods_t mentor_controller_methods = //0x0000bf64
{
    9,
    mentor_controller_init,
    mentor_controller_shutdown,
#if 0 //TODO
    mentor_set_bus_state,
    0, 0, 0,
    mentor_set_port_feature,
    mentor_clear_port_feature,
    mentor_check_port_status,
    mentor_check_device_connected,
    mentor_get_root_device_speed,
    mentor_get_timer_from_controller,
#endif
};



