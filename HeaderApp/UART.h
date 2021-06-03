#include "NewTypes.h"
#include "xc.h"
#include <pic18f4550.h>

#ifndef __UART__H
#define __UART__H
    void uart_Init(uint32_t baud);
    void readUART(void);
    void sendData(StateMachine *data);
#endif