
#include <sys/usbdi.h>




int main(int argc, char *argv[])
{
    struct usbd_connection* sp_0xd4;
    usbd_connect_parm_t sp_0x48;

    //0x00104454
    if (usbd_connect(&sp_0x48, &sp_0xd4) != 0)
    {
        //0x00104474

    }
    //loc_10448c

    return 0;
}


