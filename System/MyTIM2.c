#include "MyTIM2.h"

uint32_t MyTIM2_count = 0;

void MyTIM2_Init(void) {
	
	TIM_InternalClockConfig(TIM2);
	
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Down;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 144 - 1;	//TCKCNT
	TIM_TimeBaseInitStruct.TIM_Period = 10 - 1;	//TCNT = 200us = 0.00002s
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 1 -1;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	
	NVIC_Init(&NVIC_InitStruct);
	
	TIM_Cmd(TIM2, ENABLE);
	
	//Serial_SendStringPacket(USART2, "MyTIM2_Init_End\r\n");
}

//void TIM2_IRQHandler(void) {
//	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) {
//		MyTIM2_count ++;
//		
//		
//		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//	}
//}

