/*
 * UART_cfg.h
 *
 *  Created on: Sep 9, 2021
 *      Author: Ahmed Elgharib
 */

#ifndef UART_CFG_H_
#define UART_CFG_H_

#define NORMAL      0
#define DOUBLE      1


/*
    PARITY MODE
 */
#define DISABLED    0
#define ODD         1
#define EVEN        2

#define _5BIT       1
#define _6BIT       2
#define _7BIT       3
#define _8BIT       4
#define _9BIT       5

/*
    DOUBLE - NORMAL
*/
#define UART_SPEED  NORMAL


/*
    DISABLED - EVEN - ODD
*/
#define UART_PARITY  DISABLED

/*
    _5BIT - _6BIT - _7BIT - _8BIT
 */
#define DATAFRAM    _8BIT


/*
    1_BIT - _2BIT
 */
#define STOPBIT        _1BIT

/*
   UBRR Setting
   8MHz, 9600 BaudRate
*/
#define HIGHUBRR         0
#define LOWUBRR          103

#endif /* UART_CFG_H_ */
