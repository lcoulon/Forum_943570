/* 
 * File:   hardware.h
 * 
 * 
 *                                 PIC18F27J13 
 *                   +-----------------:_:-----------------+
 *      ISCP_VPP --> :  1 MCLRn            PGD/RP10/RB7 28 : <*> ISCP_PGD
 *        TX-ANT - > :  2 RA0/RP0          PGC/ RP9/RB6 27 : <*> ISCP_PGC
 *        RX-ANT - > :  3 RA1/RP1               RP8/RB5 26 : <*- ILS
 *  RFM_SHUTDOWN < - :  4 RA2/AN2               RP7/RB4 25 : <*- INPUT_1
 *   RFM_SPI_CSn < - :  5 RA3/AN3               RP6/RB3 24 : - > LED_GREEN_MODE
 *          10uF --> :  6 VCAP            REFO/ RP5/RB2 23 : - > BUZZER
 *           SET - > :  7 RA5/RP2               RP4/RB1 22 : < - INPUT_2
 *           GND --> :  8 VSS             INT0/ RP3/RB0 21 : < - RFM_IRQn
 *       LED_RED < - :  9 RA7/OSC1                  VDD 20 : <-- PWR
 *  LED_BLUE_SYS < - : 10 RA6/OSC2                  VSS 19 : <-- GND
 *        SLEEPn < - : 11 RC0/RP11/T1OSO  RXD1/RP18/RC7 18 : <*- RXD
 *         RELAY < - : 12 RC1/RP12/T1OSI  TXD1/RP17/RC6 17 : -*> TXD
 *       LOW_BAT - > : 13 RC2/RP13             RP16/RC5 16 : -*> RFM_SPI_MISO
 *   RFM_SPI_CLK <*- : 14 RC3/RP14             RP15/RC4 15 : <*- RFM_SPI_MISO
 *                   +-------------------------------------+
 *                                   DIP-28
 * 
 *               -->      Fix direction, always input        <--
 *               - >         Program slected, input          < -
 *               < -        Program slected,  output         - >
 *               < >             Bi-directional              < >
 *               -*>   Program slected, input, 5V tolerant   <*-
 *               <*-  Program slected, output, 5V tolerant   -*>
 *               <*>       Bi-directional, 5V tolerant       <*>
 */

#ifndef HARDWARE_H
#define	HARDWARE_H

#include <stdlib.h>             // Needed for itoa and atoi functions
#include <xc.h>                 // Header file needed if project is compiled with XC8 compiler

#define _XTAL_FREQ 16000000      // 16 Mhz


/*
 Example of EDGE_TIMOUT calculation :
                // Fosc / 4 = 40Mhz / 4 = 10Mhz  -> Tosc (cycle duration) = 1/10 Mhz = 0.0001ms => 100ns
                // Timer 3 has prescaler 1:8 and regular clock cycle is 100ns, so 100ns * 8 = 800 ns -> 0.0008ms    
                // Time = nb cycle x prescaler x Tosc
                // Time = 16 800 x 8 x 0.0001ms = 13.333 ms
                // If we have a pulse shorter than ~13ms44 (16800*8*Tosc)
 */

// ENABLE or DISABLE program features here
#define USE_RFM
#define USE_UART

//****************************************************************************
#if defined (USE_UART)
//#include "UART.h"                 // use local uart.c & uart.h
#include <usart.h>                  // plib Library file
// Variables
#define UART_buffer_SIZE	80      // nombre de caractères maxi que peut stocker le buffer UART
#endif
//****************************************************************************


/****** PORT DEFINITIONS ******/
#define LED                     LATAbits.LATA6		// * RED LED
#define LED_TRIS                TRISAbits.TRISA6

#define SYSTEM_BLUE_LED         LATAbits.LATA7 		// * SYSTEM LED
#define SYSTEM_BLUE_LED_TRIS    TRISAbits.TRISA7 

#define MODE_LED                LATBbits.LATB3 		// * MODE LED
#define MODE_LED_TRIS           TRISBbits.TRISB3 

#define SLEEP_DC                LATCbits.LATC0 		// * SLEEP DC
#define SLEEP_DC_TRIS           TRISCbits.TRISC0

#define RELAY                   LATCbits.LATC1      // * RELAY
#define RELAY_TRIS              TRISCbits.TRISC1   

#define BUZZER                  LATBbits.LATB2 		// * BUZZER
#define BUZZER_TRIS             TRISBbits.TRISB2 

// SET Push button
#define IDENT                   (PORTAbits.RA5)
#define IDENT_TRIS              (TRISAbits.TRISA5)

// INPUTS
#define ILS                    (PORTBbits.RB5)
#define ILS_TRIS               (TRISBbits.TRISB5)

#define INPUT_1                (PORTBbits.RB4)
#define INPUT_1_TRIS           (TRISBbits.TRISB4)

#define INPUT_2                (PORTBbits.RB1)
#define INPUT_2_TRIS           (TRISBbits.TRISB1)

#define LOW_BAT                (PORTCbits.RC2)
#define LOW_BAT_TRIS           (TRISCbits.TRISC2)


//****************************************************************************
// RFM2xBx
#define RFM_CS                  (LATAbits.LATA3)        // CS
#define RFM_CS_TRIS             (TRISAbits.TRISA3)

#define RFM_SCK_TRIS            (TRISCbits.TRISC3)
#define RFM_SDI_TRIS            (TRISCbits.TRISC4)
#define RFM_SDO_TRIS            (TRISCbits.TRISC5)

#define RFM_SPIEN               (SSPCON1bits.SSPEN)
#define RFM_SPI_IF              (PIR1bits.SSPIF)
#define RFM_SSPBUF              (SSPBUF)
#define RFM_SPICON1             (SSPCON1)
#define RFM_SPICON1bits         (SSPCON1bits)
#define RFM_SPISTAT             (SSPSTAT)
#define RFM_SPISTATbits         (SSPSTATbits)

#define RFM_nIRQ                (PORTBbits.RB0)
#define RFM_nIRQ_TRIS           (TRISBbits.TRISB0)

#define RFM_SHUTDOWN            (LATAbits.LATA2)
#define RFM_SHUTDOWN_TRIS       (TRISAbits.TRISA2)


#define RFM_RX_ANT              (LATAbits.LATA1)      
#define RFM_RX_ANT_TRIS         (TRISAbits.TRISA1)
                                          
#define RFM_TX_ANT              (LATAbits.LATA0)
#define RFM_TX_ANT_TRIS         (TRISAbits.TRISA0)

//****************************************************************************



#endif	// HARDWARE_H

