
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

#if 0
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

#if 1
    fprintf(stderr, "usbd_connect: r4=%p, r4->Data_0x30=%d\n", 
        r4, r4->Data_0x30);
#endif

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


/* 0x00007934 - complete */
int usbd_hcd_ext_info(struct usbd_connection* connection, 
        _Uint32t cindex, usbd_hcd_info_t* info/*r4*/)
{
#if 0
    fprintf(stderr, "usbd_hcd_ext_info: connection=%p, connection->Data_0x30=%d, cindex=%d\n", 
        connection, connection->Data_0x30, cindex);
#endif

    struct Struct_5a24 sp_0x70;
    struct
    {
        struct Struct_5a24_d Data_0; //0
        usbd_hcd_info_t Data_8; //8 +0x24
        int fill[16]; //0x2c +0x40
        //0x6c
    } sp4;    
 
    sp_0x70.Data_0 = cindex;
    sp4.Data_0.wData_2 = sizeof(sp4);

    int res = usbdi_sendcmd(connection->Data_0x30,
                7, &sp_0x70, &sp4);

    if (res == 0)
    {
        memcpy(info, &sp4.Data_8, sizeof(usbd_hcd_info_t));
    }

    return res;
}


/* 0x000078c4 - complete */
int usbd_topology_ext(struct usbd_connection *connection, 
        _Uint8t busno, usbd_bus_topology_t *tp)
{
#if 0
    fprintf(stderr, "usbd_topology_ext: connection=%p: TODO!!!\n", 
        connection);
#endif

    struct Struct_5a24 sp_0x270;
    struct
    {
        struct Struct_5a24_d Data_0; //0
        int fill_8[25]; //8 +0x64
        usbd_bus_topology_t Data_0x6c; //0x6c +0x200
        //0x26c
    } sp4;    

    sp_0x270.Data_0 = busno;
    sp4.Data_0.wData_2 = sizeof(sp4);

    int res = usbdi_sendcmd(connection->Data_0x30,
                10, &sp_0x270, &sp4);

#if 0
    fprintf(stderr, "usbd_topology_ext: res=%d\n", res);
#endif
    
    if (res == 0)
    {
        memcpy(tp, &sp4.Data_0x6c, sizeof(usbd_bus_topology_t));
    }

    return res;
}


/* 0x00005f34 - todo */
int usbd_attach(struct usbd_connection* connection/*r6*/, 
        usbd_device_instance_t* instance/*sl*/, 
        size_t extra/*r8*/, 
        struct usbd_device** device/*fp*/)
{
#if 1
    fprintf(stderr, "usbd_attach: connection=%p: TODO!!!\n", 
        connection);
#endif

    struct usbd_device* r4 = calloc(1, sizeof(struct usbd_device) + extra);
    if (r4 == NULL)
    {
        return 12;
    }

    struct Struct_5a24 sp_0x70;
    struct
    {
        struct Struct_5a24_d1 Data_0; //0
        usbd_device_instance_t Data_4; //4 +0x24
        int fill[17]; //0x28 +0x44
        //0x6c
    } sp4;    
 
    memcpy(&sp_0x70, instance, sizeof(usbd_device_instance_t));
    sp4.Data_0.wData_2 = sizeof(sp4);

    int res = usbdi_sendcmd(connection->Data_0x30,
                3, &sp_0x70, &sp4);
    if (res == 0)
    {
        r4->Data_8 = connection;
        r4->Data_0xc = 0; //r7
        r4->Data_0x10 = &r4->Data_0xc;
        r4->Data_0x14 = 0;
        r4->Data_0x18 = 0;

        memcpy(instance, &sp4.Data_4, sizeof(usbd_device_instance_t));
        memcpy(&r4->Data_0x1c, &sp4.Data_4, sizeof(usbd_device_instance_t));

#if 1
        fprintf(stderr, "usbd_attach: generation=%d, ident.vendor=0x%x, ident.device=0x%x\n", 
            instance->generation, instance->ident.vendor, instance->ident.device);
#endif

        r4->Data_0x40 = 0; //r7
        r4->Data_0x44 = (extra != 0)? r4 + 1: NULL;

#if 0 //TODO!!!
        pthread_mutex_lock(&r5->Data_0x2ac/*B698*/);
#endif

        r4->Data_0 = 0;
        r4->Data_4 = connection->Data_0x3c;
        *(r4->Data_4) = r4;
        connection->Data_0x3c = r4;

#if 0 //TODO!!!
        pthread_mutex_unlock(&r5->Data_0x2ac/*B698*/);
#endif

        *device = r4;
    }
    else
    {
        //loc_6058
        free(r4);
        return res;
    }

    return res;
}


void* usbd_alloc(size_t size)
{
#if 1
    fprintf(stderr, "usbd_alloc: a=%d: TODO!!!\n", size);
#endif

    return malloc(size);
}


void usbd_free(void *ptr)
{
#if 1
    fprintf(stderr, "usbd_free: ptr=%p: TODO!!!\n", ptr);
#endif

}


paddr_t usbd_mphys(const void *ptr)
{
#if 1
    fprintf(stderr, "usbd_mphys: ptr=%p: TODO!!!\n", ptr);
#endif

    return ptr;
}



/* 0x00009384 - todo */
struct usbd_urb* usbd_alloc_urb(struct usbd_urb *link/*r4*/)
{
#if 0
    fprintf(stderr, "usbd_alloc_urb: TODO!!!\n");
#endif

    struct Struct_5a24* r0 = usbdi_memchunk_calloc(0/*TODO!!!*/, 1, 0x70);

    if (r0 != NULL)
    {
        r0->Data_0 = r0;
        r0->wData_0x20 = 0x70;

        if (link != NULL)
        {
            struct Struct_5a24* link1 = link;

            link1->Data_4 = r0;
            link1->Data_0x24 |= 0x100000;
            r0->Data_0x24 |= 0x100000;
        }
    }

    return r0;
}



/* 0x000093f0 - todo */
int usbdi_sync_io(struct usbd_device *device/*r5*/, 
        int b/*r7*/, 
        int c/*r8*/, 
        int d/*fp*/, 
        int e, 
        int f, 
        int g,
        int h, 
        void* i, 
        int* j)
{
#if 1
    fprintf(stderr, "usbdi_sync_io: TODO!!!\n");
#endif

    struct Struct_5a24 sp_0x78; //+0x70 = 0xe8
    struct
    {
        struct Struct_5a24_d1 Data_0;
        int fill_4[26]; //4
        //0x6c;
    } sp_0xc;

    struct usbd_urb* r4 = usbd_alloc_urb(NULL);

    memcpy(&sp_0x78/*r6*/, r4, 0x70);

    sp_0xc.Data_0.wData_2 = 0x6c;

    int r6_ = usbdi_sendcmd(device->Data_8->Data_0x30,
                5, &sp_0x78/*r6*/, &sp_0xc);

#if 1
    fprintf(stderr, "usbdi_sync_io: r6_=%d: TODO!!!\n", r6_);
#endif

    //TODO!!!

    return 0;
}



/* 0x00009644 - todo */
int usbd_descriptor(struct usbd_device *device/*sl*/, 
    int set/*r8*/, 
    _Uint8t type/*fp*/, 
    _Uint16t rtype/*sb*/, 
    _Uint8t index/*arg0: sp_0x1c*/, 
    _Uint16t langid/*arg4: sp_0x20*/, 
    _Uint8t *desc/*arg8*/, 
    size_t len/*argc: r6*/)
{
#if 1
    fprintf(stderr, "usbd_descriptor: type=%d, index=%d: TODO!!!\n", 
        type, index);
#endif

    int sp_0x2c;
    int sp_0x24;

    int r5;
    void* r7;

    if (len == 0)
    {
        return 0xf0; //->loc_977c
    }

    sp_0x2c = len;
    r7 = usbd_alloc(len);
    if (r7 == NULL)
    {
        return 12;
    }

    if (set == 0)
    {
        //0x000096a4
        r5 = 0x20005;
        sp_0x24 = 6;
        //->loc_96d8
    }
    else
    {
        //loc_96b8
        memcpy(r7, desc, sp_0x2c);

        r5 = 0x20006;
        sp_0x24 = 7;
    }
    //loc_96d8
    int r5_ = usbdi_sync_io(device/*sl*/, 
            5, r5, sp_0x24, 
            rtype/*sb*/, 
            index/*sp_0x1c*/ | (type/*fp*/ << 8),
            langid/*sp_0x20*/,
            0, usbd_mphys(r7), &sp_0x2c);
    if (r5_ == 0)
    {
        if (set/*r8*/ != 0)
        {
            //0x00009730
            fprintf(stderr, "usbd_descriptor: 0x00009730: TODO!!!\n");

            //TODO!!!

            //->loc_9774
        }
        else
        {
            //loc_9750
            if (len/*r6*/ < ((uint8_t*)r7)[0])
            {
                r5_ = 0xf0;
            }

            memcpy(desc, r7, (len < sp_0x2c)? len: sp_0x2c);
        }
    }
    //loc_9774
    usbd_free(r7);

    return r5_;    
}



/* 0x0000485c - todo */
usbd_descriptors_t* usbd_parse_descriptors(struct usbd_device* device/*sb*/, 
    struct usbd_desc_node* root, 
    _Uint8t type/*r6*/, 
    int index/*r4*/, 
    struct usbd_desc_node** node)
{
#if 1
    fprintf(stderr, "usbd_parse_descriptors: index=%d: TODO!!!\n", 
        index);
#endif

    if (device->Data_0x40 == 0)
    {
        //0x00004884
//        fprintf(stderr, "usbd_parse_descriptors: 0x00004884: TODO!!!\n"); 
        if (root == NULL)
        {
            //0x0000488c
            uint32_t r5 = 0x1f6;
            int sp_0x8c;
            int sp_0x88;
            int sp_0x84;
            int sp_0x78;
            int sp_0x58;
            int sp_0x54;
            int sp_0x48;
            int sp_0x44;
            int sp_0x24;
            int sp_0x20;
            int sp_0x1c;
            uint32_t sp_0x18;
            void* sp_0x14;
            void* r7;
            
            sp_0x18 = 0xf6;
            r7 = NULL;
            sp_0x14 = NULL; //r7

            sp_0x1c = 0x2ac;
            sp_0x24 = &sp_0x84;
            sp_0x20 = &sp_0x54;
            sp_0x44 = &sp_0x58;
            sp_0x48 = &sp_0x78;
            int fp = type;
            int r6 = index;
            //->loc_48e8
//            while (1) //???
            {
                //->loc_48e8
                if (sp_0x14 == NULL)
                {
                    //0x000048f4
                    sp_0x14 = usbdi_memchunk_malloc(
                                0, //(_GLOBAL_OFFSET_TABLE_ + sp_0x1c = B698)->Data_8,
                                sp_0x18);
                    if (sp_0x14 == NULL)
                    {
                        //->loc_50a8
                        usbdi_memchunk_free(
                            0, //(_GLOBAL_OFFSET_TABLE_ + sp_0x1c = B698)->Data_8,
                            r7);
                        usbdi_memchunk_free(
                            0, //(_GLOBAL_OFFSET_TABLE_ + sp_0x1c = B698)->Data_8,
                            sp_0x14);
                        //sl = 12;
                        //->loc_4ffc
                        errno = 12;
                        return NULL;
                    }
                }
                //loc_4914
                if (r7 == NULL)
                {
                    //0x0000491c
                    r7 = usbdi_memchunk_malloc(
                                0, //(_GLOBAL_OFFSET_TABLE_ + sp_0x1c = B698)->Data_8,
                                r5);
                    if (r7 == NULL)
                    {
                        //->loc_50a8
                        usbdi_memchunk_free(
                            0, //(_GLOBAL_OFFSET_TABLE_ + sp_0x1c = B698)->Data_8,
                            r7);
                        usbdi_memchunk_free(
                            0, //(_GLOBAL_OFFSET_TABLE_ + sp_0x1c = B698)->Data_8,
                            sp_0x14);
                        //sl = 12;
                        //->loc_4ffc
                        errno = 12;
                        return NULL;
                    }
                }
                //loc_4938
                sp_0x8c = r7;
                sp_0x88 = r5;

                if (sp_0x18 > 0x11)
                {
                    //0x0000494c
                    int r0 = usbd_descriptor(device/*sb*/, 
                                0, 1, 0, 0, 0, sp_0x14, 0x12);
                    if (r0 != 0)
                    {
                        //->loc_4f50
                        fprintf(stderr, "usbd_parse_descriptors: loc_4f50: TODO!!!\n");
                    }
                    //0x0000498c
                    fprintf(stderr, "usbd_parse_descriptors: 0x0000498c: TODO!!!\n");
                }
                //loc_4f74

            } //while (1) //???
        }
        else
        {
            //loc_48d4
            errno = 0x7a;
            return NULL; //->loc_5080
        }
        //loc_48e8
    }
    else
    {
        //loc_500c
        fprintf(stderr, "usbd_parse_descriptors: loc_500c: TODO!!!\n"); 

    }

    return 0;
}



