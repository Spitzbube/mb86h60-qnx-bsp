

struct io_usb_dll_entry_t
{
    char* Data_0; //0
    int Data_4; //4
    int (*init)(); //8
    int (*shutdown)(); //12
    void* controller_methods; //16
    void* ctrl_pipe_methods; //20
    void* int_pipe_methods; //24
    void* bulk_pipe_methods; //28
    void* isoch_pipe_methods; //32
    //36???
};

