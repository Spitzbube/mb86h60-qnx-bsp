
struct USB_Controller_Inner4;
struct UsbdiGlobals_Inner_0x178;
struct io_usb_controller_methods_t;
struct io_usb_ctrl_pipe_methods_t;
struct io_usb_int_pipe_methods_t;
struct io_usb_bulk_pipe_methods_t;
struct io_usb_isoch_pipe_methods_t;


struct Struct_10bab4
{
    int Data_0; //0
    int Data_4; //4
    int Data_8; //8
    int fill_0xc; //0xc
    int Data_0x10; //0x10
    int Data_0x14; //0x14
    int Data_0x18; //0x18
    uint32_t Data_0x1c; //0x1c
    int Data_0x20; //0x20
    int Data_0x24; //0x24
    int Data_0x28; //0x28
    void* Data_0x2c; //0x2c
    uint32_t Data_0x30; //0x30
    int Data_0x34; //0x34
    int Data_0x38; //0x38
    int Data_0x3c; //0x3c
    int Data_0x40; //0x40
    int Data_0x44; //0x44
    int Data_0x48; //0x48
    int Data_0x4c; //0x4c
    uint32_t Data_0x50; //0x50
    int fill_0x54; //0x54
    int Data_0x58; //0x58
    int fill_0x5c[2]; //0x5c
    //0x64
};


struct USB_Controller_Inner4
{
    uint16_t wData_0; //0
    uint16_t wData_2; //2
    int fill_4[4]; //4
    uint8_t bData_0x14[4]; //0x14
    int fill_0x18[6]; //0x18
    uint8_t bData_0x30; //0x30
    uint8_t bData_0x31; //0x31
    uint8_t bData_0x32; //0x32
    uint8_t bData_0x33; //0x33
    uint8_t bData_0x34; //0x34
    uint8_t bData_0x35; //0x35
    uint8_t bData_0x36; //0x36
    uint8_t bData_0x37; //0x37
    int fill_0x38[12]; //0x38
    unsigned long long Data_0x68; //0x68
    int fill_0x70[6]; //0x70
    unsigned long long Data_0x88; //0x88
    int fill_0x90[2]; //0x90
    uint8_t bData_0x98; //0x98
    uint8_t bData_0x99; //0x99
    uint8_t bData_0x9a; //0x9a
    uint8_t bData_0x9b; //0x9b
    int fill_0x9c[3]; //0x9c
    uint8_t bData_0xa8; //0xa8
    uint8_t bData_0xa9; //0xa9
    uint8_t bData_0xaa; //0xaa
    uint8_t bData_0xab; //0xab
    int fill_0xac[17]; //0xac
    //0xf0???
};

#ifndef USB_CONTROLLER_PRIV_T
#define USB_CONTROLLER_PRIV_T void
#endif


struct Struct_1047a8
{
    int fill_0; //0
    int Data_4; //4
    void* Data_8; //8
    //12
};


struct Struct_112b08
{
    uint16_t fill_0; //0
    uint8_t bData_2; //2
    uint8_t bData_3; //3
    uint16_t wData_4; //4
    uint8_t bData_6; //6
    int fill_8; //8
    struct Struct_0xa4* Data_0xc; //0xc
    int fill_0x10; //0x10
    int Data_0x14; //0x14
    void* Data_0x18; //0x18
    int Data_0x1c; //0x1c
    void* Data_0x20; //0x20
    int fill_0x24; //0x24
    int Data_0x28; //0x28
    int fill_0x2c; //0x2c
    //0x30???
};


struct USB_Controller_Inner_0x7c
{
    int Data_0; //0
    int Data_4; //4
    int fill_8; //8
    uint8_t bData_0xc; //0xc
    uint8_t bData_0xd; //0xd
    int Data_0x10; //0x10
    int fill_0x14[2]; //0x14
    void* Data_0x1c; //0x1c
    int Data_0x20; //0x20
    int fill_0x24[2]; //0x24
    usbd_device_descriptor_t device_descriptor; //0x2c +0x12 = 0x3e
    struct Struct_112b08 Data_0x40; //0x40
    pthread_mutex_t Data_0x70; //0x70
    pthread_cond_t Data_0x78; //0x78
    int fill_0x80[2]; //0x80
    int Data_0x88; //0x88
    struct Struct_1047a8* Data_0x8c; //0x8c
    int fill_0x90; //0x90
    pthread_mutex_t Data_0x94; //0x94
    pthread_cond_t Data_0x9c; //0x9c
    int fill_0xa4[2]; //0xa4
    //0xac
};


struct USB_Controller
{
    char* Data_0; //0
    struct USB_Controller_Inner4* Data_4; //4
    int Data_8; //8
    int chid; //12
    int coid; //16
    pthread_t Data_0x14; //0x14
    void* Data_0x18; //0x18
    int fill_0x1c; //0x1c
    int Data_0x20; //0x20
    pthread_mutex_t Data_0x24; //0x24
    int fill_0x2c[13]; //0x2c
    int Data_0x60; //0x60
    int fill_0x64[2]; //0x64
    uint32_t Data_0x6c; //0x6c
    int Data_0x70; //0x70
    int fill_0x74; //0x74
    void** Data_0x78; //0x78
    struct USB_Controller_Inner_0x7c* Data_0x7c; //0x7c
    struct UsbdiGlobals_Inner_0x178* Data_0x80; //0x80
    USB_CONTROLLER_PRIV_T* Data_0x84; //0x84
    struct io_usb_controller_methods_t* controller_methods; //0x88
    struct io_usb_ctrl_pipe_methods_t* ctrl_pipe_methods; //0x8c
    struct io_usb_int_pipe_methods_t* int_pipe_methods; //0x90
    struct io_usb_bulk_pipe_methods_t* bulk_pipe_methods; //0x94
    struct io_usb_isoch_pipe_methods_t* isoch_pipe_methods; //0x98
    //0x9c
};



struct io_usb_controller_methods_t
{
    int Data_0; //0
    int (*controller_init)(struct USB_Controller*, int, char*); //4
    int (*controller_shutdown)(); //8
    int fill_0xc; //12
    int fill_0x10; //16
    int fill_0x14; //20
    int Data_0x18; //0x18 = 24
    int (*set_port_feature)(struct USB_Controller*, int, int); //0x1c = 28
    int (*clear_port_feature)(struct USB_Controller*, int, int); //0x20 = 32
    int (*check_port_status)(struct USB_Controller*, uint32_t*); //0x24 = 36
    int (*check_device_connected)(struct USB_Controller*, int); //0x28 = 40
    int (*get_root_device_speed)(struct USB_Controller*, int); //0x2c = 44
    //TODO!!!
    //???
};


struct io_usb_ctrl_pipe_methods_t
{
    int (*ctrl_endpoint_enable)(struct USB_Controller*, struct USB_Controller_Inner_0x7c*, struct Struct_112b08*); //0
    int fill_4; //4
    int (*ctrl_transfer)(struct USB_Controller*, struct Struct_10bab4*, struct Struct_112b08*, void*, int, int); //8
    int (*ctrl_transfer_abort)(struct USB_Controller*, struct Struct_10bab4*, struct Struct_112b08*); //12
    int Data_16; //16
};

#if 0
0x0000bf98                        dd         mentor_ctrl_endpoint_enable        ; DATA XREF=0xbf54
0x0000bf9c                        dd         mentor_ctrl_endpoint_disable
0x0000bfa0                        dd         mentor_ctrl_transfer
0x0000bfa4                        dd         mentor_ctrl_transfer_abort
0x0000bfa8                        dd         0x00000000
#endif

struct io_usb_bulk_pipe_methods_t
{
    int (*bulk_endpoint_enable)(struct USB_Controller*, struct USB_Controller_Inner_0x7c*, struct Struct_112b08*); //0
#if 0
0x0000bfc4                        dd         mentor_bulk_endpoint_disable
0x0000bfc8                        dd         mentor_bulk_transfer
0x0000bfcc                        dd         mentor_transfer_abort
0x0000bfd0                        dd         0x00000000
#endif
};


struct io_usb_isoch_pipe_methods_t
{
    int (*isoch_endpoint_enable)(struct USB_Controller*, struct USB_Controller_Inner_0x7c*, struct Struct_112b08*); //0
#if 0
0x0000bfd8                        dd         mentor_isoch_endpoint_disable
0x0000bfdc                        dd         mentor_isoch_transfer
0x0000bfe0                        dd         mentor_transfer_abort
0x0000bfe4                        dd         0x00000000
#endif
};


struct io_usb_int_pipe_methods_t
{
    int (*int_endpoint_enable)(struct USB_Controller*, struct USB_Controller_Inner_0x7c*, struct Struct_112b08*); //0
#if 0
0x0000bfac                        dd         mentor_int_endpoint_enable         ; DATA XREF=0xbf58
0x0000bfb0                        dd         mentor_int_endpoint_disable
0x0000bfb4                        dd         mentor_int_transfer
0x0000bfb8                        dd         mentor_transfer_abort
0x0000bfbc                        dd         0x0
#endif
};


struct io_usb_dll_entry_t
{
    char* Data_0; //0
    int Data_4; //4
    int (*init)(); //8
    int (*shutdown)(); //12
    struct io_usb_controller_methods_t* controller_methods; //16
    struct io_usb_ctrl_pipe_methods_t* ctrl_pipe_methods; //20
    struct io_usb_int_pipe_methods_t* int_pipe_methods; //24
    struct io_usb_bulk_pipe_methods_t* bulk_pipe_methods; //28
    struct io_usb_isoch_pipe_methods_t* isoch_pipe_methods; //32
    //36???
};

