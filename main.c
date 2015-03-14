#include <avr/io.h>
#include <util/delay.h>

#include "hal.h"
#include "seg_led.h"
#include "spi.h"
#include "uart.h"

inline static void init(void)
{
    spi_init_master();
    uart_init();
}

int main(void)
{

    init();

    while(1)
    {
        //
    }

    return 0;
}
