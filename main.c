#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <util/delay.h>

#include "hal.h"
#include "seg_led.h"
//#include "uart.h"
#include "interrupts.h"
#include "encoder.h"

/* States: xxxxxxxx
 * r:
 * r:
 * r:
 * r:
 * r:
 * S: two refresh flag. Set by timer.
 * R: refresh flag. Set by timer.
 * T: timer flag. Set by timer.
 */
volatile unsigned char state;

volatile unsigned char counter;

uint16_t temp;
uint8_t temp_bcd[LED_DIGITS];


int main(void)
{
	// start init:
	seg_led_init();

	// T/C0 init: CTC mode, 1ms
	OCR0A = 124; // 125-1
	TCCR0A |= (1<<WGM01)|(0<<WGM00); // CTC mode
	TCCR0B |= (0<<CS02)|(1<<CS01)|(1<<CS00); // prescaler: 64
	TIMSK0 |= (1<<OCIE0A); // enable comp. match interrupt

	// T/C1 init: fast PWM, 7.63Hz, clr OC1A on comp. match, set OC1A on BOTTOM
	//DDR_PWM |= (1<<PWM_PIN);
	OCR1A = 0;
	TCCR1A |= (1<<COM1A1)|(0<<COM1A0)|(1<<WGM11)|(1<<WGM10);
	TCCR1B |= (0<<WGM13)|(1<<WGM12)|(1<<CS12)|(0<<CS11)|(1<<CS10);

	// encoder init:
	encoder_init();

	sei();

	while(1)
	{
		if(state & T_FLAG)
		{
			ATOMIC_BLOCK(ATOMIC_FORCEON)
			{
				encoder_scan(&temp);

				if(temp > 0xfffe)
				{
						temp = 0; // min temperature
				}

				if(temp > 500)
				{
						temp = 500; // max temperature
				}
			}

			state ^= T_FLAG; // clear flag
		}

		if( state & R_FLAG )
		{
			ATOMIC_BLOCK(ATOMIC_FORCEON)
			{
				// TODO: this is temporary test
				bin2bcd(temp, temp_bcd);

				display.symbols[0] = led_symbols[temp_bcd[0]];
				display.symbols[1] = led_symbols[temp_bcd[1]];
				display.symbols[2] = led_symbols[temp_bcd[2]];

				seg_led_tick();
			}

			state &= ~R_FLAG; // clear flag
		}

		if( state & S_FLAG )
		{
			//
			state ^= S_FLAG;
		}

		asm volatile("nop"::);
	}
}
