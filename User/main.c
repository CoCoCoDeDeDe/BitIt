#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include <string.h>
#include "Array.h"

int main(void)
{	
	OLED_Init();
	Serial_Init(USART3, 115200, 2, 2);
	Serial_Init(USART2, 115200, 2, 2);
	
	Serial_SendStringPacket(USART3, "USART3");
	Serial_SendStringPacket(USART2, "USART2");
	
	
	while(1) {
		if(Serial_RxFlag[1] == 1) {
			OLED_ShowString(1, 1, "USART3:");
			OLED_ShowString(2, 1, "                ");
			OLED_ShowString(2, 1, Serial_Rx1StringPacket);
			
			Serial_RxFlag[1] = 0;
		}
		if (Serial_RxFlag[3] == 1) {
			OLED_ShowString(3, 1, "USART2:");
			OLED_ShowString(4, 1, "                ");
			OLED_ShowString(4, 1, Serial_Rx2StringPacket);
			
			Serial_RxFlag[3] = 0;
		}
	}
}

//Things TO DO
//  OK修复Tx
//	OK修复Rx
//	OK配置USART3的接收字符串
//	OK配置USART3的发送字符串
//	配置与USART3通信内容显示的方案





