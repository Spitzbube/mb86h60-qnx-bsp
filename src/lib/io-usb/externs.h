
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
#include <sys/dispatch.h>
#include <sys/iofunc.h>
#include <sys/iofunc.h>
#include <sys/resmgr.h>
#include <pthread.h>

#include "io-usb.h"

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
    int fill_0x24[10]; //0x24
    int Data_0x4c; //0x4c
    int fill_0x50[9]; //0x50
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
    //TODO
    struct UsbdiGlobals_Inner_0x178* Data_0x178; //0x178
    int fill_0x17c; //0x17c
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


struct USB_Controller
{
    int fill_0[27]; //0
    uint32_t Data_0x6c; //0x6c
    int fill_0x70[11]; //0x70
    //0x9c
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



extern struct UsbdiGlobals UsbdiGlobals; //0x001212b0
extern int usb_enum_priority; //0x00121574
extern int Data_1273b0; //1273b0
extern int Data_127814; //127814
extern pthread_rwlock_t usb_rwlock; //0x00127834


