


struct io_usb_controller_methods_t
{
    int Data_0; //0
    int (*controller_init)(); //4
    int (*controller_shutdown)(); //8
    int fill_0xc; //12
    int fill_0x10; //16
    int fill_0x14; //20
    int Data_0x18; //0x18 = 24
    //TODO!!!
    //???
};


struct io_usb_dll_entry_t
{
    char* Data_0; //0
    int Data_4; //4
    int (*init)(); //8
    int (*shutdown)(); //12
    struct io_usb_controller_methods_t* controller_methods; //16
    void* ctrl_pipe_methods; //20
    void* int_pipe_methods; //24
    void* bulk_pipe_methods; //28
    void* isoch_pipe_methods; //32
    //36???
};

