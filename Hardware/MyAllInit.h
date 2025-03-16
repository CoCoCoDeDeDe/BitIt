#ifndef __MYALLINIT_H
#define __MYALLINIT_H

#include "stm32f10x.h"                  // Device header



void MyAllInit_Clock(uint32_t Peripherals, FunctionalState NewState);
void MyAllInit_InitAll(void);

#endif
