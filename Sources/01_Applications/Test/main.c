/* Includes ------------------------------------------------------------------*/
#include "bsp_configuration.h"
#include "test.h"
#include <string.h>

int main(void)
{
	test_issue test_result;
    soc_core_configuration();
    soc_peripherals_configuration();

    clock_select_clock_to_output(SYSCLOCK);

    test_result = print_test_header();

    if(test_result == PASS)
    {
        while(1){}
    }
    else if(test_result == FAIL)
    {
        while(1){}
    }
    else
    {
        while(1){}
    }
}
