#include "stm32f10x.h"                  // Device header

USART_InitTypeDef USART_InitStruct;

uint8_t Serial_RxFlag = 0;	//错点：遗漏Serial_RxFlag
//用于标记状态机是否把一整个String接收完，否则不输出新接收的String等等


char Serial_TxStringPacket[100];
char Serial_RxStringPacket[100];

void Serial_Init(uint32_t USART_BaudRate) {
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//错点：遗漏时钟配置
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//错点：遗漏时钟配置
	
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_StructInit(&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	
	USART_StructInit(&USART_InitStruct);
	
	USART_InitStruct.USART_BaudRate = USART_BaudRate;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	
	USART_Init(USART2, &USART_InitStruct);
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//错点：遗漏NVIC
	
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	
	NVIC_Init(&NVIC_InitStruct);
	
	
	USART_Cmd(USART2, ENABLE);
}

void Serial_BaudRateConfig(uint32_t USART_BaudRate) {
	USART_InitStruct.USART_BaudRate = USART_BaudRate;
	
	USART_Init(USART2, &USART_InitStruct);
}

void USART2_IRQHandler() {
	if(USART_GetITStatus(USART2, USART_IT_RXNE) == SET) {
		//进入状态机程序
		
		static uint8_t s = 0;
		static uint8_t count = 0;
		uint16_t RxData = USART_ReceiveData(USART2);
		//RXNE在USART_DR被读取后自动RESET（即0，数据没有收到）
		//下一轮USART_ReceiveData()运行对USART_DR进行写操作会将TXE自动置0即RESET，即数据未被完全转移至移位寄存器
		//USART_DR是TDR和RDR在软件概念上的合并
		
		switch (s) {
			case 0:
				if(RxData == '@' && Serial_RxFlag == 0) {	//错点：遗漏判断Serial_RxFlag，即判断上一个String是否接收完毕。
					//使即使没有@也认为是新String的开头
					
					s = 1; 
					count = 0;
				} else {
					//nothing
				}
				break;
			case 1:
				if(RxData == '\r') {
					s = 2;
				} else {
					Serial_RxStringPacket[count++] = RxData;
				}
				break;
			case 2:
				if(RxData == '\n') {
					s = 0;
					Serial_RxStringPacket[count] = '\0';
					Serial_RxFlag = 1;	//错点：遗漏Serial_RxFlag。
					//此处表示一整个String已经接受完，可进行读取变量等操作。
					
				} else {
					//nothing
				}
				break;
			default:
				//fault
			break;	//dafault:内若没有要执行的代码则需要加break;
		}
	}
}

void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART2, Byte);
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);	
	//TXE置0：数据还未被完全转移至移位寄存器；TXE置1：数据已被完全转移至移位寄存器。
	//下一轮对USART_SendData()运行对USART_DR进行写操作会将TXE自动置0即RESET，即数据未被完全转移至移位寄存器
	
}

