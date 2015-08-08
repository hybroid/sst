#ifndef ADC_H_INCLUDED
#define ADC_H_INCLUDED

#include "hal.h"

#ifndef USE_UART
#	error "ADC not configured in hal.h"

#else

#include <avr/io.h>
#include <stdio.h>

inline static void adc_init(void)
{
	ADMUX |= (ADC_REF<<REFS0)|(ADC_LAR<<ADLAR)|(ADC_CH&0b0000);

	ADCSRA |= (1<<ADEN)
#ifdef ADC_IE
				|(1<<ADIE)
#endif
				|(ADC_PRESCALLER<<ADPS0);
}

#ifdef ADC_IE
#include <avr/interrupt.h>

ISR(ADC_vect)
{
	//
}
#endif

inline static void adc_channel(uint8_t number)
{
    /* number: 0-7 for ADC0-ADC7 channels,
               14 for 1.1V (Vbg),
               15 for GND
    */
    ADMUX |= number & 0b1111;
}

inline static void adc_start(void)
{
    ADCSRA |= (1<<ADSC);
}

inline static uint16_t adc_result(void)
{
	return ADC;
}

#endif

#endif // ADC_H_INCLUDED
