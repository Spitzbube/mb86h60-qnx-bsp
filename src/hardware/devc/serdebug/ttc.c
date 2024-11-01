
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <malloc.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include <termios.h>
#include <devctl.h>
#include <sys/dcmd_chr.h>
#include <sys/iomsg.h>
#include <atomic.h>
#include <hw/inout.h>
#include <sys/slog.h>
#include <sys/dispatch.h>
#include <sys/io-char.h>


extern TTYCTRL ttyctrl;
extern int my_tte(message_context_t *ctp, int code, unsigned flags, void *handle);
extern int my_timer_tick(message_context_t *ctp, int code, unsigned flags, void *handle);

#if 0
resmgr_connect_funcs_t iochar_connect_funcs;
resmgr_io_funcs_t iochar_io_funcs;
#endif


static int iochar_pm_pulse_handler()
{
    fprintf(stderr, "iochar_pm_pulse_handler: TODO!!!\n");

}


#if 0
static int io_read(resmgr_context_t *ctp, io_read_t *msg, RESMGR_OCB_T *ocb)
{
    fprintf(stderr, "io_read: TODO!!!\n");
}
#else
extern int io_read(resmgr_context_t *ctp, io_read_t *msg, RESMGR_OCB_T *ocb);
#endif

#if 0
static int io_write(resmgr_context_t *ctp, io_write_t *msg, RESMGR_OCB_T *ocb)
{
    fprintf(stderr, "io_write: TODO!!!\n");

}
#else
extern int io_write(resmgr_context_t *ctp, io_write_t *msg, RESMGR_OCB_T *ocb);
#endif

#if 0
static int io_closedup(resmgr_context_t *ctp, io_close_t *msg, RESMGR_OCB_T *ocb)
{
    fprintf(stderr, "io_closedup: TODO!!!\n");

}
#else
extern int io_closedup(resmgr_context_t *ctp, io_close_t *msg, RESMGR_OCB_T *ocb);
#endif

static int io_notify()
{
    fprintf(stderr, "io_notify: TODO!!!\n");

}


#if 0
static int io_devctl()
{
    fprintf(stderr, "io_devctl: TODO!!!\n");

}
#else
extern int io_devctl();
#endif


static int io_unblock()
{
    fprintf(stderr, "io_unblock: TODO!!!\n");

}


static int io_unblock_connect()
{
    fprintf(stderr, "io_unblock_connect: TODO!!!\n");

}

#if 1
static int io_pathconf()
{
    fprintf(stderr, "io_pathconf: TODO!!!\n");

}
#else
extern  int io_pathconf();
#endif


#if 0
static int io_closeocb()
{
    fprintf(stderr, "io_closeocb: TODO!!!\n");

}
#else
extern int io_closeocb();
#endif


int	my_ttc(int type/*r6*/, void *ptr/*r5*/, int arg/*r4*/)
{
    int r4;
    dispatch_context_t* r4_;

    switch (type)
    {
#if 1
        case TTC_INIT_PROC: //0
            //loc_3b8
            if (-1 == ThreadCtl(1, 0))
            {
                //0x000003cc
                slogf(6, 3, "io-char: Unable to obtain I/O privity. You must be userid root");
                fwrite("Unable to obtain I/O privity. You must be userid root.\n", 1, 55, stderr);
                exit(1);
            }
            //loc_3f8
            iofunc_func_init(_RESMGR_CONNECT_NFUNCS/*8*/, &iochar_connect_funcs, 
                _RESMGR_IO_NFUNCS/*0x1a = 26*/, &iochar_io_funcs);

            iochar_io_funcs.read = io_read;
            iochar_io_funcs.write = io_write;
            iochar_io_funcs.close_dup = io_closedup;
            iochar_io_funcs.close_ocb = io_closeocb;
            iochar_io_funcs.notify = io_notify;
            iochar_io_funcs.devctl = io_devctl;
            iochar_io_funcs.unblock = io_unblock;
            iochar_connect_funcs.unblock = io_unblock_connect;
            iochar_io_funcs.pathconf = io_pathconf;

            if (((TTYCTRL*)ptr)->dpp == 0)
            {
                //0x00000468
                ((TTYCTRL*)ptr)->dpp = dispatch_create();
                if (((TTYCTRL*)ptr)->dpp == 0)
                {
                    //0x00000478
                    slogf(6, 3, "io-char: Unable to create dispatch context");
                    fwrite("Unable to create dispatch context.\n", 1, 35, stderr);
                    exit(1);
                }
            }
            //loc_4a4
            ((TTYCTRL*)ptr)->event.sigev_code = pulse_attach(((TTYCTRL*)ptr)->dpp, 
                MSG_FLAG_ALLOC_PULSE/*2*/, 0, &my_tte, 0);

            if (((TTYCTRL*)ptr)->event.sigev_code == -1)
            {
                //0x000004d4
                slogf(6, 3, "io-char: Unable to attach event pulse");
                fwrite("Unable to attach event pulse.\n", 1, 30, stderr);
                exit(1);
            }
            //loc_500
            pthread_mutex_init(&((TTYCTRL*)ptr)->timer_mutex, 0);

            ((TTYCTRL*)ptr)->timer.sigev_code = pulse_attach(((TTYCTRL*)ptr)->dpp, 
                MSG_FLAG_ALLOC_PULSE/*2*/, 0, &my_timer_tick, 0);

            if (((TTYCTRL*)ptr)->timer.sigev_code == -1)
            {
                //0x0000053c
                slogf(6, 3, "io-char: Unable to attach timer pulse");
                fwrite("Unable to attach timer pulse.\n", 1, 30, stderr);
                exit(1);
            }
            //loc_568
            ((TTYCTRL*)ptr)->pm_pulse = pulse_attach(((TTYCTRL*)ptr)->dpp, 
                MSG_FLAG_ALLOC_PULSE/*2*/, 0, &iochar_pm_pulse_handler, 0);

            if (((TTYCTRL*)ptr)->pm_pulse == -1)
            {
                //0x0000058c
                slogf(6, 3, "io-char: Unable to attach power management pulse");
                fwrite("Unable to attach power management pulse.\n", 1, 41, stderr);
                exit(1);
            }
            //loc_5b8
            int coid = message_connect(((TTYCTRL*)ptr)->dpp, MSG_FLAG_SIDE_CHANNEL/*0x200*/);
            ((TTYCTRL*)ptr)->coid = coid;

            if (coid == -1)
            {
                //0x000005d0
                slogf(6, 3, "io-char: Unable to attach channel and connection");
                fwrite("Unable to attach channel and connection.\n", 1, 41, stderr);
                exit(1);
            }
            //loc_5fc
            ((TTYCTRL*)ptr)->event.sigev_notify = 4;
            ((TTYCTRL*)ptr)->timer.sigev_notify = 4;
            ((TTYCTRL*)ptr)->event.sigev_coid = coid;
            ((TTYCTRL*)ptr)->timer.sigev_coid = coid;
            ((TTYCTRL*)ptr)->event.sigev_priority = arg;
            ((TTYCTRL*)ptr)->timer.sigev_priority = arg;
            ((TTYCTRL*)ptr)->event.sigev_value.sival_int = 0;
            ((TTYCTRL*)ptr)->timer.sigev_value.sival_int = 0;
            ((TTYCTRL*)ptr)->timerid = -1;
            ((TTYCTRL*)ptr)->event_queue = _smalloc(4 * ((TTYCTRL*)ptr)->max_devs);
            ((TTYCTRL*)ptr)->perm = 0x1b6;

            r4 = 0;
            //->loc_1030
            break;
#else
        case TTC_INIT_PROC: //0
            r4 = ttc(type, ptr, arg);
            //->loc_1030
            break;
#endif

        case TTC_INIT_CC: //1
            r4 = ttc(type, ptr, arg);
            //->loc_1030
            break;

        case TTC_INIT_START: //2
            //loc_bb4
            printf("TTC_INIT_START: TODO\n");
//            r4 = ttc(type, ptr, arg);
            r4_ = dispatch_context_alloc(((TTYCTRL*)ptr)->dpp);
            if (r4_ == 0)
            {
                //0x00000bc4
                slogf(6, 3, "io-char: Unable to allocate resmgr context");
                fwrite("Could not allocate resmgr context.\n", 1, 35, stderr);
                exit(1);
            }
            //loc_bf0
#if 1
            printf("ttyctrl.flags = 0x%08x\n", ttyctrl.flags);
#endif
            if ((ttyctrl.flags & 0x02) == 0)
            {
                //0x00000c00
                procmgr_daemon(0, 6);
            }
            //loc_c0c
            ((TTYCTRL*)ptr)->timerid = TimerCreate(0, &((TTYCTRL*)ptr)->timer);

#if 1
            printf("before dispatch loop: %p\n", r4_);
#endif

            while (1)
            {
                r4_ = dispatch_block(r4_);
#if 0
                printf("dispatch_block: %p\n", r4_);
#endif
                if (r4_ == 0)
                {
                    exit(0);
                }

                dispatch_handler(r4_);
            }
            break;

        case TTC_INIT_ATTACH: //5
            r4 = ttc(type, ptr, arg);
            //->loc_1030
            break;

        case TTC_INIT_TTYNAME: //9
#if 0
            {
                //loc_c38
                char* r6 = ((TTYDEV*)ptr)->name;
                int r7 = strlen(r6) + 10;
                if (r7 > TTY_NAME_MAX)
                {
                    //->loc_102c
                    r4 = -1;
                    break;
                }
                //0x00000c50
                if (__stackavail() < (((r7 + 7) & ~7) + 0x80))
                {
                    //->loc_102c
                    r4 = -1;
                    break;
                }
                //0x00000c68
                char* r7_ = _alloca(r7);
                if (r7_ == 0)
                {
                    //->loc_102c
                    r4 = -1;
                    break;
                }
                //
                if (arg & 0x800000)
                {
                    //0x00000c88
                    memcpy(r7_, "dev", 4);
                    //->loc_cc0
                }
                else
                {
                    //loc_c9c
                    memcpy(r7_, "char-", 6);
                    strcat(r7_, basename(r6));
                }
                //loc_cc0
            }
#else
            r4 = ttc(type, ptr, arg);
#endif
            //->loc_1030
            break;

        case TTC_INIT_POWER: //11
            r4 = ttc(type, ptr, arg);
            //->loc_1030
            break;

        default:
            //loc_ffc
            slogf(6, 3, "io-char: Unknown ttc option type = 0x%08x", type);
            printf("Unknown ttc option type = 0x%08x\n", type);
            r4 = -1;
            //->loc_1030
            break;
    }

    printf("ttc type = 0x%08x, res = 0x%08x\n", type, r4);

    return r4;
}
