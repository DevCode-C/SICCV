#ifndef __MAIN__H
#define __MAIN__H
#include "pic18f4550.h"
#include "xc.h"
#include <stdlib.h>
#include <stdio.h>
#include "Config.h"
#include "adc.h"
#include "flex_lcd.h"
#include "teclado.h"
#include "servo.h"
#define _XTAL_FREQ 12000000

typedef void(*prtFuncNext)(void);

typedef struct _state
{
    uint8_t counter;
    uint8_t state;
    prtFuncNext nextFunc;
}StateMachine;


#endif