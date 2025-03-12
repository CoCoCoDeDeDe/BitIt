#ifndef __SERIAL_H
#define __SERIAL_H

#include "stm32f10x.h"                  // Device header

extern USART_InitTypeDef USART_InitStruct;

extern uint8_t Serial_RxFlag;	//错点：Serial.c中Serial_RxFlag赋值后此处不能再次赋值。

extern char Serial_TxStringPacket[100];
extern char Serial_RxStringPacket[100];

void Serial_Init(uint32_t USART_BaudRate);
void Serial_BaudRateConfig(uint32_t USART_BaudRate);
void Serial_SendByte(uint8_t Byte);



#endif
