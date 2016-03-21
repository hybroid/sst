/*
 * encoder.c
 *
 *  Created on: 19 марта 2015 г.
 *      Author: Tony Darko
 */

#include <avr/io.h>

#include "hal.h"
#include "encoder.h"

volatile uint8_t encoder_state;

extern volatile uint8_t state;

void encoder_scan(uint16_t *value)
{
	uint8_t new_state = ENCODER_STATE;

	switch(encoder_state)
	{
		case ENCODER_STATE_2:
		{
			if(new_state == ENCODER_STATE_3) (*value)--;
			if(new_state == ENCODER_STATE_0) (*value)++;
			break;
		}
		case ENCODER_STATE_0:
		{
			if(new_state == ENCODER_STATE_2) (*value)--;
			if(new_state == ENCODER_STATE_1) (*value)++;
			break;
		}
		case ENCODER_STATE_1:
		{
			if(new_state == ENCODER_STATE_0) (*value)--;
			if(new_state == ENCODER_STATE_3) (*value)++;
			break;
		}
		case ENCODER_STATE_3:
		{
			if(new_state == ENCODER_STATE_1) (*value)--;
			if(new_state == ENCODER_STATE_2) (*value)++;
			break;
		}
	}

	if(encoder_state != new_state)
	{
		state |= ENC_FLAG;
		encoder_state = new_state;
	}
}
