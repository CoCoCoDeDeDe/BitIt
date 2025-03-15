#ifndef __MYTIM_H
#define __MYTIM_H

extern uint16_t MyTIM_TIM1_overflow_count_IC1;
extern uint32_t MyTIM_TIM1_test_count;

void MyTIM_Init(void);

void MyTIM_OC1Init(void);
void MyTIM_OC2Init(void);
void MyTIM_OC4Init(void);	//错点：遗漏OC4Init在.h中声明
#endif
