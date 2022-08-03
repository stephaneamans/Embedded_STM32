/* Includes ------------------------------------------------------------------*/
#include "bsp_configuration.h"
#include "test.h"
#include <string.h>

#include "gpio.h"

int main(void)
{
    soc_core_configuration();
    soc_peripherals_configuration();

//    output_clock(SYSCLOCK);

//    print_test_header();

    spi_test();

    while(1)
    {
    };
}
