/*
 * File:   main.c
 * Author: Emmanuel
 *
 * Created on May 25, 2021, 3:49 PM
 */

#define _XTAL_FREQ 12000000
#include "HeaderApp/Config.h"           // Configuracion de los #Pragma
#include "pic18f4550.h"                 // Agregamos la libreria del microcontrolador que estamos usando 
#include "HeaderApp/adc.h"
//#include "HeaderApp/lcd.h"
#include "HeaderApp/flex_lcd.h"
#include <stdlib.h>
#include <stdio.h>


/****************Variables a utilizar*********/
uint16_t entero;
uint8_t buffer_lcd[16];

/****************Funci?n Principal*************/
void main(void)
{
    Lcd_Init();
    Lcd_Cmd(LCD_CLEAR);
    Lcd_Cmd(LCD_CURSOR_OFF);
     __delay_ms(100);
     Lcd_Out(1,1,(int8_t *)"Bienvenido :*");
    Lcd_Out(2,1,(int8_t *)"*Calculadora*");
    __delay_ms(1000);
    Lcd_Cmd(LCD_CLEAR);
    __delay_ms(100);
    adcInit(2);
    while(1)                  
    {
        entero = adcGetValue(0);
        sprintf((char *)buffer_lcd,"ADC1:%d",entero);
        Lcd_Out2(1,0,(int8_t*)buffer_lcd);
        __delay_ms(100);
        entero = adcGetValue(1);
        sprintf((char *)buffer_lcd,"ADC2:%d",entero);
        Lcd_Out2(2,0,(int8_t*)buffer_lcd);
        __delay_ms(100);
    }
    return;
}
