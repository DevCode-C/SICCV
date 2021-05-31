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
    uint16_t cantidad = 0;
    uint8_t inout = 0;
    appTimerStop();
    memset(datos.display,0,sizeof(datos.display));
    LCD_CLEAR_DATA();
    LCD_OUT_TXT(1,0,"C de vacunas:");
    while(inout != '*')
    {
        teclado(&inout);
        
        if((inout >= '0') && (inout <= '9'))
        {
            cantidad = (cantidad*10)+(inout - 48);
        }
        sprintf((char *)datos.display,"%d",cantidad);
        LCD_OUT_TXTB(2,0,datos.display);
    }
    datos.elements -= cantidad;
    datos.character = 0;
    if(datos.elements <= 0)
    {
        datos.elements = 0;
    }
    __delay_ms(500);
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