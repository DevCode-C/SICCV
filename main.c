/*
 * File:   main.c
 * Author: Emmanuel
 *
 * Created on May 25, 2021, 3:49 PM
 */


#include "HeaderApp/Config.h"         // Configuracion de los #Pragma
#include "pic18f4550.h"     // Agregamos la libreria del microcontrolador que estamos usando 
#define _XTAL_FREQ 48000000 // Definimos la frecuencia que estamos usando 

void main(void) {
    
    ADCON1 = 0x0F; //Disable all analog inputs
    TRISDbits.RD2 = 0;
    
    while(1) {

        LATDbits.LATD3 = 1;
        __delay_ms(500);
        LATDbits.LATD3 = 0;
        __delay_ms(500);
    }
}
//Hola mundo 