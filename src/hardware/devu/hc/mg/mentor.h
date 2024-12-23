

#define MUSB_PULSE_INTR  				(_PULSE_CODE_MINAVAIL+1)




#define MUSB_CSR0					0x102  // 16-bit


#define MUSB_RXCSR(n)				( 0x106 + ( 0x10 * (n) ) ) // 16-bit
#define MUSB_IDX_RXCSR				0x16	// 16-bit

	/* peripheral */
	#define RXCSR_RXPKTRDY					( 1 << 0 )
	#define RXCSR_SEND_STALL				( 1 << 5 )
	#define RXCSR_DMA_REQ_MODE				( 1 << 11 )
	#define RXCSR_DMA_REQ_TYPE0				( 0 << 11 )
	#define RXCSR_DMA_REQ_TYPE1				( 1 << 11 )
	#define RXCSR_DMA_REQ_EN				( 1 << 13 )
	#define RXCSR_AUTOCLEAR					( 1 << 15 )

	/* host mode */ 	
	//#define RXCSR_RXPKTRDY				( 1 << 0 )
	#define RXCSR_REQ_PKT					( 1 << 5 )
	//#define RXCSR_DMA_REQ_MODE			( 1 << 11 )
	//#define RXCSR_DMA_REQ_EN				( 1 << 13 )
	#define RXCSR_AUTOREQ					( 1 << 14 )
	//#define RXCSR_AUTOCLEAR				( 1 << 15 )


#define MUSB_COUNT0					0x108	// 16-bit






//#undef MB86H60


static inline uint8_t HW_Read8( struct _hctrl_t* c/*uint8_t * iobase*/, uint32_t offset ) {
	uint8_t data;
#ifdef MB86H60
	dma_SetUsbMode_LengthInput(c, 0);
    data = ((volatile uint32_t*)(c->Data_0x14))[offset];
#else
	data = *((uint8_t*)(/*iobase*/c->Data_0x14 + offset));
#endif
	return data;
}



static inline uint16_t HW_Read16( struct _hctrl_t* c, uint32_t offset ) {
    uint16_t data;
#ifdef MB86H60
	dma_SetUsbMode_LengthInput(c, 1);
    data = ((volatile uint32_t*)(c->Data_0x14))[offset];
#else
	data = *((uint16_t*)((c->Data_0x14) + offset));
#endif
	return data;
}



static inline void HW_Write8( struct _hctrl_t* c, uint32_t offset, uint8_t data ) {
#ifdef MB86H60
	dma_SetUsbMode_LengthInput(c, 0);
    ((volatile uint32_t*)(c->Data_0x14))[offset] = data;
#else
	*((uint8_t*)(c->Data_0x14 + offset)) = data;
#endif
}



static inline void HW_Write16( struct _hctrl_t* c, uint32_t offset, uint16_t data ) {
#ifdef MB86H60
	dma_SetUsbMode_LengthInput(c, 1);
    ((volatile uint32_t*)(c->Data_0x14))[offset] = data;
#else
	*((uint16_t*)((uint8_t*)(c->Data_0x14) + offset)) = data;
#endif
}



