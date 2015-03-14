#ifndef HAL_H_INCLUDED
#define HAL_H_INCLUDED

#include <avr/io.h>

/*
#define PORT(name) PORT##name
#define DDR(name) DDR##name
*/

#define cbi(port, bit) { PORT##port &= ~(1<<bit); }
#define sbi(port, bit) { PORT##port |= (1<<bit); }
#define dir(port, bit, io) { DDR##port = ( io ? DDR##port | (1<<bit) : DDR##port & ~(1<<bit) ); }

#define PORT_SPI PORTB
#define DDR_SPI DDRB
#define SPI_MOSI 3
#define SPI_MISO 4
#define SPI_SCK 5
#define SPI_SS 0

#define UART_BAUD 9600
#define UART_UBRR F_CPU/16/UART_BAUD-1

#define PORT_ENCODER PORTD
#define DDR_ENCODER DDRD
#define ENCODER_A 4
#define ENCODER_B 2
#define ENCODER_INTERRUPT INT0

#define PORT_BUZZER PORTD
#define DDR_BUZZER DDRD
#define BUZZER 3

#define PORT_PWM PORTB
#define PWM_PIN 1
#define PWM_TIMER 1
#define PWM_CHANNEL A

#define PORT_BUTTON PORTD
#define DDR_BUTTON DDRD
#define BUTTON_SB1 6
#define BUTTON_SB2 5

#define THERMO_PIN 0

#define PORT_LED_COM PORTC
#define DDR_LED_COM DDRC
#define LED_COM1 3
#define LED_COM2 4
#define LED_COM3 5

#endif // HAL_H_INCLUDED
