
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <atomic.h>
#include <signal.h>
#include <errno.h>
#include <dlfcn.h>
#include <libgen.h>
#include <sys/neutrino.h>
#include <sys/slog.h>
//#include <sys/resmgr.h>
#include <sys/procmgr.h>
#include <hw/pci.h>
#include <pthread.h>
#include <sys/usb100.h>
#include <sys/usbdi.h>

#include "io-usb.h"


/* Define our overrides before including <sys/iofunc.h> */
struct ocb;
struct UsbdiGlobals_Inner_0x178;
#define IOFUNC_OCB_T struct ocb
#define RESMGR_HANDLE_T struct UsbdiGlobals_Inner_0x178
#include <sys/iofunc.h>
#include <sys/resmgr.h>
#include <sys/dispatch.h>


// This is our own ocb block
struct ocb
{
    iofunc_ocb_t hdr; /* must always be first */
    int Data_0x18; //0x18
    //0x1c = 28
};

struct USB_Controller;

struct UsbdiGlobals_Inner_0x24
{
    struct UsbdiGlobals_Inner_0x24* Data_0; //0
    int fill_4; //4
    pthread_mutex_t Data_8; //8
    int Data_0x10; //0x10
    int fill_0x14[2]; //0x14
    int Data_0x1c; //0x1c
    //???
};

struct UsbdiGlobals_Inner_0x178
{
    void* hDll; //0
    struct io_usb_dll_entry_t* pDllEntry; //4
    char* Data_8; //8
    int Data_0xc; //12
    int Data_0x10; //16
    int fill_0x14; //20
    int Data_0x18; //0x18 = 24
    volatile unsigned int Data_0x1c; //0x1c = 28
    int Data_0x20; //0x20
    struct USB_Controller* Data_0x24[10];
    char* args[10]; //0x4c
    pthread_t Data_0x74; //0x74
    struct UsbdiGlobals_Inner_0x178* Data_0x78; //0x78
    //0x7c???
};

struct UsbdiGlobals
{
#if 0
    int fill_0[4]; //0
#else
    pthread_mutex_t Data_0; //0
#endif
    int Data_8; //8
    int Data_0xc; //0xc
    int Data_0x10; //0x10
    uint32_t Data_0x14; //0x14 = 1212c4
    int fill_0x18; //0x18
    dispatch_t* dpp; //0x1c
    void* Data_0x20; //0x20
    struct UsbdiGlobals_Inner_0x24* Data_0x24; //0x24
    void* Data_0x28; //0x28
    int Data_0x2c; //0x2c
    int Data_0x30; //0x30
    int Data_0x34; //0x34
    int fill_0x38[2]; //0x38
    int Data_0x40; //0x40
    int fill_0x44[2]; //0x44
    iofunc_mount_t Data_0x4c; //0x4c
    iofunc_attr_t iofunc_attr; //0x64
    dev_t Data_0xb8; //0xb8
    resmgr_attr_t resmgr_attr; //0xbc
    thread_pool_attr_t Data_0xdc;
    pthread_attr_t Data_0x120; //0x120
//    int fill_0x174; //0x174
    struct UsbdiGlobals_Inner_0x178* Data_0x178; //0x178
    int Data_0x17c; //0x17c
    int Data_0x180; //0x180
};


struct USB_Timer
{
    int Data_0; //0
    int Data_4; //4
    int Data_8; //8
    uint16_t wData_0xc; //12
    uint16_t wData_0xe; //14
    //16???
};


struct UdiCtrl
{
    int fill_0; //0
    int Data_4; //4
    struct ArrayClass* Data_8; //8
    //???
};


struct Struct_10acec
{
    int Data_0; //0
    int Data_4; //4
    int Data_8; //8
    int Data_0xc; //0xc
    int Data_0x10; //0x10
    int Data_0x14; //20
    void (*Data_0x18)(); //24
    void (*on_insertion)(); //28
    void (*Data_0x20)(); //32
    //???
};


struct ArrayClass
{
    int Data_0; //0
    int Data_4; //4
    int Data_8; //8
    int Data_0xc; //0xc
    int Data_0x10; //0x10
    int Data_0x14; //20
    int fill_0x18[2]; //0x18
    int Data_0x20; //0x20
    void (*on_insertion)(int, int, int, int); //0x24
    int Data_0x28; //0x28
    uint8_t bData_0x2c; //0x2c
    //0x30
};


struct UsbConfiguration
{
    int fill_0; //0
    usbd_configuration_descriptor_t configuration_descriptor; //4 +9 = 0x0d
    struct UsbConfiguration* next; //0x10
    struct UsbInterface* interfaces; //0x14
    struct USB_Controller_Inner_0x7c* Data_0x18; //0x18
    //0x1c
};


struct UsbInterface
{
    int fill_0[2];
    usbd_interface_descriptor_t Data_8; //8 +9 = 0x11
    int Data_0x14; //0x14
    int fill_0x18; //0x18
    struct UsbInterface* next; //0x1c = 28
    struct UsbEndpoint* endpoints; //0x20 = 32
    struct UsbConfiguration* Data_0x24; //0x24 = 36
    //0x28
};


struct UsbEndpoint
{
    usbd_endpoint_descriptor_t endpoint_descriptor; //0
    struct UsbEndpoint* next; //8
    struct Struct_0xa4* Data_0xc; //0xc
    struct UsbInterface* interface; //0x10
    int Data_0x14; //0x14
    struct 
    {
        int Data_0; //0
        //???
    }* Data_0x18; //0x18
    int Data_0x1c; //0x1c
    struct 
    {
        int Data_0; //0
        //???
    }* Data_0x20; //0x20
    int Data_0x24; //0x24
    int Data_0x28; //0x28
    int fill_0x2c; //0x2c
    pthread_mutex_t Data_0x30; //0x30
    pthread_cond_t Data_0x38; //0x38
    //0x40
};
#if 0
struct Struct_112b08
{
    uint16_t fill_0; //0
    uint8_t bEndpointAddress; //2
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
#endif


struct Struct_120220
{
    int fill_0; //0
    uint8_t bData_4[16]; //4
#if 0
    int fill_8; //8
    pthread_mutex_t Data_0x18[16]; //0x18
    int fill_0x98[15]; //0x98
#else
    struct 
    {
        int Data_0; //0
        pthread_mutex_t Data_4; //4
        //12???
    } Data_0x14[16]; //0x14
#endif
    //0xd4
};


struct Struct_114194
{
    struct Struct_114194* Data_0; //0
    struct Struct_114194** Data_4; //4
    usbd_device_instance_t Data_8; //8
    //0x2c
};


struct USB_Client
{
    struct 
    {
        int fill_0; //0
        void* Data_4; //4
        //???
    }* Data_0; 
    struct
    {
        int Data_0; //0
        //???
    }* Data_4; //4
    pthread_mutex_t Data_8; //8
    int Data_0x10; //0x10
    int Data_0x14; //0x14
    int fill_0x18; //0x18
    struct Struct_114194* Data_0x1c; //0x1c
    struct Struct_114194* Data_0x20; //0x20
    int Data_0x24; //0x24
    int* Data_0x28; //0x28
    //0x2c = 44
};


extern int sub_1047a8(struct Struct_1047a8**, int);
extern int usb_slogf(int opcode, int severity, int v, const char* fmt, ...);


extern struct USB_Controller usb_controllers[]; //0x0011f590 +0x14*0x8c
extern struct USB_Controller* ausb_controllers[]; //0x001201c0
extern void* Data_12021c; //12021c
extern struct Struct_120220 Data_120220[]; //0x120220
extern struct UsbdiGlobals UsbdiGlobals; //0x001212b0
extern int usb_enum_priority; //0x00121574
extern int Data_1273b0; //1273b0
extern int Data_127814; //127814
extern pthread_rwlock_t usb_rwlock; //0x00127834


