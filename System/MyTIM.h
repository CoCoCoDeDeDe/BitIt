#ifndef __MYTIM_H
#define __MYTIM_H

#include "stm32f10x.h"                  // Device header

#include "OLED.h"
#include "Serial.h"

#include "MyOLED.h"

#include "MyHCSR04.h"

extern uint16_t MyTIM_TIM1_overflowCount_forHCSR04;
extern uint32_t MyTIM_TIM1_test_count;

extern uint32_t MyTIM2_count;	//错点：extern处不可初始化

extern uint32_t MyTIM_3Timer1Count;

void MyTIM_Init(void);
void MyTIM2_Init(void);
void MyTIM3_Init(void);

void MyTIM_3Timer1(void);

#endif
