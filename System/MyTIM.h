#ifndef __MYTIM_H
#define __MYTIM_H

#include "stm32f10x.h"                  // Device header

#include "MyTest.h"
#include "OLED.h"
#include "Serial.h"

#include "MyOLED.h"

#include "MyHCSR04.h"
#include "MyDHT11.h"

#include "MyAquariumHeater.h"

extern uint32_t MyTIM_2Count;
extern uint32_t MyTIM_3Count;

void MyTIM1_Init(void);
void MyTIM2_Init(void);
void MyTIM3_Init(void);
void MyTIM3_DIV100(void);

#endif
