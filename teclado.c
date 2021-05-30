/*
 * File:   teclado.c
 * Author: Emmanuel
 *
 * Created on May 26, 2021, 12:42 AM
 */
#include <stdio.h>

#include "HeaderApp/teclado.h"
void teclado(uint8_t *valor){//Función teclado
    *valor = 0;
    PORTB=0xF0;
    if(PORTB != 0xF0){
        PORTB=0xFE;
            if(PORTBbits.RB4==0){*valor = '*';}
            if(PORTBbits.RB5==0){*valor = '0';}
            if(PORTBbits.RB6==0){*valor = '#';}
            if(PORTBbits.RB7==0){*valor = 'D';}
        PORTB=0xFD;
            if(PORTBbits.RB4==0){*valor = '7';}
            if(PORTBbits.RB5==0){*valor = '8';}
            if(PORTBbits.RB6==0){*valor = '9';}
            if(PORTBbits.RB7==0){*valor = 'C';}
        PORTB=0xFB;
            if(PORTBbits.RB4==0){*valor = '4';}
            if(PORTBbits.RB5==0){*valor = '5';}
            if(PORTBbits.RB6==0){*valor = '6';}
            if(PORTBbits.RB7==0){*valor = 'B';}
        PORTB=0xF7;
            if(PORTBbits.RB4==0){*valor = '1';}
            if(PORTBbits.RB5==0){*valor = '2';}
            if(PORTBbits.RB6==0){*valor = '3';}
            if(PORTBbits.RB7==0){*valor = 'A';}
    }
    PORTB = 0xF0;
    while (PORTB != 0xF0);
    
}