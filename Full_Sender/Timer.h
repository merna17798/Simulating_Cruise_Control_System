  
/**
 * 
 * @file Timer.h
 * @author Ahmed Elgharib
 * @date 2021-08-20
 * 
 */

#ifndef TIMER_H_
#define TIMER_H_


#include "DataTypes.h"
#include "BitMath.h"
#include "Memmap.h"

#define  TIMER0_REG_CAPACITY		256
#define  TIMER2_REG_CAPACITY		256
#define  F_CPU_MHZ       			8

/* Timer0 */
void __vector_5(void) __attribute__((signal));

typedef enum
{
	TIMER0_STOP = 0,
	TIMER0_SCALER_1,
	TIMER0_SCALER_8,
	TIMER0_SCALER_64,
	TIMER0_SCALER_256,
	TIMER0_SCALER_1024,
	EXTERNALl_FALLING,
	EXTERNAL_RISING
} EN_Timer0Scaler_t;

typedef enum
{
	TIMER0_NORMAL_MODE = 0,
	TIMER0_PHASECORRECT_MODE,
	TIMER0_CTC_MODE,
	TIMER0_FASTPWM_MODE

} EN_Timer0Mode_t;

typedef enum
{
	OCO_DISCONNECTED = 0,
	OCO_TOGGLE,
	OCO_NON_INVERTING,
	OCO_INVERTING
} EN_OC0Mode_t;

typedef enum
{
    OV_INT=0,
    OC_INT
} EN_TIMER0_INTMODE_t;




EN_ERRORSTATE_t Timer0_Init(EN_Timer0Mode_t mode, EN_Timer0Scaler_t scaler, EN_OC0Mode_t oc_mode);
void Timer0_Start(void);
void Timer0_Stop(void);
void TIMER0_voidPhaseCorrect(u8_t DutyCycle, EN_OC0Mode_t ocomode);
EN_ERRORSTATE_t Timer0_InterruptEnable(EN_TIMER0_INTMODE_t INTMode);
EN_ERRORSTATE_t Timer0_InterruptDisable(EN_TIMER0_INTMODE_t INTMode);
EN_ERRORSTATE_t Timer0_delayUs(u32_t Time);
void __vector_11(void) __attribute__((signal));
void Timer0_SetCallBack(void (*local_pf)(void));


/* TIMER1 */

typedef enum
{
	TIMER1_STOP = 0,
	TIMER1_SCALER_1,
	TIMER1_SCALER_8,
	TIMER1_SCALER_64,
	TIMER1_SCALER_256,
	TIMER1_SCALER_1024,
	EXTERNAL0_FALLING,
	EXTERNAL0_RISING
} Timer1Scaler_type;

typedef enum
{
	TIMER1_NORMAL_MODE = 0,
	TIMER1_CTC_ICR_TOP_MODE,
	TIMER1_CTC_OCRA_TOP_MODE,
	TIMER1_FASTPWM_ICR_TOP_MODE,
	TIMER1_FASTPWM_OCRA_TOP_MODE,
	TIMER1_PHASE_CORRECT_ICR_TOP_MODE

} Timer1Mode_type;

typedef enum
{
	OCRA_DISCONNECTED = 0,
	OCRA_TOGGLE,
	OCRA_NON_INVERTING,
	OCRA_INVERTING

} OC1A_Mode_type;

typedef enum
{
	OCRB_DISCONNECTED = 0,
	OCRB_TOGGLE,
	OCRB_NON_INVERTING,
	OCRB_INVERTING

} OC1B_Mode_type;

typedef enum
{
	ICU_RISING,
	ICU_FALLING
}ICU_Edge_type;

typedef enum
{
    OVF_INT=0,
    OCA_INT,
    OCB_INT,
    ICU_INT
} EN_TIMER1_INTMODE_t;

void Timer1_InputCaptureEdge(ICU_Edge_type edge);
EN_ERRORSTATE_t Timer1_Init(Timer1Mode_type mode, Timer1Scaler_type scaler, OC1A_Mode_type oc1a_mode, OC1B_Mode_type oc1b_mode);
void Timer1_Start(void);
void Timer1_Stop(void);
EN_ERRORSTATE_t Timer1_InterruptEnable(EN_TIMER0_INTMODE_t INTMode);
EN_ERRORSTATE_t Timer1_InterruptDisable(EN_TIMER0_INTMODE_t INTMode);
void Timer1_OVF_SetCallBack(void (*LocalFptr)(void));
void Timer1_OCA_SetCallBack(void (*LocalFptr)(void));
void Timer1_OCB_SetCallBack(void (*LocalFptr)(void));
void Timer1_ICU_SetCallBack(void (*LocalFptr)(void));

typedef enum
{
	TIMER2_NORMAL_MODE = 0,
	TIMER2_PHASECORRECT_MODE,
	TIMER2_CTC_MODE,
	TIMER2_FASTPWM_MODE
} EN_Timer2Mode_t;

typedef enum
{
	TIMER2_STOP = 0,
	TIMER2_SCALER_1,
	TIMER2_SCALER_8,
	TIMER2_SCALER_64,
	TIMER2_SCALER_256,
	TIMER2_SCALER_1024,
} EN_Timer2Scaler_t;
EN_ERRORSTATE_t Timer2_init(EN_Timer2Mode_t mode, EN_Timer2Scaler_t scaler);

u8_t Timer2_GetCount(void);

void Timer2_OV_InterruptEnable(void);
void Timer2_OV_InterruptDisable(void);
void Timer2_OVF_SetCallBack(void (*LocalFptr)(void));
#endif /* TIMER_H_ */
