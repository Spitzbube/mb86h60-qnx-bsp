
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>
#include <sys/neutrino.h>
#include <sys/resmgr.h>
#include <sys/usbdi.h>
#include "usbdi_priv.h"


/* 0x00005a24 - todo */
int usbdi_sendcmd(int sp_0xc, int r8, 
    struct Struct_5a24* sl, 
    struct Struct_5a24_d* r7)
{
    int r6;
    uint16_t r5;
    uint16_t r4;

    io_msg_t sp_0x230;
    iov_t sp_0x28[66]; //0x28/0x2c
    iov_t sp_0x18; //0x18/0x1c
    struct Struct_5a24* sp_0x14;
//    int sp_0x10;

#if 1
    fprintf(stderr, "usbdi_sendcmd: sp_0xc=%d, r8=%d, sl=%p, r7=%p(%d)\n", 
        sp_0xc, r8, sl, r7, (r7 != NULL)? r7->wData_2: 0);
#endif

    sp_0x230.i.type = 0x113;
    sp_0x230.i.combine_len = 8;
    sp_0x230.i.mgrid = _IOMGR_USB;
    sp_0x230.i.subtype = r8;

    SETIOV(&sp_0x28[0], &sp_0x230, 8);

    if (sl == NULL)
    {
        r4 = 0;
        r5 = 1;
        //->loc_5bbc
    }
    else
    {
        //0x00005a74
        if (r8 == 5)
        {
            //0x00005a7c
            sp_0x14 = sl;
            struct Struct_5a24* r4_ = sl;
            //r5 = 1;
            //int fp = 1;
            iov_t* r6 = &sp_0x28[0];
            //int sb = 0x70;
            //sp_0x10 = 0;
            //->loc_5b4c
            for (r5 = 1; (r4_ != 0) &&  (r5 < 0x41); )
            //while ((r4_ != 0) && (r5 < 0x41))
            {
                //loc_5aa0
                if (r4_->Data_0x10 != 0)
                {
                    atomic_add(&r4_->Data_0x10->Data_0xc, 1/*fp*/);
                }
                //loc_5ab8
                SETIOV(&r6[r5], r4_, 0x70/*sb*/);

                sp_0x230.i.combine_len += 0x70;

                r5++;

                if (r4_->Data_0x24 & 0x200000)
                {
                    //0x00005ae8
                    SETIOV(&r6[r5], r4_->Data_0x60, r4_->wData_0x5e);

                    sp_0x230.i.combine_len += r4_->wData_0x5e;

                    r5++;
                }
                //loc_5b10
                if ((r4_->Data_0x24 & 0x100000) == 0)
                {
                    r4_->wData_0x68 = 0;
                    //->loc_5b64
                    break;
                }
                //0x00005b24
                struct Struct_5a24* r3 = r4_->Data_4;
                if (r3 == NULL)
                {
                    r4_->wData_0x68 = 0;
                    r4_ = NULL/*sp_0x10*/;
                }
                else
                {
                    r4_->wData_0x68 = sp_0x230.i.combine_len - 8;
                    r4_ = r3;
                }
                //loc_5b4c
            } //while ((r4_ != 0) &&  (i < 0x41))
            //loc_5b64
            if ((sp_0x14->Data_0x10 == NULL) ||
                (sp_0x14->Data_0x10->Data_0x14 != 0) ||
                ((sp_0x14->Data_0x24 & 0x40000) == 0))
            {
                //loc_5bb8
                r4 = 0;
            }
            else
            {
                r4 = 1;
                //loc_5bbc
            }
        } //if (r8 == 5)
        else
        {
            //loc_5b94
            sp_0x230.i.combine_len = 0x78;
            
            SETIOV(&sp_0x28[1], sl, 0x70);

            r4 = 0;
            r5 = 2;
            //->loc_5bbc
        }
    } //(sl != NULL)
    //loc_5bbc
    if (r7 != NULL)
    {
        SETIOV(&sp_0x18, r7, r7->wData_2);
    }

    if (r5 > 0x41)
    {
        r6 = 0x1c;
        //->loc_5bfc
    }
    else
    {
        //0x00005bd8
        r6 = 0 - MsgSendv_r(sp_0xc, 
            &sp_0x28[0], r5, 
            &sp_0x18, (r7 != NULL)? 1: 0);
    }
    //loc_5bfc
    if ((sl != NULL) && (r8 == 5))
    {
        //0x00005c18
        if (r6 != 0)
        {
            if (sl != NULL)
            {
                //0x00005c28
                r4 = 1;

                while ((sl != NULL) && (r4 < 0x41))
                {
                    //loc_5c30
                    if (sl->Data_0x10 != NULL)
                    {
                        atomic_sub(&sl->Data_0x10->Data_0xc, 1);
                    }
                    //loc_5c48
                    if (sl->Data_0x24 & 0x200000)
                    {
                        r4++;
                    }

                    if ((sl->Data_0x24 & 0x100000) == 0)
                    {
                        //->loc_5ca0
                        break;
                    }
                    //0x00005c60
                    sl = sl->Data_4;
                    r4++;
                } //while ((sl != NULL) && (r4 < 0x41))
                //loc_5ca0
            }
            //loc_5ca0
        } //if (r6 != 0)
        //loc_5c88
        else if (r4 != 0)
        {
            //0x00005c90
            atomic_sub(&sl->Data_0x10->Data_0xc, 1);
        }
    }
    //loc_5ca0
    return r6;
}


