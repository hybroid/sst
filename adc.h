#ifndef ADC_H_INCLUDED
#define ADC_H_INCLUDED

#include <avr/io.h>

inline static void adc_init_ie(void)
{
    /* internal 1.1V reference */
    ADMUX |= (1<<REFS1)|(1<<REFS0);
    /* ADC enable, inteerrupt enable,
       prescaler ADPS:
          000 : 2
          001 : 2
          010 : 4
          011 : 8
          100 : 16
          101 : 32
          110 : 64
          111 : 128
    */
    ADCSRA |= (1<<ADEN)|(1<<ADIE)|(0<<ADPS2)|(1<<ADPS1)|(0<<ADPS0);
}

inline static void adc_channel(unsigned char number)
{
    /* number: 0-7 for ADC0-ADC7 channels,
               14 for 1.1V (Vbg),
               15 for GND
    */
    number &= 0b1111;
    ADMUX |= number;
}

inline static void adc_start(void)
{
    ADCSRA |= (1<<ADSC);
}

inline static adc_result(void)
{

}

#endif // ADC_H_INCLUDED
