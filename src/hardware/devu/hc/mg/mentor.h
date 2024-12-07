

static inline uint16_t HW_Read16( uint8_t * iobase, uint32_t offset ) {
	uint16_t data;
	data = *((uint16_t*)(iobase + offset));
	return data;
}


static inline void HW_Write16( struct Mentor_Controller* c, uint32_t offset, uint16_t data ) {
#ifdef MB86H60
	dma_SetUsbMode_LengthInput(c, 1);
    ((volatile uint32_t*)(c->Data_0x14))[offset] = data;
#else
	*((uint16_t*)((volatile uint8_t*)(c->Data_0x14) + offset)) = data;
#endif
}

