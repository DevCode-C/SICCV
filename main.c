/*
 * File:   main.c
 * Author: Emmanuel
 *
 * Created on May 25, 2021, 3:49 PM
 */

#define _XTAL_FREQ 12000000                // Agregamos la libreria del microcontrolador que estamos usando 
#include "HeaderApp/main.h"
#include "HeaderApp/servo.h"


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
    LCD_OUT_TXT(1,0,"Bienvenidos");
    __delay_ms(1000);
    LCD_CLEAR_DATA();
    adcInit(2);
    servoInit();
    while(1)                  
    {
//        entero = adcGetValue(0);
//        sprintf((char *)buffer_lcd,"ADC1:%d",entero);
//        Lcd_Out2(1,0,(int8_t*)buffer_lcd);
//        __delay_ms(100);
//        entero = adcGetValue(1);
//        sprintf((char *)buffer_lcd,"ADC2:%d",entero);
//        Lcd_Out2(2,0,(int8_t*)buffer_lcd);
//        __delay_ms(100);
        iniciarTest();
//        __delay_ms(100);
    }
    return;
}
