
#include "UART.h"
#include "UART_cfg.h"


/**
 * @brief Initialized UART
 *
 * @return EN_ERRORSTATE_t E_OK | E_ERROR
 */
void UART_Init(void)
{
    EN_ERRORSTATE_t Enstate;
    Enstate = E_OK;

    /* Boud Rate */


/* UART Double Speed */
#if UART_SPEED == DOUBLE
    SET_BIT(UCSRA, U2X);

/* UART NORMAL Speed */
#elif UART_SPEED == NORMAL
    CLR_BIT(UCSRA, U2X);
#endif

/* Select STOP Bit */
#if STOPBIT == _1BIT
    /* Set URSEL to update UCSRC*/
    CLR_BIT(UCSRC, USBS);

#elif STOPBIT == _2BIT
    /* Set URSEL to update UCSRC*/
    SET_BIT(UCSRC, URSEL);
    SET_BIT(UCSRC, USBS);
#endif

/* Disable Parity */
#if UART_PARITY == DISABLED
    CLR_BIT(UCSRC, UPM0);
    CLR_BIT(UCSRC, UPM1);
    /* Parity is Odd */

#elif UART_PARITY == ODD

    SET_BIT(UCSRC, UPM0);
    SET_BIT(UCSRC, UPM1);

/* Parity is Even */
#elif UART_PARITY == EVEN

    CLR_BIT(UCSRC, UPM0);
    SET_BIT(UCSRC, UPM1);

#endif

/* Data Fram */
#if DATAFRAM == _5BIT

    CLR_BIT(UCSRC, UCSZ0);
    CLR_BIT(UCSRC, UCSZ1);
    CLR_BIT(UCSRB, UCSZ2);

#elif DATAFRAM == _6BIT

    SET_BIT(UCSRC, UCSZ0);
    CLR_BIT(UCSRC, UCSZ1);
    CLR_BIT(UCSRB, UCSZ2);
#elif DATAFRAM == _7BIT

    CLR_BIT(UCSRC, UCSZ0);
    SET_BIT(UCSRC, UCSZ1);
    CLR_BIT(UCSRB, UCSZ2);
#elif DATAFRAM == _8BIT

    SET_BIT(UCSRC, UCSZ0);
    SET_BIT(UCSRC, UCSZ1);
    CLR_BIT(UCSRC, UCSZ2);
#elif DATAFRAM == _9BIT

    SET_BIT(UCSRC, UCSZ0);
    SET_BIT(UCSRC, UCSZ1);
    SET_BIT(UCSRB, UCSZ2);
#else
    Enstate = E_ERROR;
#endif
    /* Clear  URSEL to update UBRRH*/
    CLR_BIT(UCSRC, URSEL);
    UBRRH = HIGHUBRR;
    UBRRL = LOWUBRR;
    /**
     * @brief Receiver Enable
     *
     */
    SET_BIT(UCSRB, RXEN);
    /**
     * @brief Transmitter Enable
     *
     */
    SET_BIT(UCSRB, TXEN);


} /* UART_ENInit */
//const
void UART_Send(u8_t data)
{
    while (!GET_BIT(UCSRA, UDRE));
    UDR = data;
}

u8_t UART_Receive(void)
{
    while (!GET_BIT(UCSRA, RXC));
    return UDR;
}

