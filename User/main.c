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

//Things TO DO
//	改OLED代码
//	配置STM32-ESP串口
//	配置3个ADC+DMA设备
//	配置DHT11
//	配置超声波发射器
//	配置超声波接收
//	配置生长灯
//	配置照明
//	配置喂食控制
//	配置气泵控制
//	配置水泵控制
//	配置温度控制
