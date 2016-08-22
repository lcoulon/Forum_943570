/*********************************************************************
 *
 *     Extra Functions
 *
 *********************************************************************
 *      Delays functions from Timer 0
 *      LED flashes
*********************************************************************/
#define __EXTRA_C

#include "hardware.h"
#include "extra.h"
#include <string.h>            // Needed for strncpy /strlen functions


unsigned DWORD seconds_TMR0 = 0;        // Temps en secondes depuis mise en route de la carte
unsigned long tick_ms_timer0 = 0;       // Ticks chaque ms
unsigned int sec_timer0 = 0;
unsigned int min_timer0 = 0;
unsigned int hour_timer0 = 0;
unsigned int day_timer0 = 0;
extern unsigned char TempC_ascii[6];


// 1ms delay with TMR0
void ms_counter_TMR0(void)
{
while (!INTCONbits.TMR0IF);     // TMR0 interrupt is generated when the TMR0 register overflows from FFFFh to 0000h in 16-bit mode
T0CONbits.TMR0ON = 1;           // Timer0 On/Off Control bit:1=Enables Timer0 / 0=Stops Timer0
T0CONbits.T08BIT = 0;           // Timer0 8-bit/16-bit Control bit: 1=8-bit timer/counter / 0=16-bit timer/counter
T0CONbits.T0CS   = 0;           // TMR0 Clock Source Select bit: 0=Internal Clock (CLKO) / 1=Transition on T0CKI pin
T0CONbits.T0SE   = 0;           // TMR0 Source Edge Select bit: 0=low/high / 1=high/low
T0CONbits.PSA    = 1;           // Prescaler Assignment bit: 0=Prescaler is assigned; 1=NOT assigned/bypassed

T0CONbits.T0PS2  = 0;           // bits 2-0  PS2:PS0: Prescaler Select bits
T0CONbits.T0PS1  = 0;
T0CONbits.T0PS0  = 0;

// Clock is Fosc/4 = 16 Mhz
// Generate 1 ms delay with Timer 0 - Need 2000 clock cycles to get 1ms delay -> Timer 0 preload : 57536
// Timer0 preload (valeur de prechargement) : 55536.   55536-63536 = 9999 x 1 cycle (100ns) = 1ms

//16 Mhz
TMR0H = 0xF0;    // preset for Timer0 MSB register
TMR0L = 0x60;    // preset for Timer0 LSB register

INTCONbits.TMR0IF = 0;

tick_ms_timer0 ++;
if (tick_ms_timer0 == 4294967294ul)  tick_ms_timer0 = 0ul;
}


void seconds_counter_TMR0(void)
{

    if (INTCONbits.TMR0IF)
    {
    T0CONbits.TMR0ON = 1;
    T0CONbits.T08BIT = 0;
    T0CONbits.T0CS   = 0;
    T0CONbits.PSA    = 0;

    T0CONbits.T0PS2  = 1;       // bits 2-0  PS2:PS0: Prescaler Select bits
    T0CONbits.T0PS1  = 0;
    T0CONbits.T0PS0  = 1;

    TMR0H = 0x0B;    // preset for Timer0 MSB register
    TMR0L = 0xDC;    // preset for Timer0 LSB register

    INTCONbits.TMR0IF = 0;      // repositionne le flag a 0 pour un nouveau comptage

    seconds_TMR0 ++;             // Comptage des impulsions (tte les secondes) depuis la mise en route du timer
    if(seconds_TMR0 == 4294967294u) seconds_TMR0 = 0ul;
    }
}


// Set x quick flashes
void Flashes_GREEN_LED_xtimes(unsigned short int flashes)
{
unsigned short int flash_counter = 0;
unsigned short int i = 0;

MODE_LED = 0;

    while (flash_counter < flashes)
    {
    MODE_LED ^= 1;                  // Toggle LED state
    for (i=0;i<5;i++) __delay_ms(10);     // 50 ms delay
    MODE_LED ^= 1;                  // Toggle LED state
    for (i=0;i<5;i++) __delay_ms(10);     // 50 ms delay

    flash_counter++;
    }
}


void Flashes_BLUE_LED_xtimes(unsigned short int flashes)
{
MODE_LED = 0; // Initial state of the LED.

    while(flashes--)
    {
    SYSTEM_BLUE_LED ^= 1;                          // Toggle LED state
    for (int i=0;i<5;i++) __delay_ms(10);   // 50 ms delay
    SYSTEM_BLUE_LED ^= 1;                          // Toggle LED state
    for (int i=0;i<5;i++) __delay_ms(10);   // 50 ms delay
    }
}



eWakeReason check_reset(void)
{
    register eWakeReason Result;

    /*
     * Look at flags to see what kind of start up this is
     */
    if(WDTCONbits.DS) /* Deep sleep wake up */
    {
        if(DSWAKEHbits.DSINT0)
        {
            Result = eDSWINT0;      /* INT0 wake from deep sleep */
        }
        else if(DSWAKELbits.DSWDT)
        {
            Result = eDSWDTO;       /* Timeout wake from deep sleep */
        }
        else if(DSWAKELbits.DSPOR)
        {
            Result = eDSPOR;        /* MCLR wake from deep sleep */
            RCON |= 0b00111111;
            LATB   = 0;
        }
    }
    else              /* Other class of wake up */
    {
        if(RCONbits.NOT_PD == 0) /* Power on reset */
        {
            Result = ePOR;          /* Power On reset */
            RCON |= 0b00111111;
            LATB   = 0;
        }
        else if(RCONbits.NOT_TO)
        {
            Result = eWDTO;         /* Watch Dog Timeout reset */
            RCONbits.NOT_TO = 1;
        }
    }

    return Result;
}