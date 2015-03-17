#include <avr/io.h>

#include "seg_led.h"

volatile seg_led_t display;

const unsigned char led_symbol[] =
{
    /* 0 - SEG_B
     * 1 - SEG_F
     * 2 - SEG_A
     * 3 - SEG_E
     * 4 - SEG_D
     * 5 - SEG_dp
     * 6 - SEG_C
     * 7 - SEG_G
     */

	/*         +---+ <- A
     *    F-> /   / <- B
     *   G-> +---+
     * E -> /   / <- C
     *     +---+ <- D    (.) <- dp
     */
	/* GC.DEAFB */
     0b01011111, // 0
     0b01000001, // 1
     0b10011101, // 2
     0b11010101, // 3
     0b11000011, // 4
     0b11010110, // 5
     0b11011110, // 6
     0b01000101, // 7
     0b11011111, // 8
     0b11010111, // 9
     0b10011110, // E (#10)
     0b10001000, // r (#11)
     0b10001110, // f (#12)
     0b10000000, // - (#13)
     0b00100000, // . (#14)
};

/*
char * utoa_fast_div(uint16_t value, char *buffer)
{
    buffer += 11;
    *--buffer = 0;
    do
    {
        divmod10_t res = divmodu10(value);
        *--buffer = res.rem += '0';
        value = res.quot;
    }
    while (value != 0);
    return buffer;
}
*/
