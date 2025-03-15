#ifndef __MYTIM_H
#define __MYTIM_H

#include "stm32f10x.h"                  // Device header

#include "OLED.h"
#include "Serial.h"

extern uint16_t MyTIM_TIM1_overflow_count_IC1;
extern uint32_t MyTIM_TIM1_test_count;

void MyTIM_Init(void);

#endif
