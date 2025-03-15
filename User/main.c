#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include <string.h>
#include "Array.h"
#include "MyADC.h"
#include "MyDMA.h"
#include "MyTIM.h"
#include "MyEXTI.h"
#include "MyTB6612.h"


int main(void)
{	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//NVIC优先级分组的配置对所有中断请求是统一的
	
	MyTIM_Init();
	MyTIM_OC1Init();
	MyTIM_OC2Init();
	MyTIM_OC4Init();	//错点：遗漏OC4在运行程序中Init
	MyTB6612_Init();
	MyADC_Init();
	OLED_Init();
	OLED_Clear();
	Serial_Init(USART3, 115200, 2, 2);
	Serial_Init(USART2, 115200, 2, 2);
	
	Serial_SendStringPacket(USART3, "USART3");
	Serial_SendStringPacket(USART2, "USART2");

	//PA12——AIN2
	GPIO_WriteBit(GPIOA, GPIO_Pin_12, Bit_RESET);
	//PA15——AIN1
	GPIO_WriteBit(GPIOA, GPIO_Pin_15, Bit_SET);
	//上：问题：为何当PWM适中、AIN1&AIN2都RESET，电机还是转
	

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
//	
//	Delay_ms(500);
//	OLED_ShowString(1, 1, "                ");
//	OLED_ShowNum(1, 1, MyDMA_DMA1Result[0], 4);
//	OLED_ShowString(2, 1, "                ");
//	OLED_ShowNum(2, 1, MyDMA_DMA1Result[1], 4);
//	OLED_ShowString(3, 1, "                ");
//	OLED_ShowNum(3, 1, MyDMA_DMA1Result[2], 4);
//	OLED_ShowString(4, 1, "                ");
//	OLED_ShowNum(4, 1, MyDMA_DMA1Result[3], 4);
	
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
//	HALF配置超声波模块——PWM && GPIO
//	OK配置TB6612——PWM && GPIO
//	配置生长灯继电器——GPIO1
//	配置气泵继电器——GPIO
//	配置加热器继电器——GPIO
//	配置DHT11——OneWire
//	配置DS28B12——OneWire
//	配置WS2812——OneWire
//	配置ESP8266 01S——USART3
//	统筹NVIC优先级
//	配置MQTT:MCU——Server
//	配置时间系统
//	设计鱼缸、PCB
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





