/**
 * 
 * @file ADC.c
 * @author Ahmed Elgharib
 * @date 2021-08-29
 * 
 */

#include "ADC.h"

EN_ERRORSTATE_t ADC_Init(EN_ADCREF_t vRef, EN_ADCPrescal_t scaler)
{
    EN_ERRORSTATE_t state;
    state = E_OK;
    switch (vRef)
    {
    case REF_VCC:
        SET_BIT(ADMUX, REFS0);
        CLR_BIT(ADMUX, REFS1);
        break;
    case REF_AREF:
        CLR_BIT(ADMUX, REFS0);
        CLR_BIT(ADMUX, REFS1);
        break;
    case REF_256V:
        SET_BIT(ADMUX, REFS0);
        SET_BIT(ADMUX, REFS1);
        break;
    case REF_REV:
        CLR_BIT(ADMUX, REFS0);
        SET_BIT(ADMUX, REFS1);
        break;
    default:
        state = E_ERROR;
        break;
    }

    /*Select Scaler*/
    ADCSRA &= 0xF8;
    ADCSRA |= scaler;

    /*Enable ADC*/
    SET_BIT(ADCSRA, ADEN);

    return state;
}

u16_t ADC_StartConversion(EN_ADChannelType_t ChType)
{
    //Select Channel
    ADMUX &= 0xE0; //11100000
    ADMUX |= ChType;

    //Start Conversion
    SET_BIT(ADCSRA, ADSC);

    while (GET_BIT(ADCSRA, ADSC)){}
    u16_t AADC;
    AADC = ADCL | (ADCH << 8);
    return AADC;
}
