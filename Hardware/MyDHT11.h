#ifndef __MYDHT11_H
#define __MYDHT11_H

#include "stm32f10x.h"                  // Device header

#include "Serial.h"

typedef enum {
	IDLE,//空闲状态(未启动接收)
	RESPONSE_FALLING1,
	RESPONSE_RISING,
	RESPONSE_FALLING2,
	BIT_FALLING,
	BIT_RISING,
	END_RISING,
	FAILED//接收错误(超时或校验失败)
} MyDHT11_ReaderSMState;

extern uint8_t MyDHT11_TIM3ARCount_Ctrl;
extern uint32_t MyDHT11_TIM3ARCount;

extern uint8_t MyDHT11ReadCheckTimer_Ctrl;

extern uint8_t MyDHT11_Writer_Ctrl;
extern uint8_t MyDHT11_WriterSM_State;

extern uint8_t MyDHT11_BitsArr[];//每1个元素对应要读取的数据的每一个bit
extern uint8_t MyDHT11_DataArr[];//每1个元素对于转换完的一个字节,不包括校验位
extern MyDHT11_ReaderSMState MyDHT11_ReaderSM_State;//默认未开始接收
extern uint32_t MyDHT11_ReadIntervalCount;//存储FALLING和RISING之间TIM3CNT计数次数
extern uint32_t MyDHT11_ReadIntervalCount_Start;//存储开始记FALLING和RISING之间TIM3CNT计数次数时的TIM3CNT值
extern uint8_t MyDHT11_Flag_ReadSucced;

void MyDHT11_Init(void);
void MyDHT11_EXTICmd(FunctionalState EXTI_LineCmd);
void MyDHT11_PA4GPIOModeConfig(GPIOMode_TypeDef GPIO_Mode);
void MyDHT11_SetPA4GPIOMode_Out_PP(void);
void MyDHT11_SetPA4GPIOMode_IPU(void);
void MyDHT11_SetWriteMode(void);
void MyDHT11_SetReadMode(void);
void MyDHT11_WriterSET(void);
void MyDHT11_WriterRESET(void);
void MyDHT11_SetEXTITrigRising(void);
void MyDHT11_SetEXTITrigFalling(void);
void MyDHT11_TIM3ARCounter(void);
void MyDHT11_ReadCheckTimer(void);
void MyDHT11_WriteCtrlerSwitchOn(void);
void MyDHT11ReadCheck(void);
void MyDHT11_ReadFailed(void);
void MyDHT11_WriterSM(void);
void MyDHT11_ReaderSM(void);
void MyDHT11_StartReadIntervalCount(void);
void MyDHT11_SaveReadIntervalCount(void);
void MyDHT11_DataTranslate(void);
void MyDHT11_ReaderSM_Ready(MyDHT11_ReaderSMState State);
#endif
