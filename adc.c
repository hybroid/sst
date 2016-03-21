#include "hal.h"

#ifdef USE_ADC

#include <avr/io.h>

#include "adc.h"

volatile uint16_t adc;

#ifdef ADC_IE
#include <avr/interrupt.h>

ISR(ADC_vect)
{
#if defined(ADC_LAR) && ADC_LAR == 1
	adc = ADCH;
#else
	adc = ADC;
#endif
}

#endif

#endif
