/*
 * File:   adc.c
 * Author: Emmanuel
 *
 * Created on May 25, 2021, 7:14 PM
 */

#include <pic18.h>
#include "HeaderApp/adc.h"

void adcInit(void)
{
    /**/
    ADCON1bits.PCFG = 0b0001;
   
    /*
     Registro que configura la referencia de voltaje del puerto ADC
    */
    ADCON1bits.VCFG = 0b00;
    
    /*
     Registro que configura el pin como analogico
    */
    ADCON0bits.CHS = 0b0000;    
    
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

uint16_t adcGetValue(void)
{
    __delay_ms(1);
    GO_nDONE = 1;
    while(ADCON0bits.GO_DONE)
    {
    
    }
    return ADRES;
}