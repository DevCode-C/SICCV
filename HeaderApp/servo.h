#include "xc.h"
#include "pic18f4550.h"
#include "NewTypes.h"
#include "flex_lcd.h"

#ifndef __PWM__H
#define __PWM__H

    #define D180    45
    #define D90     39
    #define D0      33

    #define N_ELEMENTS  256
    

    void servoInit(void);
    void setServoAngle(uint8_t angle, uint8_t pin);
    void setServo(uint8_t angle, uint8_t pulsos, uint8_t pin);
    
    void appTimerInit(void);
    void appTimerStart(void);
    void appTimerStop(void);
    void appCounterInit(uint16_t reload);
    void appCounterStart(void);
    void appCounterStop(void);
    void appElemts(const int16_t * elements);
#endif