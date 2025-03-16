#include "stm32f10x.h"                  // Device header

#include <string.h>

#include "Array.h"

#include "Delay.h"

#include "Serial.h"

#include "MyTIM.h"
#include "MySG90.h"
#include "MyWaterPump.h"

#include "MyTIM2.h"
#include "MyHCSR04.h"

#include "MyWaterQualitySensor.h"
#include "MySoilMoistureSensor.h"
#include "MyLightSensor.h"
#include "MyADCAndDMA.h"

#include "OLED.h"

int main(void)
{	
//RCC=====
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
//NVIC_Group=====
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	//上：NVIC优先级分组的配置对所有中断请求是统一的
	
//Init=====
	Serial_Init(USART3, 115200, 2, 2);	//Serial1——ESP8266
	Serial_SendStringPacket(USART3, "Serial3_On\r\n");
	Serial_Init(USART2, 115200, 2, 2);	//Serail2——PC
	Serial_SendStringPacket(USART2, "Serial2_On\r\n");
	
	Delay_ms(10);	//串口初始化后的等待
	
	MyTIM_Init();
	MySG90_Init(1500);		//PA9-OC2
	MyWaterPump_Init(500);	//PA10-OC3
	
//MyTIM2_Init();
	MyHCSR04_Trig_Init();	//PA8-OC1
	MyHCSR04_Echo_Init();	//PB15-EXTI
	
	MyWaterQualitySensor_Init();
	MySoilMoistureSensor_Init();
	MyLightSensor_Init();
	MyADCAndDMA_Init(3);
	
	OLED_Init();
	OLED_Clear();
	
//Run=====
		
	
	OLED_ShowString(1, 1, "666");

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
//		OLED_ShowString(1, 1, "                ");
//		OLED_ShowNum(1, 1, MyADCAndDMA_Result[0], 4);
//		OLED_ShowString(2, 1, "                ");
//		OLED_ShowNum(2, 1, MyADCAndDMA_Result[1], 4);
//		OLED_ShowString(3, 1, "                ");
//		OLED_ShowNum(3, 1, MyADCAndDMA_Result[2], 4);
//		OLED_ShowString(4, 1, "                ");
//		OLED_ShowNum(4, 1, MyTIM2_count, 16);

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
//	OK改回main中Init
//	修OLED Bug
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
