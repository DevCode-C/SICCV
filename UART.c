/*
 * File:   UART.c
 * Author: Emmanuel
 *
 * Created on June 2, 2021, 2:53 AM
 */


#include <string.h>

#include "HeaderApp/UART.h"
#include "HeaderApp/flex_lcd.h"
#include "HeaderApp/app.h"
extern uint8_t puerto[8];
extern StateMachine datos;
//extern void appStateInitial(void);

void uart_Init(uint32_t baud)
{
    TRISCbits.RC6 = 0;
    TRISCbits.RC7 = 1;
    
    BAUDCONbits.BRG16 = 0;
    SPBRG = (uint8_t)(((_XTAL_FREQ/baud)/64)-1);
    
    TXSTAbits.BRGH = 0;
    TXSTAbits.SYNC = 0;
    TXSTAbits.TX9 = 0;
    TXSTAbits.TXEN = 1;
    
    RCSTAbits.SPEN = 1;
    RCSTAbits.RC9 = 0;
    RCSTAbits.CREN = 1;
    
    PIE1bits.RCIE = 1;
    IPR1bits.RCIP =1;
}

void readUART(void)
{
    LCD_CLEAR_DATA();
    LCD_OUT_TXTB(1,0,puerto);
    if(!memcmp(puerto,"Informacion@",12))
    {
        memset(puerto,0,sizeof(puerto));
        PIE1bits.RCIE = 1;
        datos.state = 10;
        datos.nextFunc = sendinformation;
        LCD_CLEAR_DATA();
    }
    else if (!memcmp(puerto,"Activado@",9))
    {
        LCD_CLEAR_DATA();
        memset(puerto,0,sizeof(puerto));
        datos.state = IDLE;
        datos.nextFunc = appStateRecolectData;
    }
//    memset(puerto,0,sizeof(puerto));
}

void sendData(StateMachine *data)
{
    for(uint8_t i = 0; i < strlen((const char *)data->display);)
        {
            if(TXSTAbits.TRMT == 1)
            {
                TXREG = data->display[i];
                i++;
            }
        }
}