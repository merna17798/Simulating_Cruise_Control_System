#include "EXT_INT.h"
#include "BitMath.h"
#include "Memmap.h"

void Enable_Interrupt(u8_t INT_num, Extint_State INT_STATE)
{
    EN_ERRORSTATE_t state;
    state = E_OK;
    if (INT_num == USE_INT0)
    {
        SET_BIT(GICR, INT0);
        switch (INT_STATE)
        {
        case Extint01_LowLevel:
            CLR_BIT(MCUCR, ISC01);
            CLR_BIT(MCUCR, ISC00);
            break;
        case Extint01_AnyChange:
            CLR_BIT(MCUCR, ISC01);
            SET_BIT(MCUCR, ISC00);
            break;
        case Extint01_FallingEdge:
            SET_BIT(MCUCR, ISC01);
            CLR_BIT(MCUCR, ISC00);
            break;
        case Extint01_RisingEdge:
            SET_BIT(MCUCR, ISC01);
            SET_BIT(MCUCR, ISC00);
            break;
        default:
            state = E_ERROR;
            break;
        }
    }
    else if (INT_num == USE_INT1)
    {
        SET_BIT(GICR, INT1);
        switch (INT_STATE)
        {
        case Extint01_LowLevel:
            CLR_BIT(MCUCR, ISC11);
            CLR_BIT(MCUCR, ISC10);
            break;
        case Extint01_AnyChange:
            CLR_BIT(MCUCR, ISC11);
            SET_BIT(MCUCR, ISC10);
            break;
        case Extint01_FallingEdge:
            SET_BIT(MCUCR, ISC11);
            CLR_BIT(MCUCR, ISC10);
            break;
        case Extint01_RisingEdge:
            SET_BIT(MCUCR, ISC11);
            SET_BIT(MCUCR, ISC10);
            break;
        default:
            state = E_ERROR;
            break;
        }
    }
    else if (INT_num == USE_INT2)
    {
        SET_BIT(GICR, INT2);
        switch (INT_STATE)
        {
        case Extint01_FallingEdge:
            CLR_BIT(MCUCSR, ISC2);
            break;
        case Extint01_RisingEdge:
            SET_BIT(MCUCSR, ISC2);
            break;
        default:
            state = E_ERROR;
            break;
        }
    }
}

void Enable_GI(void)
{
    SET_BIT(SREG, I_BIT);
}

void Disable_Interrupt(u8_t INT_num)
{
    if (INT_num <= USE_INT2)
    {
        switch (INT_num)
        {
        case USE_INT0:
        {
            CLR_BIT(GICR, INT0);
            break;
        }
        case USE_INT1:
        {
            CLR_BIT(GICR, INT1);
            break;
        }
        case USE_INT2:
        {
            CLR_BIT(GICR, INT2);
            break;
        }
        }
    }
    CLR_BIT(SREG, I_BIT);
}
