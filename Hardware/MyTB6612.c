//=====
//PA15——AIN1
//PA12——AIN2
//
//=====
//错点：硬件：TB6612忘记接STBY到3.3V


#include "stm32f10x.h"                  // Device header





void MyTB6612_Init(void) {
	//RCC===
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//Init===
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
}



