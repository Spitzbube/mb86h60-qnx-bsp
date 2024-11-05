
#include "io-usb.h"

struct UsbdiGlobals_Inner_0x178
{
    void* hDll; //0
    struct io_usb_dll_entry_t* pDllEntry; //4
    int fill_8; //8
    int Data_0xc; //12
    int fill_0x10[2]; //16
    int Data_0x18; //0x18 = 24
    volatile unsigned int Data_0x1c; //0x1c = 28
    int fill_0x20[21]; //0x20
    pthread_t Data_0x74; //0x74
    struct UsbdiGlobals_Inner_0x178* Data_0x78; //0x78
    //0x7c???
};

