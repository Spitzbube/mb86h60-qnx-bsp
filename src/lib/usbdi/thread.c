
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>
#include <sys/usbdi.h>
#include "device.h"


//_GLOBAL_OFFSET_TABLE_:
//0x0000b3ec

struct usbd_connection
{
    const char* Data_0; //0
    int fill_4; //4
    int Data_8; //8
    int Data_0xc; //0xc
    char** Data_0x10; //0x10
    int Data_0x14; //0x14
    usbd_device_ident_t* Data_0x18; //0x18
    usbd_funcs_t* Data_0x1c; //0x1c
    uint16_t connect_wait; //0x20
    uint8_t bData_0x22; //0x22
    int fill_0x24[3]; //0x24
    int Data_0x30; //0x30
    int Data_0x34; //0x34
    int Data_0x38; //0x38
    int* Data_0x3c; //0x3c
    void* Data_0x40; //0x40
    usbd_device_ident_t Data_0x44;
    usbd_funcs_t Data_0x58;
    struct
    {
        int fill_0[1]; //0
        //???
    } Data_0x68;
    //???
};


struct
{
    int fill_0[2]; //0
    int Data_8; //8
    int Data_0xc; //12
    int fill_0x10[10]; //0x10
    int Data_0x38; //0x38
    struct usbd_connection* Data_0x3c; //0x3c
    //???
} Data_b698; //0x0000b698
pthread_mutex_t conn_mutex; //0x0000b780


/* 0x00007d8c - todo */
static void* eventloop(void* a)
{
    fprintf(stderr, "eventloop: TODO\n");
}


/* 0x000081d4 - todo */
int usbdi_open(struct usbd_connection* r4, int r8)
{
    int i;
    int r6 = (r4->Data_0x1c->removal != NULL) || 
        (r4->Data_0x1c->insertion != NULL);

    int r7 = r4->connect_wait;

    for (i = 0; i != r7; i++)
    {
        r4->Data_0x30 = open(r4->Data_0, r6? O_RDWR: O_RDONLY);
        if (r4->Data_0x30 != -1)
        {
            break;
        }

        if (r8 != 0)
        {
            r4->Data_0x30 = open("/dev/usb", r6? O_RDWR: O_RDONLY);
            if (r4->Data_0x30 != -1)
            {
                break;
            }
        }

        sleep(1);        
    } //for (i = 0; i != r7; i++)

    return r4->Data_0x30;
}


/* 0x00008308 - todo */
int	usbd_connect(usbd_connect_parm_t *parm/*r5*/, 
        struct usbd_connection **connection/*fp*/)
{
    int res;

    struct 
    {
        int Data_0; //0
        uint16_t wData_4; //4
        uint16_t wData_6; //6
        int fill_8[26]; //8
        //0x70
    } sp_0x90;
    pthread_t sp_0x8c;
    int sp_0x88;
    sigset_t sp_0x80;
    sigset_t sp_0x78;    
    struct sched_param sp_0x50;
    pthread_attr_t sp4;

    struct usbd_connection* r4;

#if 1
    fprintf(stderr, "usbd_connect: TODO!!!\n");
#endif
    
    if ((parm->vusbd != 0) && (parm->vusbd != USBD_VERSION))
    {
        return 0x113;
    }

    int sl = (parm->funcs != 0);
    uint32_t r8 = 0;
    if (sl)
    {
        r8 = parm->evtbufsz;
        if (r8 < 0x6c)
        {
            r8 = 0x1000;
        }
    }
    //loc_835c
    uint32_t sb = r8;
    
    r4 = calloc(1, r8 + 0x68);
    if (r4 == NULL)
    {
        return 12;
    }

    r4->Data_0x38 = 0;
    r4->Data_0x3c = &r4->Data_0x38;
    const char* path = parm->path;
    r4->Data_0 = (path == NULL)? "/dev/io-usb/io-usb": path;
    r4->Data_8 = parm->flags;
    r4->Data_0xc = parm->argc;
    r4->Data_0x10 = parm->argv;
    r4->connect_wait = (parm->connect_wait == 0)? 1: parm->connect_wait;
    r4->Data_0x14 = sb;
    r4->bData_0x22 = parm->evtprio;
    usbd_device_ident_t* ip = &r4->Data_0x44;
    r4->Data_0x18 = ip;
    usbd_funcs_t* lr = &r4->Data_0x58;
    r4->Data_0x1c = lr;
    r4->Data_0x40 = (r8 == 0)? NULL: &r4->Data_0x68;
    r4->Data_0x34 = -1;

    if (parm->ident != NULL)
    {
//        memcpy(&r4->Data_0x44, parm->ident, 20);
        *ip = *parm->ident;
        //->loc_843c
    }
    else
    {
        //loc_8424
        ip->vendor = -1;
        ip->device = -1;
        ip->dclass = -1;
        ip->subclass = -1;
        ip->protocol = -1;
    }
    //loc_843c
    if (parm->funcs != NULL)
    {
        *lr = *parm->funcs;
    }
    else{
        lr->nentries = 3;
        lr->insertion = NULL;
        lr->removal = NULL;
        lr->event = NULL;
    }

    r4->Data_0x30 = usbdi_open(r4, (path == NULL));
    if (r4->Data_0x30 == -1)
    {
        //->loc_8660
        res = errno;
        //loc_8668
        free(r4);
        return res;
    }
    //0x0000847c
    int r1;
    int r2;
    int r3;
    if (sl != 0)
    {
        r1 = 7;
    }
    else
    {
        r1 = 0;
    }

    r3 = parm->flags;
    if (r3 & 1)
    {
        r2 = 8;
    }
    else
    {
        r2 = 0;
    }

    r3 &= 0x80000000;
    r3 |= r1;
    r3 |= r2;

    sp_0x90.Data_0 = r3;
    sp_0x90.wData_4 = parm->vusb;
    sp_0x90.wData_6 = parm->vusbd;

    pthread_mutex_lock(&conn_mutex);

    res = usbdi_sendcmd(r4->Data_0x30, 1, &sp_0x90, NULL);
    if (res != 0)
    {
        //loc_8630
        usbdi_memchunk_destroy(Data_b698.Data_8);
        usbdi_memchunk_destroy(Data_b698.Data_0xc);
        pthread_mutex_unlock(&conn_mutex);
        close(r4->Data_0x30);
        free(r4);
        return res;
    }
    //0x000084e0
    sp_0x8c = -1;

    usbdi_memory_info(r4);

    res = usbdi_init_client_globals();
    if (res != 0)
    {
        free(r4);
        pthread_mutex_unlock(&conn_mutex);
        return 12;
    }
    //loc_8518
    if (sl != 0)
    {
        pthread_attr_init(&sp4);
        pthread_getschedparam(pthread_self(), &sp_0x88, &sp_0x50);

        if (r4->bData_0x22 != 0)
        {
            sp_0x50.sched_priority = r4->bData_0x22;
        }
        pthread_attr_setschedpolicy(&sp4, 2);
        pthread_attr_setschedparam(&sp4, &sp_0x50);
        pthread_attr_setinheritsched(&sp4, 2);
        pthread_attr_setstacksize(&sp4, 0x4000);
        sigfillset(&sp_0x80);
        pthread_sigmask(2, &sp_0x80, &sp_0x78);
        res = pthread_create(&sp_0x8c, &sp4, eventloop, r4);
        pthread_sigmask(2, &sp_0x78, 0);
        pthread_attr_destroy(&sp4);

        if (res != 0)
        {
            //loc_8630
            usbdi_memchunk_destroy(Data_b698.Data_8);
            usbdi_memchunk_destroy(Data_b698.Data_0xc);
            pthread_mutex_unlock(&conn_mutex);
            close(r4->Data_0x30);
            free(r4);
            return res;
        }
    }
    //loc_85d4
    *connection = r4;

    pthread_sleepon_lock();

    r4->Data_0x34 = sp_0x8c;

    pthread_sleepon_signal(&r4->Data_0x34);
    pthread_sleepon_unlock();

    if (Data_b698.Data_0x38 == 0)
    {
        Data_b698.Data_0x3c = r4;
    }

    Data_b698.Data_0x38++;

    pthread_mutex_unlock(&conn_mutex);
    //->loc_8674
    return res;
}



/* 0x00007a64 - todo */
int usbd_disconnect(struct usbd_connection *connection)
{
    fprintf(stderr, "usbd_disconnect: TODO!!!\n");

    return 0;
}


/* 0x00007934 - todo */
int usbd_hcd_ext_info(struct usbd_connection *connection, 
        _Uint32t cindex, usbd_hcd_info_t *info/*r4*/)
{
#if 1
    fprintf(stderr, "usbd_hcd_ext_info: cindex=%d: TODO!!!\n", cindex);
#endif

    struct 
    {
        usbd_hcd_info_t sp_0xc; //?
        int fill[16]; //?
        struct Struct_5a24 Data_0;
    } sp_0x70;
    struct Struct_5a24_d sp4;
 
    sp_0x70.Data_0.Data_0 = cindex;
    sp4.wData_2 = 0x6c;

    int res = usbdi_sendcmd(connection->Data_0x30,
                7, &sp_0x70.Data_0, &sp4);
#if 1
    fprintf(stderr, "usbd_hcd_ext_info: res=%d: TODO!!!\n", res);
#endif

    if (res == 0)
    {
        memcpy(info, &sp_0x70.sp_0xc, sizeof(usbd_hcd_info_t));
    }

    return res;
}



