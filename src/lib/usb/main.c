

#include <stdarg.h>
#include <unistd.h>
#include <sys/usbdi.h>



int Verbosity = 0;


int main(int argc/*r5*/, char *argv/*r4*/[])
{
    struct usbd_connection* sp_0xd4;
    usbd_connect_parm_t sp_0x48 = {0};
    int r0;

    sp_0x48.vusb = 0x110;
    sp_0x48.vusbd = USBD_VERSION;

    //->loc_104430
    while (((r0 = getopt(argc, argv, "b:d:DN:tvV")) != -1) || 
            (argc > optind/**r7*/))
    {
        //loc_1042f0
        switch (r0)
        {
            case 't':
                //0x0010434c
                break;

            case 'b':
                //loc_104364
                break;

            case 'd':
                //loc_104380
                break;

            case 'D':
                //loc_10439c
                sp_0x48.flags |= 1;
                break;

            case 'N':
                //loc_1043ac
                sp_0x48.path = optarg;
                break;

            case 'v':
                //loc_1043b8
                Verbosity++;
                break;

            case 'V':
                //loc_1043c8
                break;

            default:
                //loc_104430?
                break;
        }
    }
    //0x00104454
    if (usbd_connect(&sp_0x48, &sp_0xd4) != 0)
    {
        //0x00104474

    }
    //loc_10448c

    return 0;
}


