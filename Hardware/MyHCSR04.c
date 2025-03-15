#include "MyHCSR04.h"

//下：HC_SR04->Trig——PA8——OC1——TIM1
void MyHCSR04_Trig_Init(uint16_t TIM_Pulse) {
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCStructInit(&TIM_OCInitStruct);
	TIM_OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Reset;	//设置定时器空闲时该OC的高低电平
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OCInitStruct.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Disable;	//Cmd
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;	//Cmd
	TIM_OCInitStruct.TIM_Pulse = TIM_Pulse - 1;	//设置多少次CNT自增/自减后将CNT次数存入CCR，注意实际值=寄存器值+1
	//上：给HC-SR04的Trig发送长达10us的TTL脉冲，模块就会进行测距
	TIM_OC1Init(TIM1, &TIM_OCInitStruct);
	
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	Serial_SendStringPacket(USART2, "MyHCSR04_Trig_Init_End\r\n");
}

void MyHCSR04_Echo_Init(void) {
	//RCC-GPIO, EXTI=====
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
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




