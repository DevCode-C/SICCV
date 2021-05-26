/*
 * File:   adc.c
 * Author: Emmanuel
 *
 * Created on May 25, 2021, 7:14 PM
 */

#include <pic18.h>
#include "HeaderApp/adc.h"

void adcInit(uint8_t ADC_PINs)
{
    /*Habilitacion de pines analogicos*/
    if(ADC_PINs == 0)
    {
        ADCON1bits.PCFG = 0b1110;
    }
    else
    {
        ADCON1bits.PCFG = 15 - ADC_PINs;
    }
    
    /*
     Registro que configura la referencia de voltaje del puerto ADC
    */
    ADCON1bits.VCFG = 0b00;
    
    /*
     Select A/D acquisition time
    */
    ADCON2bits.ACQT = 0b010;
    
    /*
     conversion clock
    */
    ADCON2bits.ADCS = 3;
    
    /**/
    ADCON2bits.ADFM = 1;
    ADC_ENABLE();
}

uint16_t adcGetValue(uint8_t PinADC)
{
    ADCON0bits.CHS = PinADC; 
    __delay_ms(2);
    GO_nDONE = 1;
    while(ADCON0bits.GO_DONE)
    {
    }
    return ADRES;
}