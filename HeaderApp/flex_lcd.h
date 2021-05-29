#include <stdint.h>
#ifndef __LCD__H
#define __LCD__H
    #define _XTAL_FREQ 12000000
    /*
     Definicion de los comandos
    */
    #define      LCD_FIRST_ROW           128
    #define      LCD_SECOND_ROW          192
    #define      LCD_THIRD_ROW           148
    #define      LCD_FOURTH_ROW          212
    #define      LCD_CLEAR               1
    #define      LCD_RETURN_HOME         2
    #define      LCD_CURSOR_OFF          12
    #define      LCD_UNDERLINE_ON        14
    #define      LCD_BLINK_CURSOR_ON     15
    #define      LCD_MOVE_CURSOR_LEFT    16
    #define      LCD_MOVE_CURSOR_RIGHT   20
    #define      LCD_TURN_OFF            0
    #define      LCD_TURN_ON             8
    #define      LCD_SHIFT_LEFT          24
    #define      LCD_SHIFT_RIGHT         28


    #define     LCD_OUT_TXT(y,x,text)       Lcd_Out(y,x, (const int8_t*)text)
    #define     LCD_OUT_TXTB(y,x,text)      Lcd_Out(y,x, (int8_t*)text)
    #define     LCD_CLEAR_DATA()            (Lcd_Cmd(LCD_CLEAR),__delay_ms(100))

    void Lcd_Init(void);
    
    void Lcd_Out(uint8_t y, uint8_t x, const int8_t *buffer);
    
    void Lcd_Out2(uint8_t y, uint8_t x, int8_t *buffer);
    
    void Lcd_Chr_CP(int8_t data);
    
    void Lcd_Cmd(uint8_t data);
    
    void appLCD_Init(void);
  
#endif