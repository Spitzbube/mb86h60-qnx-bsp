

struct Struct_b698
{
    pthread_mutex_t Data_0; //0 //b698
    int Data_8; //8
    int Data_0xc; //12
    int fill_0x10; //0x10
    int Data_0x14; //0x14
    int fill_0x18[8]; //0x18
    int Data_0x38; //0x38
    struct usbd_connection* Data_0x3c; //0x3c
    int typed_mem_fd; //0x40
    char* typed_memory_name; //0x44
    char* Data_0x48; //0x48
    //???
};

extern struct Struct_b698 Data_b698;


struct USB_Memchunk_Inner_0x18_Inner_8
{
    struct USB_Memchunk_Inner_0x18_Inner_8* next; //0
    struct USB_Memchunk_Inner_0x18_Inner_8* Data_4; //4
    paddr_t phys; //8
    uint16_t wData_0xc; //0xc
    uint16_t wData_0xe; //0xe
    //0x10???
};


struct USB_Memchunk_Inner_0x18
{
    uint16_t size; //0
    uint16_t count; //2
    int avail; //4
    struct USB_Memchunk_Inner_0x18_Inner_8* Data_8; //8
    //0xc
};

    
struct USB_Memchunk
{
    pthread_mutex_t mutex; //0
    int pagesize; //8
    int prot; //0xc
    int Data_0x10; //0x10
    int size; //0x14
    struct USB_Memchunk_Inner_0x18 Data_0x18[]; //0x18
    //???
};


struct usbd_desc_node
{
    struct usbd_desc_node* next; //0
    usbd_descriptors_t* descr; //4
    struct usbd_desc_node* child; //8
    //12
};


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


struct usbd_device
{
    int Data_0; //0
    int* Data_4; //4
    struct usbd_connection* Data_8; //8
    int Data_0xc; //0xc
    void* Data_0x10; //0x10
    unsigned Data_0x14; //0x14
    int Data_0x18; //0x18
    usbd_device_instance_t Data_0x1c; //0x1c +0x24
    struct usbd_desc_node* desc_node; //0x40
    void* Data_0x44; //0x44
    //0x48
};


struct usbd_pipe
{
    int fill_0[2]; //0
    struct usbd_device* Data_8;
    int fill_0xc[2]; //0xc
    uint8_t bData_0x14; //0x14
    //???
};


struct Struct_5a24_d
{
    uint16_t fill_0; //0
    uint16_t wData_2; //2
    int fill_4; //4
};

struct Struct_5a24_d1
{
    uint16_t fill_0; //0
    uint16_t wData_2; //2
};


extern int usbdi_sendcmd(int sp_0xc, int r8, 
    struct usbd_urb* sl, 
    struct Struct_5a24_d* r7);

extern int usbdi_memchunk_init(uint32_t*, int, int*, int cached);
extern void* usbdi_memchunk_malloc(int, int size);
extern void* usbdi_memchunk_calloc(int, int b, int c);
extern void usbdi_memchunk_free(struct USB_Memchunk*, void*);
extern paddr_t usbdi_memchunk_mphys(int, const void* ptr);
