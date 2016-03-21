#ifndef ADC_H_INCLUDED
#define ADC_H_INCLUDED

#include "hal.h"

#ifndef USE_ADC
#	error "ADC not configured in hal.h"

#else

#include <avr/io.h>

extern volatile uint16_t adc;

inline static void adc_init(void)
{
	ADMUX |= (ADC_REF<<REFS0)|(ADC_LAR<<ADLAR)|(ADC_CH&0b1111);

	ADCSRA |= (1<<ADEN)
#ifdef ADC_IE
			  |(1<<ADIE)
#endif
			  |(ADC_PRESCALLER<<ADPS0);
}

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
#if defined(ADC_LAR) && ADC_LAR == 1
	return ADCH;
#else
	return ADC;
#endif
}

#endif

#endif // ADC_H_INCLUDED
