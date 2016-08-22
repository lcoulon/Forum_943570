/*********************************************************************
 *
 *     UART access routines for C18
 *
 *********************************************************************
 * FileName:        UART.c
 * Dependencies:    Hardware UART module
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F
 * Compiler:        Microchip C18 v3.30 or higher
********************************************************************/
#define __UART_C

#include <stdint.h>
#include "hardware.h"
#include "UART.h"

#if defined(USE_UART)

BYTE ReadStringUART(BYTE *Dest, BYTE BufferLen)
{
    BYTE c;
    BYTE count = 0;

    while(BufferLen--)
    {
        *Dest = '\0';

        while(!DataRdyUART());
        c = ReadUART();

        if(c == '\r' || c == '\n')
            break;

        count++;
        *Dest++ = c;
    }

    return count;
}


    char BusyUSART(void)
    {
        return !TXSTAbits.TRMT;
    }
    
    void CloseUSART(void)
    {
      RCSTA &= 0x4F;  // Disable the receiver
      TXSTAbits.TXEN = 0;   // and transmitter
    
      PIE1 &= 0xCF;   // Disable both interrupts
    }
    
    char DataRdyUSART(void)
    {
        if(RCSTAbits.OERR)
        {
            RCSTAbits.CREN = 0;
            RCSTAbits.CREN = 1;
        }
      return PIR1bits.RCIF;
    }
    
    char ReadUSART(void)
    {
      return RCREG;                     // Return the received data
    }
    
    void WriteUSART(char data)
    {
      TXREG = data;      // Write the data byte to the USART
    }
    
    void getsUSART(char *buffer, unsigned char len)
    {
      char i;    // Length counter
      unsigned char data;
    
      for(i=0;i<len;i++)  // Only retrieve len characters
      {
        while(!DataRdyUSART());// Wait for data to be received
    
        data = getcUART();    // Get a character from the USART
                               // and save in the string
        *buffer = data;
        buffer++;              // Increment the string pointer
      }
    }
    
    void putsUSART( char *data)
    {
      do
      {  // Transmit a byte
        while(BusyUSART());
        putcUART(*data);
      } while( *data++ );
    }


        #if defined(__18CXX)
    void putrsUSART(const rom char *data)       // for C18 compiler
        #endif

        #if defined(__XC8)
        void putrsUSART(const char *data)           // for XC8 compiler
        #endif

    {
      do
      {  // Transmit a byte
        while(BusyUSART());
        putcUART(*data);
      } while( *data++ );
    }

#endif  //USE_UART
