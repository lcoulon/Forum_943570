/*********************************************************************
 *
 *     Extra Functions
 *
*********************************************************************/

#ifndef __EXTRA_H
#define __EXTRA_H

void ms_counter_TMR0(void);
void seconds_counter_TMR0(void);
void inverser_chaine(char chaine[]);

void Flashes_GREEN_LED_xtimes(unsigned short int flashes);
void Flashes_BLUE_LED_xtimes(unsigned short int flashes);
unsigned char check_reset(void);

#endif  //  __EXTRA_H