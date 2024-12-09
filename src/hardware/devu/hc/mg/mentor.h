

//#undef MB86H60


static inline uint16_t HW_Read16( struct Mentor_Controller* c, uint32_t offset ) {
    uint16_t data;
#ifdef MB86H60
	dma_SetUsbMode_LengthInput(c, 1);
    data = ((volatile uint32_t*)(c->Data_0x14))[offset];
#else
	data = *((uint16_t*)((c->Data_0x14) + offset));
#endif
	return data;
}



static inline void HW_Write8( struct Mentor_Controller* c, uint32_t offset, uint8_t data ) {
#ifdef MB86H60
	dma_SetUsbMode_LengthInput(c, 0);
    ((volatile uint32_t*)(c->Data_0x14))[offset] = data;
#else
	*((uint8_t*)(c->Data_0x14 + offset)) = data;
#endif
}



static inline void HW_Write16( struct Mentor_Controller* c, uint32_t offset, uint16_t data ) {
#ifdef MB86H60
	dma_SetUsbMode_LengthInput(c, 1);
    ((volatile uint32_t*)(c->Data_0x14))[offset] = data;
#else
	*((uint16_t*)((uint8_t*)(c->Data_0x14) + offset)) = data;
#endif
}

