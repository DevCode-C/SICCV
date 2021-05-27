#include "HeaderApp/servo.h"

void servoInit(void)
{
    T0CONbits.T08BIT = 1;
    T0CONbits.T0CS = 0;
    T0CONbits.PSA = 0;
    T0CONbits.T0PS = 0b111;
}

void setServoAngle(uint8_t angle)
{
    TRISBbits.TRISB1 = 0;
    TMR0 = angle;
    INTCONbits.TMR0IF = 0;
    LATBbits.LATB1 = 1;
    if(angle == D180 || angle == 1)
    {
        __delay_us(2000);
    }
    else if(angle == D0 || angle == 0)
    {
        __delay_us(1000);
    }
    T0CONbits.TMR0ON =1;
    while(!INTCONbits.TMR0IF)
    {
        LATBbits.LATB1 = 0;
    }
    INTCONbits.TMR0IF = 0;
    T0CONbits.TMR0ON =0;
}

void setServo(uint8_t angle)
{
    for(uint8_t i = 0; i < 10; i++)
    {
        setServoAngle(angle);
    }
}


