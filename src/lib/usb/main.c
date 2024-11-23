

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/usbdi.h>



int Verbosity = 0;
int Tree = 0;
int VendorUnique = 0;
char Data_1076f4[1000]; //1076f4, size???
usbd_bus_topology_t bus_topology;


/* 0x0010260c - complete */
int display(int v, const char* fmt, ...)
{
    int res;

    va_list arglist;

    va_start(arglist, fmt);
#if 1
    vfprintf(stderr, fmt, arglist);
    fprintf(stderr, "\n");
#endif
    va_end( arglist );
    return res;
}


/* 0x00104250 - todo */
int main(int argc/*r5*/, char *argv/*r4*/[])
{
    struct usbd_connection* sp_0xd4;
    usbd_hcd_info_t sp_0x78;
    usbd_connect_parm_t sp_0x48 = {0};
    uint32_t sp_0x3c;
    uint32_t sp_0x38;
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
            display(0, "USB %d (%.*s) v%x.%02x, v%x.%02x DDK, v%x.%02x HCD\n",
                sp_0x30, 8, &sp_0x78.controller[0], 
                sp_0x78.vusb >> 8, sp_0x78.vusb & 0xff,
                sp_0x78.vusbd >> 8, sp_0x78.vusbd & 0xff,
                sp_0x78.vhcd >> 8, sp_0x78.vhcd & 0xff);

            char* r4 = &Data_1076f4[0];
            if (sp_0x78.capabilities & 0x01)
            {
                //0x00104534
                r4 += sprintf(r4, "%sControl", "");
            }
            //loc_104554
            if (sp_0x78.capabilities & 0x02)
            {
                //0x0010455c
                r4 += sprintf(r4, "%sInterrupt", (r4 == &Data_1076f4[0])?
                        "": ", ");
            }
            //loc_104584
            if (sp_0x78.capabilities & 0x04)
            {
                //0x0010458c
                if (sp_0x78.capabilities & 0x200)
                {
                    //0x00104594
                    r4 += sprintf(r4, "%sBulk(SG)", (r4 == &Data_1076f4[0])?
                            "": ", ");
                    //->loc_1045f0
                }
                else
                {
                    //loc_1045c4
                    r4 += sprintf(r4, "%sBulk", (r4 == &Data_1076f4[0])?
                            "": ", ");
                }
            }
            //loc_1045f0
            if (sp_0x78.capabilities & 0x08)
            {
                //0x001045f8
                if (sp_0x78.capabilities & 0x400)
                {
                    //0x00104600
                    r4 += sprintf(r4, "%sIsoch(Stream)", (r4 == &Data_1076f4[0])?
                            "": ", ");
                    //->loc_10465c
                }
                else
                {
                    //loc_104630
                    r4 += sprintf(r4, "%sIsoch", (r4 == &Data_1076f4[0])?
                            "": ", ");
                }
            }
            //loc_10465c
            if (sp_0x78.capabilities & 0x10)
            {
                //0x00104664
                r4 += sprintf(r4, "%sLow speed", (r4 == &Data_1076f4[0])?
                        "": ", ");
            }
            //loc_10468c
            if (sp_0x78.capabilities & 0x20)
            {
                //0x00104694
                r4 += sprintf(r4, "%sFull speed", (r4 == &Data_1076f4[0])?
                        "": ", ");
            }
            //loc_1046bc
            if (sp_0x78.capabilities & 0x40)
            {
                //0x001046c4
                sprintf(r4, "%sHigh speed", (r4 == &Data_1076f4[0])?
                        "": ", ");
            }
            //loc_1046e8
            display(2, "    %s\n", &Data_1076f4[0]);

            sp_0x38 = sp_0x30;

            usbd_topology_ext(sp_0xd4, sp_0x30, &bus_topology);
        }
        //loc_104984
        sp_0x30++;
    }
    //->loc_10499c
    usbd_disconnect(sp_0xd4);

    return 0;
}




