#ifndef SEG_LED_H_INCLUDED
#define SEG_LED_H_INCLUDED

#include <avr/io.h>

#include "hal.h"

typedef struct divmod10_t
{
    uint16_t quot;
    uint8_t rem;
} divmod10_t;

typedef struct seg_led_t
{
	uint8_t symbols[3];			// bit codes of SEGs
	uint8_t current;			// current COM
	uint8_t com_bits[3];		// bit codes of COMs
} seg_led_t;

extern const uint8_t led_symbols[];

extern volatile seg_led_t display;

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

void bin2bcd(uint16_t value, unsigned char *buffer);

static inline void seg_led_set(uint8_t symbol)
{
	// clear all segments
	PORTD &= ~( 0b11111100 ); // PD7..PD2
	PORTB &= ~( 0b00000101 ); // PB2, PB0

	// set segments
	PORTD |= symbol & 0b11111100; // with mask for PD7..PD2
	PORTB |= ((symbol & 0b00000010)<<1) | ((symbol & 0b00000001)); // for PB2, PB0
}

static inline void seg_led_tick(void)
{
	if( (++display.current) >= 3)
	{
		display.current = 0;
	}

	seg_led_set( display.symbols[display.current] ); // clear all segments and set current symbol

	PORT_LED_COM &= ~( (1<<LED_COM1)|(1<<LED_COM2)|(1<<LED_COM3) ) ; // clear COM
	PORT_LED_COM |= ( display.com_bits[display.current] ); // set COM
}

static inline void seg_led_init(void)
{
	// for COMs
	DDR_LED_COM |= (1<<LED_COM1)|(1<<LED_COM2)|(1<<LED_COM3);
	display.com_bits[0] = (1<<LED_COM1);
	display.com_bits[1] = (1<<LED_COM2);
	display.com_bits[2] = (1<<LED_COM3);

	// for SEGs
	DDRD |= (1<<DDD7)|(1<<DDD6)|(1<<DDD5)|(1<<DDD4)|(1<<DDD3)|(1<<DDD2);
	DDRB |= (1<<DDB2)|(1<<DDB0);
}

#endif // SEG_LED_H_INCLUDED
