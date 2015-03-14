#include <avr/io.h>

#include "spi.h"

void spi_transmit(char data)
{
    /* set active !SS (active low) */
    PORT_SPI &= ~(1<<SPI_SS);
    /* send data */
    SPDR = data;
    while(!(SPSR & (1<<SPIF)));
    /* clear !SS */
    PORT_SPI |= (1<<SPI_SS);
}

char spi_receive(void)
{
    while(!(SPSR & (1<<SPIF)));
    return SPDR;
}

char spi_rt(char data)
{
    /* set active !SS (active low) */
    PORT_SPI &= ~(1<<SPI_SS);
    /* send and receive data */
    SPDR = data;
    while(!(SPSR & (1<<SPIF)));
    /* clear !SS */
    PORT_SPI |= (1<<SPI_SS);

    return SPDR;
}
