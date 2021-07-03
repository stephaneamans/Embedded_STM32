#include <stdint.h>

#ifndef USART_REGBASE_H_
#define USART_REGBASE_H_

#define PERIPH_BASE            0x40000000U                        /* Peripheral base address in the alias region.                        */
#define APB1PERIPH_BASE        (PERIPH_BASE)                      /* APB1 peripheral base address in the alias region.                   */
#define APB2PERIPH_BASE        (PERIPH_BASE + 0x00010000U)        /* APB2 peripheral base address in the alias region.                   */

#define USART1_BASE            (APB2PERIPH_BASE + 0x00003800U)    /* USART1 Peripheral base address in the alias region.                 */
#define USART2_BASE            (APB1PERIPH_BASE + 0x00004400U)    /* USART2 Peripheral base address in the alias region.                 */

#define USART1                 ((USART_TypeDef *)USART1_BASE)     /* USART1_Typedef structure position in the flash base address.        */
#define USART2                 ((USART_TypeDef *)USART2_BASE)     /* USART2_Typedef structure position in the flash base address.        */


/* USART registers structure        */
typedef struct
{
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
}USART_TypeDef;

#endif /* USART_REGBASE_H_ */
