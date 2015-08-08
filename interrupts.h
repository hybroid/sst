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


extern volatile unsigned char state;

extern volatile unsigned char counter;

ISR(TIMER0_COMPA_vect)
{
	state |= T_FLAG; // set T flag

	counter++;

	if(counter == 5)
	{
		counter = 0; // clear counter
		state |= R_FLAG; // set R flag
	}
}

#endif /* INTERRUPTS_H_INCLUDED */
