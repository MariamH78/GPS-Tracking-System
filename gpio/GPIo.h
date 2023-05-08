#define RED_LED 0
#define BLUE_LED 1
#define GREEN_LED 2
#define LED_ON 1
#define LED_OF 0
void PortD_Init(void);
void PortF_Init(void);
void PortB_Init(void);
unsigned char sw_value(unsigned char sw);
void SET_LED(unsigned char color,unsigned char state);