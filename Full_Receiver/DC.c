
#include "DataTypes.h"
#include "DIO.h"
#include "Timer.h"
#include "DC_config.h"
#include "DC_interface.h"


void DC_voidInit(void)
{
	//configure PB1,PB2(Motor pins) as output pins
	Timer0_Init(TIMER0_PHASECORRECT_MODE, TIMER0_SCALER_8, OCO_NON_INVERTING);
	Timer0_Start();
	DIO_setPinDirection(DC_PORT, DC_POSITIVE_PIN,OUTPUT);
	DIO_setPinDirection(DC_PORT, DC_NEGATIVE_PIN,OUTPUT);
}

/******************************************************************************
 * function to rotate the motor according to the required direction sent to it*
 ******************************************************************************/
void DC_voidRotate(dc_direction direction)
{
	if(direction == CLK_WISE)
	{
		//we using pwm so first pin is fixed to pin oc0 we can't control it here
		//Rotate clock wise
		DIO_setPin(DC_PORT, DC_POSITIVE_PIN, HIGH);
		DIO_setPin(DC_PORT, DC_NEGATIVE_PIN, LOW);
	}//end if
	else if(direction == ANTI_CLK_WISE)
	{
		//Rotate anti-clock wise
		DIO_setPin(DC_PORT, DC_POSITIVE_PIN, LOW);
		DIO_setPin(DC_PORT, DC_NEGATIVE_PIN, HIGH);
	}//end else if
}//end DC_voidRotate

/*********************************************************************
 * function to set the motor speed according to duty cycle sent to it*
 *********************************************************************/
void DC_voidSetSpeed(u8_t Copy_DutyCycle)
{
	//initialize the timer to work on PWM mode

	TIMER0_voidPhaseCorrect(Copy_DutyCycle, OCO_NON_INVERTING);
	// set the running time so we need the other connect to set to HIGH so that it can work


}//end DC_voidSpeed

void DC_voidSTOP(void)
{

	//we using pwm so first pin is fixed to pin oc0 we can't control it here
	//Rotate clock wise
	DIO_setPin(DC_PORT, DC_POSITIVE_PIN, LOW);
	DIO_setPin(DC_PORT, DC_NEGATIVE_PIN, LOW);

}//end DC_voidRotate
