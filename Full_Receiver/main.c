/*
 * main.c
 *
 *  Created on: Sep 12, 2021
 *      Author: Ahmed Elgharib
 */
#include "DataTypes.h"
#include "DIO.h"
#include "Timer.h"
#include "ADC.h"
#include "LCD.h"
#include "UART.h"
#include "DC_interface.h"

// Full APP Receiver

int main(void){
	//init UART with setting TX and RX up
	DIO_setPinDirection(PORT_D, PIN1, OUTPUT);
	DIO_setPinDirection(PORT_D, PIN0, INPUT);
	UART_Init();

	//Init Motor settings
	DC_voidInit();

	//Init LCD settings
	LCD_Init();

	//Variables to be used
	u8_t speed = 30;
	u8_t receive;

	while(1){
		//LCD Set Position to print string
		LCD_GOTO(0, 0);
		LCD_writeString("Motor Speed:");

		//setting speed up for The motor
		DC_voidSetSpeed(speed);

		//LCD Set Position to print motor speed
		LCD_GOTO(1, 0);
		LCD_writeNumber(speed);

		//Variable to receive signal from UART
		receive = UART_Receive();

		if (receive == '1'){
			if (speed <= 90 && speed >= 0){
				speed+=10;
				receive = '2';
				LCD_Clear();
			}
			else{
				speed = 100;
			}
		}
		else if (receive == '0'){
			if (speed <= 100 && speed >= 10){
				speed-=10;
				receive = '2';
				LCD_Clear();
			}
			else if (speed == 0){
				LCD_writeChar('00');
				speed = 0;
			}
		}

	}
}
