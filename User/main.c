#include "main.h"

int main(void)
{	
	MyAllInit_InitAll();
		

//	uint32_t MyTIM_TIM1_test_count_temp = MyTIM_TIM1_test_count;

	while(1) {
//	if(Serial_RxFlag[1] == 1) {
//		OLED_ShowString(1, 1, "USART3:");
//		OLED_ShowString(2, 1, "                ");
//		OLED_ShowString(2, 1, Serial_Rx1StringPacket);
//		
//		Serial_RxFlag[1] = 0;
//	}
//	if (Serial_RxFlag[3] == 1) {
//		OLED_ShowString(3, 1, "USART2:");
//		OLED_ShowString(4, 1, "                ");
//		OLED_ShowString(4, 1, Serial_Rx2StringPacket);
//		
//		Serial_RxFlag[3] = 0;
//	}
		
		
		Delay_ms(500);
		OLED_ShowString(1, 1, "                ");
		OLED_ShowNum(1, 1, MyADCAndDMA_Result[0], 4);
		OLED_ShowString(2, 1, "                ");
		OLED_ShowNum(2, 1, MyADCAndDMA_Result[1], 4);
		OLED_ShowString(3, 1, "                ");
		OLED_ShowNum(3, 1, MyADCAndDMA_Result[2], 4);
		OLED_ShowString(4, 1, "                ");
		OLED_ShowNum(4, 1, MyADCAndDMA_Result[3], 4);

		
		
//		if( MyTIM_TIM1_test_count != MyTIM_TIM1_test_count_temp )
//		{
//			OLED_ShowString(1, 1, "                ");
//			OLED_ShowNum(1, 1, MyTIM_TIM1_test_count, 8);
//		}
		
	}
	
	
	
}

//Things TO DO
//  OK修复Tx
//	OK修复Rx
//	OK配置USART3的接收字符串
//	OK配置USART3的发送字符串
//	HALF配置PA0,PA1,PB0,PB1的DAC和DMA
//	OK配置TIM1
//	OK配置舵机——PWM
//	OK配置TB6612——PWM && GPIO
//	OK规范各模块代码
//	OK完善AllInit.c\AllInit.h
//	HALF配置超声波模块——PWM && GPIO
//	配置生长灯继电器——GPIO1
//	配置气泵继电器——GPIO
//	配置加热器继电器——GPIO
//	配置DHT11——OneWire
//	配置DS28B12——OneWire
//	配置WS2812——OneWire
//	配置ESP8266 01S——USART3
//	统筹NVIC优先级
//	配置MQTT:MCU——Server
//	配置时间系统、
//	设计鱼缸、PCB、喂食器
//OLD TASK
//	HALF调查各个外设的现有代码和库
//	OK调查土壤湿度传感器原理
//	OK调查水温传感器原理
//	重新配置DAC+DMA
//	重新规划引脚
//	OK调查DHT11原理
//	调查超声波模块原理
//	调查水泵模块原理
//	OK研究继电器
//	配置与USART3通信内容显示的方案





