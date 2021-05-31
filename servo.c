#include "HeaderApp/servo.h"

void servoInit(void)
{
//    T0CONbits.T08BIT = 1;
//    T0CONbits.T0CS = 0;
//    T0CONbits.PSA = 0;
//    T0CONbits.T0PS = 0b111;
    T2CONbits.T2CKPS = 0b10;
    T2CONbits.T2OUTPS0 = 1;
    T2CONbits.T2OUTPS1 = 1;
    T2CONbits.T2OUTPS2 = 1;
    T2CONbits.T2OUTPS3 = 1;
}

void setServoAngle(uint8_t angle)
{
    TRISBbits.TRISB1 = 0;
//    TMR0 = angle;
    TMR2 = angle;
    PR2 = 255;
//    INTCONbits.TMR0IF = 0;
    PIR1bits.TMR2IF = 0;
    LATBbits.LATB1 = 1;
    if(angle == D180 || angle == 1)
    {
        __delay_us(2000);
    }
    else if(angle == D0 || angle == 0)
    {
        __delay_us(1000);
    }
//    T0CONbits.TMR0ON =1;
    T2CONbits.TMR2ON = 1;
    while(!PIR1bits.TMR2IF)
    {
        LATBbits.LATB1 = 0;
    }
//    INTCONbits.TMR0IF = 0;
    T2CONbits.TMR2ON = 0;
    PIR1bits.TMR2IF = 0;
//    T0CONbits.TMR0ON =0;
}

void setServo(uint8_t angle, uint8_t pulsos)
{
    for(uint8_t i = 0; i < pulsos; i++)
    {
        setServoAngle(angle);
    }
}

void appTimerInit(void)
{
    /*
     COndifuracion del timer3 para apliacion especifica
    */
    T3CONbits.TMR3ON = 0;
    T3CONbits.RD16 = 1;
    T3CONbits.TMR3CS = 0;
    T3CONbits.T3CKPS = 0b11;
    T3CONbits.T3NSYNC = 1;
      
    /*
     Configuracion del Timer0 para aplicaion de contador
    */
    T0CONbits.TMR0ON = 0;
    T0CONbits.T08BIT = 1;
    T0CONbits.T0CS = 1;
    T0CONbits.T0SE = 0;
    T0CONbits.PSA = 1;
//    T0CONbits.T0PS = 0;
    TRISAbits.TRISA4 = 1;
    
    /*
     COnfiguracion de la interrupcion de periferico para el overflow del TMR0
     * Alta Prioridad
    */
    INTCONbits.TMR0IE = 1;
    INTCONbits.TMR0IF = 0;
    INTCON2bits.TMR0IP = 1;
    
    /*
     Configuracion de la interrupcion de perifericos para el overflow del TMR3
     * Baja Prioridad
    */
    PIR2bits.TMR3IF = 0;
    IPR2bits.TMR3IP = 0;
    PIE2bits.TMR3IE = 1;
}
void appTimerStart(void)
{
    TMR3 = 20536;
    T3CONbits.TMR3ON = 1;
}

void appTimerStop(void)
{
    T3CONbits.TMR3ON = 0;
}

void appCounterInit(uint16_t reload)
{
    TMR0 = reload + 1;
}

void appCounterStart(void)
{
    
    T0CONbits.TMR0ON = 1;
}

void appCounterStop(void)
{
    T0CONbits.TMR0ON = 0;
}

void appElemts(const int16_t * elements)
{
    uint8_t dataout[6] = {0};
    sprintf((char *)dataout,"#:%d",*elements);
    LCD_OUT_TXTB(2,10,dataout);
}
