/*
 * File:   UART.c
 * Author: Emmanuel
 *
 * Created on June 2, 2021, 2:53 AM
 */


#include "HeaderApp/UART.h"

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