#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
//#include <util/delay_basic.h>
#include <avr/wdt.h>

#include "hal.h"
#include "seg_led.h"
//#include "uart.h"
#include "interrupts.h"
#include "encoder.h"
#include "adc.h"

static void (*jump_to_boot)(void) = BOOT_ADDR;

/* States: xxxxxxxx
 * r:
 * r:
 * DC: delay counter
 * CC: conversion complete
 * ENC: "encoder changed" flag.
 * AD: AD flag. Set by PWM timer.
 * R: refresh flag. Set by timer, 5ms.
 * T: timer flag. Set by timer, 1ms.
 */
volatile uint8_t state = 0b00000000;

volatile uint8_t counter = 0;
volatile uint8_t set_counter = 0;
#define SET_DELAY 125 // Delay: (5*SET_DELAY)ms

uint16_t temp_set = 50;
uint16_t temp_get = 0;
uint8_t temp_bcd[LED_DIGITS];

int main(void)
{
	// disable Watchdog
	wdt_disable();

	// start init:
	seg_led_init();

	// T/C0 init: CTC mode, 1ms (1kHz)
	OCR0A = 124; // 125-1
	TCCR0A |= (1<<WGM01)|(0<<WGM00); // CTC mode
	TCCR0B |= (0<<CS02)|(1<<CS01)|(1<<CS00); // prescaler: 64
	TIMSK0 |= (1<<OCIE0A); // enable comp. match interrupt

	// T/C1 init
	DDR_PWM |= (1<<PWM_PIN); // change direction to output
	OCR1A = 0; // set PWM value to 0 (off)
	OCR1B = 511; // set comp. value for ch.B (interrupt for start ADC)
	TIMSK1 |= (1<<OCIE1B); // enable comp. match interrupt
	TCCR1A |= (1<<COM1A1)|(0<<COM1A0)|(1<<WGM11)|(0<<WGM10); // OC1A clear on compare match, set OC1A at bottom
	TCCR1B |= (0<<WGM13)|(1<<WGM12) // Fast PWM, 9 bit, 61Hz
			  |(1<<CS12)|(0<<CS11)|(0<<CS10); // ..set prescaller to 256 and start counter!

	// encoder init:
	encoder_init();

	// ADC init:
	adc_init();

	sei();

	adc_start();
	state |= AD_FLAG;

	while(1)
	{
		if(state & T_FLAG)
		{
			ATOMIC_BLOCK(ATOMIC_FORCEON)
			{
				encoder_scan(&temp_set);

				if( state & ENC_FLAG )
				{
					if(temp_set < 100 || temp_set > 0xFFFE)
					{
						temp_set = 100; // min temperature
					}
					else if(temp_set > 400)
					{
						temp_set = 400; // max temperature
					}

					set_counter = SET_DELAY;

					state |= DC_FLAG;
					state &= ~ENC_FLAG;
				}
			}

			state ^= T_FLAG; // clear flag
		}

		if( state & R_FLAG )
		{
			if( state & DC_FLAG )
			{
				if (--set_counter == 0)
				{
					ATOMIC_BLOCK(ATOMIC_FORCEON)
					{
						bin2bcd(temp_get, temp_bcd);
					}

					state &= ~DC_FLAG;
				}
				else
				{
					ATOMIC_BLOCK(ATOMIC_FORCEON)
					{
						bin2bcd(temp_set, temp_bcd);
					}
				}

				display.symbols[0] = led_symbols[temp_bcd[0]];
				display.symbols[1] = led_symbols[temp_bcd[1]];
				display.symbols[2] = led_symbols[temp_bcd[2]];
			}

			seg_led_tick();

			state &= ~R_FLAG; // clear flag
		}

		if( state & AD_FLAG )
		{
			if( (adc == 255) && !(state & DC_FLAG) )
			{
				display.symbols[0] = led_symbols[10];
				display.symbols[1] = led_symbols[11];
				display.symbols[2] = led_symbols[11];
			}
			else
			{
				ATOMIC_BLOCK(ATOMIC_FORCEON)
				{
					if(adc>50)
					{
						adc -= 34;
						temp_get = ((uint16_t)(adc)*4) + 100 - adc - (adc/2)
								- ( (adc > (180-34)) ? 20 : (adc > (150-34)) ? 10 : (adc > (135-34)) ? 5 : 0 );
					}
					else
					{
						temp_get = (adc * 3) - 5;
					}

					temp_get += 30; // cold solder compensation
				}

				if( !(state & DC_FLAG) )
				{
					state |= DC_FLAG;
					set_counter = 1;
				}
			}

			// start AD conversion
			adc_start();

			state &= ~AD_FLAG;
		}

		asm volatile("nop"::);
	}
}
