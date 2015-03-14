#include <avr/io.h>

#include "uart.h"

void uart_transmit(char data)
{
    while( !(UCSR0A & (1<<UDRE0)) );
    UDR0 = data;
}

char uart_receive(void)
{
    while( !(UCSR0A & (1<<RXC0)) );
    return UDR0;
}
