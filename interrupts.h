/*
 * interrupts.h
 *
 *  Created on: 15 марта 2015 г.
 *      Author: Tony Darko
 */

#ifndef INTERRUPTS_H_INCLUDED
#define INTERRUPTS_H_INCLUDED

#include <avr/interrupt.h>
#include "seg_led.h"

ISR(SPI_STC_vect)
{
	PORT_LED_COM &= ~((1<<LED_COM3)|(1<<LED_COM2)|(1<<LED_COM1));
	PORT_SPI |= (1<<SPI_SS);
	PORT_LED_COM |= display.com_bits[display.current];
}

ISR(TIMER0_OVF_vect)
{
	//cli();
	//TCNT0 = 4;
	seg_led_tick();
	//sei();
}

#endif /* INTERRUPTS_H_INCLUDED */
