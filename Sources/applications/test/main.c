/* Includes ------------------------------------------------------------------*/
#include "bsp_configuration.h"
#include "test.h"
#include <string.h>

int main(void)
{
    soc_core_configuration();
    soc_peripherals_configuration();

//    output_clock(SYSCLOCK);

    print_test_header();
    while(1){}
}
