#include "main.h"

#ifndef __PWM__H
#define __PWM__H

    void pwmInit(void);
    void setPwmPeriod(void);
    void setPwmDutyCycle(void);
    void delay_mS(uint32_t time_mS);
    void delay_uS(uint32_t time_uS);
#endif