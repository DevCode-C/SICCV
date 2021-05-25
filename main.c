/*
 * File:   main.c
 * Author: Emmanuel
 *
 * Created on May 25, 2021, 3:49 PM
 */


#include "Config.h"
#include "pic18f4550.h"
#define _XTAL_FREQ 48000000

void main(void) {
    
    TRISDbits.TRISD3 = 1;
    LATDbits.LATD3 = 0;
    
    while (1) 
    {
        LATDbits.LATD3 = 1;
        __delay_ms(100);
        LATDbits.LATD3 = 0;
        __delay_ms(100);
    }

    
    return;
}
