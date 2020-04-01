#include <stdint.h>

#define PERIPH_BASE            0x40000000U                            /* Peripheral base address in the alias region.                       */
#define APB2PERIPH_BASE        (PERIPH_BASE + 0x00010000U)            /* APB2 peripheral base address in the alias region.                  */

#define GPIOA_BASE             (APB2PERIPH_BASE + 0x00000800U)        /* GPIOA Peripheral base address in the alias region.                 */
#define GPIOB_BASE             (APB2PERIPH_BASE + 0x00000C00U)        /* GPIOB Peripheral base address in the alias region.                 */
#define GPIOC_BASE             (APB2PERIPH_BASE + 0x00001000U)        /* GPIOC Peripheral base address in the alias region.                 */
#define GPIOD_BASE             (APB2PERIPH_BASE + 0x00001400U)        /* GPIOD Peripheral base address in the alias region.                 */
#define AFIO_BASE              (APB2PERIPH_BASE + 0x00000000U)        /* AFIO Peripheral base address in the alias region.                  */

#define GPIOA                  ((GPIO_TypeDef *)GPIOA_BASE)           /* GPIOA_Typedef structure position in the flash base address.        */
#define GPIOB                  ((GPIO_TypeDef *)GPIOB_BASE)           /* GPIOB_Typedef structure position in the flash base address.        */
#define GPIOC                  ((GPIO_TypeDef *)GPIOC_BASE)           /* GPIOC_Typedef structure position in the flash base address.        */
#define GPIOD                  ((GPIO_TypeDef *)GPIOD_BASE)           /* GPIOD_Typedef structure position in the flash base address.        */
#define AFIO                   ((AFIO_TypeDef *)AFIO_BASE)            /* AFIO_Typedef structure position in the flash base address.         */


/* GPIO registers structure        */
typedef struct
{
    volatile uint32_t CRL;
    volatile uint32_t CRH;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t BRR;
    volatile uint32_t LCKR;
}GPIO_TypeDef;

/* AFIO registers structure         */
typedef struct
{
    volatile uint32_t EVCR;
    volatile uint32_t MAPR;
    volatile uint32_t EXTICR[4];
    volatile uint32_t RESERVED0;
    volatile uint32_t MAPR2;
}AFIO_TypeDef;
