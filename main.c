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

