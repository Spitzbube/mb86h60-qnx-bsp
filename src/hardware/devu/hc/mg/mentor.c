
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


struct io_usb_dll_entry_t io_usb_dll_entry = //0x0000bf40
{
    "devu-mb86h60-mg.so",
    0xffffffff,
    mentor_init,
    mentor_shutdown,
#if 0 //TODO
    &mentor_controller_methods,
    &mentor_ctrl_pipe_methods,
    &mentor_int_pipe_methods,
    &mentor_bulk_pipe_methods,
    &mentor_isoch_pipe_methods,
#endif
};


#if 0
                              mentor_controller_methods:
0x0000bf64                        dd         0x00000009                         ; DATA XREF=0xbf50
0x0000bf68                        dd         mentor_controller_init
0x0000bf6c                        dd         mentor_controller_shutdown
0x0000bf70                        dd         mentor_set_bus_state
0x0000bf74                        dd         0x0
0x0000bf78                        dd         0x0
0x0000bf7c                        dd         0x0
0x0000bf80                        dd         mentor_set_port_feature
0x0000bf84                        dd         mentor_clear_port_feature
0x0000bf88                        dd         mentor_check_port_status
0x0000bf8c                        dd         mentor_check_device_connected
0x0000bf90                        dd         mentor_get_root_device_speed
0x0000bf94                        dd         mentor_get_timer_from_controller
#endif


