#include "hal.h"

#if defined(USE_UART)

#include <avr/io.h>

#include "uart.h"

void uart_transmit(char data)
{
    while( !(UCSRA & (1<<UDRE)) );
    UDR = data;
}

char uart_receive(void)
{
    while( !(UCSRA & (1<<RXC)) );
    return UDR;
}

#endif
