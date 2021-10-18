/*
 * Switches.c
 *
 *  Created on: Sep 17, 2021
 *      Author: Ahmed Elgharib
 */

#include "DIO.h"
#include "Switches.h"

void Switch_Init(u8_t Port_Name, u8_t Pin_No)
{
	DIO_setPinDirection(Port_Name, Pin_No, INPUT);
}

u8_t getSwitchValue(u8_t Port_Name, u8_t Pin_No)
{
	u8_t value = DIO_getPin(Port_Name, Pin_No);
	return value;
}
