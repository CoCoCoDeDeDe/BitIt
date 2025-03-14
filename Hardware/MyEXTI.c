#include "stm32f10x.h"                  // Device header

uint16_t HCSR04_distance;


void MyEXTI(void) {
	//RCC-GPIO, EXTI=====
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	//EXTI虽然连接APB2总线，但是其RCC时钟无需手动开启
	
	//Init-GPIO, EXTI=====
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource15);
	
	//EXTI=====
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_StructInit(&EXTI_InitStruct);
	EXTI_InitStruct.EXTI_Line = EXTI_Line15;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	//上：注意：小心混淆Rising和Falling
	EXTI_Init(&EXTI_InitStruct);
	
	//错点：遗漏NVIC
	//NVIC=====
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStruct);
	
}

//下：中断函数
void EXTI15_10_IRQHandler(void) {
	//EXTI Line 10to15的中断是合并的
	if(EXTI_GetITStatus(EXTI_Line15) == SET) {
		
	}
	EXTI_ClearITPendingBit(EXTI_Line15);
}




