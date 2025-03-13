#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Delay.h"

//=====================================
//本文件用于配置水质传感器、光照传感器、水温传感器、土壤湿度传感器的GPIO+ADC+ADC_DMACmd配置
//水质传感器——GPIOA——GPIO_Pin_0
//光照传感器——GPIOA——GPIO_Pin_1
//水温传感器——GPIOB——GPIO_Pin_0
//土壤湿度传感器——GPIOB——GPIO_Pin_1
//=====================================

uint16_t MyDMA_DMA1Result[4];

void MyADC_Init() {
	
	//时钟配置{GPIOA,GPIOB,ADC,DMA1}
	//ADCCLK来自ADC分频器
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);	//时钟树
	
	//GPIO配置{AIN}
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_StructInit(&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	
	//ADC通道配置
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);	//水质传感器——GPIOA——GPIO_Pin_0
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);	//光照传感器——GPIOA——GPIO_Pin_1
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 3, ADC_SampleTime_55Cycles5);	//水温传感器——GPIOB——GPIO_Pin_0
	//错点：未匹配正确Ch。正确：PB0--Ch8
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 4, ADC_SampleTime_55Cycles5);	//土壤湿度传感器——GPIOB——GPIO_Pin_1
	//错点：未匹配正确Ch。正确：PB1--Ch9
	//	通道0	PA0
	//	通道1	PA1
	//	通道2	PA2
	//	通道3	PA3
	//	通道4	PA4
	//	通道5	PA5
	//	通道6	PA6
	//	通道7	PA7
	//	通道8	PB0
	//	通道9	PB1
	//	通道10	PC0
	//	通道11	PC1
	//	通道12	PC2
	//	通道13	PC3
	//	通道14	PC4
	//	通道15	PC5
	

	//ADC初始化
	ADC_InitTypeDef ADC_InitStruct;
	ADC_StructInit(&ADC_InitStruct);
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;	//开启连续转换
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//无外部触发
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;	//选单ADC
	ADC_InitStruct.ADC_NbrOfChannel = 4;
	ADC_InitStruct.ADC_ScanConvMode = ENABLE;	//开启扫描模式（多Ch）
	ADC_Init(ADC1, &ADC_InitStruct);
		
	
	//ADC_DMACmd
	ADC_DMACmd(ADC1, ENABLE);
	
	
	//DMA配置
	DMA_InitTypeDef DMA_InitStruct;
	DMA_StructInit(&DMA_InitStruct);
	
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;	//规则数据寄存器ADC1->DR
	//错点：遗漏ADC1->DR前的&
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	//ADC1 got continue mode, dont need inc
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)MyDMA_DMA1Result;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStruct.DMA_BufferSize = 4;
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStruct.DMA_Priority = DMA_Priority_Medium;
	
	DMA_Init(DMA1_Channel1, &DMA_InitStruct);
	
	
	//Cmd
	ADC_Cmd(ADC1, ENABLE);
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	
	//ADC_Calibration
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);
	//RSTCAL：复位校准 (Reset calibration) 位3 
	//该位由软件设置并由硬件清除。在校准寄存器被初始化后该位将被清除。
	//0：校准寄存器已初始化；
	//1：初始化校准寄存器。
	//注：如果正在进行转换时
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) == SET);
	//CAL：A/D校准 (A/D Calibration) 位2 
	//该位由软件设置以开始校准，并在校准结束时由硬件清除。
	//0：校准完成；
	//1：开始校准。
	
	//ADCSTART
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	
	

}




