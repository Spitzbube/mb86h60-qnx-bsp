
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


extern int tte(message_context_t *ctp, int code, unsigned flags, void *handle);


#if 1

int my_tte(message_context_t *ctp, int code, unsigned flags, void *handle)
{
//    fprintf(stderr, "my_tte: TODO!!!\n");

    return tte(ctp, code, flags, handle);
}

#endif

