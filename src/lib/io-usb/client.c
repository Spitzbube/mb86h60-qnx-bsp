

#include "externs.h"


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
    int Data_0x1c; //0x1c
    int* Data_0x20; //0x20
    int Data_0x24; //0x24
    int* Data_0x28; //0x28
    //0x2c = 44
};


/* 114ab4 - complete */
int usbdi_client_create(int r6, struct USB_Client** pclient)
{
#if 0
    fprintf(stderr, "usbdi_client_create: TODO!!!\n");
#endif

    int res;
    struct USB_Client* client = malloc(sizeof(struct USB_Client));
    if (client == NULL)
    {
        return 12;
    }

    res = pthread_mutex_init(&client->Data_8, 0);
    if (res != 0)
    {
        free(client);
        return res;
    }

    client->Data_0x10 = r6;
    client->Data_0x14 = -1;
    client->Data_0x1c = 0;
    client->Data_0x20 = &client->Data_0x1c;
    client->Data_0x24 = 0;
    client->Data_0x28 = &client->Data_0x24;
    client->Data_0 = UsbdiGlobals.Data_0x24;
    if (client->Data_0 != 0)
    {
        client->Data_0->Data_4 = client;
    }
    else
    {
        UsbdiGlobals.Data_0x28 = client;
    }
    UsbdiGlobals.Data_0x24 = client;
    client->Data_4 = &UsbdiGlobals.Data_0x24;

    *pclient = client;

    return res;
}


/* 0x001149a4 - todo */
int usbdi_client_destroy(struct USB_Client* client)
{
#if 0
    fprintf(stderr, "usbdi_client_destroy: TODO\n");
#endif

    pthread_mutex_lock(&UsbdiGlobals.Data_0);

    if (client->Data_0 != 0)
    {
        client->Data_0->Data_4 = client->Data_4;
    }
    else
    {
        UsbdiGlobals.Data_0x28 = client->Data_4;
    }

    client->Data_4->Data_0 = client->Data_0;

    pthread_mutex_unlock(&UsbdiGlobals.Data_0);

    pthread_mutex_lock(&client->Data_8);

    if (client->Data_0x14 != -1)
    {
        MsgError_r(client->Data_0x14, 9);

        client->Data_0x14 = -1;
    }
    //loc_114a18
    struct
    {
        struct
        {
            int fill_0; //0
            int Data_4; //4
            //???
        }* Data_0; //0
        struct
        {
            int Data_0; //0
            //???
        }* Data_4; //4
        int Data_8; //8
        //???
    }* r4 = client->Data_0x1c;
    while (r4 != NULL)
    {
        //loc_114a2c
        if (r4->Data_0 != 0)
        {
            r4->Data_0->Data_4 = r4->Data_4;
        }
        else
        {
            client->Data_0x20 = r4->Data_4;
        }

        r4->Data_4->Data_0 = r4->Data_0;
        void* r5 = r4->Data_0;

        pthread_mutex_unlock(&client->Data_8);

        udi_detach(client, &r4->Data_8, client->Data_0x10);

        pthread_mutex_lock(&client->Data_8);

        usbdi_memchunk_free(UsbdiGlobals.Data_0xc, r4);

        //if (r5 == NULL) break;
        r4 = r5;
    } //while (r4 != NULL)
    //loc_114a8c
    return dequeue(&client->Data_0x24);
}


