/*
 * File:   app.c
 * Author: Emmanuel
 *
 * Created on May 29, 2021, 4:04 PM
 */
#include <string.h>
#include "HeaderApp/app.h"
#include "HeaderApp/UART.h"

extern StateMachine datos;
void appInit(void)
{
    appISRConfig();
    appLCD_Init();
    adcInit(2);
    appTimerInit();
    appCounterInit(0);
    servoInit();
    uart_Init(9600);
    setServo(D0,10,0);
    
    
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

void appStateRecolectData(void)
{
    appADC(&datos);
    appBat(&datos);
//    appElemts(&datos.elements);
    appElemts(&datos);
    if(datos.state == 2)
    {
        if(datos.elements == TMR0)
        {
            datos.elements = (int16_t)TMR0;
            appCounterStop();
            datos.state = 0;
            setServo(D0,10,2);
            LATAbits.LA5 = 0;
            setServo(D180,10,0);
        }
    }
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
    else if(PORTAbits.RA3)
    {
        setServo(D0,10,0);
    }
}

void appGetElements(void)   //Funcion para la obtencion de elementos y activacion de la etapa de entrega
{
    datos.state = 2;
    appTimerStop();
    LCD_CLEAR_DATA();
    appSubGetData(&datos);
    LCD_CLEAR_DATA();
    appSubGiveElemts(&datos);
    datos.nextFunc = appStateInitial;
    appTimerStart();
}



void appSubGetData(StateMachine *data_Inout) //Funcion donde se introduce los valores del teclado matricial
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
    data_Inout->elements += (int16_t)cantidad;
}

void appSubGiveElemts(StateMachine *data)   //Funcionn donde se inicia el contador
{
    appCounterStart();
    setServo(D90,10,2);
    LATAbits.LA5 = 1;
}

void warning(void)
{
    appTimerStop();
    LCD_CLEAR_DATA();
    LCD_OUT_TXT(1,0,"Sin vacunas");
    LCD_OUT_TXT(2,0,"Recarga Porfavor");
    setServo(D180,10,1);
    while(datos.state == 10);
    appTimerStart();
}

void confirmacion(void)
{
    LCD_OUT_TXT(1,0,"Confirmacion");
    while(datos.state == IDLE_CONFIRMATION);
    LCD_CLEAR_DATA();
    appTimerStart();
}

void sendinformation(void)
{
    appADC(&datos);
    sendData(&datos);
    appBat(&datos);
    sendData(&datos);
    appElemts(&datos);
    sendData(&datos);
    memset(datos.display,0,sizeof(datos.display));
    sprintf((char *)datos.display,"@");
    sendData(&datos);
    
    memset(datos.display,0,sizeof(datos.display));
    datos.state = IDLE;
    datos.nextFunc = appStateInitial;
}