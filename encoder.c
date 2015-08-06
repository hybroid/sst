/*
 * encoder.c
 *
 *  Created on: 19 марта 2015 г.
 *      Author: Tony Darko
 */

#include "hal.h"
#include "encoder.h"

volatile unsigned char encoder_state;

void encoder_scan(unsigned int *value)
{
	unsigned char new_state = ENCODER_STATE;

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

	encoder_state = new_state;
}
