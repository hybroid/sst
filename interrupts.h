/*
 * interrupts.h
 *
 *  Created on: 15 марта 2015 г.
 *      Author: Tony Darko
 */

#ifndef INTERRUPTS_H_INCLUDED
#define INTERRUPTS_H_INCLUDED

#include <avr/interrupt.h>

#include "hal.h"
#include "seg_led.h"


extern volatile uint8_t state;

extern volatile uint8_t counter;
extern volatile uint8_t counter2;

ISR(TIMER0_COMPA_vect)
{
	state |= T_FLAG; // set T flag

	if(++counter == 5)
	{
		counter = 0; // clear counter
		state |= R_FLAG; // set R flag
	}

}

ISR(TIMER1_COMPB_vect)
{
	state |= AD_FLAG;
}

#endif /* INTERRUPTS_H_INCLUDED */
