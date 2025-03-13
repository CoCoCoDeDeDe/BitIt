#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include <string.h>
#include "Array.h"

int main(void)
{	
	OLED_Init();
	//Serial_Init(USART1, 115200, 2, 2);
	Serial_Init(USART2, 115200, 2, 2);
	
	OLED_ShowString(4, 1, "OLED_ON");
	
	//Serial_SendStringPacket(USART1, "usart1");
	Serial_SendStringPacket(USART2, "usart2");
	
	
	while(1) {
		if(Serial_RxFlag[2] == 1) {
			OLED_ShowString(1,1,"                ");
			OLED_ShowString(1,1,Serial_RxStringPacket);
			OLED_ShowString(2,1,"2");
			
			Serial_RxFlag[2] = 0;
		}
	}
}

//Things TO DO
//  OK修复Tx
//	OK修复Rx
//	配置usart1的接收字符串
//	配置与usart1通信内容显示的方案





