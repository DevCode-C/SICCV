#include "HeaderApp/servo.h"

void servoInit(void)
{
    T0CONbits.T08BIT = 1;
    T0CONbits.T0CS = 0;
    T0CONbits.PSA = 0;
    T0CONbits.T0PS = 0b111;
    TMR0 = 235;
}

void setServoPeriod(void);

void setServoDutyCycle(void);

void iniciarTest(void)
{
    TRISBbits.TRISB1 = 0;
    TMR0 = 20;
    INTCONbits.TMR0IF = 0;
    T0CONbits.TMR0ON =1;
    while(!INTCONbits.TMR0IF)
    {
        LATBbits.LATB1 = 1;
    }
    LATBbits.LATB1 = 0;
    INTCONbits.TMR0IF = 0;
    T0CONbits.TMR0ON =0;
    
    
}

