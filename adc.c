/*
 * File:   adc.c
 * Author: Emmanuel
 *
 * Created on May 25, 2021, 7:14 PM
 */
#include "HeaderApp/main.h"

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

void appADC(void)
{
    uint8_t dataOut[9] = {0}; 
    float lm35val = adcGetValue(0);
    lm35val = (float)((lm35val*4.88)/10.0);
    sprintf((char *)dataOut,"T:%0.1f C",lm35val);
    LCD_OUT_TXTB(1,0,dataOut);
}

void appBat(void)
{
    uint8_t dataOut[8] = {0}; 
    float bat = adcGetValue(1);
    bat = (float)((bat*5.0)/1024.0);
    sprintf((char *)dataOut,"Bat:%d",(int)((bat*100)/5));
    LCD_OUT_TXTB(2,0,dataOut);
}