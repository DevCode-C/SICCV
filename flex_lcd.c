/*
 * File:   lcd.c
 * Author: Emmanuel
 *
 * Created on May 25, 2021, 11:28 PM
 */

#include <xc.h>
#include "pic18f4550.h"
#include "HeaderApp/flex_lcd.h"

//Se necesita verificar si algun pin tiene alguna otra conexion que se necesite.
#define TRISRD7     TRISDbits.TRISD7
#define LCD_LD7     LATDbits.LD7      // D7

#define TRISRD6     TRISDbits.TRISD6
#define LCD_LD6     LATDbits.LD6       // D6

#define TRISRD5     TRISDbits.TRISD5
#define LCD_LD5     LATDbits.LD5       // D5

#define TRISRD4     TRISDbits.TRISD4
#define LCD_LD4     LATDbits.LD4      // D4

#define TRISEN      TRISDbits.TRISD3
#define LCD_EN      LATDbits.LD3       // EN

#define TRISRS      TRISDbits.TRISD2
#define LCD_RS      LATDbits.LD2       // RS

void Lcd_Init(void)
{
    TRISRD7 = 0;
    TRISRD6 = 0;
    TRISRD5 = 0;
    TRISRD4 = 0;
    TRISEN = 0;
    TRISRS = 0;
    __delay_ms(34);
    for (uint8_t i = 0; i < 4; i++) {
        LCD_LD7 = 0;
        LCD_LD6 = 0;
        LCD_LD5 = 1;
        LCD_LD4 = 1;
        LCD_EN = 0;
        LCD_RS = 0;
        LCD_LD7 = 0;
        LCD_LD6 = 0;
        LCD_LD5 = 1;
        LCD_LD4 = 1;
        LCD_EN = 1;
        LCD_RS = 0;
        __delay_us(5);
        LCD_LD7 = 0;
        LCD_LD6 = 0;
        LCD_LD5 = 1;
        LCD_LD4 = 1;
        LCD_EN = 0;
        LCD_RS = 0;
        __delay_us(5500);
    }
    LCD_LD7 = 0; 
    LCD_LD6 = 0; 
    LCD_LD5 = 1; 
    LCD_LD4 = 0; 
    LCD_EN = 0; 
    LCD_RS = 0;
    LCD_LD7 = 0; 
    LCD_LD6 = 0; 
    LCD_LD5 = 1; 
    LCD_LD4 = 0; 
    LCD_EN = 1; 
    LCD_RS = 0;
    __delay_us(5);
    LCD_LD7 = 0; 
    LCD_LD6 = 0; 
    LCD_LD5 = 1; 
    LCD_LD4 = 0; 
    LCD_EN = 0; 
    LCD_RS = 0;
    __delay_us(5500);
    
    uint8_t data = 0;
    data = 40;
    Lcd_Cmd(data);
    data = 16;
    Lcd_Cmd(data);
    data = 1;
    Lcd_Cmd(data);
    data = 15;
    Lcd_Cmd(data);
    
}

void Lcd_Out(uint8_t y, uint8_t x, const int8_t *buffer)
{
    uint8_t data;
    switch (y)
    {
        case 1: 
            data = 128 + x;
            break;
        case 2: 
            data = 192 + x; 
            break;
        case 3:
            data = 148 + x;
            break;
        case 4: 
            data = 212 + x;
            break;
        default: break;
    }
    
    Lcd_Cmd(data);
    while(*buffer)              // Write data to LCD up to null
    {                
        Lcd_Chr_CP(*buffer);
        buffer++;               // Increment buffer
    }
}

void Lcd_Out2(uint8_t y, uint8_t x, int8_t *buffer)
{
    uint8_t data;
    switch (y)
    {
        case 1: 
            data = 128 + x;
            break;
        case 2: 
            data = 192 + x; 
            break;
        case 3:
            data = 148 + x;
            break;
        case 4: 
            data = 212 + x;
            break;
        default: break;
    }
    
    Lcd_Cmd(data);
    while(*buffer)              // Write data to LCD up to null
    {                
        Lcd_Chr_CP(*buffer);
        buffer++;               // Increment buffer
    }
}

void Lcd_Chr_CP(int8_t data)
{
    LCD_EN = 0;
    LCD_RS = 1;
    LCD_LD7 = (data & 0b10000000)>>7;
    LCD_LD6 = (data & 0b01000000)>>6;
    LCD_LD5 = (data & 0b00100000)>>5;
    LCD_LD4 = (data & 0b00010000)>>4;
    _delay(10);
    LCD_EN = 1;
    __delay_us(5);
    LCD_EN = 0;
    LCD_LD7 = (data & 0b00001000)>>3;
    LCD_LD6 = (data & 0b00000100)>>2;
    LCD_LD5 = (data & 0b00000010)>>1;
    LCD_LD4 = (data & 0b00000001);
    _delay(10);
    LCD_EN = 1;
    __delay_us(5); 
    LCD_EN = 0;
    __delay_us(5);
    __delay_us(5500);
}

void Lcd_Cmd(uint8_t data)
{
    LCD_EN = 0; LCD_RS = 0;
    LCD_LD7 = (data & 0b10000000)>>7;
    LCD_LD6 = (data & 0b01000000)>>6;
    LCD_LD5 = (data & 0b00100000)>>5;
    LCD_LD4 = (data & 0b00010000)>>4;
    _delay(10);
    LCD_EN = 1;
    __delay_us(5);
    LCD_EN = 0;
    LCD_LD7 = (data & 0b00001000)>>3;
    LCD_LD6 = (data & 0b00000100)>>2;
    LCD_LD5 = (data & 0b00000010)>>1;
    LCD_LD4 = (data & 0b00000001);
    _delay(10);
    LCD_EN = 1;
    __delay_us(5);
    LCD_EN = 0;
    __delay_us(5500);
}
