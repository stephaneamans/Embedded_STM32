/* Includes ------------------------------------------------------------------*/
#include "bsp_configuration.h"
#include "test.h"


int main(void)
{
    test_issue test_result;
    soc_core_configuration();
    soc_peripherals_configuration();

    test_result = test_queue();

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
