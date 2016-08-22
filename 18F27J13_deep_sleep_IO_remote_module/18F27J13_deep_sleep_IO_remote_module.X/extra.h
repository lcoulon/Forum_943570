/*********************************************************************
 *
 *     Extra Functions
 *
*********************************************************************/

#ifndef __EXTRA_H
#define __EXTRA_H

/*
 * Enumerate reasons we wake up
 */
typedef enum { ePOR, eWDTO, eDSPOR, eDSWDTO, eDSWINT0 } eWakeReason;

void ms_counter_TMR0(void);
void seconds_counter_TMR0(void);
void inverser_chaine(char chaine[]);

void Flashes_GREEN_LED_xtimes(unsigned short int flashes);
void Flashes_BLUE_LED_xtimes(unsigned short int flashes);
eWakeReason check_reset(void);

#endif  //  __EXTRA_H