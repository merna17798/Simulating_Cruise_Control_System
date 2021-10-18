
/**
 * 
 * @file Timer.h
 * @author Ahmed Elgharib
 * @date 2021-08-20
 * 
 */

#include "Timer.h"

/****************************Pointer to functions to be assigned to ISR*********************************/

static void (*Timer1_OVF_Fptr)(void) = NULLPTR;
static void (*Timer1_OCA_Fptr)(void) = NULLPTR;
static void (*Timer1_OCB_Fptr)(void) = NULLPTR;
static void (*Timer1_ICU_Fptr)(void) = NULLPTR;

static void (*Timer0_OVF_Fptr)(void) = NULLPTR;
static void (*Timer2_OVF_Fptr)(void) = NULLPTR;

static u8_t holdPrescal = 0;
static u16_t gPrescal = 1;
static u16_t Counter = 0;
static volatile u32_t gOVFNUM = 1;

EN_ERRORSTATE_t Timer0_Init(EN_Timer0Mode_t mode, EN_Timer0Scaler_t scaler, EN_OC0Mode_t oc_mode)
{
	EN_ERRORSTATE_t state;
	state = E_OK;
	switch (mode)
	{
	case TIMER0_NORMAL_MODE:
		CLR_BIT(holdPrescal, WGM00);
		CLR_BIT(holdPrescal, WGM01);
		break;
	case TIMER0_PHASECORRECT_MODE:
		SET_BIT(holdPrescal, WGM00);
		CLR_BIT(holdPrescal, WGM01);
		break;
	case TIMER0_CTC_MODE:
		CLR_BIT(holdPrescal, WGM00);
		SET_BIT(holdPrescal, WGM01);
		break;
	case TIMER0_FASTPWM_MODE:
		SET_BIT(holdPrescal, WGM00);
		SET_BIT(holdPrescal, WGM01);
		break;
	default:
		state = E_ERROR;
		break;
	}

	holdPrescal &= 0XF8; //0b11111000
	holdPrescal |= scaler;
	gPrescal = scaler;

	switch (oc_mode)
	{
	case OCO_DISCONNECTED:
		CLR_BIT(holdPrescal, COM00);
		CLR_BIT(holdPrescal, COM01);
		break;
	case OCO_TOGGLE:
		SET_BIT(holdPrescal, COM00);
		CLR_BIT(holdPrescal, COM01);
		break;
	case OCO_NON_INVERTING:
		CLR_BIT(holdPrescal, COM00);
		SET_BIT(holdPrescal, COM01);
		break;
	case OCO_INVERTING:
		SET_BIT(holdPrescal, COM00);
		SET_BIT(holdPrescal, COM01);
		break;
	default:
		state = E_ERROR;
		break;
	}
	return state;
}

void Timer0_Start()
{
	TCCR0 = holdPrescal;
}

void Timer0_Stop()
{
	TCCR0 &= 0x07;
}

void TIMER0_voidPhaseCorrect(u8_t DutyCycle, EN_OC0Mode_t ocomode)
{
	if (ocomode == OCO_INVERTING)
	{
		OCR0 = 255 - ((TIMER0_REG_CAPACITY * DutyCycle) / 100);
	}

	else if (ocomode == OCO_NON_INVERTING)
	{
		OCR0 = (255 * DutyCycle) / 100;
	}
}

EN_ERRORSTATE_t Timer0_InterruptEnable(EN_TIMER0_INTMODE_t INTMode)
{
	EN_ERRORSTATE_t state;
	state = E_OK;
	switch (INTMode)
	{
	case OV_INT:
		SET_BIT(TIMSK, TOIE0);
		break;
	case OC_INT:
		SET_BIT(TIMSK, OCIE0);
		break;
	default:
		state = E_ERROR;
		break;
	}
	SET_BIT(SREG, I_BIT);
	return state;
}

EN_ERRORSTATE_t Timer0_InterruptDisable(EN_TIMER0_INTMODE_t INTMode)
{
	EN_ERRORSTATE_t state;
	state = E_OK;
	switch (INTMode)
	{
	case OV_INT:
		CLR_BIT(TIMSK, TOIE0);
		break;
	case OC_INT:
		CLR_BIT(TIMSK, OCIE0);
		break;
	default:
		state = E_ERROR;
		break;
	}
	return state;
}

void Timer0_SetCallBack(void (*LocalFptr)(void))
{
	Timer0_OVF_Fptr = LocalFptr;
}

EN_ERRORSTATE_t Timer0_delayUs(u32_t Time)
{
	EN_ERRORSTATE_t state;
	state = E_OK;

	if (gPrescal == TIMER0_SCALER_8)
	{
		gPrescal = 8;
	}
	else if (gPrescal == TIMER0_SCALER_64)
	{
		gPrescal = 64;
	}
	else if (gPrescal == TIMER0_SCALER_256)
	{
		gPrescal = 256;
	}
	else if (gPrescal == TIMER0_SCALER_1024)
	{
		gPrescal = 1024;
	}
	else
	{
		state = E_ERROR;
	}

	float TickTime = gPrescal / F_CPU_MHZ;
	u32_t numbOfTick = Time / TickTime;
	gOVFNUM = numbOfTick / 250;

	return state;
}


void __vector_11(void)
{
	TCNT0 = 6;
	Counter++;
	if(Timer0_OVF_Fptr != NULLPTR)
	{
		if(Counter == gOVFNUM)
		{
			Timer0_OVF_Fptr();
			Counter=0;
		}

	}
}


/* Timer1 */
static u8_t gPre1A;
static u8_t gPre1B;
EN_ERRORSTATE_t Timer1_Init(Timer1Mode_type mode, Timer1Scaler_type scaler, OC1A_Mode_type oc1a_mode, OC1B_Mode_type oc1b_mode)
{
	EN_ERRORSTATE_t state;
	state = E_OK;

	switch (mode)
	{
	case TIMER1_NORMAL_MODE:
		CLR_BIT(gPre1A, WGM10);
		CLR_BIT(gPre1A, WGM11);
		CLR_BIT(gPre1B, WGM12);
		CLR_BIT(gPre1B, WGM13);
		break;
	case TIMER1_CTC_ICR_TOP_MODE:
		CLR_BIT(gPre1A, WGM10);
		CLR_BIT(gPre1A, WGM11);
		SET_BIT(gPre1B, WGM12);
		SET_BIT(gPre1B, WGM13);
		break;

	case TIMER1_CTC_OCRA_TOP_MODE:
		CLR_BIT(gPre1A, WGM10);
		CLR_BIT(gPre1A, WGM11);
		SET_BIT(gPre1B, WGM12);
		CLR_BIT(gPre1B, WGM13);
		break;

	case TIMER1_FASTPWM_ICR_TOP_MODE:
		CLR_BIT(gPre1A, WGM10);
		SET_BIT(gPre1A, WGM11);
		SET_BIT(gPre1B, WGM12);
		SET_BIT(gPre1B, WGM13);
		break;

	case TIMER1_FASTPWM_OCRA_TOP_MODE:
		SET_BIT(gPre1A, WGM10);
		SET_BIT(gPre1A, WGM11);
		SET_BIT(gPre1B, WGM12);
		SET_BIT(gPre1B, WGM13);
		break;
	default:
		state = E_ERROR;
		break;
	}

	switch (oc1a_mode)
	{
	case OCRA_DISCONNECTED:
		CLR_BIT(gPre1A, COM1A0);
		CLR_BIT(gPre1A, COM1A1);
		break;
	case OCRA_TOGGLE:
		SET_BIT(gPre1A, COM1A0);
		CLR_BIT(gPre1A, COM1A1);
		break;
	case OCRA_NON_INVERTING:
		CLR_BIT(gPre1A, COM1A0);
		SET_BIT(gPre1A, COM1A1);
		break;
	case OCRA_INVERTING:
		SET_BIT(gPre1A, COM1A0);
		SET_BIT(gPre1A, COM1A1);
		break;
	default:
		state = E_ERROR;
		break;
	}

	switch (oc1b_mode)
	{
	case OCRB_DISCONNECTED:
		CLR_BIT(gPre1A, COM1B0);
		CLR_BIT(gPre1A, COM1B1);
		break;
	case OCRB_TOGGLE:
		SET_BIT(gPre1A, COM1B0);
		CLR_BIT(gPre1A, COM1B1);
		break;
	case OCRB_NON_INVERTING:
		CLR_BIT(gPre1A, COM1B0);
		SET_BIT(gPre1A, COM1B1);
		break;
	case OCRB_INVERTING:
		SET_BIT(gPre1A, COM1B0);
		SET_BIT(gPre1A, COM1B1);
		break;
	default:
		state = E_ERROR;
		break;
	}

	gPre1B &= 0XF8;
	gPre1B |= scaler;

	return state;
}

void Timer1_InputCaptureEdge(ICU_Edge_type edge)
{
	if (edge == ICU_RISING)
	{
		SET_BIT(TCCR1B, ICES1);
	}
	else if (edge == ICU_FALLING)
	{
		CLR_BIT(TCCR1B, ICES1);
	}
}

void Timer1_Start(void)
{
	TCCR1A = gPre1A;
	TCCR1B = gPre1B;
}

void Timer1_Stop(void)
{
	TCCR1B &= 0x07;
}

EN_ERRORSTATE_t Timer1_InterruptEnable(EN_TIMER0_INTMODE_t INTMode)
{
	EN_ERRORSTATE_t state;
	state = E_OK;

	switch (INTMode)
	{
	case OVF_INT:
		SET_BIT(SREG, I_BIT);
		SET_BIT(TIMSK, TOIE1);
		break;
	case OCA_INT:
		SET_BIT(SREG, I_BIT);
		SET_BIT(TIMSK, OCIE1A);
		break;
	case OCB_INT:
		SET_BIT(SREG, I_BIT);
		SET_BIT(TIMSK, OCIE1B);
		break;
	case ICU_INT:
		SET_BIT(SREG, I_BIT);
		SET_BIT(TIMSK, TICIE1);
		break;
	default:
		state = E_ERROR;
		break;
	}

	return state;
}

EN_ERRORSTATE_t Timer1_InterruptDisable(EN_TIMER0_INTMODE_t INTMode)
{
	EN_ERRORSTATE_t state;
	state = E_OK;

	switch (INTMode)
	{
	case OVF_INT:
		CLR_BIT(TIMSK, TOIE1);
		break;
	case OCA_INT:
		CLR_BIT(TIMSK, OCIE1A);
		break;
	case OCB_INT:
		CLR_BIT(TIMSK, OCIE1B);
		break;
	case ICU_INT:
		CLR_BIT(TIMSK, TICIE1);
		break;
	default:
		state = E_ERROR;
		break;
	}
	return state;
}
