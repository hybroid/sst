#ifndef UART_H_INCLUDED
#define UART_H_INCLUDED

#include "hal.h"

inline static void uart_init(void)
{
    /* set baud rate */
    UBRR0H = (unsigned char)((UART_UBRR)>>8);
    UBRR0L = (unsigned char)(UART_UBRR);
    /* enable Rx and Tx */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    /* frame format: 8 bits data, 2 stop bits */
    UCSR0C = (1<<USBS0)|(1<<UCSZ00);
}

inline static void uart_init_rx(void)
{
    /* set baud rate */
    UBRR0H = (unsigned char)((UART_UBRR)>>8);
    UBRR0L = (unsigned char)(UART_UBRR);
    /* enable Rx and Tx */
    UCSR0B = (1<<RXEN0);
    /* frame format: 8 bits data, 2 stop bits */
    UCSR0C = (1<<USBS0)|(1<<UCSZ00);
}

inline static void uart_init_tx(void)
{
    /* set baud rate */
    UBRR0H = (unsigned char)((UART_UBRR)>>8);
    UBRR0L = (unsigned char)(UART_UBRR);
    /* enable Rx and Tx */
    UCSR0B = (1<<TXEN0);
    /* frame format: 8 bits data, 2 stop bits */
    UCSR0C = (1<<USBS0)|(1<<UCSZ00);
}

void uart_transmit(char data);

char uart_receive(void);

#endif // UART_H_INCLUDED
