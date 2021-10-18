/*
 * main.c
 *
 *  Created on: Sep 12, 2021
 *      Author: Ahmed Elgharib
 */
#include <avr/interrupt.h>
#include "DIO.h"
#include "Timer.h"
#include "ADC.h"
#include "LCD.h"
#include "UART.h"
#include "Switches.h"
#include "EXT_INT.h"

// Full APP Sender

ISR (INT0_vect)
{
	CLR_BIT(SREG, I_BIT);
	UART_Send('1');
}

ISR (INT1_vect)
{
	CLR_BIT(SREG, I_BIT);
	UART_Send('0');
}
//u8_t flag=2;
//void dddd(void){
//	if (getSwitchValue(PORT_D, PIN2)){
//		flag = 1;
//	}
//	else if (getSwitchValue(PORT_D, PIN3)){
//		flag = 0;
//	}
//}
int main(void){
	//init UART with setting TX and RX up
	DIO_setPinDirection(PORT_D, 1, 1);
	DIO_setPinDirection(PORT_D, 0, 0);
	UART_Init();

	// Setting pins up for push buttons
	Switch_Init(PORT_D, PIN2);
	Switch_Init(PORT_D, PIN3);

//	Timer2_init(TIMER2_NORMAL_MODE, TIMER2_SCALER_8);
//	Timer2_OV_InterruptEnable();
//	Timer2_OVF_SetCallBack(dddd);

	Enable_GI();

	while(1){
		if(getSwitchValue(PORT_D, PIN2)){
			_delay_ms(250);
			if(getSwitchValue(PORT_D, PIN2)){
				Enable_Interrupt(USE_INT0, Extint01_RisingEdge);
			}
		}
		if(getSwitchValue(PORT_D, PIN3)){
			_delay_ms(250);
			if(getSwitchValue(PORT_D, PIN3)){
				Enable_Interrupt(USE_INT1, Extint01_RisingEdge);
			}
		}

//
//		if(flag == 1){
//			UART_Send('1');
//			flag = 2;
//		}
//		else if (flag == 0){
//			UART_Send('0');
//			flag = 2;
//		}
	}
}
