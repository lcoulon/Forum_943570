/*********************************************************************
 *
 *     Interrupts functions
 *
 *********************************************************************
 *
 *
*********************************************************************/
#define __INTERRUPTS_C

#include "hardware.h"
#include <string.h>                             // Needed for strncpy /strlen functions
#include <stdlib.h>                             // Needed for itoa and atoi functions
#include "interrupts.h"
#include "extra.h"

BOOL TRANSMIT_IDENT = FALSE;
BOOL DOOR_OPEN = FALSE;
BOOL SEND_DOOR_REPORT = FALSE;


// 433 Mhz reception - nIRQ interrupt on RB0 for RFM22B module
HF_Rx_IT(void)
{
    if(INTCONbits.INT0IF && INTCONbits.INT0IE)   // INT0 external interrupt occurred ( falling edge on RB0 ) ?
    {

    // do things with RFM22 module here

    INTCONbits.INT0IF = 0;
   }
}



ILS_Input_Detected(void)
{
if(INTCON3bits.INT1IF && INTCON3bits.INT1IE)
    {
        if(ILS == 1)
        {
        __delay_ms(10);                     // Debounce ILS contact : wait for 10ms.

            if (ILS == 1)
            {
            DOOR_OPEN = TRUE;
            SEND_DOOR_REPORT = TRUE;
            INTCON3bits.INT1IF = 0;         // clear INT1 interrupt
            }
        }
    }
}



SET_Button_IDENT(void)
{
if(INTCON3bits.INT2IF && INTCON3bits.INT2IE)
    {
        if(IDENT == 0)
        {
        __delay_ms(10);                     // Debounce push button contact : wait for 10ms.

            if (IDENT == 0)
            {
                TRANSMIT_IDENT = TRUE;      // Bouton SET appuyé
            }
            INTCON3bits.INT2IF = 0;         // clear INT2 interrupt
        }
    }
}