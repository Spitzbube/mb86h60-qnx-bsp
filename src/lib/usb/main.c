

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/usbdi.h>



int Verbosity = 0;
int Tree = 0;
int VendorUnique = 0;
char Data_1076f4[1000]; //1076f4, size???
usbd_bus_topology_t bus_topology;


/* 0x0010260c - complete */
int display(int v, const char* fmt, ...)
{
    int res = -1;

    va_list arglist;

    va_start(arglist, fmt);
#if 1
    vfprintf(stderr, fmt, arglist);
//    fprintf(stderr, "\n");
#endif
    va_end( arglist );
    return res;
}

#if 0
0x001052f8                        dd         0x00105ca8                         ; "Device Address             ", DATA XREF=sub_1027b4+184, sub_1027b4+384, dword_1029ac, sub_1029b4+52, sub_1029b4+232, sub_1029b4+300, sub_1029b4+364, sub_1029b4+444, sub_102be0+56, switch_table_102f10+524, switch_table_102f10+596
0x001052fc                        dd         0x00105cc4                         ; "Upstream Host Controller   "
0x00105300                        dd         0x00105ce0                         ; "Upstream Device Address    "
0x00105304                        dd         0x00105cfc                         ; "Upstream Port              "
[4] 0x00105308                        dd         0x00105d18                         ; "Upstream Port Speed        "
0x0010530c                        dd         0x00105d34                         ; "Vendor                     "
0x00105310                        dd         0x00105d50                         ; "Product                    "
0x00105314                        dd         0x00105d6c                         ; "Device Release             "
0x00105318                        dd         0x00105d88                         ; "USB Spec Release           "
0x0010531c                        dd         0x00105da4                         ; "Serial Number              "
[10]0x00105320                        dd         0x00105dc0                         ; "Class                      "
0x00105324                        dd         0x00105ddc                         ; "Subclass                   "
0x00105328                        dd         0x00105df8                         ; "Protocol                   "
0x0010532c                        dd         0x00105e14                         ; "Max PacketSize0            "
0x00105330                        dd         0x00105e30                         ; "Languages                  "
0x00105334                        dd         0x00105e4c                         ; "Current Frame              "
0x00105338                        dd         0x00105e68                         ; "Hub Number Ports           "
0x0010533c                        dd         0x00105e84                         ; "Hub Characteristics        "
0x00105340                        dd         0x00105ea0                         ; "Hub Power On->Good         "
0x00105344                        dd         0x00105ebc                         ; "Hub Power Requirements     "
0x00105348                        dd         0x00105ed8                         ; "Class-Specific             "
0x0010534c                        dd         0x00105ef4                         ; "Vendor-Specific            "
[22]0x00105350                        dd         0x00105f10                         ; "Configurations             "
0x00105354                        dd         0x00105f2c                         ; "  Configuration            "
0x00105358                        dd         0x00105f48                         ; "    Attributes             "
0x0010535c                        dd         0x00105f64                         ; "    Max Power              "
0x00105360                        dd         0x00105f80                         ; "    Class-Specific         "
0x00105364                        dd         0x00105f9c                         ; "    Vendor-Specific        "
0x00105368                        dd         0x00105fb8                         ; "    Interfaces             "
0x0010536c                        dd         0x00105fd4                         ; "      Interface            "
0x00105370                        dd         0x00105ff0                         ; "        Class              "
0x00105374                        dd         0x0010600c                         ; "        Subclass           "
0x00105378                        dd         0x00106028                         ; "        Protocol           "
0x0010537c                        dd         0x00106044                         ; "        Class-Specific     "
0x00105380                        dd         0x00106060                         ; "        Vendor-Specific    "
0x00105384                        dd         0x0010607c                         ; "        Endpoints          "
0x00105388                        dd         0x00106098                         ; "          Endpoint         "
0x0010538c                        dd         0x001060b4                         ; "            Attributes     "
0x00105390                        dd         0x001060d0                         ; "            Max Packet Size"
0x00105394                        dd         0x001060ec                         ; "            Interval       "
0x00105398                        dd         0x00106108                         ; "            Refresh        "
0x0010539c                        dd         0x00106124                         ; "            Sync Address   "
0x001053a0                        dd         0x00106140                         ; "            Class-Specific "
0x001053a4                        dd         0x0010615c                         ; "            Vendor-Specific"
0x001053a8                        dd         0x00106178                         ; "                           "
0x001053ac                        dd         0x00105ca8                         ; "Device Address             "
0x001053b0                        dd         0x00105cc4                         ; "Upstream Host Controller   "
0x001053b4                        dd         0x00105ce0                         ; "Upstream Device Address    "
0x001053b8                        dd         0x00105cfc                         ; "Upstream Port              "
0x001053bc                        dd         0x00105d18                         ; "Upstream Port Speed        "
0x001053c0                        dd         0x00105d34                         ; "Vendor                     "
0x001053c4                        dd         0x00105d50                         ; "Product                    "
0x001053c8                        dd         0x00105d6c                         ; "Device Release             "
0x001053cc                        dd         0x00105d88                         ; "USB Spec Release           "
0x001053d0                        dd         0x00105da4                         ; "Serial Number              "
0x001053d4                        dd         0x00105dc0                         ; "Class                      "
0x001053d8                        dd         0x00105ddc                         ; "Subclass                   "
0x001053dc                        dd         0x00105df8                         ; "Protocol                   "
0x001053e0                        dd         0x00105e14                         ; "Max PacketSize0            "
0x001053e4                        dd         0x00105e30                         ; "Languages                  "
0x001053e8                        dd         0x00105e4c                         ; "Current Frame              "
0x001053ec                        dd         0x00105e68                         ; "Hub Number Ports           "
0x001053f0                        dd         0x00105e84                         ; "Hub Characteristics        "
0x001053f4                        dd         0x00105ea0                         ; "Hub Power On->Good         "
0x001053f8                        dd         0x00105ebc                         ; "Hub Power Requirements     "
0x001053fc                        dd         0x00105ed8                         ; "Class-Specific             "
0x00105400                        dd         0x00105ef4                         ; "Vendor-Specific            "
0x00105404                        dd         0x00105f10                         ; "Configurations             "
0x00105408                        dd         0x00106194                         ; "+ Configuration            "
0x0010540c                        dd         0x001061b0                         ; "|   Attributes             "
0x00105410                        dd         0x001061cc                         ; "|   Max Power              "
0x00105414                        dd         0x001061e8                         ; "|   Class-Specific         "
0x00105418                        dd         0x00106204                         ; "|   Vendor-Specific        "
0x0010541c                        dd         0x00106220                         ; "|   Interfaces             "
0x00105420                        dd         0x0010623c                         ; "|   + Interface            "
0x00105424                        dd         0x00106258                         ; "|   |   Class              "
0x00105428                        dd         0x00106274                         ; "|   |   Subclass           "
0x0010542c                        dd         0x00106290                         ; "|   |   Protocol           "
0x00105430                        dd         0x001062ac                         ; "|   |   Class-Specific     "
0x00105434                        dd         0x001062c8                         ; "|   |   Vendor-Specific    "
0x00105438                        dd         0x001062e4                         ; "|   |   Endpoints          "
0x0010543c                        dd         0x00106300                         ; "|   |   + Endpoint         "
0x00105440                        dd         0x0010631c                         ; "|   |   |   Attributes     "
0x00105444                        dd         0x00106338                         ; "|   |   |   Max Packet Size"
0x00105448                        dd         0x00106354                         ; "|   |   |   Interval       "
0x0010544c                        dd         0x00106370                         ; "|   |   |   Refresh        "
0x00105450                        dd         0x0010638c                         ; "|   |   |   Sync Address   "
0x00105454                        dd         0x001063a8                         ; "|   |   |   Class-Specific "
0x00105458                        dd         0x001063c4                         ; "|   |   |   Vendor-Specific"
0x0010545c                        dd         0x001063e0                         ; "|   |   |                  "
#endif



/* 1025a4 - todo */
char* sub_1025a4(int a, int b, int c, int* d, int* e)
{
#if 0
    fprintf(stderr, "sub_1025a4: TODO!!!\n");
#endif

    *e = 0;
    *d = 0;

    switch (a)
    {
        case 2:
            return "Communication";

        case 0:
            return "Independent per interface";

        case 9:
            return "Hub";

        case 0xff:
            return "Vendor-specific";

        default:
            break;
    }

    return "Unknown";
}


/* 1026bc - todo */
char* sub_1026bc(int a, int b, int c)
{
#if 0
    fprintf(stderr, "sub_1026bc: TODO!!!\n");
#endif

    switch (b & 0x03)
    {
        case 0:
            //loc_1026ec
            return "Control";
            //break;

        case 1:
            //loc_1026f8
            if (c == 0)
            {
                if (a & 0x80)
                {
                    return "Isoch/IN";
                }
                else
                {
                    return "Isoch/OUT";
                }
            }
            else
            {
                //loc_102718

                //TODO
                return "loc_102718: TODO!!!";
            }
            break;

        case 2:
            //loc_102784
            if (a & 0x80)
            {
                return "Bulk/IN";
            }
            else
            {
                return "Bulk/OUT";
            }
            break;

        case 3:
            //loc_10279c
            if (a & 0x80)
            {
                return "Interrupt/IN";
            }
            else
            {
                return "Interrupt/OUT";
            }
            break;

        default:
            //loc_1026e0
            return "Unknown";
            //break;
    }

    return "";
}


static const struct 
{
    const char* strings[45];
} 
TreeStrings[2] = //0x001052f8
{
    //[0]
    {
        {
            "Device Address             ",//[0]
            "Upstream Host Controller   ",
            "Upstream Device Address    ",
            "Upstream Port              ",
            "Upstream Port Speed        ",//[4]
            "Vendor                     ",
            "Product                    ",
            "Device Release             ",
            "USB Spec Release           ",//[8]
            "Serial Number              ",
            "Class                      ",
            "Subclass                   ",
            "Protocol                   ",//[12]
            "Max PacketSize0            ",
            "Languages                  ",
            "Current Frame              ",
            "",//[16]
            "",//[17]
            "",//[18]
            "",//[19]
            "",//[20]
            "",//[21]
            "Configurations             ",//[22]
            "  Configuration            ",
            "    Attributes             ",
            "    Max Power              ",
            "",//[26]
            "",//[27]
            "    Interfaces             ",//[28]
            "      Interface            ",//[29]
            "        Class              ",//[30]
            "        Subclass           ",//[31]
            "        Protocol           ",//[32]
            "        Class-Specific     ",//[33]
            "        Vendor-Specific    ",//[34]
            "        Endpoints          ",//[35]
            "          Endpoint         ",//[36]
            "            Attributes     ",//[37]
            "            Max Packet Size",//[38]
            "            Interval       ",//[39]
            "            Refresh        ",//[40]
            "            Sync Address   ",//[41]
            "            Class-Specific ",//[42]
        }
    },
    //[1] //0x001053ac
    {
        {
            "Device Address             ",//[0]
            "Upstream Host Controller   ",
            "Upstream Device Address    ",
            "Upstream Port              ",
            "Upstream Port Speed        ",//[4]
            "Vendor                     ",
            "Product                    ",
            "Device Release             ",
            "USB Spec Release           ",//[8]
            "Serial Number              ",
            "Class                      ",
            "Subclass                   ",
            "Protocol                   ",//[12]
            "Max PacketSize0            ",
            "Languages                  ",
            "Current Frame              "
            "",//[16]
            "",//[17]
            "",//[18]
            "",//[19]
            "",//[20]
            "",//[21]
            "Configurations             ",//[22]
            "+ Configuration            ",
            "|   Attributes             ",
            "|   Max Power              ",
            "",//[26]
            "",//[27]
            "|   Interfaces             ",//[28]
            "|   + Interface            ",//[29]
            "|   |   Class              ",//[30]
            "|   |   Subclass           ",//[31]
            "|   |   Protocol           ",//[32]
            "|   |   Class-Specific     ",//[33]
            "|   |   Vendor-Specific    ",//[34]
            "|   |   Endpoints          ",//[35]
            "|   |   + Endpoint         ",//[36]
            "|   |   |   Attributes     ",//[37]
            "|   |   |   Max Packet Size",//[38]
            "|   |   |   Interval       ",//[39]
            "|   |   |   Refresh        ",//[40]
            "|   |   |   Sync Address   ",//[41]
            "|   |   |   Class-Specific ",//[42]
            "|   |   |   Vendor-Specific",//[43]
            "|   |   |                  ",//[44]
        }
    },
};


/* 1027b4 - todo */
int sub_1027b4(struct usbd_device* sp_0xc, 
        int sp_0x20, 
        struct usbd_desc_node* sp_0x10, 
        int sp_0x14, 
        int arg0)
{
#if 1
    fprintf(stderr, "sub_1027b4: TODO!!!\n");
#endif

    usbd_descriptors_t* fp;

#if 0 //TODO!!!
    if (display(sp_0x14, NULL) != 0)
    {
        return 0; //->loc_1029a4
    }
#endif
    //0x001027e0
    int sp8 = 0;
    //sl = " %02x";
    //sp_0x24 = " ";
    //->loc_102980
    while ((fp = usbd_parse_descriptors(sp_0xc,
                    sp_0x10, 0/*type*/, sp8/*index*/, NULL)) != NULL)
    {
        //loc_102800
        switch (fp->generic.bDescriptorType[0])
        {
            case USB_DESC_DEVICE: //1
            case USB_DESC_CONFIGURATION: //2
            case USB_DESC_STRING: //3
            case USB_DESC_INTERFACE: //4
            case USB_DESC_ENDPOINT: //5
            case USB_DESC_HUB: //0x29
                //->loc_102974
                break;

            default:
                //0x00102830
                break;
        }
        //loc_102974
        sp8++;
    } //while (usbd_parse_descriptors...)

    return 1;
}


/* 1034ec - todo */
int sub_1034ec(struct usbd_device* sp_0xc, 
        usbd_descriptors_t* r4, 
        usbd_descriptors_t* sl, 
        int sp_0x14, 
        struct usbd_desc_node* arg0, 
        int arg4)
{
#if 0
    fprintf(stderr, "sub_1034ec: TODO!!!\n");
#endif

    char* sp_0x24;
    char* sp_0x20;
    int sp_0x1c;
    int sp_0x18;

    display(1, "%s: %d\n"/*r7*/, TreeStrings[Tree].strings[0], sp_0x14);
    display(2, "%s: %d\n"/*r7*/, TreeStrings[Tree].strings[1], 
        bus_topology.ports[sp_0x14].upstream_hc);
    display(2, "%s: %d\n"/*r7*/, TreeStrings[Tree].strings[2], 
        bus_topology.ports[sp_0x14].upstream_devno);
    display(2, "%s: %d\n"/*r7*/, TreeStrings[Tree].strings[3], 
        bus_topology.ports[sp_0x14].upstream_port);

    switch (bus_topology.ports[sp_0x14].upstream_port_speed)
    {
        case 1:
            //loc_1035ec
            display(2, "%s: %s\n", TreeStrings[Tree].strings[4], "Low");
            break;

        case 2:
            //0x001035bc
            display(2, "%s: %s\n", TreeStrings[Tree].strings[4], "High");
            //->loc_103660
            break;

        default:
            //loc_103628
            display(2, "%s: %s\n", TreeStrings[Tree].strings[4], "Full");
            //->loc_103660
            break;
    }
    //loc_103660
    char* strVendor = usbd_string(sp_0xc, r4->device.iManufacturer, arg4);
    if (strVendor == NULL)
    {
        //0x00103678
        switch (r4->device.idVendor)
        {
            //TODO!!!

            default:
                display(1, "%s: 0x%04x\n", TreeStrings[Tree].strings[5],
                    r4->device.idVendor, strVendor);
                break;
        }
    }
    else
    {
        //loc_10396c
        display(1, "%s: 0x%04x (%s)\n", TreeStrings[Tree].strings[5],
            r4->device.idVendor, strVendor);
    }

    char* strProduct = usbd_string(sp_0xc, r4->device.iProduct, arg4);
    display(1, (strProduct != NULL)? "%s: 0x%04x (%s)\n": "%s: 0x%04x (%s)\n",
        TreeStrings[Tree].strings[6], 
        r4->device.idProduct, strProduct);
    display(2, "%s: r%x.%02x\n", TreeStrings[Tree].strings[7],
        r4->device.bcdDevice >> 8, r4->device.bcdDevice & 0xff);
    display(3, "%s: v%x.%02x\n", TreeStrings[Tree].strings[8],
        r4->device.bcdUSB >> 8, r4->device.bcdUSB & 0xff);
    display(3, "%s: %s\n", TreeStrings[Tree].strings[9],
        usbd_string(sp_0xc, r4->device.iSerialNumber, arg4));

    if (r4->device.bDeviceClass == 0)
    {
        //0x00103a94
        char* strClass = sub_1025a4(0, 0, 0, &sp_0x24, &sp_0x20);

        display(1, "%s: 0x%02x (%s)\n", TreeStrings[Tree].strings[10], 0, strClass);
        //->loc_103bc8
    }
    else
    {
        //loc_103ae8
        char* strClass = sub_1025a4(r4->device.bDeviceClass, 
                    r4->device.bDeviceSubClass, 
                    r4->device.bDeviceProtocol, 
                    &sp_0x24, &sp_0x20);

        display(1, "%s: 0x%02x (%s)\n", TreeStrings[Tree].strings[10], 
            r4->device.bDeviceClass, strClass);
        display(1, (sp_0x24 != NULL)? "%s: 0x%02x (%s)\n": "%s: 0x%02x\n",
            TreeStrings[Tree].strings[11], r4->device.bDeviceSubClass, sp_0x24);
        display(1, (sp_0x20 != NULL)? "%s: 0x%02x (%s)\n": "%s: 0x%02x\n",
            TreeStrings[Tree].strings[12], r4->device.bDeviceProtocol, sp_0x20);
    }
    //loc_103bc8
    display(1, "%s: %d\n", TreeStrings[Tree].strings[13], r4->device.bMaxPacketSize0);

    if (sl == NULL)
    {
        //0x00103c04
        display(3, "%s: No string descriptors\n", TreeStrings[Tree].strings[14]);
        //->loc_103f10
    }
    else
    {
        //loc_103c38
        if (display(3, "%s: ", TreeStrings[Tree].strings[14]) != 0)
        {
            //0x00103c70

            //TODO!!!

            //loc_103f00
            display(3, "\n");
        }
        //loc_103f10
    }

    if (display(4, "%s: ", TreeStrings[Tree].strings[15]) != 0)
    {
        //0x00103f48
        if (usbd_get_frame(sp_0xc, &sp_0x1c, &sp_0x18) == 0)
        {
            display(4, "%d (%d bytes)\n", sp_0x1c, sp_0x18);
        }
        else
        {
            //loc_103f7c
            display(4, "Unknown\n");
        }
    }
    //loc_103f8c
    if (r4->device.bDeviceClass == USB_CLASS_HUB)
    {
        //0x00103f98
#if 1
        fprintf(stderr, "sub_1034ec: 0x00103f98: TODO!!!\n");
#endif

        //TODO!!!
    }
    //loc_104154
    sub_1027b4(sp_0xc, 0, arg0, 3, 0x15);

    return display(2, "%s: %d\n", TreeStrings[Tree].strings[22],
        r4->device.bNumConfigurations);
}


/* 1029b4 - todo */
int sub_1029b4(int sp_0xc, 
        struct usbd_device* fp, 
        usbd_descriptors_t* sb, 
        usbd_descriptors_t* r4, 
        struct usbd_desc_node* arg0, 
        int arg4)
{
#if 0
        fprintf(stderr, "sub_1029b4: TODO!!!\n");
#endif

    int sl = (r4->endpoint.bLength == 10)? 1: 0;

    display(4, "%s: %d\n"/*r7*/, TreeStrings[Tree].strings[36],
        r4->endpoint.bEndpointAddress & 0x0f);

    display(4, "%s: %s\n", TreeStrings[Tree].strings[37],
        sub_1026bc(r4->endpoint.bEndpointAddress,
            r4->endpoint.bmAttributes, sl));

    display(4, "%s: %d\n"/*r7*/, TreeStrings[Tree].strings[38],
        r4->endpoint.wMaxPacketSize);

    if (r4->endpoint.bmAttributes & 0x01)
    {
        //0x00102a70
        if (bus_topology.ports[sp_0xc].upstream_port_speed == 2)
        {
            //0x00102a8c
            if (r4->endpoint.bInterval > 3)
            {
                //0x00102a98
                int r3 = 1 << (r4->endpoint.bInterval - 1);
                int r1 = r3 + 7;
                r3 = (r3 < 0)? r1: 0;

                display(4, "%s: %d ms\n", TreeStrings[Tree].strings[39],
                    r3 >> 3);
                //->loc_102b50
            }
            else
            {
                //loc_102adc
                display(4, "%s: %d mframe\n", TreeStrings[Tree].strings[39],
                    1 << (r4->endpoint.bInterval - 1));
                //->loc_102b50
            }
        }
        else
        {
            //loc_102b1c
            display(4, "%s: %d ms\n", TreeStrings[Tree].strings[39],
                r4->endpoint.bInterval);
        }
    }
    //loc_102b50
    if ((sl != 0) /*&& (sb->endpoint.5... == 1)*/)
    {
        //0x00102b64
        fprintf(stderr, "sub_1029b4: 0x00102b64: TODO!!!\n");

        //TODO!!!
    }
    //loc_102bb8
    sub_1027b4(fp, sb, arg0, 6, 43);

    return 0;
}



/* 102be0 - todo */
int sub_102be0(struct usbd_device* sb, 
        usbd_descriptors_t* r4, 
        struct usbd_desc_node* sl, 
        int d)
{
#if 0
        fprintf(stderr, "sub_102be0: TODO!!!\n");
#endif

    char* strIface = usbd_string(sb, r4->interface.iInterface, d);

    display(3, (strIface != 0)? "%s: %d / %d (%s)\n": "%s: %d / %d\n",
        TreeStrings[Tree].strings[29], r4->interface.bInterfaceNumber,
        r4->interface.bAlternateSetting, strIface);
    //r3 = r4->interface.bInterfaceClass
    //r2 = r4->interface.bInterfaceSubClass
    //r1 = r4->interface.bInterfaceProtocol

    char* r8 = NULL;
    switch (r4->interface.bInterfaceClass/*r3*/)
    {
#if 0 //TODO!!!
        case 0x0d:
            //loc_102ccc
            break;

        case 1:
            //loc_102cdc
            break;

        case 2:
            //loc_102d34
            break;

        case 3:
            //loc_102e18
            break;

        case 7:
            //loc_102e88
            break;
#endif

        case 8:
            //loc_102f00
            switch (r4->interface.bInterfaceSubClass/*r2*/)
            {
                case 2:
                    //loc_102f28
                    //r8 = 0;
                    //r5 = "SFF8020i"
                    //r0 = "Mass Storage";
                    //->loc_10328c
                    display(3, "%s: 0x%02x (%s)\n"/*r6*/,
                        TreeStrings[Tree].strings[30],
                        r4->interface.bInterfaceClass,
                        "Mass Storage");
                    //r1 = r6;
                    //->loc_103160
                    display(3, "%s: 0x%02x (%s)\n"/*r6*/,
                        TreeStrings[Tree].strings[31],
                        r4->interface.bInterfaceSubClass,
                        "SFF8020i"/*r5*/);
                    //0x00103190
                    //TODO!!!
                    break;

                default:
                    //loc_102f40
                    //r5 = ""
                    //r0 = "Mass Storage";
                    //->loc_103118
                    display(3, "%s: 0x%02x (%s)\n",
                        TreeStrings[Tree].strings[30],
                        r4->interface.bInterfaceClass,
                        "Mass Storage");
                    //0x0010314c
                    //TODO!!!
                    break;

                case 1:
                    //loc_102f50
                    //r8 = 0;
                    //r5 = "RBC"
                    //r0 = "Mass Storage";
                    //->loc_10328c
                    display(3, "%s: 0x%02x (%s)\n"/*r6*/,
                        TreeStrings[Tree].strings[30],
                        r4->interface.bInterfaceClass,
                        "Mass Storage");
                    //r1 = r6;
                    //->loc_103160
                    display(3, "%s: 0x%02x (%s)\n"/*r6*/,
                        TreeStrings[Tree].strings[31],
                        r4->interface.bInterfaceSubClass,
                        "RBC"/*r5*/);
                    //0x00103190
                    //TODO!!!
                    break;

                case 3:
                    //loc_102f68
                    //r8 = 0;
                    //r5 = "QIC-157"
                    //r0 = "Mass Storage";
                    //->loc_10328c
                    display(3, "%s: 0x%02x (%s)\n"/*r6*/,
                        TreeStrings[Tree].strings[30],
                        r4->interface.bInterfaceClass,
                        "Mass Storage");
                    //r1 = r6;
                    //->loc_103160
                    display(3, "%s: 0x%02x (%s)\n"/*r6*/,
                        TreeStrings[Tree].strings[31],
                        r4->interface.bInterfaceSubClass,
                        "QIC-157"/*r5*/);
                    //0x00103190
                    //TODO!!!
                    break;

                case 4:
                    //loc_102f80
                    //r8 = 0;
                    //r5 = "UFI"
                    //r0 = "Mass Storage";
                    //->loc_10328c
                    display(3, "%s: 0x%02x (%s)\n"/*r6*/,
                        TreeStrings[Tree].strings[30],
                        r4->interface.bInterfaceClass,
                        "Mass Storage");
                    //r1 = r6;
                    //->loc_103160
                    display(3, "%s: 0x%02x (%s)\n"/*r6*/,
                        TreeStrings[Tree].strings[31],
                        r4->interface.bInterfaceSubClass,
                        "UFI"/*r5*/);
                    //0x00103190
                    //TODO!!!
                    break;

                case 5:
                    //loc_102f98
                    //r8 = 0;
                    //r5 = "SFF8070i"
                    //r0 = "Mass Storage";
                    //->loc_10328c
                    display(3, "%s: 0x%02x (%s)\n"/*r6*/,
                        TreeStrings[Tree].strings[30],
                        r4->interface.bInterfaceClass,
                        "Mass Storage");
                    //r1 = r6;
                    //->loc_103160
                    display(3, "%s: 0x%02x (%s)\n"/*r6*/,
                        TreeStrings[Tree].strings[31],
                        r4->interface.bInterfaceSubClass,
                        "SFF8070i"/*r5*/);
                    //0x00103190
                    //TODO!!!
                    break;

                case 6:
                    //loc_102fb0
                    //r8 = 0;
                    //r5 = "SCSI"
                    //r0 = "Mass Storage";
                    //->loc_10328c
                    display(3, "%s: 0x%02x (%s)\n"/*r6*/,
                        TreeStrings[Tree].strings[30],
                        r4->interface.bInterfaceClass,
                        "Mass Storage");
                    //r1 = r6;
                    //->loc_103160
                    display(3, "%s: 0x%02x (%s)\n"/*r6*/,
                        TreeStrings[Tree].strings[31],
                        r4->interface.bInterfaceSubClass,
                        "SCSI"/*r5*/);
                    //0x00103190
                    //TODO!!!
                    break;

            }
            break;

#if 0
        case 0x0a:
            //loc_102fc8
            break;

        case 0xfe:
            //loc_1030a0
            break;

        case 0xff:
            //loc_1030ec
            break;

        case 5:
            //loc_10310c
            break;

        case 9:
            //loc_103230
            break;
#endif

        default:
            //loc_1030fc
            //r8 = 0;
            //r0 = "Unknown";
            //->loc_10323c
            display(3, "%s: 0x%02x (%s)\n", TreeStrings[Tree].strings[30],
                r4->interface.bInterfaceClass,
                "Unknown");
            //r5 = 0;
            //->loc_103158
            break;
    }

    display(3, (r8 != NULL)? "%s: 0x%02x (%s)\n": "%s: 0x%02x\n",
        TreeStrings[Tree].strings[32], 
        r4->interface.bInterfaceProtocol, r8);

    sub_1027b4(sb, r4, sl, 5, 34);

    return display(4, "%s: %s + %d\n", TreeStrings[Tree].strings[35],
        sub_1026bc(0, 0, 0), r4->interface.bNumEndpoints);
}



/* 103318 - todo */
int sub_103318(struct usbd_device* r5, 
        usbd_descriptors_t* sl, 
        struct usbd_desc_node* r8, 
        struct usbd_desc_node* sb, 
        int arg0)
{
#if 0
        fprintf(stderr, "sub_103318: TODO!!!\n");
#endif

    char* strConf = usbd_string(r5, sl->configuration.iConfiguration, arg0);

    display(2, (strConf != 0)? "%s: %d (%s)\n": "%s: %d\n",
        TreeStrings[Tree].strings[23], sl->configuration.bConfigurationValue,
        strConf);

    switch (sl->configuration.bmAttributes & 0x60)
    {
        case 0:
            display(2, "%s: 0x%02x (%s)\n", TreeStrings[Tree].strings[24],
                sl->configuration.bmAttributes, "Bus-powered");
            break;

        case 0x20:
            //loc_1033bc
            display(2, "%s: 0x%02x (%s)\n", TreeStrings[Tree].strings[24],
                sl->configuration.bmAttributes, "Bus-powered, Remote-wakeup");
            break;

        case 0x40:
            //loc_1034d8
            display(2, "%s: 0x%02x (%s)\n", TreeStrings[Tree].strings[24],
                sl->configuration.bmAttributes, "Self-powered");
            break;

        case 0x60:
            //loc_1033d8
            display(2, "%s: 0x%02x (%s)\n", TreeStrings[Tree].strings[24],
                sl->configuration.bmAttributes, "Self-powered, Remote-wakeup");
            break;

        default:
            //loc_1033c8
            display(2, "%s: 0x%02x\n", TreeStrings[Tree].strings[24],
                sl->configuration.bmAttributes);
            break;
    }

    display(2, "%s: %d mA\n", TreeStrings[Tree].strings[25],
        sl->configuration.MaxPower * 2);

    sub_1027b4(r5, 0, sb, 4, 0x1b);

    int r4 = 0;
    //r6 = 0;
    //r7 = 4;
    //->loc_103468
    while (usbd_parse_descriptors(r5, r8, 
        USB_DESC_INTERFACE/*r7*/, r4, NULL/*r6*/) != 0)
    {
        //loc_103464
        r4++;
    }

    return display(3, (r4 > sl->configuration.bNumInterfaces)? 
        "%s: %d (with %d alternate)\n": "%s: %d\n",
        TreeStrings[Tree].strings[28], 
        sl->configuration.bNumInterfaces,
        r4 - sl->configuration.bNumInterfaces);
}



/* 0x00104250 - todo */
int main(int argc/*r5*/, char *argv/*r4*/[])
{
    struct usbd_connection* sp_0xd4;
    struct usbd_device* sp_0xd0;
    struct usbd_desc_node* sp_0xcc;
    struct usbd_desc_node* sp_0xc8;
    struct usbd_desc_node* sp_0xc4;
    struct usbd_desc_node* sp_0xc0;
    usbd_device_instance_t sp_0x9c;
    usbd_hcd_info_t sp_0x78;
    usbd_connect_parm_t sp_0x48 = {0};
    uint32_t sp_0x40;
    uint32_t sp_0x3c;
    uint32_t sp_0x38;
    uint32_t sp_0x34;
    uint32_t sp_0x30;
    uint32_t sp_0x2c;
//    int sp_0x28;
//    int sp_0x24;
    int r0;

    sp_0x48.vusb = 0x110;
    sp_0x48.vusbd = USBD_VERSION;
    sp_0x2c = 64;
    sp_0x3c = 1;
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
    sp_0x40 = sp_0x3c;

    r0 = usbd_connect(&sp_0x48, &sp_0xd4);
    if (r0 != 0)
    {
        //0x00104474
        fatal(argv[0], "unable to connect to USB - %s", strerror(r0));
    }
    //loc_10448c
    //fp = &sp_0xc4
    //r8 = &sp_0xc0
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

            if (sp_0x2c >= sp_0x40)
            {
                //0x0010473c
                //r7 = sp_0x3c;

                //loc_10474c
                memset(&sp_0x9c/*r4*/, -1, sizeof(usbd_device_instance_t));

                sp_0x9c.path = sp_0x38;
                sp_0x9c.devno = sp_0x3c; //r7

                int r0 = usbd_attach(sp_0xd4, &sp_0x9c, 0, &sp_0xd0);
                if (r0 == 0)
                {
                    //0x00104788
#if 0
                    fprintf(stderr, "device: generation=%d, ident.vendor=0x%x, ident.device=0x%x\n", 
                        sp_0x9c.generation, sp_0x9c.ident.vendor, sp_0x9c.ident.device);
#endif

                    usbd_descriptors_t* r4;
                    r4 = usbd_parse_descriptors(sp_0xd0, NULL, USB_DESC_DEVICE, 0, &sp_0xcc);
#if 0
                    fprintf(stderr, "usb: r4=%p, sp_0xcc=%p\n", r4, sp_0xcc);
#endif
                    if (r4 != NULL)
                    {
                        //0x001047ac
                        int langid; //r5;
                        usbd_descriptors_t* r2;
                        r2 = usbd_parse_descriptors(sp_0xd0, NULL, USB_DESC_STRING, 0, NULL);
                        if (r2 != NULL)
                        {
                            //0x001047cc
                            langid = r2->string.bString[0];
                            //r0 = sp_0xd0;
                            //r1 = r4;
                        } //if (r2 != NULL)
                        else
                        {
                            //loc_1049b0
                            langid = 0;
                            //(sp_0xd0, r4, 0);
                            //->loc_1047d8
                        }
                        //loc_1047d8
                        if (sub_1034ec(sp_0xd0, r4, r2, sp_0x3c/*r7*/, sp_0xcc, langid) != 0)
                        {
                            //0x001047f0
                            int indexConf/*sp_0x24*/ = 0;
                            //sp_0x28 = 0;
                            usbd_descriptors_t* r1;
                            //r6 = 5;
                            //->loc_1048b8
                            while ((r1 = usbd_parse_descriptors(sp_0xd0,
                                    sp_0xcc, USB_DESC_CONFIGURATION, 
                                    indexConf, &sp_0xc8)) != 0)
                            {
                                //loc_104804
                                if (sub_103318(sp_0xd0, r1, sp_0xc8, sp_0xc8, langid) != 0)
                                {
                                    int indexIf = 0;
                                    //sb = 4;
                                    //->loc_10488c
                                    while ((r1 = usbd_parse_descriptors(sp_0xd0,
                                                sp_0xc8, 
                                                USB_DESC_INTERFACE/*sb*/, 
                                                indexIf, &sp_0xc4/*fp*/)) != 0)
                                    {
                                        //loc_10482c
                                        if (sub_102be0(sp_0xd0, r1, sp_0xc4, langid) != 0)
                                        {
                                            int indexEp/*r4*/ = 0/*sp_0x28*/;
                                            usbd_descriptors_t* r3;
                                            //->loc_104868
                                            while ((r3 = usbd_parse_descriptors(sp_0xd0, 
                                                            sp_0xc4, 
                                                            USB_DESC_ENDPOINT/*r6*/, 
                                                            indexEp, &sp_0xc0/*r8*/)) != 0)
                                            {
                                                //loc_10484c
                                                sub_1029b4(sp_0x3c/*r7*/, sp_0xd0, 
                                                    r3, r3, sp_0xc0, langid);

                                                indexEp++;
                                            }
                                        }
                                        //loc_104888
                                        indexIf++;
                                        //loc_10488c
                                    } //while (usbd_parse_descriptors(USB_DESC_INTERFACE))
                                }
                                //loc_1048ac
                                indexConf++;
                            } //while (usbd_parse_descriptors(USB_DESC_CONFIGURATION))
                            //0x001048dc
                            //loc_104914
                        }
                        //loc_104914
                    } //if (r4 != NULL)
                    else
                    {
                        //loc_1048e0
                        //if (x == 0)
                        {
                            //0x001048f4
                            fprintf(stderr, "device %d - descriptors - %s\n"/*sp_0x44*/, 
                                sp_0x3c/*r7*/, strerror(errno));
                        }
                    }                    
                    //loc_104914
                    display(0, "\n");
                    usbd_detach(sp_0xd0);
                    //->loc_104974
                }
                else
                {
                    //loc_104930
                    fprintf(stderr, "device %d - attach - %s\n",
                        sp_0x3c/*r7*/, strerror(r0));
                }
                //loc_104974
                //r7++;
                //if (r7 < sp_0x2c) -> loc_10474c
            } //if (sp_0x2c >= sp_0x40)
            //loc_104984
        }
        //loc_104984
        sp_0x30++;
        //->loc_1044a0
    } //while (sp_0x30 <= sp_0x34)
    //->loc_10499c
    usbd_disconnect(sp_0xd4);

    return 0;
}




