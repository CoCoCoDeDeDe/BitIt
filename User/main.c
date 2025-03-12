#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include <string.h>
#include "Array.h"

int main(void)
{	
	OLED_Init();
	Serial_Init(115200);
	
	while(1)
	{
		if(Serial_RxFlag == 1)
		{
			OLED_ShowString(1,1,"                ");
			OLED_ShowString(1,1,Serial_RxStringPacket);
			
			Serial_RxFlag = 0;
		}
	}
}



