
#include <sys/iofunc.h>
#include <sys/resmgr.h>
#include "externs.h"


int Data_11be40; //11be40

int Data_11c6d0; //11c6d0

int Data_11ddf4; //11ddf4

int _iou_ex; //0x0011f3a4 

struct USB_Controller usb_controllers[20]; //0x0011f590 +0x14*0x8c
int ausb_controllers[20]; //0x001201c0
pthread_mutex_t usb_mmutex; //0x120210
int Data_12021c; //12021c

int Data_1212c4; //1212c4
int usb_enum_priority = 0; //0x00121574
int usb_coid = 0; //0x00121578
int usb_priority = 0; //0x0012157c
int usb_chid = 0; //0x00121580
int usb_dflt_timeout = 0; //0x00121584
int usb_prefix = 0; //0x0012158c
int usb_verbosity = 0; //0x001215a0
struct UdiCtrl UdiCtrl; //0x001215a4
pthread_rwlock_t usb_rwlock; //0x00127834

