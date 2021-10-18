/*
 * Switches.h
 *
 *  Created on: Sep 17, 2021
 *      Author: Ahmed Elgharib
 */

#ifndef SWITCHES_H_
#define SWITCHES_H_

void Switch_Init(u8_t Port_Name, u8_t Pin_No);
u8_t getSwitchValue(u8_t Port_Name, u8_t Pin_No);

#endif /* SWITCHES_H_ */
