
struct USB_Controller_Inner4;
struct UsbdiGlobals_Inner_0x178;
struct io_usb_controller_methods_t;


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
    int Data_0x60; //0x60
    uint32_t Data_0x6c; //0x6c
    int Data_0x70; //0x70
    int fill_0x74; //0x74
    void* Data_0x78; //0x78
    void* Data_0x7c; //0x7c
    struct UsbdiGlobals_Inner_0x178* Data_0x80; //0x80
    USB_CONTROLLER_PRIV_T* Data_0x84; //0x84
    struct io_usb_controller_methods_t* controller_methods; //0x88
    void* Data_0x8c; //0x8c
    void* Data_0x90; //0x90
    void* Data_0x94; //0x94
    void* Data_0x98; //0x98
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
    //TODO!!!
    //???
};


struct io_usb_dll_entry_t
{
    char* Data_0; //0
    int Data_4; //4
    int (*init)(); //8
    int (*shutdown)(); //12
    struct io_usb_controller_methods_t* controller_methods; //16
    void* ctrl_pipe_methods; //20
    void* int_pipe_methods; //24
    void* bulk_pipe_methods; //28
    void* isoch_pipe_methods; //32
    //36???
};

