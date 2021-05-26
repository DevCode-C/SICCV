/*
 * File:   main.c
 * Author: Emmanuel
 *
 * Created on May 25, 2021, 3:49 PM
 */


#include "HeaderApp/Config.h"           // Configuracion de los #Pragma
#include "pic18f4550.h"                 // Agregamos la libreria del microcontrolador que estamos usando 
#include "HeaderApp/adc.h"
#include "HeaderApp/lcd.h"
void main(void) {
    
//    ADCON1 = 0x0F;
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    TRISAbits.TRISA2 = 0;
    TRISD = 0x00;
    adcInit(2);
    while(1) {

        LATD = (uint8_t)adcGetValue(0);
        LATAbits.LA2 = 1;
        __delay_ms(500);
        LATD = (uint8_t)adcGetValue(1);
        LATAbits.LA2 = 0;
        __delay_ms(500);
    }
}