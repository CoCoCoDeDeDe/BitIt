#include "MyAllInit.h"

void MyAllInit_Clock(uint32_t Peripherals, FunctionalState NewState) {
	if(Peripherals & PERIPH_GPIOA) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, NewState);
	}
	
	if(Peripherals & PERIPH_GPIOB) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, NewState);
	}
	
	if(Peripherals & PERIPH_GPIOC) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, NewState);
	}

//下：错点：EXTI时钟不用手动开启
//	if(Peripherals & PERIPH_EXTI) {
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_EXTI, NewState);
//	}
	
	if(Peripherals & PERIPH_TIM1) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, NewState);
	}
	
	if(Peripherals & PERIPH_ADC1) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, NewState);
	}
	
	if(Peripherals & PERIPH_USART1) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, NewState);
	}
	
	if(Peripherals & PERIPH_USART2) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, NewState);
	}
	
	if(Peripherals & PERIPH_USART3) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, NewState);
	}
	
	if(Peripherals & PERIPH_DMA1) {
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, NewState);
	}
}
//上：使用案例：
//MyAllInit_Clock(PERIPH_GPIOA | PERIPH_GPIOA | PERIPH_GPIOA);
//	//一句话开启n个时钟

void MyAllInit_InitAll() {
	
	MyAllInit_Clock(
	PERIPH_GPIOA | PERIPH_GPIOB | PERIPH_GPIOC | 
	PERIPH_TIM1 | PERIPH_ADC1 | PERIPH_USART2 | 
	PERIPH_USART3 | PERIPH_DMA1, 
	ENABLE);
	
//	FunctionalState NewState = ENABLE;
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, NewState);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, NewState);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, NewState);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, NewState);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, NewState);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, NewState);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, NewState);
//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, NewState);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	//上：NVIC优先级分组的配置对所有中断请求是统一的
	
	//Serial1——ESP8266
	Serial_Init(USART3, 115200, 2, 2);
	Serial_SendStringPacket(USART3, "Serial3_Init_End\r\n");
	//Serail2——PC
	Serial_Init(USART2, 115200, 2, 2);
	Serial_SendStringPacket(USART2, "Serial3_Init_End\r\n");
	//下：串口初始化后的等待
	Delay_ms(10);
	
	MyTIM_Init();
	MySG90_Init(1500);		//PA9-OC2
	MyWaterPump_Init(500);	//PA10-OC3
	
//	MyTIM2_Init();
	MyHCSR04_Trig_Init();	//PA8-OC1
	MyHCSR04_Echo_Init();	//PB15-EXTI
	
	MyWaterQualitySensor_Init();
	MySoilMoistureSensor_Init();
	MyLightSensor_Init();
	MyADCAndDMA_Init(3);
	
	OLED_Init();
	
	Serial_SendStringPacket(USART2, "MyAllInit_InitAll_End\r\n");
}


