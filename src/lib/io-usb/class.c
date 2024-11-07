
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

#include "externs.h"


struct ArrayClass  ArrayClass[8]; //0x00127230



/* 0x0010acec - todo */
struct ArrayClass* CLASS_RegisterDriver(struct Struct_10acec* a)
{
#if 0
    fprintf(stderr, "CLASS_RegisterDriver\n");
#endif

    uint32_t i;
    struct ArrayClass* p = &ArrayClass[0];

    for (i = 0; i < 8; i++, p++)
    {
        if (p->bData_0x2c == 0)
        {
            p->Data_0 = a->Data_0;
            p->Data_4 = a->Data_4;
            p->Data_8 = a->Data_8;
            p->Data_0xc = a->Data_0xc;
            p->Data_0x10 = a->Data_0x10;
            p->Data_0x14 = a->Data_0x14;
            p->Data_0x20 = a->Data_0x18;
            p->Data_0x24 = a->Data_0x1c;
            p->Data_0x28 = a->Data_0x20;
            p->bData_0x2c = 1;

            return p;
        }
    }

    return 0;
}


