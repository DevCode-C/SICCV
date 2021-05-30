#include "pic18f4550.h"
#include "stdint.h"
#ifndef __ADC__H
#define __ADC__H
    #define _XTAL_FREQ 12000000             // Definimos la frecuencia que estamos usando 
    #define ADC_ENABLE()    ADCON0bits.ADON = 1
    #define ADC_DISABLE()   ADCON0bits.ADON = 0;

    /*
        Inicializa el perifico ADC
    */
    void adcInit(uint8_t ADC_PINs);
    
    /*
     Retorna el valor del Puerto ADC
    */
    uint16_t adcGetValue(uint8_t PinADC);
    
    
    void appADC(void);
    
    void appBat(void);
    
#endif