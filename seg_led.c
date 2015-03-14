#include <avr/io.h>

#include "seg_led.h"

char led_display[3];

char led_symbol[] =
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
     0b11111010, // 0
     0b10000010, // 1
     0b10111001, // 2
     0b10101011, // 3
     0b11000011, // 4
     0b01101011, // 5
     0b01111011, // 6
     0b10100010, // 7
     0b11111011, // 8
     0b11101011, // 9
     0b01111001, // E (#10)
     0b00010001, // r (#11)
     0b01110001, // f (#12)
     0b00000001, // - (#13)
     0b00000100, // . (#14)
};

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
