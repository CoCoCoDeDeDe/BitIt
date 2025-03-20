#ifndef __MYAQUARIUMHEATER_H
#define __MYAQUARIUMHEATER_H

#include "stm32f10x.h"                  // Device header

#define	GPIO_Heater	GPIOB
#define PIN_Heater	GPIO_Pin_12

void MyAquariumHeater_Init(void);
void MyAquariumHeater_On(void);
void MyAquariumHeater_Off(void);
void MyAquariumHeater_Cmd(BitAction BitVal);
void MyAquariumHeater_GetBitVal(void);
void MyAquariumHeater_GetBitVal(void);

#endif
