/**
 * 
 * @file LCD.c
 * @author Ahmed Elgharib
 * @date 2021-08-20
 * 
 */

#include "LCD.h"
#include "LCD_cnfg.h"
#include "DIO.h"

#if LCD_CURRENT_MODE == LCD_8BITS_MODE
void LCD_Init(void)
{
    _delay_ms(50);
    LCD_sendCommand(LCD_COM_FUNCTION_SET_8BIT);
    _delay_ms(1);
    LCD_sendCommand(CURSOR_ON);
    _delay_ms(1);
    LCD_sendCommand(LCD_COM_CLEAR);
    _delay_ms(2);
    LCD_sendCommand(LCD_COM_ENTRYMODE);
    _delay_ms(1);
}

static void LCD_sendCommand(u8_t command)
{
    DIO_setPin(LCD_RS_PORT, LCD_RS_PIN, LOW);
    DIO_setPin(LCD_RW_PORT, LCD_RW_PIN, LOW);
    DIO_voidSetPortValue(LCD_8BITS_DATA_PORT, command);
    DIO_setPin(LCD_E_PORT, LCD_E_PIN, HIGH);
    _delay_ms(1);
    DIO_setPin(LCD_E_PORT, LCD_E_PIN, LOW);
    _delay_ms(1);
}

static void LCD_writeData(u8_t data)
{
    DIO_setPin(LCD_RS_PORT, LCD_RS_PIN, HIGH);
    DIO_setPin(LCD_RW_PORT, LCD_RW_PIN, LOW);
    DIO_voidSetPortValue(LCD_8BITS_DATA_PORT, data);
    DIO_setPin(LCD_E_PORT, LCD_E_PIN, HIGH);
    _delay_ms(1);
    DIO_setPin(LCD_E_PORT, LCD_E_PIN, LOW);
    _delay_ms(1);
}

#elif LCD_CURRENT_MODE == LCD_4BITS_MODE

void LCD_Init(void)
{
	DIO_setPinDirection(LCD_4BITS_PORT, LCD_4BITS_PIN1, 1);
	DIO_setPinDirection(LCD_4BITS_PORT, LCD_4BITS_PIN2, 1);
	DIO_setPinDirection(LCD_4BITS_PORT, LCD_4BITS_PIN3, 1);
	DIO_setPinDirection(LCD_4BITS_PORT, LCD_4BITS_PIN4, 1);
	DIO_setPinDirection(LCD_RS_PORT, LCD_RS_PIN, 1);
	DIO_setPinDirection(LCD_E_PORT, LCD_E_PIN, 1);
    _delay_ms(35);
    LCD_sendCommand(LCD_COM_HOME);
    _delay_ms(1);
    LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE);
    _delay_ms(1);
    LCD_sendCommand(CURSOR_ON);
    _delay_ms(1);
    LCD_sendCommand(LCD_COM_CLEAR);
    _delay_ms(2);
    LCD_sendCommand(LCD_COM_ENTRYMODE);
    _delay_ms(1);
}

void LCD_sendCommand(u8_t command)
{
    DIO_setPin(LCD_RS_PORT, LCD_RS_PIN, LOW);
    DIO_setPin(LCD_4BITS_PORT, LCD_4BITS_PIN1, GET_BIT(command, 4));
    DIO_setPin(LCD_4BITS_PORT, LCD_4BITS_PIN2, GET_BIT(command, 5));
    DIO_setPin(LCD_4BITS_PORT, LCD_4BITS_PIN3, GET_BIT(command, 6));
    DIO_setPin(LCD_4BITS_PORT, LCD_4BITS_PIN4, GET_BIT(command, 7));

    DIO_setPin(LCD_E_PORT, LCD_E_PIN, HIGH);
    _delay_ms(1);
    DIO_setPin(LCD_E_PORT, LCD_E_PIN, LOW);
    _delay_ms(1);

    DIO_setPin(LCD_4BITS_PORT, LCD_4BITS_PIN1, GET_BIT(command, 0));
    DIO_setPin(LCD_4BITS_PORT, LCD_4BITS_PIN2, GET_BIT(command, 1));
    DIO_setPin(LCD_4BITS_PORT, LCD_4BITS_PIN3, GET_BIT(command, 2));
    DIO_setPin(LCD_4BITS_PORT, LCD_4BITS_PIN4, GET_BIT(command, 3));

    DIO_setPin(LCD_E_PORT, LCD_E_PIN, HIGH);
    _delay_ms(1);
    DIO_setPin(LCD_E_PORT, LCD_E_PIN, LOW);
    _delay_ms(1);
}

void LCD_writeData(u8_t data)
{
    DIO_setPin(LCD_RS_PORT, LCD_RS_PIN, HIGH);
    DIO_setPin(LCD_4BITS_PORT, LCD_4BITS_PIN1, GET_BIT(data, 4));
    DIO_setPin(LCD_4BITS_PORT, LCD_4BITS_PIN2, GET_BIT(data, 5));
    DIO_setPin(LCD_4BITS_PORT, LCD_4BITS_PIN3, GET_BIT(data, 6));
    DIO_setPin(LCD_4BITS_PORT, LCD_4BITS_PIN4, GET_BIT(data, 7));

    DIO_setPin(LCD_E_PORT, LCD_E_PIN, HIGH);
    _delay_ms(1);
    DIO_setPin(LCD_E_PORT, LCD_E_PIN, LOW);
    _delay_ms(1);

    DIO_setPin(LCD_4BITS_PORT, LCD_4BITS_PIN1, GET_BIT(data, 0));
    DIO_setPin(LCD_4BITS_PORT, LCD_4BITS_PIN2, GET_BIT(data, 1));
    DIO_setPin(LCD_4BITS_PORT, LCD_4BITS_PIN3, GET_BIT(data, 2));
    DIO_setPin(LCD_4BITS_PORT, LCD_4BITS_PIN4, GET_BIT(data, 3));

    DIO_setPin(LCD_E_PORT, LCD_E_PIN, HIGH);
    _delay_ms(1);
    DIO_setPin(LCD_E_PORT, LCD_E_PIN, LOW);
    _delay_ms(1);
}
#endif

void LCD_writeChar(u8_t ch)
{
    LCD_writeData(ch);
}

void LCD_Clear(void)
{
	LCD_sendCommand(LCD_COM_CLEAR);
}

void LCD_writeString(u8_t *str)
{
    u8_t i;
    for(i=0; str[i]; i++){
    	LCD_writeData(str[i]);
    }
}

void LCD_writeNumber(u64_t num)
{
    u8_t str[16]={0},i=0;
    while(num>0){
    	str[i]=num%10+'0';
    	i++;
    	num=num/10;
    }
    for (int j=i; j>0; j--){
    	LCD_writeData(str[j-1]);
    }
}

void LCD_GOTO(u8_t raw, u8_t col)
{
    switch (raw)
	{
	case 0:
		if ((col < 16) && (col >= 0))
		{
			LCD_sendCommand(LCD_COM_SET_CURSOR_FIRST_LINE + col);
		}
		break;
	case 1:
		if ((col < 16) && (col >= 0))
		{
			LCD_sendCommand(LCD_COM_SET_CURSOR_SECOND_LINE + col);
		}
		break;
	}
}
