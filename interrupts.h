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

#if defined(USE_SPI)
ISR(SPI_STC_vect)
{
	PORT_LED_COM &= ~((1<<LED_COM3)|(1<<LED_COM2)|(1<<LED_COM1));
	PORT_SPI |= (1<<SPI_SS);
	PORT_LED_COM |= display.com_bits[display.current];
}
#endif

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
