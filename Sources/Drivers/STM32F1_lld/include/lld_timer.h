/*
 *        lld_timer.h
 *
 *    Created on: Mar 17, 2020
 *    Author: Stéphane Amans
 */
#ifndef TIMER_H_
#define TIMER_H_


/* Include files:        */
#include <stdint.h>

#include "configuration.h"
#include "lld_clock.h"
#include "lld_nvic.h"
#include "regbase_tim.h"


/* MISSING: ENABLE CAPTURE INTERRUPT  */


typedef enum
{
    timer          = 0,
    input_capture  = 1,
    output_compare = 2,
    pwm_input      = 3,
    pwm_output     = 4
}timer_mode;


typedef enum
{
    frozen       = 0x00,
    active       = 0x10,
    inactive     = 0x20,
    toggle       = 0x30,
    fce_inactive = 0x40,
    fce_active   = 0x50,
    pwm1         = 0x60,
    pwm2         = 0x70
}oc_mode;

typedef enum
{
    channel_1 = 0,
    channel_2 = 1,
    channel_3 = 2,
    channel_4 = 3
}channel_type;


typedef enum
{
    ccx_channel_output           = 0,
    ccx_channel_input_ICx_on_TI2 = 1,
    ccx_channel_input_ICx_on_TI1 = 2,
    ccx_channel_input_ICx_on_TRC = 3
}ic_oc_pin_mux;


typedef enum
{
    out_active_high_in_rising = 0,
    out_active_low_in_falling = 1
}ic_oc_polarity;


typedef enum
{
    none = 0,
    irq  = 2,
    dma  = 200
}irq_dma_active;

typedef enum
{
    one_pulse = 0,
    continuous = 1
}oc_length;


typedef struct
{
    TIM_TypeDef *timer;
    uint32_t duration;
    oc_mode out_cmp_mode;
    timer_mode mode;
    channel_type channel;
    ic_oc_pin_mux tim_mux;
    ic_oc_polarity polarity;
    uint8_t frequency;
    uint8_t percent_pwm;
    oc_length length;
    uint8_t prescaler;
    struct
    {
        irq_dma_active active;
        uint8_t rising;
        uint8_t priority;
        void(*callback)(uint32_t);
    }irq_dma;
}t_timer_cfg;





/* Functions prototypes:                       */

/** Configure timer (port, pin, in/out, mode, interruption):
 *
 * \param timer: Pointer to the timer register base.
 * \param cfg: Configuration structure.
 *
 * \return : Error code or 0 if OK.
 *
 */
uint8_t timer_init(t_timer_cfg *cfg);


/** Disable a timer port clock.
 *
 * \param timer : address of the TIM entity to unclock.
 *
 * \return : Error code or OK.
 *
 */
uint8_t timer_disable_clock(TIM_TypeDef *timer);


/** Set timer prescaler.
 *
 * \param prescaler : Prescaler value for the timer.
 *
 * \return : Error code or OK.
 *
 */
uint8_t timer_disable_clock(TIM_TypeDef *timer);


/** Start timer.
 *
 * \param timer : address of the timer.
 *
 * \return : Error code or OK.
 *
 */
uint8_t tim_start(TIM_TypeDef *timer);


/** Stop timer.
 *
 * \param timer : address of the timer.
 *
 * \return : Error code or OK.
 *
 */
uint8_t tim_stop(TIM_TypeDef *timer);


/** Wait timer end by polling.
 *
 * \param timer : address of the timer.
 * \param channel: number of the channel to start.
 *
 * \return : Error code or OK.
 *
 */
uint8_t tim_wait(TIM_TypeDef *timer, channel_type channel);



/* Pointer callback function table prototype	*/
void (*tim1_callback[4])(uint32_t pin_numb);



#endif /* TIMER_H_ */
