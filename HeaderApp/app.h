#include "main.h"

#ifndef __APP__H
#define __APP__H

    void appInit(void);
    
    void appISRConfig(void);
    
    void appStateRecolectData(void);
    
    void appGetElements(void);
    
    void appSubGetData(StateMachine *data_Inout);
    
    void appSubGiveElemts(StateMachine *data);
    
    void warning(void);
    
    void appStateInitial(void);

#endif