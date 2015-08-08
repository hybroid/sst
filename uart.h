#ifndef UART_H_INCLUDED
#define UART_H_INCLUDED

#include "hal.h"

#if !defined(USE_UART)
#	error "UART not configured in hal.h"

#else

#include <avr/io.h>
#include <util/setbaud.h>

inline static void uart_init(void)
{
	/* set baud rate */
	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;
#if USE_2X
	UCSRA |= (1<<U2X);
#endif
	/* enable Rx and Tx */
	UCSRB |= ((1<<RXEN) | (1<<TXEN));
    /* frame format: 8 bits data, 1 stop bit */
	UCSRC |= ((1<<UCSZ1) | (1<<UCSZ0));
}

inline static void uart_init_rx(void)
{
	/* set baud rate */
	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;
    /* enable Rx only */
    UCSRB = (1<<RXEN);
    /* frame format: 8 bits data, 1 stop bit */
	UCSRC |= ((1<<UCSZ1) | (1<<UCSZ0));
}

inline static void uart_init_tx(void)
{
	/* set baud rate */
	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;
    /* enable Tx only */
    UCSRB = (1<<TXEN);
    /* frame format: 8 bits data, 1 stop bit */
	UCSRC |= ((1<<UCSZ1) | (1<<UCSZ0));
}

void uart_transmit(char data);

char uart_receive(void);

#endif

#endif // UART_H_INCLUDED
