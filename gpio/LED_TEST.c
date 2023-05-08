#include"TM4C123.h"
#include"GPIo.h"



 int main()
{
 PortD_Init( );
 PortF_Init();
 PortB_Init();
    while (1)
    {
      SET_LED(RED_LED,LED_ON);
			SET_LED(BLUE_LED,LED_OF);
			SET_LED(GREEN_LED,LED_ON);
    }
    
}
