/*
 * File:   adc.c
 * Author: Emmanuel
 *
 * Created on May 25, 2021, 7:14 PM
 */
#include "HeaderApp/adc.h"
#include <string.h>

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
    
    TRISCbits.TRISC1 = 0;
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

void appADC(StateMachine *data)
{
    memset(data->display,0,sizeof(data->display));
    float lm35val = adcGetValue(0);
    lm35val = (float)((lm35val*4.88)/10.0);
//    sprintf((char *)dataOut,"T:%02d.%02d C",(uint8_t)lm35val,(uint8_t)((uint8_t)(lm35val*100)%100));
    sprintf((char *)data->display,"T:%02d.%02d C",(uint8_t)lm35val,(uint8_t)((uint8_t)(lm35val*100)%100));
    LCD_OUT_TXTB(1,0,data->display);
    if(((int)lm35val < 2))
    {
        LATCbits.LATC1 = 0;
    }
    else if(((int)lm35val >= 7))
    {
        LATCbits.LATC1 = 1;
    }
}

void appBat(StateMachine *data)
{
    memset(data->display,0,sizeof(data->display));
//    float bat = adcGetValue(1);
//    bat = (float)((bat*5.0)/1024.0);
//    bat = ((bat*100)/5.0);
//    data->bat = (uint8_t)((bat*100)/5);
    data->bat = adcGetValue(1);
    data->bat = (uint16_t)(((data->bat *5.0)/1024.0)*100);
    data->bat = (uint16_t)((data->bat*100.0)/500.0);
    sprintf((char *)data->display,"Bat:%02d",(data->bat));
    LCD_OUT_TXTB(2,0,data->display);
}