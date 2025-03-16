//===============================
//PWM1-OC1——超声波发射
//
//
//===============================

#include "MyTIM.h"                  // Device header

uint16_t MyTIM_TIM1_overflowCount_forHCSR04;
uint32_t MyTIM_TIM1_test_count = 0;

/**
  * @brief  TIM1初始化
  * @param  无
  * @retval 无
  */
void MyTIM_Init(void) {
	
	//Triger==========
	TIM_InternalClockConfig(TIM1);
	
	//TimeBase==========
	TIM_TimeBaseInitTypeDef TIME_TimeBaseInitStruct;
	TIM_TimeBaseStructInit(&TIME_TimeBaseInitStruct);
	TIME_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	//用于决定对定时器输入信号滤波的采样频率，采样频率=fCLK/TIM_CKD_DIVx
	//采样频率高——滤波弱——相应快
	//采样频率低——滤波强——相应慢
	//TIM_CKD_DIV1：表示采样时钟频率等于定时器内部时钟频率（CK_INT），即不进行分频。
	//TIM_CKD_DIV2：采样时钟频率为定时器内部时钟频率的 1/2。
	//TIM_CKD_DIV4：采样时钟频率为定时器内部时钟频率的 1/4。
	
	TIME_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;	//CNT每个周期内从0到TIM_Period递增
	TIME_TimeBaseInitStruct.TIM_Period = (uint16_t)(20000 - 1);	//寄存器0——计数次数1
	//SG90电机要求其PWM周期为20ms，即fCNT = 1 / 20ms = 50Hz，TCNT = 20ms
	TIME_TimeBaseInitStruct.TIM_Prescaler = (uint16_t)(72 - 1);	//计数器的时钟频率(CK_CNT)等于fCK_PSC/( PSC[15:0]+1)
	//上: TCKCNT = 1us, fCKCNT = 1MHz
	TIME_TimeBaseInitStruct.TIM_RepetitionCounter = (uint8_t)(1 - 1);	//寄存器0——计数次数1。
	//This parameter must be a number between 0x00 and 0xFF.(0~255)
	
	//Formula: CK_CNT = fCLK / Prescaler + 1											= CNT进行count的频率			= 72MHz / 72 = 1MHz
	//Formula: fCNT = fCLK / (Prescaler + 1)(Period + 1)								= ARR重装频率 = CNT溢出频率	= 1MHz / 1 = 1 / 1000000s = 0.0000001s = 1us
	//Formula: fUI = fCLK / (Prescaler + 1) / (Period + 1) / (RepetitionCounter + 1)	= UpdateInterrupt的频率
	//高级定时器专有TIM_RepetitionCounter
	
	TIM_TimeBaseInit(TIM1, &TIME_TimeBaseInitStruct);
	
	//ITConfig==========
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
	
	
	//NVIC==========
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM1_UP_IRQn;	//NVIC指向的中断请求配置变量存储在stm32f10x.h文件中
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	
	NVIC_Init(&NVIC_InitStruct);
	
	//Cmd==========
	TIM_Cmd(TIM1, ENABLE);
	
	Serial_SendStringPacket(USART2, "MyTIM_Init_End\r\n");
}

void TIM1_UP_IRQHandler() {	//错点：Handler函数名列表在startup_stm32f10x_md.s文件
	
	if(TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
	{
		MyTIM_TIM1_overflowCount_forHCSR04 ++;	//供IC1在其自己的中断中判断ARR是否重装以及重装了几次
		
		MyHCSR04_Tick();
		
		//MyTIM_TIM1_test_count ++;
		
	}
	TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
}


