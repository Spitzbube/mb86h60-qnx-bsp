

struct Struct_5a24
{
    int Data_0; //4
    struct Struct_5a24* Data_4; //4
    int fill_8[2]; //8
    struct
    {
        int fill_0[3]; //0
        int Data_0xc; //0xc
        int fill_0x10; //0x10
        int Data_0x14; //0x14
        //???
    }* Data_0x10; //0x10
    int fill_0x14[4]; //0x14
    int Data_0x24; //0x24
    int fill_0x28[13]; //0x28
    uint16_t fill_0x5c; //0x5c
    uint16_t wData_0x5e; //0x5e
    int Data_0x60; //0x60
    int fill_0x64; //0x64
    uint16_t wData_0x68; //0x68
    int fill_0x6c; //0x6c
    //0x70
};

struct Struct_5a24_d
{
    uint16_t fill_0; //0
    uint16_t wData_2; //2
    int fill_4; //4
};


extern int usbdi_sendcmd(int sp_0xc, int r8, 
    struct Struct_5a24* sl, 
    struct Struct_5a24_d* r7);


