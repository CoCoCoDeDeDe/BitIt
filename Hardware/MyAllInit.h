#ifndef __MYALLINIT_H
#define __MYALLINIT_H

#include "stm32f10x.h"                  // Device header

#include <string.h>
#include "Array.h"

#include "Delay.h"

#include "Serial.h"

#include "MyTIM.h"
#include "MyHCSR04.h"
#include "MySG90.h"
#include "MyWaterPump.h"

#include "MyWaterQualitySensor.h"
#include "MySoilMoistureSensor.h"
#include "MyLightSensor.h"
#include "MyADCAndDMA.h"

#include "OLED.h"

//随笔：加入新功能，特别是系统性的功能，加完以后第一时间测试
//下：错点：严重，把<<左移错写为>>右移
#define PERIPH_GPIOA	(1U << 0)	//RCC_APB2ENR_GPIOAEN
#define PERIPH_GPIOB	(1U << 1)	//RCC_APB2ENR_GPIOBEN
#define PERIPH_GPIOC	(1U << 2)	//RCC_APB2ENR_GPIOCEN
#define PERIPH_TIM1		(1U << 3)	//RCC_APB2ENR_TIM1EN
#define PERIPH_ADC1		(1U << 4)	//RCC_APB2ENR_DMAEN
#define PERIPH_USART1	(1U << 5)	//RCC_APB2ENR_USART1EN
#define PERIPH_USART2	(1U << 6)	//RCC_APB1ENR_USART2EN
#define PERIPH_USART3	(1U << 7)	//RCC_APB1ENR_USART3EN
#define PERIPH_DMA1		(1U << 8)	//RCC_AHBENR_ADC1EN

void MyAllInit_Clock(uint32_t Peripherals, FunctionalState NewState);
void MyAllInit_InitAll(void);

#endif
