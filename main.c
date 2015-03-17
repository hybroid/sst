#include <avr/io.h>
#include <avr/interrupt.h>
//#include <util/delay.h>

#include "hal.h"
#include "seg_led.h"
#include "spi.h"
//#include "uart.h"
#include "interrupts.h"

int main(void)
{
	// start init:
	seg_led_init();

	// T/C0 init
	//TCCR0A
	TCCR0B |= (0<<CS02)|(1<<CS01)|(1<<CS00); // prescaler: 64
	TIMSK0 |= (1<<TOIE0); // enable overflow interrupt

	spi_init_master_ie();
    //uart_init();
	// <- end of init

    //display.digits[0] = led_symbol[0];
    //display.digits[1] = led_symbol[2];
    //display.digits[2] = led_symbol[5];

    sei();

    while(1)
    {
        asm volatile("nop"::);
    }
}
