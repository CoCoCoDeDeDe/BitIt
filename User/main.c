#include "stm32f10x.h"                  // Device header

#include <string.h>

#include "Array.h"

#include "Delay.h"

#include "MyTest.h"

#include "Serial.h"

#include "MyTIM.h"
#include "MySG90.h"
#include "MyWaterPump.h"

#include "MyHCSR04.h"
#include "MyDHT11.h"
#include "MyDS18B20.h"

#include "MyWaterQualitySensor.h"
#include "MySoilMoistureSensor.h"
#include "MyLightSensor.h"

#include "MyADCAndDMA.h"

#include "MyPlantGrowLamp.h"
#include "MyAirPump.h"
#include "MyAquariumHeater.h"

#include "OLED.h"

int main(void)
{
	Delay_ms(1000);	//等待设备电压稳定
	
//RCC=====
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//错点：用EXTI要开启AFIO

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
//NVIC_Group=====
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	//上：NVIC优先级分组的配置对所有中断请求是统一的
	
//Init=====
	MyTest_PB5_Init();
	
	Serial_Init(USART3, 115200, 2, 1);	//Serial1——ESP8266
	Serial_SendStringPacketV2(USART3, "Serial3_On\r\n");
	
	Serial_Init(USART2, 115200, 2, 2);	//Serail2——PC
	Serial_SendStringPacketV2(USART2, "Serial2_On\r\n");
	
	MyTIM1_Init();
	MyTIM2_Init();
	MyTIM3_Init();
	
	MySG90_Init(1500);		//PA9-OC2
	MyWaterPump_Init(500);	//PA10-OC3
	
	MyHCSR04_Trig_Init();	//PA8-OC1
	MyHCSR04_Echo_Init();	//PB15-EXTI
	
	MyDHT11_Init();//【错点】遗漏main中运行Init
	
	MyWaterQualitySensor_Init();
	MySoilMoistureSensor_Init();
	MyLightSensor_Init();
	
	MyADCAndDMA_Init(3);
	
	MyPlantGrowLamp_Init();
	MyAirPump_Init();
	MyAquariumHeater_Init();
	
	OLED_Init();
	OLED_Clear();
	
//Run=====
	while(1) {
//		if(Serial_RxFlag[1] == 1) {
//			OLED_ShowString(1, 1, "USART3:");
//			OLED_ShowString(2, 1, "                ");
//			OLED_ShowString(2, 1, Serial_Rx1StringPacket);
//			
//			Serial_RxFlag[1] = 0;
//		}
//		
//		if (Serial_RxFlag[3] == 1) {
//			OLED_ShowString(3, 1, "USART2:");
//			OLED_ShowString(4, 1, "                ");
//			OLED_ShowString(4, 1, Serial_Rx2StringPacket);
//			
//			Serial_RxFlag[3] = 0;
//		}
//		
//			OLED_ShowString(2, 1, "                ");
//			OLED_ShowNum(2, 1, MyADCAndDMA_Result[1], 4);
//			OLED_ShowString(3, 1, "                ");
//			OLED_ShowNum(3, 1, MyADCAndDMA_Result[2], 4);
//			OLED_ShowString(4, 1, "                ");
//			OLED_ShowNum(4, 1, 999, 16);
		
//		float HCSR04_distanceTemp = HCSR04_distance;
//		if(HCSR04_distanceTemp != HCSR04_distance) {
//			OLED_ShowString(3, 1, "                ");
//			OLED_ShowNum(3, 1, (uint16_t)HCSR04_distance, 4);
//			
//			HCSR04_distanceTemp = HCSR04_distance;
//		}
		

//		OLED_ShowNum(1, 1, MyTIM_2Count, 16);
//		OLED_ShowNum(2, 1, MyTIM_3Count, 16);
//		OLED_ShowNum(3, 1, MyDHT11_Count_WriterSM, 16);
		OLED_ShowNum(4, 1, MyDHT11_DataArr[0], 8);
		OLED_ShowNum(4, 9, MyDHT11_DataArr[2], 8);
		
//		OLED_ShowNum(4, 1, MyDHT11_Count_ReadInterval, 16);

//		OLED_ShowNum(1, 1, MyDHT11_Count_ReadBit, 16);
		
		
		MyAirPump_Cmd(Bit_RESET);
		
		MyAquariumHeater_Cmd(Bit_RESET);
		
		MyPlantGrowLamp_Cmd(Bit_RESET);
		
	}
}

void TIM1_UP_IRQHandler(void) {		//IT per 20ms=	0.02s
	if(TIM_GetITStatus(TIM1, TIM_IT_Update) == SET) {
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
		
	}
}

void TIM2_IRQHandler(void) {
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) {
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		
		MyTIM_2Count++;
		
		MyHCSR04_TrigCtrler();
		
		
		
		MyDHT11_WriterSM();
		
		//Serial_SendStringPacketV2(USART2, "TIM2_IRQHandler\r\n");
	}
}


void TIM3_IRQHandler(void) {//TCKCNT=1us,TCKCNT=TIT=0.01s
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) == SET) {
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		
		MyTIM_3Count++;
		
		MyTIM3_DIV100();
		
		MyDHT11_Count_TIM3ARer();
		
		MyDHT11_ReadCheckTimer();
		
	}
}

void EXTI4_IRQHandler(void) {
	if(EXTI_GetITStatus(EXTI_Line4) == SET) {
		EXTI_ClearITPendingBit(EXTI_Line4);
		
		MyDHT11_ReaderSM();//【错点】写错在EXTI15_10_IEQHandler
		
		//Serial_SendStringPacketV2(USART2, "EXTI4\r\n");
		//Serial_SendStringPacketV2(USART2, "E");
	}
}

void EXTI9_5_IRQHandler(void) {	//EXTI Line 5to9的中断是合并的
	if(EXTI_GetITStatus(EXTI_Line5) == SET) {
		EXTI_ClearITPendingBit(EXTI_Line5);
		
		
	}
	if(EXTI_GetITStatus(EXTI_Line6) == SET) {
	EXTI_ClearITPendingBit(EXTI_Line6);
		
		
	}
}

void EXTI15_10_IRQHandler(void) {	//EXTI Line 10to15的中断是合并的
	if(EXTI_GetITStatus(EXTI_Line15) == SET) {
		EXTI_ClearITPendingBit(EXTI_Line15);
		//Serial_SendStringPacketV2(USART2, "EXTI15_10_IRQHandler\r\n");
		
		MyHCSR04_EchoCtrlerSM();
		
	}
}


