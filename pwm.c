#include "HeaderApp/pwm.h"

void pwmInit(void)
{
    TRISCbits.TRISC1 = 0;
    CCP1CONbits.CCP1M = 0xC;
}

void setPwmPeriod(void);

void setPwmDutyCycle(void);

void delay_mS(uint32_t time_mS)
{
    delay_uS(time_mS*990);
}

void delay_uS(uint32_t time_uS)
{
    for (uint16_t i = 0;  i< time_uS*3; i++) {
        asm("NOP");
    }

}