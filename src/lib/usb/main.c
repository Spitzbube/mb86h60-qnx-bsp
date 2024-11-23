

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/usbdi.h>



int Verbosity = 0;
int Tree = 0;
int VendorUnique = 0;


/* 0x00104250 - todo */
int main(int argc/*r5*/, char *argv/*r4*/[])
{
    struct usbd_connection* sp_0xd4;
    usbd_hcd_info_t sp_0x78;
    usbd_connect_parm_t sp_0x48 = {0};
    uint32_t sp_0x3c;
    uint32_t sp_0x34;
    uint32_t sp_0x30;
    uint32_t sp_0x2c;
    int r0;

    sp_0x48.vusb = 0x110;
    sp_0x48.vusbd = USBD_VERSION;
    sp_0x34 = 9;
    sp_0x30 = 0;

    //->loc_104430
    while (((r0 = getopt(argc, argv, "b:d:DN:tvV")) != -1) || 
            (argc > optind/**r7*/))
    {
        //loc_1042f0
        switch (r0)
        {
            case 't':
                //0x0010434c: Alternative output format (tree-like)
                Tree = 1;
                break;

            case 'b':
                //loc_104364: Display devices on specific 'busno' only
                sp_0x30 = sp_0x34 = strtoul(optarg, NULL, 0);
                break;

            case 'd':
                //loc_104380: Display device 'devno' only
                sp_0x3c = sp_0x2c = strtoul(optarg, NULL, 0);
                break;

            case 'D':
                //loc_10439c
                sp_0x48.flags |= 1;
                break;

            case 'N':
                //loc_1043ac: Name of the USB manager to query (e.g. "/dev/io-usb/io-usb" )
                sp_0x48.path = optarg;
                break;

            case 'v':
                //loc_1043b8: Increase level of verbosity
                Verbosity++;
                break;

            case 'V':
                //loc_1043c8: Display vendor-unique descriptors (at given verbosity level)
                VendorUnique++;
                break;

            case '?':
                //loc_1043d8
                fatal(argv[0], "unknown option '-%c'", optopt);
                break;

            case ':':
                //loc_1043f8
                fatal(argv[0], "missing argument for '-%c'", optopt);
                break;

            default:
                //loc_104430?
                break;
        }
    }
    //0x00104454
    r0 = usbd_connect(&sp_0x48, &sp_0xd4);
    if (r0 != 0)
    {
        //0x00104474
        fatal(argv[0], "unable to connect to USB - %s", strerror(r0));
    }
    //loc_10448c
    while (sp_0x30 <= sp_0x34)
    {
        //loc_1044a0
        r0 = usbd_hcd_ext_info(sp_0xd4, sp_0x30, &sp_0x78);
        if (r0 == 0)
        {

        }
        //loc_104984
        sp_0x30++;
    }
    //->loc_10499c
    usbd_disconnect(sp_0xd4);

    return 0;
}


