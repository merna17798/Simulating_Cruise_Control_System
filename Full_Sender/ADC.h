/**
 * 
 * @file ADC.h
 * @author Ahmed Elgharib
 * @date 2021-08-29
 * 
 */

#ifndef ADC_H_
#define ADC_H_

#include "DataTypes.h"
#include "BitMath.h"
#include "Memmap.h"

typedef enum
{
    REF_VCC = 0,
    REF_AREF,
    REF_256V,
    REF_REV
} EN_ADCREF_t;

typedef enum
{
    ADC_Scal_2 = 1,
    ADC_Scal_4,
    ADC_Scal_8,
    ADC_Scal_16,
    ADC_Scal_32,
    ADC_Scal_64,
    ADC_Scal_128
} EN_ADCPrescal_t;

typedef enum
{
    CH_0=0,
    CH_1,
    CH_2,
    CH_3,
    CH_4,
    CH_5,
    CH_6,
    CH_7
} EN_ADChannelType_t;

EN_ERRORSTATE_t ADC_Init(EN_ADCREF_t vRef, EN_ADCPrescal_t scaler);
u16_t ADC_StartConversion(EN_ADChannelType_t ChType);


#endif