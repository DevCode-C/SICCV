/*
 * File:   adc.c
 * Author: Emmanuel
 *
 * Created on May 25, 2021, 7:14 PM
 */

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
    ADCON2bits.ACQT = 0b110;
    
    /*
     conversion clock
    */
    ADCON2bits.ADCS = 0b010;
    
}