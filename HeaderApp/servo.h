#include "xc.h"
#include "pic18f4550.h"
#include "NewTypes.h"
#include "flex_lcd.h"

#ifndef __PWM__H
#define __PWM__H

    #define D180    45
    #define D90     38
    #define D0      33
    

    void servoInit(void);
    void setServoAngle(uint8_t angle);
    void setServo(uint8_t angle, uint8_t pulsos);
    
    void appTimerInit(void);
    void appTimerStart(void);
    void appTimerStop(void);
    void appElemts(const uint8_t * elements);
#endif