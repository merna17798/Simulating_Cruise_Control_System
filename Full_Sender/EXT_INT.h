/*
 * external-interupt.h
 *
 *  Created on: 12 Aug 2021
 *      Author: Merna Saleh
 */

#ifndef EXT_INT_H_
#define EXT_INT_H_
#include "DataTypes.h"

/*configuration structure Interrupt mode*/
typedef enum {
	Extint01_LowLevel=0,
	Extint01_AnyChange=1,
	Extint01_FallingEdge=2,
	Extint01_RisingEdge=3
}Extint_State;
/*
 * User allowed to use these variables
 * */
#define USE_INT0 0
#define USE_INT1 1
#define USE_INT2 2
/*Function prototypes*/
void Enable_GI(void);
void Enable_Interrupt(u8_t INT_num, Extint_State INT_STATE);
void Disable_Interrupt(u8_t INT_num);
#endif /* EXTERNAL_INTERUPT_H_ */
