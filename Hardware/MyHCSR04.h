#ifndef __MYHC_SR04_H
#define __MYHC_SR04_H
//上：错点：在 C 和 C++ 里，标识符（像宏名、变量名、函数名等）仅能由字母（大写或小写）、
//	数字以及下划线 _ 构成，且不能以数字开头。
//	你代码中的 __MYHC-SR04_H 包含了 - 字符，这就违背了标识符的命名规则，所以编译器会给出警告。

#include "stm32f10x.h"                  // Device header

#include "Array.h"

#include "Delay.h"

#include "MyTIM.h"

#include "Serial.h"

extern float MyHCSR04_Distance_mm;


void MyHCSR04_Trig_Init(void);
void MyHCSR04_Echo_Init(void);

void MyHCSR04_SETer(void);
void MyHCSR04_RESETer(void);

extern uint32_t MyHCSR04_EchoTimerStart;
extern uint32_t MyHCSR04_EchoTimerResult;

void MyHCSR04_EchoTimerSM(void);
float MyHCSR04_ResultFilter(void);

static float MyHCSR04_Distance_mm;

uint16_t MyHCSR04_DistanceCounter_mm(void);

#endif
