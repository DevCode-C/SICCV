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
    appADC(&datos);
    appBat(&datos);
    appElemts(&datos.elements);
    datos.nextFunc = appStateInitial;
}
void appStateInitial(void)
{
//    LCD_CLEAR_DATA();
    teclado(&datos.character);
    if(datos.character != 0)
    {
        datos.state = 1;
    }
//    sprintf((char *)datos.display,"%c",(char)datos.character);
//    LCD_OUT_TXTB(1,0,datos.display);
}

void appGetElements(void)
{
    appTimerStop();
    LCD_CLEAR_DATA();
    while(1)
    {
        teclado(&datos.character);
        sprintf((char *)datos.display,"%c",(char)datos.character);
        LCD_OUT_TXTB(1,0,datos.display);
    }
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
        if((datos.counter == 10) && (datos.state == 0))
        {
            datos.counter = 0;
            datos.nextFunc = appStateRecolectData;
        }
        else if(datos.state == 1)
        {
            datos.nextFunc = appGetElements;
        }
        TMR3 = 20536;
    }
}
void __interrupt(high_priority) isrH(void)
{
    
}