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
    appADC();
    appBat();
    appElemts(&datos.elements);
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

void __interrupt(low_priority) isrL(void)
{
    if(TMR3IE && TMR3IF)
    {
        TMR3IF = 0;
        
        datos.counter++;
        if(datos.counter == 10)
        {
            datos.counter = 0;
            datos.nextFunc = appStateRecolectData;
        }
        TMR3 = 20536;
    }
}
void __interrupt(high_priority) isrH(void)
{
    
}