#ifndef HAL_H_INCLUDED
#define HAL_H_INCLUDED

#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 8000000
#endif

#define T_FLAG 0b00000001
#define R_FLAG 0b00000010
#define S_FLAG 0b00000100

/* SPI not used in this hardware */
#define PORT_SPI PORTB
#define DDR_SPI DDRB
#define SPI_MOSI 3
#define SPI_MISO 4
#define SPI_SCK 5
#define SPI_SS 0

#define BAUD 38400

// UART registers
#if defined(__AVR_ATmega88__) || defined(__AVR_ATmega88A__)
#define DEVCODE 0x73
#define UDR			UDR0
#define UCSRA		UCSR0A
#	define RXC		RXC0
#	define TXC		TXC0
#	define UDRE		UDRE0
#	define FE		FE0
#	define DOR		DOR0
#	define UPE		UPE0
#	define U2X		U2X0
#	define MPCM		MPCM0
#define UCSRB		UCSR0B
#	define RXCIE	RXCIE0
#	define TXCIE	TXCIE0
#	define UDRIE	UDRIE0
#	define RXEN		RXEN0
#	define TXEN		TXEN0
#	define UCSZ2	UCSZ02
#	define RXB8		RXB80
#	define TXB8		TXB80
#define UCSRC		UCSR0C
#	define UMSEL1	UMSEL01
#	define UMSEL0	UMSEL00
#	define UPM1		UPM01
#	define UPM0		UPM00
#	define USBS		USBS0
#	define UCSZ1	UCSZ01
#	define UCSZ0	UCSZ00
#	define UCPOL	UCPOL0
#define UBRR		UBRR0
#	define UBRRH	UBRR0H
#	define UBRRL	UBRR0L

#else
#	error "Bootloader code does not support this MCU"
#endif

#define PORT_ENCODER PORTB
#define DDR_ENCODER DDRB
#define PIN_ENCODER PINB
#define ENCODER_A 6
#define ENCODER_B 7
//#define ENCODER_INTERRUPT INT0 // now not used
#define ENCODER_STATE ( ( PIN_ENCODER & ((1<<ENCODER_A)|(1<<ENCODER_B)) ) >> ENCODER_A )
#define ENCODER_STATE_0 0b00 // A - bit 1, B - bit 0.
#define ENCODER_STATE_1 0b01
#define ENCODER_STATE_2 0b10
#define ENCODER_STATE_3 0b11


#define PORT_BUZZER PORTC
#define DDR_BUZZER DDRC
#define BUZZER 2

#define PORT_PWM PORTB
#define DDR_PWM DDRB
#define PWM_PIN 1
#define PWM_TIMER 1
#define PWM_CHANNEL A

/* now now buttons in hardware
#define PORT_BUTTON PORTD
#define DDR_BUTTON DDRD
#define BUTTON_SB1 6
#define BUTTON_SB2 5
*/

#define THERMO_CH 7

#define PORT_LED_COM PORTC
#define DDR_LED_COM DDRC
#define LED_DIGITS 3
#define LED_COM(n) LED_COM##n
#define LED_COM1 5
#define LED_COM2 4
#define LED_COM3 3

#endif // HAL_H_INCLUDED
