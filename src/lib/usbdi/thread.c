
#include <stdint.h>
#include <stdlib.h>
#include <sys/usbdi.h>





/* 0x000009ac - todo */
int	usbd_connect(usbd_connect_parm_t *parm/*r5*/, 
        struct usbd_connection **connection/*sb*/)
{
    struct
    {
        const char* Data_0; //0
        int fill_4; //4
        int Data_8; //8
        int Data_0xc; //0xc
        char** Data_0x10; //0x10
        int Data_0x14; //0x14
        int fill_0x18[2]; //0x18
        uint16_t wData_0x20; //0x20
        uint8_t bData_0x22; //0x22
        int fill_0x24[5]; //0x24
        int Data_0x38; //0x38
        int* Data_0x3c; //0x3c
        //???
    }* r4;
    
    if ((parm->vusbd != 0) && (parm->vusbd != 0x101))
    {
        return 0x113;
    }

    int r8 = (parm->funcs != 0);
    uint32_t r6 = 0;
    if (r8)
    {
        r6 = parm->evtbufsz;
        if (r6 < 0x6c)
        {
            r6 = 0x1000;
        }
    }
    //loc_9f8
    uint32_t sl = r6;
    
    r4 = calloc(1, r6 + 0x68);
    if (r4 == NULL)
    {
        return 12;
    }

    r4->Data_0x38 = 0;
    r4->Data_0x3c = &r4->Data_0x38;
    const char* r7 = parm->path;
    r4->Data_0 = (r7 != NULL)? r7: NULL;
    r4->Data_8 = parm->flags;
    r4->Data_0xc = parm->argc;
    r4->Data_0x10 = parm->argv;
    r4->wData_0x20 = (parm->connect_wait == 0)? 1: parm->connect_wait;
    r4->Data_0x14 = r6;
    r4->bData_0x22 = parm->evtprio;

    //TODO!!!

    return 0;
}

