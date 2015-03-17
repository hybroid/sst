#ifndef SEG_LED_H_INCLUDED
#define SEG_LED_H_INCLUDED

#include <avr/io.h>
#include "spi.h"
#include "hal.h"

typedef struct divmod10_t
{
    uint16_t quot;
    uint8_t rem;
} divmod10_t;

typedef struct seg_led_t
{
	unsigned char digits[3];
	unsigned char current;
	unsigned char previous;
	unsigned char com_bits[3];
} seg_led_t;

extern const unsigned char led_symbol[];

extern volatile seg_led_t display;

/*
inline static divmod10_t divmodu10(uint16_t n)
{
    divmod10_t res;
    // умножаем на 0.8
    res.quot = n >> 1;
    res.quot += res.quot >> 1;
    res.quot += res.quot >> 4;
    res.quot += res.quot >> 8;
    //res.quot += res.quot >> 16;
    uint16_t qq = res.quot;
    // делим на 8
    res.quot >>= 3;
    // вычисляем остаток
    res.rem = (uint8_t)(n - ((res.quot << 1) + (qq & ~7ul)));
    // корректируем остаток и частное
    if(res.rem > 9)
    {
        res.rem -= 10;
        res.quot ++;
    }
    return res;
}

char * utoa_fast_div(uint16_t value, char *buffer);
*/

inline static void seg_led_tick(void)
{
	display.current++;
	if(display.current == 3)
	{
		display.current = 0;
	}
	spi_transmit_bg(display.digits[display.current]);
}

static inline void seg_led_init()
{
	DDR_LED_COM |= (1<<LED_COM1)|(1<<LED_COM2)|(1<<LED_COM3);
	display.com_bits[0] = (1<<LED_COM1);
	display.com_bits[1] = (1<<LED_COM2);
	display.com_bits[2] = (1<<LED_COM3);
}

#endif // SEG_LED_H_INCLUDED
