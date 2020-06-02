#include <stdint.h>

#define PERIPH_BASE           0x40000000U							/* Peripheral base address in the alias region. 				*/
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x00020000U)           /* AHB peripheral base address in the alias region.                 */
#define RCC_BASE              (AHBPERIPH_BASE + 0x00001000U)        /* RCC Peripheral base address in the alias region.                 */
#define RCC                   ((RCC_TypeDef *)RCC_BASE)             /* RCC_Typedef structure position in the flash base address.        */


/* RCC registers structure        */
typedef struct
{
    volatile uint32_t CR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t APB1RSTR;
    volatile uint32_t AHBENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t APB1ENR;
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
} RCC_TypeDef;
