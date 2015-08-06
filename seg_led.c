#include <avr/io.h>

#include "hal.h"
#include "seg_led.h"

volatile seg_led_t display;

const uint8_t led_symbols[] =
{
    /* 0 - D  -PB0
     * 1 - G  -PB2
     * 2 - A  -PD2
     * 3 - F  -PD3
     * 4 - B  -PD4
     * 5 - C  -PD5
     * 6 - dp -PD6
     * 7 - E  -PD7
     */

	/*         +---+ <- A
     *    F-> /   / <- B
     *   G-> +---+
     * E -> /   / <- C
     *     +---+ <- D    (.) <- dp
     */
	/* E.CBFAGD */
     0b10111101, // 0
     0b00110000, // 1
     0b10010111, // 2
     0b00110111, // 3
     0b00111010, // 4
     0b00101111, // 5
     0b10101111, // 6
     0b00110100, // 7
     0b10111111, // 8
     0b00111111, // 9
     0b10001111, // E (#10)
     0b10000010, // r (#11)
     0b10001110, // f (#12)
     0b00000010, // - (#13)
     0b01000000, // . (#14)
};


void bin2bcd(uint16_t value, uint8_t *buffer)
{
	unsigned char *ptr = buffer;
    buffer += LED_DIGITS;

    do
    {
    	if(value == 0)
    	{
    		*--buffer = 0;
    	}
    	else
    	{
			divmod10_t res = divmodu10(value);
			*--buffer = res.rem;
			value = res.quot;
    	}
    } while( buffer != ptr );

}
