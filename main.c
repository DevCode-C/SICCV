/*
 * File:   main.c
 * Author: Emmanuel
 *
 * Created on May 25, 2021, 3:49 PM
 */

#include "HeaderApp/main.h"
#include "HeaderApp/app.h"

StateMachine datos = {0,255,0,0,{0},appStateInitial};
void main(void)
{
    TRISBbits.TRISB3 = 0;
    LATBbits.LATB2 = 0;
    appInit();
    while(1)                  
    {
        
        LATBbits.LATB3 = !LATBbits.LATB3;
        __delay_ms(100);
        datos.nextFunc();
    }
    return;
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