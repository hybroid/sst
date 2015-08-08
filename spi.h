#ifndef SPI_H_INCLUDED
#define SPI_H_INCLUDED

#include "hal.h"

#if !defined(USE_SPI)
#	error "SPI not configured in hal.h"

#else

#include <avr/io.h>
#include <avr/interrupt.h>

#if !defined(SPI_IE)
inline static void spi_init_master(void)
{
    DDR_SPI |= (1<<SPI_MOSI)|(1<<SPI_SCK)|(1<<SPI_SS);
    SPCR = (1<<SPE)|(1<<MSTR)|(0<<SPR1)|(0<<SPR0)|(1<<SPI2X); // at fosc/2
}

#else
/* Init SPI with interrupt */
inline static void spi_init_master(void)
{
    DDR_SPI |= (1<<SPI_MOSI)|(1<<SPI_SCK)|(1<<SPI_SS);
    SPCR = (1<<SPIE)|(1<<SPE)|(1<<MSTR)|(1<<SPR1)|(0<<SPR0)|(0<<SPI2X); // @ fosc/4
}

/* interrupt handler */
ISR(SPI_STC_vect)
{
	//
}
#endif

inline static void spi_init_slave(void)
{
    DDR_SPI |= (1<<SPI_MISO);
    SPCR = (1<<SPE);
}

inline static void spi_transmit_bg(char data)
{
	PORT_SPI &= ~(1<<SPI_SS);
	SPDR = data;
}

void spi_transmit(char data);

char spi_receive(void);

char spi_rt(char data);

#endif

#endif // SPI_H_INCLUDED
