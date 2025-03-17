#include "MyHCSR04.h"

#define GPIOTrig GPIOA
#define PinTrig GPIO_Pin_12
#define GPIOEcho GPIOB
#define PinEcho GPIO_Pin_15

//下：HC_SR04->Trig——PA8——OC1——TIM1
void MyHCSR04_Trig_Init(void) {	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;	//错点：改回非PWM后要改AF为Out
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_WriteBit(GPIOTrig, PinTrig, Bit_RESET);
	
	//Serial_SendStringPacket(USART2, "MyHCSR04_Trig_Init_End\r\n");
}

EXTI_InitTypeDef EXTI_InitStruct;

void MyHCSR04_Echo_Init(void) {
	//RCC-GPIO, EXTI=====
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	//EXTI虽然连接APB2总线，但是其RCC时钟无需手动开启
	
	//Init-GPIO, EXTI=====
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	//EXTI=====
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource15);
	//EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_StructInit(&EXTI_InitStruct);
	EXTI_InitStruct.EXTI_Line = EXTI_Line15;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;//注意：小心混淆Rising和Falling
	EXTI_Init(&EXTI_InitStruct);
	
	//错点：遗漏NVIC
	//NVIC=====
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&NVIC_InitStruct);
	
}

void MyHCSR04_SETer(void) {
	if(MyTIM_3Timer1Count < 15) {
		GPIO_WriteBit(GPIOTrig, PinTrig, Bit_SET);
	}
}

void MyHCSR04_RESETer(void) {
	if(MyTIM_3Timer1Count >= 15) {
		GPIO_WriteBit(GPIOTrig, PinTrig, Bit_RESET);
	}
}

uint32_t MyHCSR04_EchoTimerStart;
uint32_t MyHCSR04_EchoTimerResult;

void MyHCSR04_EchoTimerSM(void) {
	static uint8_t MyHCSR04_EchoTimerSMState;
	if(MyHCSR04_EchoTimerSMState == 0) {
		MyHCSR04_EchoTimerStart = MyTIM_3Timer1Count;
		
		MyHCSR04_EchoTimerSMState = 1;
		
		EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
		EXTI_Init(&EXTI_InitStruct);
	} else if(MyHCSR04_EchoTimerSMState == 1) {
		MyHCSR04_EchoTimerResult = MyTIM_3Timer1Count - MyHCSR04_EchoTimerStart;
		
		MyHCSR04_EchoTimerStart = 0;
		
		MyHCSR04_EchoTimerSMState = 0;
		
		EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
		EXTI_Init(&EXTI_InitStruct);
	}
}

float MyHCSR04_ResultFilter(void) {
	static uint8_t ResultFilter_Counter = 0;
	ResultFilter_Counter ++;
	static uint16_t ResultFilter_Arr[10];
	MyArray_TailAdd_uint16_t(ResultFilter_Arr, MyHCSR04_EchoTimerResult, 10);
	if (ResultFilter_Counter < 10) {
		return MyArray_GetAverage_uint16_t(ResultFilter_Counter, ResultFilter_Arr);
	} else{
		return MyArray_GetAverage_uint16_t(10, ResultFilter_Arr);
	}
}

float MyHCSR04_Distance_mm;

uint16_t MyHCSR04_DistanceCounter_mm(void) {
	return 0.343 * MyHCSR04_ResultFilter() * 100.0 / 2.0;
}
