/*
 * File:   app.c
 * Author: Emmanuel
 *
 * Created on May 29, 2021, 4:04 PM
 */
#include <string.h>

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
        datos.character = 0;
    }
}

void appGetElements(void)
{
    datos.state = 0;
    appTimerStop();
    LCD_CLEAR_DATA();
    appSubGetData(&datos);
    LCD_CLEAR_DATA();
    datos.nextFunc = appStateInitial;
    appTimerStart();
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

void appSubGetData(StateMachine *data_Inout)
{
    uint16_t cantidad = 0;
    uint8_t inout = 0;
    memset(data_Inout->display,0,sizeof(data_Inout->display));
    LCD_OUT_TXT(1,0,"C de vacunas:");
    while(inout != '*')
    {
        teclado(&inout);
        
        if((inout >= '0') && (inout <= '9'))
        {
            cantidad = (cantidad*10)+(inout - 48);
        }
        sprintf((char *)data_Inout->display,"%d",cantidad);
        LCD_OUT_TXTB(2,0,data_Inout->display);
    }
    data_Inout->elements = (int16_t)cantidad;
}

void appSubGiveElemts(StateMachine *data)
{
    
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