/*
 * File:   main.c
 * Author: Emmanuel
 *
 * Created on May 25, 2021, 3:49 PM
 */

#include "HeaderApp/main.h"
#include "HeaderApp/app.h"

StateMachine datos = {0,0,IDLE_CONFIRMATION,0,0,{0},confirmacion};
uint8_t puerto[16] = {0}; 
void main(void)
{
    TRISB = 0xF0;
    INTCON2bits.RBPU = 0;
    TRISAbits.TRISA2 = 0;
    TRISAbits.TRISA5 = 0;
    appInit();
    while(1)                  
    {
//        LATAbits.LA2= !LATAbits.LA2;
//        __delay_ms(100);
        datos.nextFunc();
//        sendinformation();
        
    }
    return;
}

void __interrupt(low_priority) isrL(void)
{
    if(TMR3IE && TMR3IF)
    {
        TMR3IF = 0;
        datos.counter++;
        if((datos.counter == 5) && (datos.state == 0 || datos.state == 2))
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
    static uint8_t counter = 0;
    if(TMR0IE && TMR0IF)
    {
        TMR0IF = 0;
        datos.state = 10;
        datos.nextFunc = warning;
    }
    if(RCIF && RCIE)
    {   
        puerto[counter] = RCREG;
        if(puerto[counter] != '@')
        {
            counter ++;
        }
        else
        {
            datos.state = 4;
            datos.nextFunc = readUART;
            counter = 0;
        }
    }
}

