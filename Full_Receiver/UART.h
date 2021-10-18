#ifndef UART_H_
#define UART_H_

#include "DataTypes.h"
#include "Memmap.h"
#include "BitMath.h"

void UART_Init(void);
void UART_Send(u8_t data);
u8_t UART_Receive(void);
void UART_sendString(u8_t *str);
void UART_receiveString(u8_t *str);
void UART_sendLong(u32_t num);
u32_t UART_receiveLong(void);

#endif
