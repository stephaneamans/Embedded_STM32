#include <stdint.h>

#ifndef EXTI_REGBASE_H_
#define EXTI_REGBASE_H_
    
#define PERIPH_BASE        0x40000000U                            /* Peripheral base address in the alias region.                     */
#define APB2PERIPH_BASE    (PERIPH_BASE + 0x00010000U)            /* APB2 Peripheral base address in the alias region.                */
#define EXTI_BASE          (APB2PERIPH_BASE + 0x00000400U)        /* EXTI Peripheral base address in the alias region.                */
#define EXTI               ((EXTI_TypeDef *)EXTI_BASE)            /* EXTI_Typedef structure position in the EXTI base address.        */


/* EXTI registers structure        */
typedef struct
{
    volatile uint32_t IMR;
    volatile uint32_t EMR;
    volatile uint32_t RTSR;
    volatile uint32_t FTSR;
    volatile uint32_t SWIER;
    volatile uint32_t PR;
} EXTI_TypeDef;

#endif /* EXTI_REGBASE_H_ */
