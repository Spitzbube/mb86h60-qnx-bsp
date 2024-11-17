
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    int Data_0x24; //0x24
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
    void (*Data_0x1c)(); //28
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
    int Data_0x24; //0x24
    int Data_0x28; //0x28
    uint8_t bData_0x2c; //0x2c
    //0x30
};


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


extern int sub_1047a8(struct Struct_1047a8**, int);

extern struct USB_Controller usb_controllers[]; //0x0011f590 +0x14*0x8c
extern void* Data_12021c; //12021c
extern struct Struct_120220 Data_120220[]; //0x120220
extern struct UsbdiGlobals UsbdiGlobals; //0x001212b0
extern int usb_enum_priority; //0x00121574
extern int Data_1273b0; //1273b0
extern int Data_127814; //127814
extern pthread_rwlock_t usb_rwlock; //0x00127834


