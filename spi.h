#ifndef SPI_H_INCLUDED
#define SPI_H_INCLUDED

#include "hal.h"

inline static void spi_init_master(void)
{
    DDR_SPI |= (1<<SPI_MOSI)|(1<<SPI_SCK)|(1<<SPI_SS);
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);//|(1<<SPI2X); // at fosc/2
}

inline static void spi_init_slave(void)
{
    DDR_SPI |= (1<<SPI_MISO);
    SPCR = (1<<SPE);
}

void spi_transmit(char data);

char spi_receive(void);

char spi_rt(char data);

#endif // SPI_H_INCLUDED
