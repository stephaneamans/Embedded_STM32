#include <stdint.h>

#define PERIPH_BASE        0x40000000U                           /* Peripheral base address in the alias region.                */
#define AHBPERIPH_BASE    (PERIPH_BASE + 0x00020000U)            /* AHB peripheral base address in the alias region.            */

#define DMA1_BASE         (AHBPERIPH_BASE + 0x00000000U)         /* DMA1 Peripheral base address in the alias region.           */
#define DMA1_Ch1_BASE     (AHBPERIPH_BASE + 0x00000008U)         /* DMA1 Channel 1 Peripheral base address in the alias region. */
#define DMA1_Ch2_BASE     (AHBPERIPH_BASE + 0x0000001CU)         /* DMA1 Channel 2 Peripheral base address in the alias region. */
#define DMA1_Ch3_BASE     (AHBPERIPH_BASE + 0x00000030U)         /* DMA1 Channel 3 Peripheral base address in the alias region. */
#define DMA1_Ch4_BASE     (AHBPERIPH_BASE + 0x00000044U)         /* DMA1 Channel 4 Peripheral base address in the alias region. */
#define DMA1_Ch5_BASE     (AHBPERIPH_BASE + 0x00000058U)         /* DMA1 Channel 5 Peripheral base address in the alias region. */
#define DMA1_Ch6_BASE     (AHBPERIPH_BASE + 0x0000006CU)         /* DMA1 Channel 6 Peripheral base address in the alias region. */
#define DMA1_Ch7_BASE     (AHBPERIPH_BASE + 0x00000080U)         /* DMA1 Channel 7 Peripheral base address in the alias region. */

#define DMA1              ((DMA_TypeDef *)DMA1_BASE)             /* DMA_Typedef structure position in the base address.         */
#define DMA1_Ch1          ((DMA_Channel_TypeDef *)DMA1_Ch1_BASE) /* DMA_Channel_Typedef structure position in the base address. */
#define DMA1_Ch2          ((DMA_Channel_TypeDef *)DMA1_Ch2_BASE) /* DMA_Channel_Typedef structure position in the base address. */
#define DMA1_Ch3          ((DMA_Channel_TypeDef *)DMA1_Ch3_BASE) /* DMA_Channel_Typedef structure position in the base address. */
#define DMA1_Ch4          ((DMA_Channel_TypeDef *)DMA1_Ch4_BASE) /* DMA_Channel_Typedef structure position in the base address. */
#define DMA1_Ch5          ((DMA_Channel_TypeDef *)DMA1_Ch5_BASE) /* DMA_Channel_Typedef structure position in the base address. */
#define DMA1_Ch6          ((DMA_Channel_TypeDef *)DMA1_Ch6_BASE) /* DMA_Channel_Typedef structure position in the base address. */
#define DMA1_Ch7          ((DMA_Channel_TypeDef *)DMA1_Ch7_BASE) /* DMA_Channel_Typedef structure position in the base address. */


/* DMA registers structure        */
typedef struct
{
    volatile uint32_t ISR;
    volatile uint32_t IFCR;
} DMA_TypeDef;


/* DMA channel registers structure         */
typedef struct
{
    volatile uint32_t CCR;
    volatile uint32_t CNDTR;
    volatile uint32_t CPAR;
    volatile uint32_t CMAR;
}DMA_Channel_TypeDef;
