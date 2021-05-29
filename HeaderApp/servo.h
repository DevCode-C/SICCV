#include "main.h"

#ifndef __PWM__H
#define __PWM__H

    #define D180    45
    #define D0      33
    void servoInit(void);
    void setServoAngle(uint8_t angle);
    void setServo(uint8_t angle, uint8_t pulsos);
    
    void appTimerInit(void);
    void appTimerStart(void);
#endif