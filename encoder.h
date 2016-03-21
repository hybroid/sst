/*
 * encoder.h
 *
 *  Created on: 19 марта 2015 г.
 *      Author: Tony Darko
 */

#ifndef ENCODER_H_INCLUDED
#define ENCODER_H_INCLUDED

#include "hal.h"

extern volatile uint8_t encoder_state;

static inline void encoder_init(void)
{
	PORT_ENCODER |= (1<<ENCODER_A)|(1<<ENCODER_B);
	encoder_state = ENCODER_STATE;
}

extern void encoder_scan(uint16_t *value);

#endif /* ENCODER_H_INCLUDED */
