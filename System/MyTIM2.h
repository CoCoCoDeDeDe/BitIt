#ifndef __MYTIM2_H
#define __MYTIM2_H

#include "stm32f10x.h"                  // Device header

extern uint32_t MyTIM2_count;	//错点：extern处不可初始化

void MyTIM2_Init(void);

#endif
