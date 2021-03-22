/*
 * lld_clock.h
 *
 * Created on: Apr 20, 2019
 * Author: Stephane Amans
 */
#ifndef LLD_CLOCK_H_
#define LLD_CLOCK_H_

/* Include files:        */
#include <stdint.h>
#include <string.h>

#include "configuration_module_activation.h"
#include "configuration_timer.h"
#include "globals.h"
#include "regbase_flash.h"
#include "regbase_reset_clock.h"


/* Define units          */
#define  HZ  *1
#define KHZ  *1000
#define MHZ  *1000000

#define  SEC  *1000000000
#define MSEC  *1000000
#define USEC  *1000



/* Source selection enumeration definition:        */
typedef enum
{
    HSI_OSC     = 1,  /* High speed internal oscillator mask.    */
    SYSCLOCK    = 2,  /* System clock ID for output.             */
    HSE_OSC     = 3,  /* High speed external oscillator mask.    */
    HSE_BYP     = 4,  /* High speed external drive source mask.  */
    PLL_HSI     = 5,  /* PLL clocked with HSI oscillator.        */
    PLL_HSE     = 6,  /* PLL clocked with HSE oscillator.        */
    PLL_HSE_BYP = 7   /* PLL clocked with HSE Bypass oscillator. */
}clock_sources;


/* Clock initialization structure definition :        */
typedef struct
{
    uint32_t sys_clk;
    uint32_t AHB_clk;
    uint32_t APB1_clk;
    uint32_t APB2_clk;
    int source;
}t_clock_cfg;


/* Functions prototypes:        */

/** Configure all SOC clocks.
 *
 * \param cfg: Confuguration structure.
 *
 * \return: Error code or OK.
 *
 */
t_error_handling clock_init(t_clock_cfg *cfg);


/** Select the clock to output on the dedicated pin.
 *
 * \param source: Source clock to output.
 *
 * \return: Error code or OK.
 *
 */
t_error_handling clock_select_clock_to_output(clock_sources source);


/** Get AHB clock frequency.
 *
 * \param: void
 *
 * \return: AHB clock frequency.
 *
 */
uint32_t get_ahb_clock(void);


/** Get APB1 clock frequency.
 *
 * \param: void
 *
 * \return: APB1 clock frequency.
 *
 */
uint32_t get_apb1_clock(void);


/** Get APB2 clock frequency.
 *
 * \param: void
 *
 * \return: APB2 clock frequency.
 *
 */
uint32_t get_apb2_clock(void);


/** Get system clock frequency.
 *
 * \param: void
 *
 * \return: system clock frequency.
 *
 */
uint32_t get_sys_clock(void);

#endif /* LLD_CLOCK_H_ */
