#ifndef __MYTIM_H
#define __MYTIM_H

#include "stm32f10x.h"                  // Device header

#include "OLED.h"
#include "Serial.h"

#include "MyHCSR04.h"

extern uint16_t MyTIM_TIM1_overflowCount_forHCSR04;
extern uint32_t MyTIM_TIM1_test_count;

void MyTIM_Init(void);

#endif
