

typedef struct
{
	uint32_t dwOutFunction; //0
	uint32_t dwInFunction; //4
	uint8_t bPin; //8

} Struct_20401328;


typedef struct
{
	char bData_0;
	int fill_4; //4
	int Data_8; //8
	//12
} Struct_20611068;

extern int gpio_init(void);
extern int gpio_open(Struct_20401328* pParams, Struct_20611068** r5);
