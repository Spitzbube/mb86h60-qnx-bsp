

struct Struct_b698
{
    pthread_mutex_t Data_0; //0 //b698
    int Data_8; //8
    int Data_0xc; //12
    int fill_0x10[10]; //0x10
    int Data_0x38; //0x38
    struct usbd_connection* Data_0x3c; //0x3c
    //???
};

extern struct Struct_b698 Data_b698;

struct usbd_device
{
    int Data_0; //0
    int* Data_4; //4
    struct usbd_connection* Data_8; //8
    int Data_0xc; //0xc
    void* Data_0x10; //0x10
    unsigned Data_0x14; //0x14
    int Data_0x18; //0x18
    usbd_device_instance_t Data_0x1c; //0x1c +0x24
    int Data_0x40; //0x40
    void* Data_0x44; //0x44
    //0x48
};


struct usbd_urb
{
    int Data_0; //4
    struct usbd_urb* Data_4; //4
    struct
    {
        int fill_0[3]; //0
        int Data_0xc; //0xc
        //???
    }* Data_8; //8
    struct
    {
        int Data_0; //0
        //???
    }* Data_0xc; //0xc
    struct
    {
        int fill_0[3]; //0
        int Data_0xc; //0xc
        int fill_0x10; //0x10
        int Data_0x14; //0x14
        //???
    }* Data_0x10; //0x10
    struct Struct_107288* Data_0x14; //0x14
    int fill_0x18[2]; //0x18
    uint16_t wData_0x20; //0x20
    uint16_t wData_0x22; //0x22
    int Data_0x24; //0x24
    uint8_t bData_0x28; //0x28
    uint8_t bData_0x29; //0x29
    uint8_t wData_0x2a; //0x2a
    int Data_0x2c; //0x2c
    int Data_0x30; //0x30
    int Data_0x34; //0x34
    int Data_0x38; //0x38
    int Data_0x3c; //0x3c
    int Data_0x40; //0x40
    void* pData; //0x44
    int dwLength; //0x48
    int fill_0x4c; //0x4c
    int Data_0x50; //0x50
    int Data_0x54; //0x54
    uint16_t wValue; //0x58
    uint16_t wData_0x5a; //0x5a
    uint8_t request; //0x5c
    uint8_t request_type; //0x5d
    uint16_t wData_0x5e; //0x5e
    int Data_0x60; //0x60
    int Data_0x64; //0x64
    uint16_t wData_0x68; //0x68
    int fill_0x6c; //0x6c
    //0x70
};


struct Struct_5a24_d
{
    uint16_t fill_0; //0
    uint16_t wData_2; //2
    int fill_4; //4
};

struct Struct_5a24_d1
{
    uint16_t fill_0; //0
    uint16_t wData_2; //2
};


extern int usbdi_sendcmd(int sp_0xc, int r8, 
    struct usbd_urb* sl, 
    struct Struct_5a24_d* r7);

extern void* usbdi_memchunk_calloc(int, int b, int c);
extern paddr_t usbdi_memchunk_mphys(int, const void* ptr);
