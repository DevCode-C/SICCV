/*
 * File:   main.c
 * Author: Emmanuel
 *
 * Created on May 25, 2021, 3:49 PM
 */

#include "HeaderApp/main.h"
#include "HeaderApp/app.h"

StateMachine datos = {0,255,0,0,0,{0},appStateInitial};
void main(void)
{
    TRISB = 0xF0;
    INTCON2bits.RBPU = 0;
    TRISAbits.TRISA3 = 0;
    appInit();
    while(1)                  
    {
        LATAbits.LA3 = !LATAbits.LA3;
        __delay_ms(100);
        datos.nextFunc();
        
    }
    return;
}

