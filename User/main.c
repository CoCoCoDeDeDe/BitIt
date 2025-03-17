#include "stm32f10x.h"                  // Device header

#include <string.h>

#include "Array.h"

#include "Delay.h"

#include "Serial.h"

#include "MyTIM.h"
#include "MySG90.h"
#include "MyWaterPump.h"

#include "MyHCSR04.h"

#include "MyWaterQualitySensor.h"
#include "MySoilMoistureSensor.h"
#include "MyLightSensor.h"
#include "MyADCAndDMA.h"

#include "OLED.h"

int main(void)
{	
//RCC=====
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	//错点：用EXTI要开启AFIO

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
//NVIC_Group=====
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	//上：NVIC优先级分组的配置对所有中断请求是统一的
	
//Init=====
	Serial_Init(USART3, 115200, 2, 1);	//Serial1——ESP8266
	Serial_SendStringPacket(USART3, "Serial3_On\r\n");
	Serial_Init(USART2, 115200, 2, 2);	//Serail2——PC
	Serial_SendStringPacket(USART2, "Serial2_On\r\n");
	
	Delay_ms(10);	//串口初始化后的等待
	
	MyTIM_Init();
	MySG90_Init(1500);		//PA9-OC2
	MyWaterPump_Init(500);	//PA10-OC3
	
	MyTIM2_Init();
	MyHCSR04_Trig_Init();	//PA8-OC1
	MyHCSR04_Echo_Init();	//PB15-EXTI
	
	MyTIM3_Init();
	
	MyWaterQualitySensor_Init();
	MySoilMoistureSensor_Init();
	MyLightSensor_Init();
	MyADCAndDMA_Init(3);
	
	OLED_Init();
	OLED_Clear();
	
//Run=====
	
	OLED_ShowString(2, 1, "1212312313");
	
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

//		
//			OLED_ShowString(2, 1, "                ");
//			OLED_ShowNum(2, 1, MyADCAndDMA_Result[1], 4);
//			OLED_ShowString(3, 1, "                ");
//			OLED_ShowNum(3, 1, MyADCAndDMA_Result[2], 4);
//			OLED_ShowString(4, 1, "                ");
//			OLED_ShowNum(4, 1, 999, 16);

		uint16_t MyADCAndDMA_Result0temp;
		if(MyADCAndDMA_Result0temp != MyADCAndDMA_Result[0]) {
			OLED_ShowString(1, 1, "                ");
			OLED_ShowNum(1, 1, MyADCAndDMA_Result[0], 4);
			
			MyADCAndDMA_Result0temp = MyADCAndDMA_Result[0];
		}
		
//		float HCSR04_distanceTemp = HCSR04_distance;
//		if(HCSR04_distanceTemp != HCSR04_distance) {
//			OLED_ShowString(3, 1, "                ");
//			OLED_ShowNum(3, 1, (uint16_t)HCSR04_distance, 4);
//			
//			HCSR04_distanceTemp = HCSR04_distance;
//		}
		
		OLED_ShowNum(3, 1, (uint16_t)MyHCSR04_DistanceCounter_mm(), 4);
		
	}
	
}

void TIM1_UP_IRQHandler() {		//IT per 20ms
	if(TIM_GetITStatus(TIM1, TIM_IT_Update) == SET) {
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
		
	}
}

void TIM2_IRQHandler(void) {
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) {
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		
	}
}

void TIM3_IRQHandler(void) {
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET ) {
		
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		
		MyTIM_3Timer1();	//提供周期为80us,从0自增到79的MyTIM_3Timer1Count
		
		MyHCSR04_SETer();
		
		MyHCSR04_RESETer();
		
	}
}

void EXTI15_10_IRQHandler(void) {	//EXTI Line 10to15的中断是合并的
	if(EXTI_GetITStatus(EXTI_Line15) == SET) {
		
		EXTI_ClearITPendingBit(EXTI_Line15);
		
		MyHCSR04_EchoTimerSM();
		
		
	}
}


