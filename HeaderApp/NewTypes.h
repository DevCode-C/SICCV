#ifndef __NEWTYPES__H
#define __NEWTYPES__H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ 12000000
#define CAPACITY    510
#define IDLE                0
#define IDLE_CONFIRMATION   8

typedef void(*prtFuncNext)(void);

typedef struct _state
{
    uint8_t counter;
    int16_t elements;
    uint8_t state;
    uint16_t bat;
    uint8_t character;
    uint8_t display[16];
    prtFuncNext nextFunc;
}StateMachine;

#endif