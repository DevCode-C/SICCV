/*
 * File:   app.c
 * Author: Emmanuel
 *
 * Created on May 29, 2021, 4:04 PM
 */
#include "HeaderApp/app.h"

extern StateMachine datos;
void appInit(void)
{
    appISRConfig();
    appLCD_Init();
    adcInit(2);
    appTimerInit();
    appTimerStart();
    
    
}

void appStateRecolectData(void)
{
    uint8_t dataOut[16] = {0}; 
    sprintf((char *)dataOut,"ADC1:%d",adcGetValue(0));
    LCD_OUT_TXTB(1,0,dataOut);
    sprintf((char *)dataOut,"ADC2:%d",adcGetValue(1));
    LCD_OUT_TXTB(2,0,dataOut);
    datos.nextFunc = appStateInitial;
}
void appStateInitial(void)
{

}

void appISRConfig(void)
{
    /*
     Activacion de interrupcion globales, perifericos y prioridades de interrupcion
    */
    RCONbits.IPEN = 1;
    INTCONbits.GIE_GIEH = 1;
    INTCONbits.PEIE_GIEL = 1;
}