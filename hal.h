#ifndef HAL_H_INCLUDED
#define HAL_H_INCLUDED

#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 8000000
#endif

#define T_FLAG		0b00000001
#define R_FLAG		0b00000010
#define AD_FLAG		0b00000100
#define ENC_FLAG	0b00001000
#define DC_FLAG		0b00010000

/* Bootloader */
#define BOOT_ADDR	0x0e00

/* SPI not used in this hardware */
//#define USE_SPI		// uncomment this line for use SPI

#define PORT_SPI PORTB
#define DDR_SPI DDRB
#define SPI_MOSI 3
#define SPI_MISO 4
#define SPI_SCK 5
#define SPI_SS 0
//#define SPI_IE		// uncomment this for use interrupts from SPI


/* UART */
#define USE_UART
#define BAUD 38400

#if defined(__AVR_ATmega88__) || defined(__AVR_ATmega88A__)
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
#	error "MCU not support"
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

/* Buzzer defines */
#define PORT_BUZZER PORTC
#define DDR_BUZZER DDRC
#define BUZZER 2

/* PWM defines */
#define PORT_PWM PORTB
#define DDR_PWM DDRB
#define PWM_PIN 1
#define PWM_TIMER 1
#define PWM_CHANNEL A

/* ADC defines */
#define USE_ADC
#define ADC_CH		7
#define ADC_REF 	0b11	// 0 - AREF; 1 - AVcc; 3 - internal 1.1V (ATmega48/88/168)
#define ADC_PRESCALLER 6	// PRESCALLER = 2^(ADC_PRESCALLER), ADC_PRESCALLER=0..7, 0=1 - div factor 2, 7 - div factor 128
#define ADC_IE
#define ADC_LAR		1		// left adjust result, for 8-bit result

#endif // HAL_H_INCLUDED
