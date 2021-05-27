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
#include <stdlib.h>
#include <stdio.h>
#define _XTAL_FREQ 12000000

/****************Variables a utilizar*********/
float decimal= 4.47;
uint16_t entero=20;
char buffer_lcd[20];

/****************Funci?n Principal*************/
void main(void)
{
    TRISD=0x00;               //Configuramos el Puerto D como salida digital.
    lcd_init();               //Inicializamos la pantalla LCD.
    adcInit(2);
    lcd_clear();          //Limpiamos pantalla LCD
    lcd_gotoxy(1,1);      //Ubicamos el cursor en fila 1, columna 1
    lcd_putc("**IDE MPLAB X**");  //mostramos una cadena de caracteres en la pantalla LCD
    lcd_gotoxy(2,1);      //Ubicamos el cursor en fila2, columna 1
    lcd_putc("******XC8******");  //mostramos una cadena de caracteres en la pantalla LCD
    __delay_ms(1000);
    lcd_clear();
    while(1)                  //Bucle Infinito 
    {
        entero = adcGetValue(0);
        sprintf(buffer_lcd,"ADC1:%d",entero);
        lcd_gotoxy(1,1);
        lcd_putc(buffer_lcd);
        __delay_ms(100);
        entero = adcGetValue(1);
        sprintf(buffer_lcd,"ADC2:%d",entero);
        lcd_gotoxy(2,1);
        lcd_putc(buffer_lcd);
        __delay_ms(100);
    }
    return;
}
