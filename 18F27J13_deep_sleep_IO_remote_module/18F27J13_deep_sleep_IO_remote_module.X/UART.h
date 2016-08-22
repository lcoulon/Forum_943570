/*********************************************************************
 *
 *     UART access routines for C18
 *
 *********************************************************************
 * FileName:        UART.h
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 * Compiler:        Microchip C18 v3.30 or higher
 *                  HI-TECH PICC-18 PRO 9.63PL2 or higher
 * Company:         Microchip Technology, Inc.
********************************************************************/
#ifndef __UART_H
#define __UART_H


#if defined (USE_UART)
#include "hardware.h"

// UART mapping functions for consistent API names across 8-bit and 16 or
// 32 bit compilers.  For simplicity, everything will use "UART" instead
// of USART/EUSART/etc.


        #define BusyUART()      BusyUSART()
        #define CloseUART()     CloseUSART()
        #define ConfigIntUART(a)    ConfigIntUSART(a)
        #define DataRdyUART()       DataRdyUSART()
        #define OpenUART(a,b,c)     OpenUSART(a,b,c)
        #define ReadUART()      ReadUSART()
        #define WriteUART(a)        WriteUSART(a)
        #define getsUART(a,b,c)     getsUSART(b,a)
        #define putsUART(a)     putsUSART(a)
        #define getcUART()      ReadUSART()
        #define putcUART(a)     WriteUSART(a)

        #if defined(__18CXX)
        #define putrsUART(a)        putrsUSART((far rom char*)a)    // for C18 compiler
        #endif

        #if defined(__XC8)
        #define putrsUART(a)        putrsUSART((const char*)a)      // for XC8 compiler
        #endif

    char BusyUSART(void);
    void CloseUSART(void);
    char DataRdyUSART(void);
    char ReadUSART(void);
    void WriteUSART(char data);
    void getsUSART(char *buffer, unsigned char len);
    void putsUSART(char *data);
        #if defined(__18CXX)
    void putrsUSART(const rom char *data);                          // for C18 compiler
        #endif

        #if defined(__XC8)
        void putrsUSART(const char *data);                              // for XC8 compiler
        #endif


#endif  // (USE_UART)
#endif  //  __UART_H