/*********************************************************************
 *
 *      Interrupts functions
 *
*********************************************************************/
#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include "hardware.h"

HF_Rx_IT(void);
ILS_Input_Detected(void);
SET_Button_IDENT(void);

#endif  //  __INTERRUPTS_H